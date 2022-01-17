# 変更履歴

--------------------------------------------------

## Changes for 1.17.99

* New
  * IUTEST_*_COMPLEX_EQ アサーションを追加

* Improved
  * IUTEST_*_ALMOST_EQ が ::std::complex に対応
  * 例外発生時にも SCOPED_TRACE のメッセージを出力するように変更
  * 空のテストスイート名・テスト名に static_assert を追加
  * GoogleTest の GTEST_REMOVE_LEGACY_TEST_CASEAPI_ に対応
  * Intel Compiler に対応

* Changes
  * TestCase の別名 TestSuite に対応（iutest はどちらもサポートし続けます）
  * IUTEST_ASSERT_EXIT を IUTEST_TERMINATE_ON_FAILURE に変更

* Bug fixes
  * その他いくつかの不具合を修正

--------------------------------------------------

## Changes for 1.17.1

* New
  * GTEST_SKIP 対応
  * IUTEST_*_NE_RANGE アサーションを追加
  * IUTEST_*_NE_COLLECTIONS アサーションを追加

* Improved
  * ::std::wstring_view / ::std::u16string_view / ::std::u32string_view 対応
  * Variadic Templates 非対応コンパイラーでの型パラメータの型表示を改善

* Changes
  * アサーションに operator << したときの出力を PrintToString したものと同じになるように変更
  * iuwandbox: Wandbox 向けにサイズ圧縮したヘッダーをデフォルトで使用するように変更
  * iuwandbox: 上記に伴いフルバージョンのヘッダーを使うオプション(--no-iutest-use-wandbox-min)を追加
  * deprecated: iuwandbox: --iutest-use-wandbox-min
  * Python2 のサポート終了

* Bug fixes
  * C++20 で削除された basic_ostream::operator << に対応
  * IUTEST_AP が同じ名前空間に複数定義できない問題を修正
  * Google Test 旧バージョンとの互換性を修正
  * その他いくつかの不具合を修正

--------------------------------------------------

## Changes for 1.17.0

* New
  * ::std::string_view 対応
  * ::std::filesystem 対応
  * FreeBSD 対応
  * ALMOST_EQ アサーション を追加
  * --iutest_locale_ctype オプションを追加

* Improved
  * setlocale(LC_CTYPE, IUTEST_FLAG(locale_ctype)) をテスト実行開始時に行うように修正
  * Visual Studio 2019 対応

* Changes
  * 大きな配列/コンテナ/オブジェクトの pinter を修正
  * iutest_main で setlocale していたものを廃止
  * junit xml 出力で出力するテストが 0 だった場合にファイル書き出ししないように修正
  * CSV パラメータ生成でファイルオープン失敗した場合の警告レベルを FATAL から WARNING に変更
  * CSV パラメータ生成で要素がなかった場合に WARNING 出力
  * deprecated: IUTEST_USE_OWN_LIST

* Bug fixes
  * いくつかの不具合を修正

--------------------------------------------------

## Changes for 1.16.7

* Improved
  * iuwandbox: コードサイズをさらに削減したヘッダーファイルに対応（--iutest-use-wandbox-min）

* Bug fixes
  * 古い google mock の互換性エラー修正
  * いくつかの不具合を修正

--------------------------------------------------

## Changes for 1.16.6

* Improved
  * Matcher に (NanSensitive)FloatNear/DoubleNear を追加
  * Matcher に template 版の浮動小数点数比較を追加・(NanSensitive)FloatingPointEq/FloatingPointNear
  * long double に対応

* Changes
  * iuwandbox: -D__WANDBOX__ コンパイラーオプションを必ずつけるように変更

* Bug fixes
  * iuwandbox: dryrun オプションが失敗を返す問題を修正
  * いくつかのコンパイラー警告を修正

--------------------------------------------------

## Changes for 1.16.5

* Improved
  * IUTEST_*_NULL, IUTEST_*_NOTNULL を可変長引数対応
  * IUTEST_*_HRESULT_SUCCEEDED, IUTEST_*_HRESULT_FAILED を可変長引数対応
  * compatibility: iuutil に ad_hoc_testresult の取得関数を追加

