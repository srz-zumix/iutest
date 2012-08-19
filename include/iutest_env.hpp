//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_env.hpp
 * @brief		iris unit test 環境 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_env_HPP_F4017EAB_6CA3_4e6e_8983_059393DADD04_
#define INCG_IRIS_iutest_env_HPP_F4017EAB_6CA3_4e6e_8983_059393DADD04_

//======================================================================
// include
#include "internal/iutest_charcode.hpp"
#include "internal/iutest_random.hpp"
#include "internal/iutest_regex.hpp"
#include "iutest_listener.hpp"

//======================================================================
// define
/**
 * @ingroup	IUTEST_UTIL
 * @brief	フラグセット
 * @details	指定可能なフラグ\n
 *			shuffle (bool)\n
 *			also_run_disabled_tests (bool)\n
 *			break_on_failure (bool)\n
 *			throw_on_failure (bool)\n
 *			catch_exceptions (bool)\n
 *			random_seed (unsigned int)\n
 *			print_time (bool)\n
 *          color (string)\n
 *          filter (string)\n
 *          repeat (int)\n
 *			list_tests (bool)\n
*/
#define IUTEST_FLAG(name)	IIUT_FLAG(name)

/**
 * @private
 * @{
*/
#define IIUT_FLAG(name)		TestEnv::name()

/**
 * @}
*/

namespace iutest
{

//======================================================================
// function
/**
 * @brief	環境変数の取得
*/
inline ::std::string EnvironmentString(const char* name) { ::std::string var; detail::GetEnvironmentVariable(name, var); return var; }

//======================================================================
// class
/**
 * @brief	環境セットクラス
*/
class Environment
{
public:
	virtual ~Environment(void)	{}
	virtual void SetUp(void)	{}	//!< 事前処理
	virtual void TearDown(void)	{}	//!< 事後処理
};

/**
 * @brief	テストフラグ
*/
class TestFlag
{
public:
	/**
	 * @brief	テストフラグ保存/復元クラス
	*/
	class ScopedGuard
	{
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(ScopedGuard);

		int m_test_flags;
	public:
		ScopedGuard(void) 
		{
			m_test_flags = TestFlag::GetInstance().m_test_flags;
		}
		~ScopedGuard(void) 
		{
			TestFlag::GetInstance().m_test_flags = m_test_flags;
		}
	};
public:
	/** 
	 * @brief	フラグ
	*/
	enum Kind
	{
		SHUFFLE_TESTS			= 0x00000001,	//!< シャッフルテスト
		RUN_DISABLED_TESTS		= 0x00000002,	//!< DISABLED テストも実行
		FILTERING_TESTS			= 0x00000004,	//!< テストのフィルタリング
		BREAK_ON_FAILURE		= 0x00000010,	//!< テスト失敗時にブレーク
		THROW_ON_FAILURE		= 0x00000040,	//!< 致命的な失敗時に throw する
		CONSOLE_COLOR_ON		= 0x00000100,	//!< 色つき出力ON
		CONSOLE_COLOR_OFF		= 0x00000200,	//!< 色つき出力OFF
		CONSOLE_COLOR_ANSI		= 0x00000400,	//!< エスケープシーケンスで出力
		PRINT_TIME				= 0x00001000,	//!< 経過時間の出力
		CATCH_EXCEPTION_EACH	= 0x00010000,	//!< 例外を catch する(TestInfo)
		CATCH_EXCEPTION_GLOBAL	= 0x00020000,	//!< 例外を catch する(UnitTest)
		CATCH_EXCEPTION			= 0x00030000,	//!< 例外を catch する
		OUTPUT_XML_REPORT		= 0x01000000,	//!< xml 出力
		SHOW_HELP				= 0x10000000,	//!< ヘルプ表示
		SHOW_VERSION			= 0x20000000,	//!< バージョン表示
		SHOW_TESTS_LIST			= 0x40000000,	//!< テストのリスト表示
		SHOW_FEATURE			= 0x80000000,	//!< 機能の出力
		MASK					= 0xFFFFFFFF,	//!< マスク

