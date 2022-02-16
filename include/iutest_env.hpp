//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_env.hpp
 * @brief       iris unit test 環境 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_ENV_HPP_F4017EAB_6CA3_4E6E_8983_059393DADD04_
#define INCG_IRIS_IUTEST_ENV_HPP_F4017EAB_6CA3_4E6E_8983_059393DADD04_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "internal/iutest_charcode.hpp"
#include "internal/iutest_random.hpp"
#include "internal/iutest_regex.hpp"
#include "iutest_listener.hpp"
// IWYU pragma: end_exports

//======================================================================
// define
/**
 * @ingroup IUTEST_UTIL
 * @brief   フラグセット
 * @details 指定可能なフラグ\n
 *          shuffle (bool)\n
 *          also_run_disabled_tests (bool)\n
 *          break_on_failure (bool)\n
 *          throw_on_failure (bool)\n
 *          warning_into_error (bool)\n
 *          catch_exceptions (bool)\n
 *          catch_exceptions_each   (bool)\n
 *          catch_exceptions_global (bool)\n
 *          random_seed (unsigned int)\n
 *          print_time (bool)\n
 *          color (string)\n
 *          filter (string)\n
 *          flagfile (string)\n
 *          output (string)\n
 *          repeat (int)\n
 *          list_tests (bool)\n
 *          list_tests_with_where (bool)\n
 *          verbose (bool)\n
 *          file_location_style_msvc (bool)\n
 *          default_package_name (string)\n
 *          ostream_formatter (ostream)\n
 *          locale_ctype (string)\n
*/
#define IUTEST_FLAG(name)   IIUT_FLAG(name)

/**
 * @private
 * @{
*/
#define IIUT_FLAG(name)     TestEnv::name()

/**
 * @}
*/

#if IUTEST_HAS_LIB && IUTEST_HAS_EXTERN_TEMPLATE

namespace iutest { class Environment; }

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN()

extern template class ::std::vector< ::iutest::Environment* >;

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END()

#endif

namespace iutest
{

//======================================================================
// function
/**
 * @brief   環境変数の取得
*/
inline ::std::string EnvironmentString(const char* name)
{
    ::std::string var;
    detail::GetEnvironmentVariable(name, var);
    return var;
}

//======================================================================
// class
/**
 * @brief   環境セットクラス
*/
class Environment
{
public:
    virtual ~Environment()
    {
        IUTEST_IGNORE_EXCEPTION_BEGIN()
        {
            Release();
        }
        IUTEST_IGNORE_EXCEPTION_END()
    }
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DECLARE_NOEXCEPT()

    virtual void SetUp() {}     //!< 事前処理
    virtual void TearDown() {}  //!< 事後処理

IUTEST_PRAGMA_WARN_POP()

private:
    void Release();
private:
    struct should_be_SetUp {};
    virtual should_be_SetUp* Setup() IUTEST_CXX_NOEXCEPT_SPEC IUTEST_CXX_FINAL { return IUTEST_NULLPTR; }
};

/**
 * @brief   テストフラグ
*/
class TestFlag
{
public:
    /**
     * @brief   テストフラグ保存/復元クラス
     * @private
    */
    class ScopedGuard
    {
        IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(ScopedGuard);

        int m_test_flags;
    public:
        ScopedGuard() IUTEST_CXX_NOEXCEPT_SPEC
        {
            m_test_flags = TestFlag::GetInstance().m_test_flags;
        }
        ~ScopedGuard()
        {
            TestFlag::GetInstance().m_test_flags = m_test_flags;
        }
    };
public:
    /**
     * @brief   フラグ
    */
    enum Kind
    {
        SHUFFLE_TESTS           = 0x00000001,   //!< シャッフルテスト
        RUN_DISABLED_TESTS      = 0x00000002,   //!< DISABLED テストも実行
        FILTERING_TESTS         = 0x00000004,   //!< テストのフィルタリング

        BREAK_ON_FAILURE        = 0x00000010,   //!< テスト失敗時にブレーク
        THROW_ON_FAILURE        = 0x00000040,   //!< 致命的な失敗時に throw する
        WARNING_INTO_ERROR      = 0x00000080,   //!< 警告をエラーとする