* Changes
  * ad_hoc_testresult の取得関数名を ad_hoc_test_result に変更

* Bug fixes
  * iuwandbox: iuwandbox で std-cxx の指定をするとオプションチェックで失敗する不具合を修正

--------------------------------------------------

## Changes for 1.16.4

* 変更
  * deprecated: IUTEST_IGNORE 関係を非推奨にしました

* 修正
  * バグ修正

--------------------------------------------------

## Changes for 1.16.3

* 追加
  * IUTEST_ASSERT,IUTEST_EXPECT の Variadic 対応
  * iuwandbox: --iutest-use-main を追加

* 変更
  * iuwandbox: Wandbox の std オプション変更への追従とヒント出力

* 修正
  * gtest 各バージョンの互換性の不備を修正
  * バグ修正

--------------------------------------------------

## Changes for 1.16.2

* 追加
  * 警告をエラーとするオプション(--iutest_warning_into_error)を追加

* 削除
  * NaCl サポートを終了

* 修正
  * バグ修正

--------------------------------------------------

## Changes for 1.16.1

* 追加
  * XML_OUTPUT_FILE 環境変数に対応

* 変更
  * IUTEST_BUILD を非推奨に変更し、IUTEST_MICROVER を追加
  * Wandbox の更新に合わせて iuwandbox を変更
  * iuwandbox: --list_compiler のようなオプション名中の _ を - に変更（_ 付きの旧オプションは将来のバージョンで廃止）

* 修正
  * iuwandbox: -f,--compiler-option-raw で複数のオプションを適切にパースするように修正
  * バグ修正

--------------------------------------------------

## Changes for 1.16.0

* 追加
  * iuwandbox で複数ソースファイルに対応
  * 例外アサーションで構造化例外（SEH）もキャッチできるように対応

* 変更
  * --iutest_filter のルールを Google Test 互換に修正

* 修正
  * バグ修正

--------------------------------------------------

## Changes for 1.15.2

* 追加
  * IUTEST_TYPED_TEST_P に対して friend できるように IUTEST_FRIEND_TYPED_TEST_P_DECLARATION/IUTEST_FRIEND_TYPED_TEST_P を追加
  * iuwandbox に --sprout/--msgpack オプションを追加

* 変更
  * iuwandbox の --list_compiler オプションでバージョンを出力しないように変更。--verbose を付けると以前と同じバージョン付きの出力をする
  * deprecated: IUTEST_HAS_STRSTREAM は将来的に削除されます
  * deprecated: IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE は将来的に削除されます

* 修正
  * iuwandbox で --expand_include オプションを付けなかった場合の include されたファイルの対応を修正
  * iuwandbox の --boost オプションが Python3 で使えない問題を修正
  * iuwandbox で未定義オプションを指定した場合にエラーにならない問題を修正
  * IUTEST(A, B_C) と IUTEST(A_B, C) が名前の衝突でコンパイルエラーになる問題を修正
  * 色付きコンソールの自動判定を修正
  * バグ修正

--------------------------------------------------

## Changes for 1.15.1

* 追加
  * stderr に xml の内容を出力するリスナーを追加
  * iuwandbox に xml 出力オプション(--xml, --junit)を追加

* 変更
  * --help|spec|feature|version を同時に使用可能に変更 (e.g. --spec --feature)

* 修正
  * CSV パラメータのパス解決処理を修正
  * fused-src 生成ツールを修正
  * バグ修正

--------------------------------------------------

## Changes for 1.15.0

* 追加
  * --iutest_output オプションで repeat 回数のフォーマットに対応 e.g. --iutest_output=xml:test_%d.xml
  * CSV ファイルから値のパラメータ作成に対応
  * 値のパラメータ化テストのテスト名指定方法の Google Test 互換対応

* 変更
  * IUTEST_ALIAS_TESTNAME_F,IUTEST_JAPANESE_NAME_F の引数の順番を変更
  * 値のパラメータ化テストのテスト名指定方法を変更
  * IUTEST_TYPED_TEST_APPEND_TYPENAME を IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME に変更

* 修正
  * バグ修正

--------------------------------------------------

## Changes for 1.14.0

* 変更
  * 大幅なリファクタリング