		DEFAULT = CATCH_EXCEPTION|PRINT_TIME		//!< デフォルト
	};

private:
	TestFlag(void)
		: m_test_flags(DEFAULT) {}

public:
	/** @private */
	static TestFlag&	GetInstance(void)	{ static TestFlag flag; return flag; }
public:
	/**
	 * @brief	フラグのビット操作
	 * @details	flag = (flag | enable) & mask;
	 * @param [in]	enable	= 論理和
	 * @param [in]	mask	= マスク値
	*/
	static void		SetFlag(int enable, int mask=-1)	{ GetInstance().m_test_flags |= enable; GetInstance().m_test_flags &= mask; }
	/**
	 * @brief	フラグが立っているかどうか
	 * @param [in]	flag	= 検査対象フラグ
	 * @return	真偽値
	*/
	static bool		IsEnableFlag(int flag)				{ return GetInstance().m_test_flags & flag ? true : false; }

private:
	template<int KIND>
	class Fragment
	{
		typedef Fragment<KIND>	_Myt;
	public:
		Fragment(void) {}
		Fragment(bool f)	{ SetFlag(KIND, f ? -1 : ~KIND); }
		_Myt&	operator = (bool f)	{ SetFlag(KIND, f ? -1 : ~KIND); return *this; }
		operator bool (void) const { return IsEnableFlag(KIND); }
	};

private:
	friend	class TestEnv;

	int m_test_flags;
};

// declare
class TestPartResultReporterInterface;

/**
 * @brief	テスト環境
*/
class TestEnv
{
	typedef ::std::vector<Environment*>	iuEnvironmentList;
private:
	class OptionString
	{
	protected:
		::std::string	m_option;
	public:
		bool operator == (const char* c_str_)		{ return m_option == c_str_; }
		bool operator == (const ::std::string& str)	{ return m_option == str; }
		bool operator != (const char* c_str_)		{ return m_option != c_str_; }
		bool operator != (const ::std::string& str)	{ return m_option != str; }

	public:
		const char* c_str(void) const	{ return m_option.c_str(); }
		size_t	length(void) const		{ return m_option.length(); }
	};

public:

	/**
	 * @private
	 * @{
	*/
	typedef TestFlag::Fragment<TestFlag::SHUFFLE_TESTS>			shuffle;
	typedef TestFlag::Fragment<TestFlag::RUN_DISABLED_TESTS>	also_run_disabled_tests;
	typedef TestFlag::Fragment<TestFlag::BREAK_ON_FAILURE>		break_on_failure;
	typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION>		catch_exceptions;
	typedef TestFlag::Fragment<TestFlag::THROW_ON_FAILURE>		throw_on_failure;
	typedef TestFlag::Fragment<TestFlag::PRINT_TIME>			print_time;
	typedef TestFlag::Fragment<TestFlag::SHOW_TESTS_LIST>		list_tests;

	typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION_EACH>		catch_exceptions_each;
	typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION_GLOBAL>	catch_exceptions_global;

	/**
	 * @}
	*/

	/**
	 * @private
	 * @brief	乱数シード設定用オブジェクト
	*/
	typedef class RandomSeedSet
	{
	public:
		RandomSeedSet(void) {}
		RandomSeedSet(unsigned int seed) { init_random(seed); } 
		RandomSeedSet&	operator = (unsigned int seed)	{ init_random(seed); return *this; }
		operator unsigned int (void) const { return get_random_seed(); }
	} random_seed;

	/**
	 * @private
	 * @brief	リピート回数設定用オブジェクト
	*/
	typedef class RepeatCountSet
	{
	public:
		RepeatCountSet(void) {}
		RepeatCountSet(int count) { set_repeat_count(count); } 
		RepeatCountSet&	operator = (int count)	{ set_repeat_count(count); return *this; }
		operator int (void) const { return get_repeat_count(); }
	} repeat;