        CONSOLE_COLOR_ON        = 0x00000100,   //!< 色つき出力ON
        CONSOLE_COLOR_OFF       = 0x00000200,   //!< 色つき出力OFF
        CONSOLE_COLOR_ANSI      = 0x00000400,   //!< エスケープシーケンスで出力

        PRINT_TIME              = 0x00001000,   //!< 経過時間の出力
        FILELOCATION_STYLE_MSVC = 0x00002000,   //!< ファイル/行出力スタイルを Visual Studio スタイルにする
        VERBOSE                 = 0x00004000,   //!< verbose

        CATCH_EXCEPTION_EACH    = 0x00010000,   //!< 例外を catch する(TestInfo)
        CATCH_EXCEPTION_GLOBAL  = 0x00020000,   //!< 例外を catch する(UnitTest)
        CATCH_EXCEPTION         = 0x00030000,   //!< 例外を catch する

        SHOW_HELP               = 0x01000000,   //!< ヘルプ表示
        SHOW_VERSION            = 0x02000000,   //!< バージョン表示
        SHOW_FEATURE            = 0x04000000,   //!< 機能の出力
        SHOW_SPEC               = 0x08000000,   //!< Specの出力

        SHOW_TESTS_LIST         = 0x20000000,   //!< テストのリスト表示
        SHOW_TESTS_LIST_WITH_WHERE
                                = 0x40000000,   //!< テストのリスト表示(with where)

        SHOW_INFO_MASK          = 0x0F000000,   //!< 情報表示系マスク
        SHOW_MASK               = 0x7F000000,   //!< 表示系マスク
        MASK                    = 0x7FFFFFFF,   //!< マスク

        //! デフォルト
#if defined(_MSC_VER)
        DEFAULT = CATCH_EXCEPTION|PRINT_TIME|FILELOCATION_STYLE_MSVC
#else
        DEFAULT = CATCH_EXCEPTION|PRINT_TIME
#endif
    };

private:
    TestFlag() IUTEST_CXX_NOEXCEPT_SPEC
        : m_test_flags(DEFAULT) {}

public:
    /** @private */
    static TestFlag& GetInstance() IUTEST_CXX_NOEXCEPT_SPEC { static TestFlag flag; return flag; }
public:
    /**
     * @brief   フラグのビット操作
     * @details flag = (flag | enable) & mask;
     * @param [in]  enable  = 論理和
     * @param [in]  mask    = マスク値
    */
    static void SetFlag(int enable, int mask=-1) IUTEST_CXX_NOEXCEPT_SPEC
    {
        GetInstance().m_test_flags |= enable;
        GetInstance().m_test_flags &= mask;
    }
    /**
     * @brief   フラグが立っているかどうか
     * @param [in]  flag    = 検査対象フラグ
     * @return  真偽値
    */
    static bool IsEnableFlag(int flag) IUTEST_CXX_NOEXCEPT_SPEC { return (GetInstance().m_test_flags & flag) ? true : false; }

private:
    template<int KIND>
    class Fragment
    {
        typedef Fragment<KIND> _Myt;
    public:
        Fragment() IUTEST_CXX_NOEXCEPT_SPEC {}
        Fragment(bool enabled) IUTEST_CXX_NOEXCEPT_SPEC { SetFlag(KIND, enabled ? -1 : ~KIND); } // NOLINT
        _Myt& operator = (bool enabled) IUTEST_CXX_NOEXCEPT_SPEC { SetFlag(KIND, enabled ? -1 : ~KIND); return *this; }
        operator bool() const IUTEST_CXX_NOEXCEPT_SPEC { return IsEnableFlag(KIND); }
    };

private:
    friend class TestEnv;
#if defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
    friend class ScopedGuard;
#endif