* 修正
  * ::iutest::Range を Enum に対応
  * tools の python 3.x 系対応

--------------------------------------------------

## Changes for 1.13.0

* 追加
  * --iutest_flagfile コマンドラインオプションに対応
  * MFC コンテナ対応
  * 値のパラメータ化テストのテスト名指定に対応
  * 型付けテストのテスト名に型名をつけるオプションマクロ (IUTEST_TYPED_TEST_APPEND_TYPENAME) を追加
  * 非ヨーダ記法を提供するヘッダー（iutest_util_no_yoda.hpp）を追加
  * Visual Studio 2015 対応

* 修正
  * tr1/iutest_vc_unittest.hpp を修正
  * バグ修正

--------------------------------------------------

## Changes for 1.12.0

* 追加
  * Matcher に MatchesRegex,ContainsRegex を追加
  * Matcher に ElementsAreArrayForward を追加
  * IUTEST_*_MATCHES_REGEXEQ,NE、IUTEST_*_CONTAINS_REGEXEQ,NE 追加
  * --iutest_filter=@filter.txt のようにファイルからフィルター指定できるように対応
  * quick_exit 対応
  * Visual Studio 2015 RC 対応
  * twilio 対応
  * Nuget パッケージ公開

* 変更
  * IUTEST_PACKAGE v2 (多重定義制限の撤廃)
  * ElementsAreArray で要素数の一致チェックを行うように変更（以前までの ElementsAreArray は ElementsAreArrayForward に変更）
  * IUTEST_REPORT_SKIPPED を IUTEST_HAS_REPORT_SKIPPED に変更

* 修正
  * IUTEST_MAKE_PEEP で関数ポインターの typedef をしなくてもいいように修正
  * バグ修正

--------------------------------------------------

## Changes for 1.11.1

* 修正
  * IUTEST_REGISTER_TYPED_TEST_CASE_P でテスト名の後ろの空白が名前に含まれてしまう不具合を修正
  * バグ修正

--------------------------------------------------

## Changes for 1.11.0

* 追加
  * fused-src 対応
  * Wandbox 対応
  * Matcher に Eq,Ne,Le,Lt,Ge,Gt,IsNull,NotNull,TypeEq を追加
  * Matcher に StrEq,StrNe,StrCaseEq,StrCaseNe,HasSubstr を追加
  * Matcher に FloatEq,DoubleEq,NanSensitiveFloatEq,NanSensitiveDoubleEq を追加
  * Matcher に Not,ResultOf,Pointee を追加
  * コンテナMatcher に Each,ContainerEq,Pointwise,At,IsEmpty,ElementsAre,ElementsAreArray を追加
  * メンバーMatcher に Key,Pair,Field,Property を追加
  * ワイルドカードMatcher A,_ を追加

* 変更
  * コンテナMatcher の Contains から HasSubstr 機能を削除

* 修正
  * IUTEST_*_FLOAT_EQ,DOUBLE_EQ で NAN の比較が真を返す不具合を修正
  * コンテナMatcher の条件に Matcher を使えるように修正
  * Visual Studio 2015 Preview 対応
  * バグ修正

--------------------------------------------------

## Changes for 1.10.0

* 追加
  * --verbose コマンドラインオプションを追加
  * --iutest_default_package_name コマンドラインオプションを追加
  * operatoer == のないオブジェクトの IUTEST_*_EQ 対応
  * operatoer != のないオブジェクトの IUTEST_*_NE 対応
  * junit xml 出力に対応（--iutest_output=junit）
  * IUTEST_FLAG(ostream_formatter) を追加
  * tuple 要素を取得する GetParam tempalate 関数を追加
  * ARM対応

* 修正
  * --iutest_break_on_failure でスキップや警告でも停止していた不具合を修正
  * Visual Studio 14 CTP 3 対応
  * バグ修正

--------------------------------------------------

## Changes for 1.9.1

* 変更
  * TestFixutre を定義しなくても IUTEST_P が使えるように対応

* 修正
  * IUTEST_P,IUTEST_TYPED_TEST_P で DISABLED_ 指定が機能しない問題を修正
  * Visual Studio 14 CTP 対応