	/**
	 * @private
	 * @brief	色付き出力オプション設定用オブジェクト
	*/
	typedef class ColorOptionSet : public OptionString
	{
	public:
		ColorOptionSet(void)
		{
			if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_OFF) ) m_option = "no";
			else if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ON) ) m_option = "yes";
			else if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ANSI) ) m_option = "ansi";
			else m_option = "auto";
		}
		const ColorOptionSet& operator = (const char* c_str_)
		{
			m_option = c_str_;
			ParseOutputOption(c_str_);
			return *this;
		}
		const ColorOptionSet& operator = (const ::std::string& str)
		{
			m_option = str;
			ParseOutputOption(str.c_str());
			return *this;
		}
	} color;

	/**
	 * @private
	 * @brief	フィルターオプション設定用オブジェクト
	*/
	typedef class FilterOption : public OptionString
	{
	public:
		FilterOption(void)
		{
			m_option = get_vars().m_test_filter;
		}
		const FilterOption& operator = (const char* c_str_)
		{
			m_option = c_str_;
			set_test_filter(c_str_);
			return *this;
		}
		const FilterOption& operator = (const ::std::string& str)
		{
			m_option = str;
			set_test_filter(str.c_str());
			return *this;
		}
	} filter;

private:
	struct Variable
	{
		Variable(void)
			: m_random_seed(0)
			, m_current_random_seed(0)
			, m_repeat_count(1)
			, m_testpartresult_reporter(NULL)
		{}
		unsigned int		m_random_seed;
		unsigned int		m_current_random_seed;
		int					m_repeat_count;
		::std::string		m_report_file;
		::std::string		m_test_filter;
		detail::iuRandom	m_genrand;
		iuEnvironmentList	m_environment_list;
		TestEventListeners	m_event_listeners;
		TestPartResultReporterInterface*	m_testpartresult_reporter;
	};

	static Variable& get_vars(void) { static Variable v; return v; }

public:

	static detail::iuRandom&	genrand(void)				{ return get_vars().m_genrand; }				//!< 乱数生成器
	static unsigned int			get_random_seed(void)		{ return get_vars().m_random_seed; }			//!< 乱数シード
	static unsigned int			current_random_seed(void)	{ return get_vars().m_current_random_seed; }	//!< 乱数シード
	static int					get_repeat_count(void)		{ return get_vars().m_repeat_count; }			//!< 繰り返し回数
	static const char*			get_report_filepath(void)	{ return get_vars().m_report_file.c_str(); }	//!< 出力xmlパス
	static const char*			test_filter(void)			{ return get_vars().m_test_filter.c_str(); }	//!< フィルター文字列

	/** @private */
	static TestEventListeners&	event_listeners(void)	{ return get_vars().m_event_listeners; }
	/** @private */
	static TestPartResultReporterInterface* GetGlobalTestPartResultReporter(void)		{ return get_vars().m_testpartresult_reporter; }
	/** @private */
	static void SetGlobalTestPartResultReporter(TestPartResultReporterInterface* ptr)	{ get_vars().m_testpartresult_reporter = ptr; }

private:
	static iuEnvironmentList&	environments(void)		{ return get_vars().m_environment_list; }

public:
	/**
	 * @brief	グローバル環境セットクラスの追加
	 * @param [in]	env	= 環境セットクラスアドレス
	 * @return	登録されたクラスアドレス
	*/
	static Environment* AddGlobalTestEnvironment(Environment* env)
	{
		if( env == NULL ) return NULL;
		environments().push_back(env);
		return env;
	}