    int m_test_flags;
};

// declare
class TestPartResultReporterInterface;

/**
 * @brief   テスト環境
*/
class TestEnv
{
    typedef ::std::vector<Environment*> iuEnvironmentList;

public:
    /**
     * @private
     * @{
    */
    typedef TestFlag::Fragment<TestFlag::SHUFFLE_TESTS>         shuffle;
    typedef TestFlag::Fragment<TestFlag::RUN_DISABLED_TESTS>    also_run_disabled_tests;
    typedef TestFlag::Fragment<TestFlag::BREAK_ON_FAILURE>      break_on_failure;
    typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION>       catch_exceptions;
    typedef TestFlag::Fragment<TestFlag::THROW_ON_FAILURE>      throw_on_failure;
    typedef TestFlag::Fragment<TestFlag::WARNING_INTO_ERROR>    warning_into_error;
    typedef TestFlag::Fragment<TestFlag::PRINT_TIME>            print_time;
    typedef TestFlag::Fragment<TestFlag::SHOW_TESTS_LIST>       list_tests;
    typedef TestFlag::Fragment<TestFlag::SHOW_TESTS_LIST_WITH_WHERE> list_tests_with_where;

    typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION_EACH>      catch_exceptions_each;
    typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION_GLOBAL>    catch_exceptions_global;

    typedef TestFlag::Fragment<TestFlag::FILELOCATION_STYLE_MSVC>   file_location_style_msvc;
    typedef TestFlag::Fragment<TestFlag::VERBOSE>   verbose;

    /**
     * @}
    */

    /**
     * @private
     * @brief   乱数シード設定用オブジェクト
    */
    typedef class RandomSeedSet
    {
    public:
        RandomSeedSet() IUTEST_CXX_NOEXCEPT_SPEC {}
        RandomSeedSet(unsigned int seed) IUTEST_CXX_NOEXCEPT_SPEC { init_random(seed); }
        RandomSeedSet& operator = (unsigned int seed) IUTEST_CXX_NOEXCEPT_SPEC { init_random(seed); return *this; }
        operator unsigned int() const IUTEST_CXX_NOEXCEPT_SPEC { return get_random_seed(); }
    } random_seed;

    /**
     * @private
     * @brief   リピート回数設定用オブジェクト
    */
    typedef class RepeatCountSet
    {
    public:
        RepeatCountSet() IUTEST_CXX_NOEXCEPT_SPEC {}
        RepeatCountSet(int count) IUTEST_CXX_NOEXCEPT_SPEC { set_repeat_count(count); }
        RepeatCountSet& operator = (int count) IUTEST_CXX_NOEXCEPT_SPEC { set_repeat_count(count); return *this; }
        operator int() const IUTEST_CXX_NOEXCEPT_SPEC { return get_repeat_count(); }
    } repeat;

#if defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
    friend class RandomSeedSet;
    friend class RepeatCountSet;
#endif

    template<typename T>
    class StateVariable
    {
        bool m_dirty;
        T   m_value;
    public:
        StateVariable() IUTEST_CXX_NOEXCEPT_SPEC : m_dirty(false), m_value(T()) {}
        StateVariable& operator = (const T& rhs) IUTEST_CXX_NOEXCEPT_SPEC { m_value = rhs; m_dirty = true; return *this; }
        operator const T& () const IUTEST_CXX_NOEXCEPT_SPEC { return m_value; }
        const T& operator ()() const IUTEST_CXX_NOEXCEPT_SPEC { return m_value; }
        bool is_dirty() const IUTEST_CXX_NOEXCEPT_SPEC { return m_dirty; }
        void flush() IUTEST_CXX_NOEXCEPT_SPEC { m_dirty = false; }
        T& get() IUTEST_CXX_NOEXCEPT_SPEC { return m_value; }
        const T& get() const IUTEST_CXX_NOEXCEPT_SPEC { return m_value; }
    };

private:
    struct Variable
    {
        Variable() IUTEST_CXX_NOEXCEPT_SPEC
            : m_random_seed(0)
            , m_current_random_seed(0)
            , m_before_origin_random_seed(0)
            , m_repeat_count(1)
            , m_testpartresult_reporter(IUTEST_NULLPTR)
        {}
        unsigned int        m_random_seed;
        unsigned int        m_current_random_seed;
        unsigned int        m_before_origin_random_seed;
        int                 m_repeat_count;
        StateVariable< ::std::string >  m_output_option;
        ::std::string       m_test_filter;
        ::std::string       m_flagfile;
#if IUTEST_HAS_STREAM_RESULT
        StateVariable< ::std::string >  m_stream_result_to;
#endif
        ::std::string       m_default_package_name;
        detail::iuRandom    m_genrand;
        iuEnvironmentList   m_environment_list;
        TestEventListeners  m_event_listeners;
        TestPartResultReporterInterface*    m_testpartresult_reporter;
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
        iu_stringstream     m_ostream_formatter;
#endif
        ::std::string       m_locale_ctype;
    };

