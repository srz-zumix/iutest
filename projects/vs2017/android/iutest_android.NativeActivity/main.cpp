/*
* Copyright (C) 2010 The Android Open Source Project
*
* Apache License Version 2.0 (「本ライセンス」) に基づいてライセンスされます。;
* 本ライセンスに準拠しない場合はこのファイルを使用できません。
* 本ライセンスのコピーは、以下の場所から入手できます。
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* 適用される法令または書面での同意によって命じられない限り、本ライセンスに基づいて頒布されるソフトウェアは、
* 明示黙示を問わず、いかなる保証も条件もなしに現状のまま
* 頒布されます。
* 本ライセンスでの権利と制限を規定した文言ついては、
* 本ライセンスを参照してください。
*
*/

#include "../../../../include/iutest.hpp"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", __VA_ARGS__))

/**
* 保存状態のデータです。
*/
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
* アプリの保存状態です。
*/
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

/**
* 現在の表示の EGL コンテキストを初期化します。
*/
static int engine_init_display(struct engine* engine) {
    // OpenGL ES と EGL の初期化

    /*
    * 目的の構成の属性をここで指定します。
    * 以下で、オンスクリーン ウィンドウと
    * 互換性のある、各色最低 8 ビットのコンポーネントの EGLConfig を選択します
    */
    const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };
    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* ここで、アプリケーションは目的の構成を選択します。このサンプルでは、
    * 抽出条件と一致する最初の EGLConfig を
    * 選択する単純な選択プロセスがあります */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID は、ANativeWindow_setBuffersGeometry() に
    * よって受け取られることが保証されている EGLConfig の属性です。
    * EGLConfig を選択したらすぐに、ANativeWindow バッファーを一致させるために
    * EGL_NATIVE_VISUAL_ID を使用して安全に再構成できます。*/
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
    context = eglCreateContext(display, config, NULL, NULL);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    // GL の状態を初期化します。
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    return 0;
}

/**
* ディスプレイ内の現在のフレームのみ。
*/
static void engine_draw_frame(struct engine* engine) {
    if (engine->display == NULL) {
        // ディスプレイがありません。
        return;
    }

    // 色で画面を塗りつぶします。
    glClearColor(((float)engine->state.x) / engine->width, engine->state.angle,
        ((float)engine->state.y) / engine->height, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    eglSwapBuffers(engine->display, engine->surface);
}

/**
* 現在ディスプレイに関連付けられている EGL コンテキストを削除します。
*/
static void engine_term_display(struct engine* engine) {
    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

/**
* 次の入力イベントを処理します。
*/
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
    struct engine* engine = (struct engine*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        engine->state.x = AMotionEvent_getX(event, 0);
        engine->state.y = AMotionEvent_getY(event, 0);
        return 1;
    }
    return 0;
}

/**
* 次のメイン コマンドを処理します。
*/
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
    case APP_CMD_SAVE_STATE:
        // 現在の状態を保存するようシステムによって要求されました。保存してください。
        engine->app->savedState = malloc(sizeof(struct saved_state));
        *((struct saved_state*)engine->app->savedState) = engine->state;
        engine->app->savedStateSize = sizeof(struct saved_state);
        break;
    case APP_CMD_INIT_WINDOW:
        // ウィンドウが表示されています。準備してください。
        if (engine->app->window != NULL) {
            engine_init_display(engine);
            engine_draw_frame(engine);
        }
        break;
    case APP_CMD_TERM_WINDOW:
        // ウィンドウが非表示または閉じています。クリーン アップしてください。
        engine_term_display(engine);
        break;
    case APP_CMD_GAINED_FOCUS:
        // アプリがフォーカスを取得すると、加速度計の監視を開始します。
        if (engine->accelerometerSensor != NULL) {
            ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                engine->accelerometerSensor);
            // 目標は 1 秒ごとに 60 のイベントを取得することです (米国)。
            ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                engine->accelerometerSensor, (1000L / 60) * 1000);
        }
        break;
    case APP_CMD_LOST_FOCUS:
        // アプリがフォーカスを失うと、加速度計の監視を停止します。
        // これにより、使用していないときのバッテリーを節約できます。
        if (engine->accelerometerSensor != NULL) {
            ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                engine->accelerometerSensor);
        }
        // また、アニメーションを停止します。
        engine->animating = 0;
        engine_draw_frame(engine);
        break;
    }
}

/**
* これは、android_native_app_glue を使用しているネイティブ アプリケーション
* のメイン エントリ ポイントです。それ自体のスレッドでイベント ループによって実行され、
* 入力イベントを受け取ったり他の操作を実行したりします。
*/
void android_main(struct android_app* state) {
    struct engine engine;

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;

    // 加速度計の監視の準備
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
        ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
        state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        // 以前の保存状態で開始します。復元してください。
        engine.state = *(struct saved_state*)state->savedState;
    }

    engine.animating = 1;

    // ループはスタッフによる開始を待っています。

    ::iutest::InitIrisUnitTest();
    IUTEST_RUN_ALL_TESTS();

    while (1) {
        // 保留中のすべてのイベントを読み取ります。
        int ident;
        int events;
        struct android_poll_source* source;

        // アニメーションしない場合、無期限にブロックしてイベントが発生するのを待ちます。
        // アニメーションする場合、すべてのイベントが読み取られるまでループしてから続行します
        // アニメーションの次のフレームを描画します。
        while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
            (void**)&source)) >= 0) {

            // このイベントを処理します。
            if (source != NULL) {
                source->process(state, source);
            }

            // センサーにデータがある場合、今すぐ処理します。
            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                        &event, 1) > 0) {
                        LOGI("accelerometer: x=%f y=%f z=%f",
                            event.acceleration.x, event.acceleration.y,
                            event.acceleration.z);
                    }
                }
            }

            // 終了するかどうか確認します。
            if (state->destroyRequested != 0) {
                engine_term_display(&engine);
                return;
            }
        }

        if (engine.animating) {
            // イベントが完了したら次のアニメーション フレームを描画します。
            engine.state.angle += .01f;
            if (engine.state.angle > 1) {
                engine.state.angle = 0;
            }

            // 描画は画面の更新レートに合わせて調整されているため、
            // ここで時間調整をする必要はありません。
            engine_draw_frame(&engine);
        }
    }
}