private:
	/**
	 * @brief	環境セットクラスの解放
	*/
	static void ReleaseGlobalTestEnvironment(void)
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
	 * @brief	コマンドライン引数の解析
	*/
	template<typename CharType>
	static void	ParseCommandLine(int* pargc, CharType** argv)
	{
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
	 * @brief	コマンドライン引数の解析(vector)
	*/
	template<typename CharType>
	static void	ParseCommandLine(::std::vector< ::std::basic_string<CharType> >& argv)
	{
		for( typename ::std::vector< ::std::basic_string<CharType> >::iterator it = argv.begin(); it != argv.end(); )
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
private:
	template<typename CharType>
	static bool	ParseCommandLineElem(CharType* argv)
	{
		typedef typename detail::mbs_ptr<CharType>::type formatter;

		bool find = false;
		formatter argv_format;
		const char* str = argv_format.ptr(argv);
		if( *str == '-' )
		{
			find = true;
			++str;
			if( *str == '-' )
			{
				++str;
				bool iuoption = false;
				{
					const char* const base_str = str;
					if( *str == 'g' ) 
					{
						++str;
						iuoption = true;
					}
					if(*str == 'i' && *(str+1) == 'u' )
					{
						str += 2;
						iuoption = true;
					}
					const char option_prefix[] = "test_";
					for( int i=0, size=sizeof(option_prefix)/sizeof(option_prefix[0])-1; i < size; ++i, ++str )
					{
						if( *str != option_prefix[i] )
						{
							iuoption = false;
							str = base_str;
							break;
						}
					}
				}
				if( iuoption )
				{
					// --iutest_*
					if( strstr(str, "output") == str )
					{
						find = ParseOutputOption(ParseOptionSettingStr(str));
					}
					else if( detail::IsStringEqual(str, "list_tests") )
					{
						TestFlag::SetFlag(TestFlag::SHOW_TESTS_LIST);
					}
					else if( strstr(str, "color") == str )
					{
						find = ParseColorOption(ParseOptionSettingStr(str));
					}
					else if( detail::IsStringEqual(str, "shuffle") )
					{
						TestFlag::SetFlag(TestFlag::SHUFFLE_TESTS);
					}
					else if( strstr(str, "random_seed") == str )
					{
						const char* opt = ParseOptionSettingStr(str);
						if( opt != NULL )
						{
							char* end = NULL;
							long seed = strtol(opt, &end, 0);
							init_random(static_cast<unsigned int>(seed));
						}
						else
						{
							find = false;
						}
					}
					else if( detail::IsStringEqual(str, "also_run_disabled_tests") )
					{
						TestFlag::SetFlag(TestFlag::RUN_DISABLED_TESTS);
					}
					else if( strstr(str, "break_on_failure") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::BREAK_ON_FAILURE, 1);
					}
					else if( strstr(str, "catch_exceptions") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::CATCH_EXCEPTION, -1);
					}
					else if( strstr(str, "throw_on_failure") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::THROW_ON_FAILURE, 1);
					}
					else if( strstr(str, "print_time") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::PRINT_TIME, -1);
					}
					else if( strstr(str, "repeat") == str )
					{
						const char* opt = ParseOptionSettingStr(str);
						if( opt != NULL )
						{
							char* end = NULL;
							long count = strtol(opt, &end, 0);
							set_repeat_count(static_cast<int>(count));
						}
						else
						{
							find = false;
						}
					}
					else if( strstr(str, "filter") == str )
					{
						const char* opt = ParseOptionSettingStr(str);
						if( opt != NULL )
						{
							set_test_filter(opt);
						}
					}
					else
					{
						find = false;
					}
					if( !find )
					{
						// 該当するオプションがない場合はヘルプ表示
						TestFlag::SetFlag(TestFlag::SHOW_HELP);
					}
				}
				else if( detail::IsStringEqual(str, "help") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_HELP);
				}
				else if( detail::IsStringEqual(str, "version") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_VERSION);
				}
				else if( detail::IsStringEqual(str, "feature") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_FEATURE);
				}
				else
				{
					find = false;
				}
			}
			else
			{
				if( detail::IsStringEqual(str, "v") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_VERSION);
				}
				else if( detail::IsStringEqual(str, "h")
					|| detail::IsStringEqual(str, "?") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_HELP);
				}
				else
				{
					find = false;
				}
			}
		}
		return find;
	}