    static Variable& get_vars() IUTEST_CXX_NOEXCEPT_SPEC { static Variable sVars; return sVars; }

private:
    static const char*          get_output_option_c_str() IUTEST_CXX_NOEXCEPT_SPEC { return get_vars().m_output_option.get().c_str(); }
#if IUTEST_HAS_STREAM_RESULT
    static const char*          get_stream_result_to_c_str() IUTEST_CXX_NOEXCEPT_SPEC { return get_vars().m_stream_result_to.get().c_str(); }
#endif

public:
    //! get random generator
    static detail::iuRandom& genrand() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_genrand;
    }
     //! random seed
    static unsigned int get_random_seed() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_random_seed;
    }
     //! current test random seed
    static unsigned int current_random_seed() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_current_random_seed;
    }
    //! repeat count
    static int get_repeat_count() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_repeat_count;
    }
    //! output option
    static const StateVariable< ::std::string >& get_output_option() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_output_option;
    }
    //! root package option
    static const char* get_default_package_name() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_default_package_name.c_str();
    }
    //! filter string
    static const char* test_filter() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_test_filter.c_str();
    }
    //! flag file
    static const char* get_flagfile() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_flagfile.c_str();
    }
#if IUTEST_HAS_STREAM_RESULT
    static const StateVariable< ::std::string >& get_stream_result_to() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_stream_result_to;
    }
#endif
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
    static void                 global_ostream_copyfmt(iu_ostream& os) { os.copyfmt(get_vars().m_ostream_formatter); }  // NOLINT
#endif
    //!< ctype locale option
    static const char* get_locale_ctype() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_locale_ctype.c_str();
    }
    static bool is_specific_locale_ctype() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return !get_vars().m_locale_ctype.empty();
    }

    /**
     * @brief   xml 出力パスを取得
    */
    static ::std::string get_report_xml_filepath();
    /**
     * @brief   junit xml 出力パスを取得
    */
    static ::std::string get_report_junit_xml_filepath();

    /** @private */
    static TestEventListeners& event_listeners() IUTEST_CXX_NOEXCEPT_SPEC { return get_vars().m_event_listeners; }
    /** @private */
    static TestPartResultReporterInterface* GetGlobalTestPartResultReporter() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_testpartresult_reporter;
    }
    /** @private */
    static void SetGlobalTestPartResultReporter(TestPartResultReporterInterface* ptr) IUTEST_CXX_NOEXCEPT_SPEC
    {
        get_vars().m_testpartresult_reporter = ptr;
    }
    /** @private */
    static bool has_output_option() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return !get_vars().m_output_option.get().empty();
    }
    /** @private */
    static bool is_output_option_dirty() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return get_vars().m_output_option.is_dirty();
    }
    /** @private */
    static void flush_output_option() IUTEST_CXX_NOEXCEPT_SPEC
    {
        get_vars().m_output_option.flush();
    }

private:
    /**
     * @brief   乱数シードの設定
    */
    static void init_random(unsigned int seed) IUTEST_CXX_NOEXCEPT_SPEC
    {
        get_vars().m_random_seed = seed;
    }

    /**
     * @brief   繰り返し回数の設定
    */
    static void set_repeat_count(int count) IUTEST_CXX_NOEXCEPT_SPEC
    {
        get_vars().m_repeat_count = count;
    }

    /**
     * @brief   フィルター文字列の設定
    */
    static void set_test_filter(const char* str)
    {
        get_vars().m_test_filter = str == IUTEST_NULLPTR ? "*" : str;
        TestFlag::SetFlag(TestFlag::FILTERING_TESTS);
    }

    /**
     * @brief   flagfile の設定
    */
    static void set_flagfile_path(const char* str)
    {
        get_vars().m_flagfile = str;
    }

    /**
     * @brief   flagfile の設定
    */
    static void set_flagfile(const char* str)
    {
        ParseFlagFileOption(str);
        LoadFlagFile();
    }