--------------------------------------------------

## Changes for 1.9.0

* 追加
  * IUTEST_*_THAT 追加
  * 式アサーション追加（IUTEST_ASSERT, IUTEST_EXPECT, IUTEST_INFORM, IUTEST_ASSUME）
  * 式アサーション追加（IUTEST_*_NOT）
  * IUTEST_USE_MAIN 追加(main 関数定義 config)

* 変更
  * IUTEST_ASSERT を IUTEST_ASSERT_EXIT に変更

--------------------------------------------------

## Changes for 1.8.1

* 修正
  * SetUp/SetUpTestCase での SKIP/ASSUME に対応
  * MAC OS 判定、ビルドエラー修正(thanks to mogemimi for the pull request)
  * --iutest_filter で : 区切りの複数条件指定が正しく動作しない不具合を修正
  * --iutest_list_tests_with_where で値のパラメータも出力するように修正
  * バグ修正

--------------------------------------------------

## Changes for 1.8.0

* 追加
  * IUTEST_*_EQ_RANGE を追加
  * IUTEST_*_STRIN,IUTEST_*_STRNOTIN を追加
  * IUTEST_FLAG(output) に対応
  * IUTEST_*_NO_FAILURE の gtest モード対応
  * Visual Studio Type Visualizer 用 .natvis ファイルを追加
  * AVR 対応

* 変更
  * IUTEST_USE_THROW_ON_ASSERT_FAILURE を IUTEST_USE_THROW_ON_ASSERTION_FAILURE に変更
  * IUTEST_USE_THROW_ON_ASSERTION_FAILURE を指定した場合 SKIP や ASSUME も例外を投げるように変更
  * IUTEST_*_NO_FAILURE が警告やスキップを失敗と判断しないように変更
  * リスナーのセットアップ関数を変更
  * パッケージ内の値のパラメータ化テストのテストケース名が pkg.prefix/testcase となるように変更
  * IUTEST_SCOPED_PEEP,IUTEST_MAKE_SCOPED_PEEP を廃止
  * ソースコードのエンコーディングを UTF8 BOM 有りに変更

* 修正
  * IUTEST_*_TRUE/FALSE を可変長対応
  * フィクスチャークラス名を IUTEST_TEST マクロのテストケース名に使用した場合にエラーになるように修正(MSVC拡張)
  * Visual C++ Compiler November 2013 CTP 対応
  * バグ修正

--------------------------------------------------

## Changes for 1.7.0

* 追加
  * 値のパラメータを operator + で連結できるように修正
  * 値のパラメータを連結する ::iutest::Concat を追加
  * テストフィクスチャの定義が省ける値のパラメータ化テストを追加(IUTEST_AP,IUTEST_INSTANTIATE_TEST_CASE_AP(Visual Studio では IUTEST_P,IUTEST_INSTANTIATE_TEST_CASE_P でも省略可能))
  * IUTEST_TYPED_TEST,IUTEST_TYPED_TEST_P の別名マクロを追加(IUTEST_T, IUTEST_TP)
  * xml 出力に timestamp を追加
  * 前提条件の検証用マクロ IUTEST_ASSUME_* を追加
  * Windows 向けメニュー登録ユーティリティを追加
  * SSTP 通知リスナーを追加

* 修正
  * 値のパラメータ化テストが日本語テスト名に対応していなかった問題を修正
  * ビルドエラー修正
  * バグ修正

--------------------------------------------------

## Changes for 1.6.1

* 修正
  * Visual Studio 2013 Preview 対応

--------------------------------------------------

## Changes for 1.6.0

* 追加
  * stream result 対応
  * gtest モードで AssertionReturn が使えるように対応
  * ::iutest::RandomGenerator を追加

* 修正
  * ASSERT_*, EXPECT_*, INFORM_* マクロのストリームに iomanip が使用できなかった問題を修正
  * --iutest_filter にマッチしたテスト数が取得できるように修正
  * XML 出力の skipped にメッセージを出力するように修正
  * ::iutest::RandomValues で乱数シードを指定できるように修正