private:
	/**
	 * @brief	環境変数から設定構築
	*/
	static void LoadEnviromentVariable(void)
	{
		{
			int var = 0;
			if( detail::GetEnvironmentInt("IUTEST_ALSO_RUN_DISABLED_TESTS", var) )
			{
				TestFlag::SetFlag(TestFlag::RUN_DISABLED_TESTS
					, var ? TestFlag::MASK : ~(TestFlag::RUN_DISABLED_TESTS) );
			}
			if( detail::GetEnvironmentInt("IUTEST_SHUFFLE", var) )
			{
				TestFlag::SetFlag(TestFlag::SHUFFLE_TESTS
					, var ? TestFlag::MASK : ~(TestFlag::SHUFFLE_TESTS) );
			}
			if( detail::GetEnvironmentInt("IUTEST_RANDOM_SEED", var) )
			{
				init_random((unsigned int)var);
			}
			if( detail::GetEnvironmentInt("IUTEST_CATCH_EXCEPTIONS", var) )
			{
				TestFlag::SetFlag(TestFlag::CATCH_EXCEPTION
					, var ? TestFlag::MASK : ~(TestFlag::CATCH_EXCEPTION) );
			}
			if( detail::GetEnvironmentInt("IUTEST_BREAK_ON_FAILURE", var) )
			{
				TestFlag::SetFlag(TestFlag::BREAK_ON_FAILURE
					, var ? TestFlag::MASK : ~(TestFlag::BREAK_ON_FAILURE) );
			}
			if( detail::GetEnvironmentInt("IUTEST_THROW_ON_FAILURE", var) )
			{
				TestFlag::SetFlag(TestFlag::THROW_ON_FAILURE
					, var ? TestFlag::MASK : ~(TestFlag::THROW_ON_FAILURE) );
			}
			if( detail::GetEnvironmentInt("IUTEST_PRINT_TIME", var) )
			{
				TestFlag::SetFlag(TestFlag::PRINT_TIME
					, var ? TestFlag::MASK : ~(TestFlag::PRINT_TIME) );
			}
			if( detail::GetEnvironmentInt("IUTEST_REPEAT", var) )
			{
				set_repeat_count(var);
			}
		}
		{
			char var[128] = {0};
			if( detail::GetEnvironmentVariable("IUTEST_COLOR", var) )
			{
				ParseColorOption(var);
			}
		}
		{
			char path[260+32] = {0};
			if( detail::GetEnvironmentVariable("IUTEST_OUTPUT", path) )
			{
				ParseOutputOption(path);
			}
			if( detail::GetEnvironmentVariable("IUTEST_FILTER", path) )
			{
				set_test_filter(path);
			}
		}
	}

private:
	/**
	 * @brief	セットアップ
	*/
	static void	SetUp(void)
	{
		unsigned int seed = get_random_seed();
		if( seed == 0 )
		{
			seed = detail::GetIndefiniteValue();
		}
		get_vars().m_current_random_seed = seed;
		genrand().init(seed);
	}

private:
	/**
	 * @brief	乱数シードの設定
	*/
	static void	init_random(unsigned int seed)
	{
		get_vars().m_random_seed = seed;
	}

	/**
	 * @brief	繰り返し回数の設定
	*/
	static void	set_repeat_count(int count)
	{
		get_vars().m_repeat_count = count;
	}

	/**
	 * @brief	フィルター文字列の設定
	*/
	static void	set_test_filter(const char* str)
	{
		get_vars().m_test_filter = str;
		TestFlag::SetFlag(TestFlag::FILTERING_TESTS);
	}