#if IUTEST_HAS_STREAM_RESULT
    /**
     * @brief   stream result の設定
    */
    static void set_stream_result_to(const char* str)
    {
        get_vars().m_stream_result_to = detail::NullableString(str);
    }
#endif

    /**
     * @brief   color オプション文字列を取得
    */
    static const char* get_color_option() IUTEST_CXX_NOEXCEPT_SPEC
    {
        if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ANSI) )
        {
            return "ansi";
        }
        else if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ON) )
        {
            return "yes";
        }
        else if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_OFF) )
        {
            return "no";
        }
        return "auto";
    }
    /**
     * @brief   color オプションを設定
    */
    static void set_color_option(const char* str) IUTEST_CXX_NOEXCEPT_SPEC
    {
        ParseColorOption(str);
    }

    /**
     * @brief   output オプションを設定
    */
    static void set_output_option(const char* str)
    {
        get_vars().m_output_option = detail::NullableString(str);
    }

    /**
     * @brief   default_package_name オプションを設定
    */
    static void set_default_package_name(const char* str)
    {
        get_vars().m_default_package_name = detail::NullableString(str);
    }

    /**
     * @brief   locale_ctype オプションを設定
    */
    static void set_locale_ctype(const char* str)
    {
        get_vars().m_locale_ctype = detail::NullableString(str);
    }

private:
    typedef const char* (*pfnOptionStringGet)();
    typedef void(*pfnOptionStringSet)(const char*);
    template<pfnOptionStringGet G, pfnOptionStringSet S>
    class OptionString
    {
        typedef OptionString<G, S> _Myt;
        typedef const _Myt& _Argt;
    protected:
        ::std::string m_option;
    public:
        friend bool operator == (const char* c_str_, _Argt rhs)         { return rhs.m_option == c_str_; }
        friend bool operator == (const ::std::string& str, _Argt rhs)   { return rhs.m_option == str; }
        friend bool operator == (_Argt lhs, const char* c_str_)         { return lhs.m_option == c_str_; }
        friend bool operator == (_Argt lhs, const ::std::string& str)   { return lhs.m_option == str; }
        friend bool operator != (const char* c_str_, _Argt rhs)         { return rhs.m_option != c_str_; }
        friend bool operator != (const ::std::string& str, _Argt rhs)   { return rhs.m_option != str; }
        friend bool operator != (_Argt lhs, const char* c_str_)         { return lhs.m_option != c_str_; }
        friend bool operator != (_Argt lhs, const ::std::string& str)   { return lhs.m_option != str; }

        operator ::std::string() const { return m_option; }
    public:
        bool empty() const          { return m_option.empty(); }
        const char* c_str() const   { return m_option.c_str(); }
        size_t length() const       { return m_option.length(); }
    public:
        OptionString()
            : m_option(G())
        {
        }
        const _Myt& operator = (const char* c_str_)
        {
            m_option = detail::NullableString(c_str_);
            S(c_str_);
            return *this;
        }
        const _Myt& operator = (const ::std::string& str)
        {
            m_option = str;
            S(str.c_str());
            return *this;
        }
    };

public:
    /**
     * @private
     * @brief   色付き出力オプション設定用オブジェクト
    */
    typedef OptionString<get_color_option, set_color_option> color;

    /**
     * @private
     * @brief   フィルターオプション設定用オブジェクト
    */
    typedef OptionString<test_filter, set_test_filter> filter;

    /**
     * @private
     * @brief   フィルターオプション設定用オブジェクト
    */
    typedef OptionString<get_flagfile, set_flagfile> flagfile;

    /**
     * @private
     * @brief   出力オプション設定用オブジェクト
    */
    typedef OptionString<get_output_option_c_str, set_output_option> output;

#if IUTEST_HAS_STREAM_RESULT
    /**
     * @private
     * @brief   stream resultオプション設定用オブジェクト
    */
    typedef OptionString<get_stream_result_to_c_str, set_stream_result_to> stream_result_to;