* 変更
  * AssertionReturn の仕様変更
  * spi で TestPartResult 数をチェックするように変更
  * spi で substr でメッセージをチェックするように変更
  * --iutest_filter でマッチしなかったテストは XML に出力しないように変更
  * デフォルトログ出力を --iutest_filter の結果を考慮した出力に変更

--------------------------------------------------

## Changes for 1.5.0

* 追加
  * iutest_list_tests_with_where コマンドラインオプションを追加
  * 日本語テスト名に対応機能を追加

* 修正
  * IUTEST_TYPED_TEST_CASE,IUTEST_TYPED_TEST_CASE_P に直接 ::iutest::Types を書けるように修正
  * 誤った使い方をした場合にエラーを出力するように修正
  * C++11 noexcept に対応

* 変更
  * SetUpTestCase などのテスト実行中以外でも RecordProperty できるように変更
  * IUTEST_PEEP の仕様変更

--------------------------------------------------

## Changes for 1.4.0

* 追加
  * ::iutest::Types メンバーに型を取得する get を追加
  * 値のパラメータ化テスト向けに任意のパラメータを生成する ValuesGen を追加
  * 値のパラメータ化テスト向けに乱数パラメータを生成する RandomValues を追加

* 修正
  * IUTEST_ASSERT_* で void 以外の戻り値を返せるように修正(::iutest::AssertionReturn)
  * ::iutest::ValuesIn を initializer_list に対応
  * extern template 対応
  * 古いコンパイラへの対応

* 変更
  * C++11 random ヘッダーが使用できるとき distribution を使うように変更

--------------------------------------------------

## Changes for 1.3.1

* 追加
  * コンパイルの通らないテストコードを許可するテスト生成マクロ(*_IGNORE)を追加

* 修正
  * IUTEST_SKIP() << "message" に対応
  * スキップ時のログ出力を修正

--------------------------------------------------

## Changes for 1.3.0

* 追加
  * ライブラリビルド対応
  * メッセージ出力のファイル/行のフォーマットを動的に変更できるオプションを追加(--iutest_file_location)
  * IUTEST_*_NO_FAILURE を追加
  * IUTEST_FRIEND_TYPED_TEST を追加

* 修正
  * gtest モードでのビルドエラー修正
  * CUDA 対応
  * IUTEST_*_FATAL_FAILURE, IUTEST_*_NONFATAL_FAILURE で lambda を利用して変数にアクセスできるように修正
  * GTEST で始まる環境変数に対応

* 変更
  * IUTEST_THROW_ON_ASSERT_FAILURE を IUTEST_USE_THROW_ON_ASSERT_FAILURE に変更
  * IUTEST_*_NO_FATAL_FAILURE が FATAL FAILURE のみで判断するように変更

--------------------------------------------------

## Changes for 1.2.0

* 追加
  * IUTEST_*_EQ_COLLECTIONS アサーションを追加
  * 名前空間を提供する IUTEST_PACKAGE 追加
  * プログレス出力リスナーを追加

* 修正
  * Android NDK 対応
  * IUTEST_*_NO_THROW で失敗したときに例外の情報を出力するように修正
  * IUTEST_*_STRNE, IUTEST_*_STRCASENE の失敗メッセージを改善
  * デフォルト printer のワイド文字列対応

--------------------------------------------------

## Changes for 1.1.1

* 修正
  * ビルドエラー修正
  * 定義と宣言を分離

--------------------------------------------------

## Changes for 1.1.0

* 追加
  * オールペア法による組み合わせを作成する iutest::Pairwise を追加
  * 明示的なスキップとして IUTEST_SKIP を追加
  * 例外の値を検査するアサーションを追加
  * ファイルパス操作補助クラスの追加

* 修正
  * CRT セキュリティ強化関数の失敗時ハンドラに対応
  * コンソール出力先を動的に変更できるように修正
  * Visual Studio UnitTest Framework 対応(tr1)
  * マルチバイト文字が XML 出力で出力できない問題を修正

* 変更
  * iutest::InitIrisUnitTest が呼ばれていない場合に警告を出すように変更
  * IUTEST_*_EQ で if( expected == actual ) から if( actual == expected ) に変更

--------------------------------------------------

## Changes for 1.0.0

* 初期リリース