private:
	/**
	 * @brief	オプション文字列から設定文字列の先頭アドレスを取得
	*/
	static inline const char* ParseOptionSettingStr(const char* opt)
	{
		const char* eq = strchr(opt, '=');
		if( eq == NULL ) return eq;
		return eq+1;
	}
	/**
	 * @brief	IUTEST_COLOR オプションの判定
	*/
	static bool	ParseColorOption(const char* option)
	{
		if( option == NULL ) return false;

		if( IsYes(option) )
		{
			TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_ON, ~TestFlag::CONSOLE_COLOR_OFF);
		}
		else if( IsNo(option) )
		{
			TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_OFF, ~TestFlag::CONSOLE_COLOR_ON);
		}
		else if( detail::IsStringCaseEqual(option, "auto") )
		{
			// auto
			TestFlag::SetFlag(0, ~(TestFlag::CONSOLE_COLOR_ON|TestFlag::CONSOLE_COLOR_OFF));
		}
		else if( detail::IsStringCaseEqual(option, "ansi") )
		{
			// ansi
			TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_ON|TestFlag::CONSOLE_COLOR_ANSI, ~TestFlag::CONSOLE_COLOR_OFF);
		}
		else 
		{
			return false;
		}
		return true;
	}

	/**
	 * @brief	IUTEST_OUTPUT オプションの判定
	*/
	static bool	ParseOutputOption(const char* option)
	{
		if( option == NULL ) return false;
		if( strstr(option, "xml") != NULL )
		{
			TestFlag::SetFlag(TestFlag::OUTPUT_XML_REPORT);
		}
		else
		{
			return false;
		}
		const char* file = strchr(option+3, ':');
		if( file != NULL )
		{
			get_vars().m_report_file = file+1;
		}
		return true;
	}

	/**
	 * @brief	yes オプションか no オプションかの判定
	 * @param [in]	option	= オプション文字列
	 * @param [in]	flag	= フラグ
	 * @param [in]	def		= 引数なしの場合のオペレーション
	 * @return	成否
	*/
	static bool ParseYesNoFlagOption(const char* option, TestFlag::Kind flag, int def)
	{
		const char* str = ParseOptionSettingStr(option);
		int yesno = str != NULL ? ParseYesNoOption(str) : def;
		if( yesno < 0 )
		{
			return false;
		}
		TestFlag::SetFlag(flag, yesno ? TestFlag::MASK : ~(flag) );
		return true;
	}

	/**
	 * @brief	yes オプションか no オプションかの判定
	 * @param [in]	option	= オプション文字列
	 * @retval	< 0	= 該当なし
	 * @retval	0	= NO
	 * @retval	> 0 = YES
	*/
	static int ParseYesNoOption(const char* option)
	{
		if( option == NULL ) return -1;
		if( IsYes(option) ) return 1;
		if( IsNo(option) ) return 0;
		return -1;
	}

	/**
	 * @brief	yes オプションか判定
	*/
	static bool IsYes(const char* option)
	{
		if( detail::IsStringCaseEqual(option, "yes")
			|| detail::IsStringCaseEqual(option, "y")
			|| detail::IsStringCaseEqual(option, "on")
			|| detail::IsStringCaseEqual(option, "true")
			|| detail::IsStringCaseEqual(option, "t")
			|| detail::IsStringEqual(option, "1") ) 
		{
			return true;
		}
		return false;
	}
	/**
	 * @brief	no オプションか判定
	*/
	static bool IsNo(const char* option)
	{
		if( detail::IsStringCaseEqual(option, "no")
			|| detail::IsStringCaseEqual(option, "n")
			|| detail::IsStringCaseEqual(option, "off")
			|| detail::IsStringCaseEqual(option, "false")
			|| detail::IsStringCaseEqual(option, "f")
			|| detail::IsStringEqual(option, "0") ) 
		{
			return true;
		}
		return false;
	}

private:
	friend class UnitTest;
};

}	// end of namespace iutest

#endif