#endif

    /**
     * @private
     * @brief   default_package_name オプション設定用オブジェクト
    */
    typedef OptionString<get_default_package_name, set_default_package_name> default_package_name;

    /**
     * @private
     * @brief   locale_ctype オプション設定用オブジェクト
    */
    typedef OptionString<get_locale_ctype, set_locale_ctype> locale_ctype;

#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
    /**
     * @private
     * @brief   ostream_formatter オプション設定用オブジェクト
    */
    typedef class OStreamFormatter : public iu_stringstream
    {
        IUTEST_WORKAROUND_MSC_STLSTREAM_C4250()
    public:
        OStreamFormatter() IUTEST_CXX_NOEXCEPT(false)
        {
            copyfmt(get_vars().m_ostream_formatter);
        }
        virtual ~OStreamFormatter()
        {
            IUTEST_IGNORE_EXCEPTION_BEGIN()
            {
                get_vars().m_ostream_formatter.copyfmt(*this);
            }
            IUTEST_IGNORE_EXCEPTION_END()
        }
    } ostream_formatter;

#if defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
    friend class OStreamFormatter;
#endif

#endif

private:
    static iuEnvironmentList& environments() IUTEST_CXX_NOEXCEPT_SPEC { return get_vars().m_environment_list; }

public:
    /**
     * @brief   グローバル環境セットクラスの追加
     * @param [in]  env = 環境セットクラスアドレス
     * @return  登録されたクラスアドレス
    */
    static Environment* AddGlobalTestEnvironment(Environment* env)
    {
        if( env != IUTEST_NULLPTR )
        {
            environments().push_back(env);
        }
        return env;
    }

    /**
     * @brief   グローバル環境セットクラスの削除
     * @param [in]  env = 環境セットクラスアドレス
     * @return  削除されたクラスアドレス
    */
    static Environment* ReleaseGlobalTestEnvironment(Environment* env)
    {
        if( env == IUTEST_NULLPTR )
        {
            return IUTEST_NULLPTR;
        }
        iuEnvironmentList& list = environments();
        iuEnvironmentList::iterator it = ::std::find(list.begin(), list.end(), env);
        if( it == list.end() )
        {
            return IUTEST_NULLPTR;
        }
        list.erase(it);
        return env;
    }

    /**
     * @brief   default package name を追加
    */
    static ::std::string AddDefaultPackageName(const char* testsuite_name);

private:
    /**
     * @brief   環境セットクラスの解放
    */
    static void ReleaseGlobalTestEnvironment() IUTEST_CXX_NOEXCEPT_SPEC
    {
        // すべて解放する
        for( iuEnvironmentList::iterator it=environments().begin(); it != environments().end(); )
        {
            Environment* p = *it;
            it = environments().erase(it);
            delete p;
        }
    }

public:
    /**
     * @private
     * @brief   コマンドライン引数の解析
    */
    template<typename CharType>
    static void ParseCommandLine(int* pargc, CharType** argv)
    {
        if( argv == IUTEST_NULLPTR )
        {
            return;
        }
        int argc = *pargc;

        for( int i=0; i < argc; )
        {
            if( ParseCommandLineElem(argv[i]) )
            {
                --argc;
                // 見つかった場合、オプションを末尾に移動
                for( int k=i; k < argc; ++k )
                {
                    CharType* tmp = argv[k];
                    argv[k] = argv[k+1];
                    argv[k+1] = tmp;
                }
            }
            else
            {
                ++i;
            }
        }
        *pargc = argc;
    }

    /**
     * @private
     * @brief   コマンドライン引数の解析(vector)
    */
    template<typename CharType>
    static void ParseCommandLine(::std::vector< ::std::basic_string<CharType> >& argv)
    {
        typedef ::std::vector< ::std::basic_string<CharType> > argv_t;
        for( typename argv_t::iterator it = argv.begin(); it != argv.end(); )
        {
            if( ParseCommandLineElem(it->c_str()) )
            {
                it = argv.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    /** @brief  フラグファイルをロード */
    static bool LoadFlagFile();

private:
    template<typename CharType>
    static bool ParseCommandLineElem(CharType* argv)
    {
        typedef typename detail::mbs_ptr<CharType> formatter;

        formatter argv_format;
        const char* str = argv_format.ptr(argv);
        return ParseCommandLineElemA(str);
    }
    static bool ParseCommandLineElemA(const char* str);
    static bool ParseIutestOptionCommandLineElemA(const char* str);
    static bool SetFlag(int enable, int mask = -1) IUTEST_CXX_NOEXCEPT_SPEC;

private:
    /**
     * @brief   環境変数から設定構築
    */
    static void LoadEnvironmentVariable();

    /**
     * @brief   セットアップ
    */
    static void SetUp() IUTEST_CXX_NOEXCEPT_SPEC;

private:
    /**
     * @brief   オプション文字列から設定文字列の先頭アドレスを取得
    */
    static inline const char* ParseOptionSettingStr(const char* opt) IUTEST_CXX_NOEXCEPT_SPEC
    {
        const char* eq = strchr(opt, '=');
        if( eq == IUTEST_NULLPTR )
        {
            return IUTEST_NULLPTR;
        }
        return eq+1;
    }
    /**
     * @brief   IUTEST_COLOR オプションの判定
    */
    static bool ParseColorOption(const char* option) IUTEST_CXX_NOEXCEPT_SPEC;

    /**
     * @brief   IUTEST_OUTPUT オプションの判定
    */
    static bool ParseOutputOption(const char* option);

    /**
     * @brief   IUTEST_FILE_LOCATION オプションの判定
    */
    static bool ParseFileLocationOption(const char* option) IUTEST_CXX_NOEXCEPT_SPEC;

    /**
     * @brief   IUTEST_FILTER オプションの判定
    */
    static bool ParseFilterOption(const char* option);

    /**
     * @brief   IUTEST_FLAGFILE オプションの判定
    */
    static bool ParseFlagFileOption(const char* option);

    /**
     * @brief   yes オプションか no オプションかの判定
     * @param [in]  str     = コマンドライン文字列（関数ないでオプション文字列部分を取得する）
     * @param [in]  flag    = フラグ
     * @param [in]  def     = 引数なしの場合のオペレーション
     * @return  成否
    */
    static bool ParseYesNoFlagCommandLine(const char* str, TestFlag::Kind flag, int def) IUTEST_CXX_NOEXCEPT_SPEC;

    /**
     * @brief   yes オプションか no オプションかの判定
     * @param [in]  option  = オプション文字列
     * @retval  < 0 = 該当なし
     * @retval  0   = NO
     * @retval  > 0 = YES
    */
    static int ParseYesNoOption(const char* option) IUTEST_CXX_NOEXCEPT_SPEC;

    /**
     * @brief   yes オプションか判定
    */
    static bool IsYes(const char* option) IUTEST_CXX_NOEXCEPT_SPEC;
    /**
     * @brief   no オプションか判定
    */
    static bool IsNo(const char* option) IUTEST_CXX_NOEXCEPT_SPEC;

private:
    friend class UnitTest;
};

/**
 * @brief   ostream_formatter オプションが適用された stringstream
*/
class iu_global_format_stringstream : public iu_stringstream
{
    IUTEST_WORKAROUND_MSC_STLSTREAM_C4250()
public:
    iu_global_format_stringstream() IUTEST_CXX_NOEXCEPT(false)
    {
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
        TestEnv::global_ostream_copyfmt(*this);
#endif
    }
    explicit iu_global_format_stringstream(const char* str) IUTEST_CXX_NOEXCEPT(false)
        : iu_stringstream(str)
    {
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
        TestEnv::global_ostream_copyfmt(*this);
#endif
    }
    explicit iu_global_format_stringstream(const ::std::string& str) IUTEST_CXX_NOEXCEPT(false)
        : iu_stringstream(str)
    {
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
        TestEnv::global_ostream_copyfmt(*this);
#endif
    }
};

template<typename T>
inline iu_ostream& operator << (iu_ostream& os, const TestEnv::StateVariable<T>& value)
{
    return os << value.get();
}


}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_env.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_ENV_HPP_F4017EAB_6CA3_4E6E_8983_059393DADD04_
