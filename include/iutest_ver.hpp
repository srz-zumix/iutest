﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_ver.hpp
 * @brief       iris unit test version
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_VER_HPP_D65CB7A7_D2AD_40FE_8F5F_8FBF376A0010_
#define INCG_IRIS_IUTEST_VER_HPP_D65CB7A7_D2AD_40FE_8F5F_8FBF376A0010_

//======================================================================
// define
#define IUTEST_VER          0x01179902u     //!< iutest version 1.17.99.2
#define IUTEST_MAJORVER     0x01u           //!< Major Version
#define IUTEST_MINORVER     0x17u           //!< Minor Version
#define IUTEST_MICROVER     0x99u           //!< Micro Version
#define IUTEST_REVISION     0x02u           //!< Revision

#define IUTEST_BUILD        IUTEST_MICROVER //!< @deprecated

/**
 * @mainpage
 * @sa  @b  ProjectHome \n
 *          OSDN        : https://osdn.jp/projects/iutest/ \n
 *          github      : https://github.com/srz-zumix/iutest \n
 *          google group: https://groups.google.com/forum/?fromgroups#!forum/g-iutest \n
 *
 * @par     copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License.
 *
 * @par     LICENSE

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: \n
 \n
* Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer. \n
 \n
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution. \n
 \n
* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission. \n
 \n
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @page    cmdline     コマンドラインオプション
 * @par     Command Line Options
 <table>
   <tr><td>--help, -h                        </td><td></td><td>Generate help message.</td></tr>
   <tr><td>--iutest_output                   </td><td>xml|junit[:path]</td><td>Path of xml report.</td></tr>
   <tr><td>--iutest_list_tests               </td><td></td><td>List up tests.</td></tr>
   <tr><td>--iutest_list_tests_with_where    </td><td></td><td>List up tests with where.</td></tr>
   <tr><td>--iutest_color                    </td><td>&lt;yes|no|auto|ansi&gt;</td><td>Console color enable.</td></tr>
   <tr><td>--iutest_flagfile                 </td><td>&lt;file&gt;</td><td>Set the flag from the file.</td></tr>
   <tr><td>--iutest_filter                   </td><td>&lt;filter&gt;</td><td>Select the test run.</td></tr>
   <tr><td>--iutest_shuffle                  </td><td></td><td>Do shuffle test.</td></tr>
   <tr><td>--iutest_random_seed              </td><td>&lt;seed&gt;</td><td>Set random seed.</td></tr>
   <tr><td>--iutest_also_run_disabled_tests  </td><td></td><td>Run disabled tests.</td></tr>
   <tr><td>--iutest_break_on_failure         </td><td>[yes|no]</td><td>When that failed to break.</td></tr>
   <tr><td>--iutest_throw_on_failure         </td><td>[yes|no]</td><td>When that failed to throw.</td></tr>
   <tr><td>--iutest_warning_into_error       </td><td>[yes|no]</td><td>Make warnings into error.</td></tr>
   <tr><td>--iutest_catch_exceptions         </td><td>&lt;yes|no&gt;</td><td>Catch exceptions enable.</td></tr>
   <tr><td>--iutest_print_time               </td><td>&lt;yes|no&gt;</td><td>Setting the display of elapsed time.</td></tr>
   <tr><td>--iutest_repeat                   </td><td>&lt;count&gt;</td><td>Set the number of repetitions of the test. use a negative count to repeat forever.</td></tr>
   <tr><td>--iutest_stream_result_to         </td><td>&lt;host:port&gt;</td><td>Set stream test results server.</td></tr>
   <tr><td>--iutest_file_location            </td><td>&lt;auto|vs|gcc&gt;</td><td>Format file location messages.</td></tr>
   <tr><td>--iutest_default_package_name     </td><td>[name]</td><td>Set default root package name.</td></tr>
   <tr><td>--iutest_locale_ctype             </td><td>[name]</td><td>setlocate(LC_CTYPE, [name]).</td></tr>
   <tr><td>--verbose                         </td><td></td><td>Verbose option.</td></tr>
   <tr><td>--feature                         </td><td></td><td>Show iutest feature.</td></tr>
   <tr><td>--version, -v                     </td><td></td><td>Show iutest version.</td></tr>
 </table>
  * yes or no option can use "yes|y|on|true|t|1|no|n|off|false|f|0"
*/

/**
 * @page    environmentoptions  環境変数オプション
 * @par     Environment variable Options
 <table>
   <tr><td>IUTEST_OUTPUT=xml|junit[:path]  </td><td>Path of xml report.</td></tr>
   <tr><td>IUTEST_COLOR=yes|no|auto        </td><td>Console color enable.</td></tr>
   <tr><td>IUTEST_FLAGFILE=file            </td><td>Set the flag from the file.</td></tr>
   <tr><td>IUTEST_FILTER=filter            </td><td>Select the test run.</td></tr>
   <tr><td>IUTEST_SHUFFLE                  </td><td>Do shuffle test.</td></tr>
   <tr><td>IUTEST_RANDOM_SEED=seed         </td><td>Set random seed.</td></tr>
   <tr><td>IUTEST_ALSO_RUN_DISABLED_TESTS  </td><td>Run disabled tests.</td></tr>
   <tr><td>IUTEST_BREAK_ON_FAILURE=0|1     </td><td>When that failed to break.</td></tr>
   <tr><td>IUTEST_THROW_ON_FAILURE=0|1     </td><td>When that failed to throw.</td></tr>
   <tr><td>IUTEST_WARNING_INTO_ERROR=0|1   </td><td>Make warnings into error.</td></tr>
   <tr><td>IUTEST_CATCH_EXCEPTIONS=0|1     </td><td>Catch exceptions enable.</td></tr>
   <tr><td>IUTEST_PRINT_TIME=0|1           </td><td>Setting the display of elapsed time.</td></tr>
   <tr><td>IUTEST_REPEAT=count             </td><td>Set the number of repetitions of the test.</td></tr>
   <tr><td>IUTEST_FILE_LOCATION=auto|vs|gcc</td><td>Format file location messages.</td></tr>
   <tr><td>IUTEST_ROOT_PACKAGE_NAME=[name] </td><td>Set root package name.</td></tr>
 </table>
*/

/**
 * @page    changelog   変更履歴
 * @par     Changes
 <ul>
  <li>v1.18.0.0
    <ul>
      <li>TestCase の別名 TestSuite に対応（iutest はどちらもサポートし続けます）</li>
      <li>例外発生時にも SCOPED_TRACE のメッセージを出力するように変更</li>
      <li>空のテストスイート名・テスト名に static_assert を追加</li>
      <li>GoogleTest の GTEST_REMOVE_LEGACY_TEST_CASEAPI_ に対応</li>
    </ul>
  </li>
  <li>v1.17.1.0
    <ul>
      <li>GTEST_SKIP 対応</li>
      <li>IUTEST_*_NE_RANGE アサーションを追加</li>
      <li>IUTEST_*_NE_COLLECTIONS アサーションを追加</li>
      <li>::std::wstring_view / ::std::u16string_view / ::std::u32string_view 対応</li>
      <li>アサーションに operator &lt;&lt; したときの出力を PrintToString したものと同じになるように変更</li>
      <li>テストをリピートした際のレポート出力ファイル名の書式を printf 書式から {I} に変更({I} にリピート回数が置換されます)</li>
      <li>iuwandbox: Wandbox 向けにサイズ圧縮したヘッダーをデフォルトで使用するように変更</li>
      <li>iuwandbox: 上記に伴いフルバージョンのヘッダーを使うオプション(--no-iutest-use-wandbox-min)を追加</li>
      <li>deprecated: iuwandbox: --iutest-use-wandbox-min</li>
      <li>Python2 のサポート終了</li>
      <li>C++20 で削除された basic_ostream::operator &lt;&lt; に対応</li>
      <li>IUTEST_AP が同じ名前空間に複数定義できない問題を修正</li>
      <li>Google Test 旧バージョンとの互換性を修正</li>
    </ul>
  </li>
  <li>v1.17.0.0
    <ul>
      <li>大きな配列/コンテナ/オブジェクトの pinter を修正</li>
      <li>::std::string_view 対応</li>
      <li>::std::filesystem 対応</li>
      <li>FreeBSD 対応</li>
      <li>ALMOST_EQ アサーション を追加</li>
      <li>--iutest_locale_ctype オプションを追加</li>
      <li>setlocale(LC_CTYPE, IUTEST_FLAG(locale_ctype)) をテスト実行開始時に行うように修正</li>
      <li>iutest_main で setlocale していたものを廃止</li>
      <li>Visual Studio 2019 対応</li>
      <li>junit xml 出力で出力するテストが 0 だった場合にファイル書き出ししないように修正</li>
      <li>CSV パラメータ生成でファイルオープン失敗した場合の警告レベルを FATAL から WARNING に変更/li>
      <li>CSV パラメータ生成で要素がなかった場合に WARNING 出力</li>
      <li>deprecated: IUTEST_USE_OWN_LIST</li>
      <li>deprecated: codecvt</li>
    </ul>
  </li>
  <li>v1.16.7.0
    <ul>
      <li>古い google mock の互換性エラー修正</li>
    </ul>
  </li>
  <li>v1.16.6.0
    <ul>
      <li>Matcher に (NanSensitive)FloatNear/DoubleNear を追加</li>
      <li>Matcher に template 版の浮動小数点数比較を追加・(NanSensitive)FloatingPointEq/FloatingPointNear</li>
      <li>long double に対応</li>
      <li>iuwandbox: -D__WANDBOX__ コンパイラーオプションを必ずつけるように変更</li>
      <li>iuwandbox: dryrun オプションが失敗を返す問題を修正</li>
      <li>Fixed: いくつかのコンパイラー警告を修正</li>
    </ul>
  </li>
  <li>v1.16.5.0
    <ul>
      <li>IUTEST_*_NULL, IUTEST_*_NOTNULL を可変長引数対応</li>
      <li>IUTEST_*_HRESULT_SUCCEEDED, IUTEST_*_HRESULT_FAILED を可変長引数対応</li>
      <li>ad_hoc_testresult の取得関数名を ad_hoc_test_result に変更</li>
      <li>compatibility: iuutil に ad_hoc_testresult の取得関数を追加</li>
      <li>iuwandbox で std-cxx の指定をするとオプションチェックで失敗する不具合を修正</li>
    </ul>
  </li>
  <li>v1.16.4.0
    <ul>
      <li>deprecated: IUTEST_IGNORE 関係を非推奨にしました</li>
      <li>コンパイルエラーの修正</li>
    </ul>
  </li>
  <li>v1.16.3.0
    <ul>
      <li>IUTEST_ASSERT,IUTEST_EXPECT の Variadic 対応</li>
      <li>gtest 各バージョンの互換性の不備を修正</li>
    </ul>
  </li>
  <li>v1.16.2.0
    <ul>
      <li>警告をエラーとするオプション(--iutest_warning_into_error)を追加</li>
    </ul>
  </li>
  <li>v1.16.1.0
    <ul>
      <li>IUTEST_BUILD を非推奨に変更し、IUTEST_MICROVER を追加</li>
      <li>XML_OUTPUT_FILE 環境変数に対応</li>
    </ul>
  </li>
  <li>v1.16.0.0
    <ul>
      <li>iuwandbox で複数ソースファイルに対応</li>
      <li>例外アサーションで構造化例外（SEH）もキャッチできるように対応</li>
      <li>--iutest_filter のルールを Google Test 互換に修正</li>
    </ul>
  </li>
  <li>v1.15.2.0
    <ul>
      <li>IUTEST_TYPED_TEST_P に対して friend できるように IUTEST_FRIEND_TYPED_TEST_P_DECLARATION/IUTEST_FRIEND_TYPED_TEST_P を追加</li>
      <li>iuwandbox に --sprout/--msgpack オプションを追加</li>
      <li>iuwandbox の --list_compiler オプションでバージョンを出力しないように変更。--verbose を付けると以前と同じバージョン付きの出力をする</li>
      <li>iuwandbox で --expand_include オプションを付けなかった場合の include されたファイルの対応を修正</li>
      <li>iuwandbox の --boost オプションが Python3 で使えない問題を修正</li>
      <li>iuwandbox で未定義オプションを指定した場合にエラーにならない問題を修正</li>
      <li>IUTEST(A, B_C) と IUTEST(A_B, C) が名前の衝突でコンパイルエラーになる問題を修正</li>
      <li>色付きコンソールの自動判定を修正</li>
      <li>deprecated: IUTEST_HAS_STRSTREAM は将来的に削除されます</li>
      <li>deprecated: IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE は将来的に削除されます</li>
    </ul>
  </li>
  <li>v1.15.1.0
    <ul>
      <li>stderr に xml の内容を出力するリスナーを追加</li>
      <li>iuwandbox に xml 出力オプション(--xml, --junit)を追加</li>
      <li>--help|spec|feature|version を同時に使用可能に変更 (e.g. --spec --feature)</li>
      <li>CSV パラメータのパス解決処理を修正</li>
      <li>fused-src 生成ツールを修正</li>
    </ul>
  </li>
  <li>v1.15.0.0
    <ul>
      <li>--iutest_output オプションで repeat 回数のフォーマットに対応 e.g. --iutest_output=xml:test_%d.xml</li>
      <li>CSV ファイルから値のパラメータ作成に対応</li>
      <li>IUTEST_ALIAS_TESTNAME_F,IUTEST_JAPANESE_NAME_F の引数の順番を変更</li>
      <li>値のパラメータ化テストのテスト名指定方法を変更</li>
      <li>値のパラメータ化テストのテスト名指定方法の Google Test 互換対応</li>
      <li>IUTEST_TYPED_TEST_APPEND_TYPENAME を IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME に変更</li>
    </ul>
  </li>
  <li>v1.14.0.0
    <ul>
      <li>::iutest::Range を Enum に対応</li>
      <li>大幅なリファクタリング</li>
    </ul>
  </li>
  <li>v1.13.0.0
    <ul>
      <li>--iutest_flagfile コマンドラインオプションに対応</li>
      <li>MFC コンテナ対応</li>
      <li>値のパラメータ化テストのテスト名指定に対応</li>
      <li>型付けテストのテスト名に型名をつけるオプションマクロ (IUTEST_TYPED_TEST_APPEND_TYPENAME) を追加</li>
      <li>非ヨーダ記法を提供するヘッダーを追加</li>
      <li>Visual Studio 2015 対応</li>
      <li>tr1/iutest_vc_unittest.hpp を修正</li>
    </ul>
  </li>
  <li>v1.12.0.0
    <ul>
      <li>IUTEST_PACKAGE v2 (多重定義制限の撤廃)</li>
      <li>Matcher に MatchesRegex,ContainsRegex を追加</li>
      <li>Matcher に ElementsAreArrayForward を追加</li>
      <li>ElementsAreArray で要素数の一致チェックを行うように変更（以前までの ElementsAreArray は ElementsAreArrayForward に変更）</li>
      <li>IUTEST_*_MATCHES_REGEXEQ,NE、IUTEST_*_CONTAINS_REGEXEQ,NE 追加</li>
      <li>--iutest_filter=@filter.txt のようにファイルからフィルター指定できるように対応</li>
      <li>IUTEST_MAKE_PEEP で関数ポインターの typedef をしなくてもいいように修正</li>
      <li>quick_exit 対応</li>
      <li>IUTEST_REPORT_SKIPPED を IUTEST_HAS_REPORT_SKIPPED に変更</li>
      <li>Visual Studio 2015 Preview 対応</li>
      <li>twilio 対応</li>
    </ul>
  </li>
  <li>v1.11.1.0
    <ul>
      <li>IUTEST_REGISTER_TYPED_TEST_CASE_P でテスト名の後ろの空白が名前に含まれてしまう不具合を修正</li>
    </ul>
  </li>
  <li>v1.11.0.0
    <ul>
      <li>fused-src 対応</li>
      <li>Wandbox 対応</li>
      <li>Matcher に Eq,Ne,Le,Lt,Ge,Gt,IsNull,NotNull,TypeEq を追加</li>
      <li>Matcher に StrEq,StrNe,StrCaseEq,StrCaseNe,HasSubstr を追加</li>
      <li>Matcher に FloatEq,DoubleEq,NanSensitiveFloatEq,NanSensitiveDoubleEq を追加</li>
      <li>Matcher に Not,ResultOf,Pointee を追加</li>
      <li>コンテナMatcher に Each,ContainerEq,Pointwise,At,IsEmpty,SizeIs,ElementsAre,ElementsAreArray を追加</li>
      <li>コンテナMatcher の Contains から HasSubstr 機能を削除</li>
      <li>コンテナMatcher の条件に Matcher を使えるように修正</li>
      <li>メンバーMatcher に Key,Pair,Field を追加</li>
      <li>ワイルドカードMatcher A,_ を追加</li>
      <li>IUTEST_*_FLOAT_EQ,DOUBLE_EQ で NAN の比較が真を返す不具合を修正</li>
      <li>Visual Studio 2015 Preview 対応</li>
    </ul>
  </li>
  <li>v1.10.0.0
    <ul>
      <li>--verbose コマンドラインオプションを追加</li>
      <li>--iutest_default_package_name コマンドラインオプションを追加</li>
      <li>operatoer == のないオブジェクトの IUTEST_*_EQ 対応</li>
      <li>operatoer != のないオブジェクトの IUTEST_*_NE 対応</li>
      <li>junit xml 出力に対応（--iutest_output=junit）</li>
      <li>tuple の要素を取得する GetParam template 関数を追加</li>
      <li>IUTEST_FLAG(ostream_formatter) を追加</li>
      <li>tuple 要素を取得する GetParam tempalate 関数を追加</li>
      <li>ARM対応</li>
      <li>--iutest_break_on_failure でスキップや警告でも停止していた不具合を修正</li>
      <li>Visual Studio 14 CTP 3 対応</li>
    </ul>
  </li>
  <li>v1.9.1.0
    <ul>
      <li>IUTEST_P,IUTEST_TYPED_TEST_P で DISABLED_ 指定が機能しない問題を修正</li>
      <li>TestFixutre を定義しなくても IUTEST_P が使えるように対応</li>
      <li>Visual Studio 14 CTP 対応</li>
    </ul>
  </li>
  <li>v1.9.0.0
    <ul>
      <li>IUTEST_*_THAT 追加</li>
      <li>式アサーション追加（IUTEST_ASSERT, IUTEST_EXPECT, IUTEST_INFORM, IUTEST_ASSUME）</li>
      <li>式アサーション追加（IUTEST_*_NOT）</li>
      <li>IUTEST_USE_MAIN 追加(main 関数定義 config)</li>
      <li>IUTEST_ASSERT を IUTEST_ASSERT_EXIT に変更</li>
    </ul>
  </li>
  <li>v1.8.1.0
    <ul>
      <li>SetUp/SetUpTestCase での SKIP/ASSUME に対応</li>
      <li>MAC OS 判定、ビルドエラー修正 (thanks to mogemimi for the pull request)</li>
      <li>--iutest_filter で : 区切りの複数条件指定が正しく動作しない不具合を修正</li>
      <li>--iutest_list_tests_with_where で値のパラメータも出力するように修正</li>
      <li>バグ修正</li>
    </ul>
  </li>
  <li>v1.8.0.0
    <ul>
      <li>IUTEST_USE_THROW_ON_ASSERT_FAILURE を IUTEST_USE_THROW_ON_ASSERTION_FAILURE に変更</li>
      <li>IUTEST_USE_THROW_ON_ASSERTION_FAILURE を指定した場合 SKIP や ASSUME も例外を投げるように変更</li>
      <li>IUTEST_*_EQ_RANGE を追加</li>
      <li>IUTEST_*_STRIN,IUTEST_*_STRNOTIN を追加</li>
      <li>IUTEST_FLAG(output) に対応</li>
      <li>IUTEST_*_NO_FAILURE の gtest モード対応</li>
      <li>AVR 対応</li>
      <li>IUTEST_*_NO_FAILURE が警告やスキップを失敗と判断しないように変更</li>
      <li>IUTEST_*_TRUE/FALSE を可変長対応</li>
      <li>フィクスチャークラス名を IUTEST_TEST マクロのテストケース名に使用した場合にエラーになるように修正(MSVC拡張)</li>
      <li>パッケージ内の値のパラメータ化テストのテストケース名が pkg.prefix/testcase となるように変更</li>
      <li>Visual C++ Compiler November 2013 CTP 対応</li>
      <li>リスナーのセットアップ関数を変更</li>
      <li>IUTEST_SCOPED_PEEP,IUTEST_MAKE_SCOPED_PEEP を廃止</li>
      <li>ソースコードのエンコーディングを UTF8 BOM 有りに変更</li>
      <li>バグ修正</li>
    </ul>
  </li>
  <li>v1.7.0.0
    <ul>
      <li>テストフィクスチャの定義が省ける値のパラメータ化テストを追加(IUTEST_AP,IUTEST_INSTANTIATE_TEST_CASE_AP)</li>
      <li>値のパラメータを operator + で連結できるように修正</li>
      <li>値のパラメータを連結する ::iutest::Concat を追加</li>
      <li>IUTEST_TYPED_TEST,IUTEST_TYPED_TEST_P の別名マクロを追加(IUTEST_T, IUTEST_TP)</li>
      <li>xml 出力に timestamp を追加</li>
      <li>前提条件の検証用マクロ IUTEST_ASSUME_* を追加</li>
      <li>SSTP 通知リスナーを追加</li>
      <li>Windows 向けメニュー登録ユーティリティを追加</li>
      <li>値のパラメータ化テストが日本語テスト名に対応していなかった問題を修正</li>
      <li>ビルドエラー修正</li>
    </ul>
  </li>
  <li>v1.6.1.0
    <ul>
      <li>Visual Studio 2013 Preview 対応</li>
    </ul>
  </li>
  <li>v1.6.0.0
    <ul>
      <li>stream result 対応</li>
      <li>gtest モードで AssertionReturn が使えるように対応</li>
      <li>AssertionReturn の仕様変更</li>
      <li>::iutest::RandomGenerator を追加</li>
      <li>::iutest::RandomValues で乱数シードを指定できるように修正</li>
      <li>spi で TestPartResult 数をチェックするように変更</li>
      <li>spi で substr でメッセージをチェックするように変更</li>
      <li>ASSERT_*, EXPECT_*, INFORM_* マクロのストリームに iomanip が使用できなかった問題を修正</li>
    </ul>
  </li>
  <li>v1.5.0.4
    <ul>
      <li>--iutest_filter でマッチしなかったテストは XML に出力しないように変更</li>
      <li>XML 出力の skipped にメッセージを出力するように修正</li>
      <li>--iutest_filter にマッチしたテスト数が取得できるように修正</li>
      <li>デフォルトログ出力を --iutest_filter の結果を考慮した出力に変更</li>
    </ul>
  </li>
  <li>v1.5.0.0
    <ul>
      <li>日本語テスト名に対応</li>
      <li>SetUpTestCase などのテスト実行中以外でも RecordProperty できるように変更</li>
      <li>iutest_list_tests_with_where コマンドラインオプションを追加</li>
      <li>IUTEST_TYPED_TEST_CASE,IUTEST_TYPED_TEST_CASE_P に直接 ::iutest::Types を書けるように修正/li>
      <li>誤った使い方をした場合にエラーを出力するように修正</li>
      <li>IUTEST_PEEP の仕様変更</li>
      <li>MiniDump 出力に対応</li>
      <li>noexcept に対応</li>
    </ul>
  </li>
  <li>v1.4.0.0
    <ul>
      <li>IUTEST_ASSERT_* で void 以外の戻り値を返せるように修正(::iutest::AssertionReturn)</li>
      <li>::iutest::Types メンバーに型を取得する get を追加</li>
      <li>::iutest::ValuesIn を initializer_list に対応</li>
      <li>値のパラメータ化テスト向けに任意のパラメータを生成する ValuesGen を追加</li>
      <li>値のパラメータ化テスト向けに乱数パラメータを生成する RandomValues を追加</li>
      <li>extern template 対応</li>
      <li>C++11 random ヘッダーが使用できるとき distribution を使うように変更</li>
      <li>コード分析ツールのためのコードの追加情報(__analysis_assume) を IUTEST_*_NULL と IUTEST_*_NOTNULL に追加(MSVC)</li>
      <li>古いコンパイラへの対応</li>
    </ul>
  </li>
  <li>v1.3.1.0
    <ul>
      <li>IUTEST_SKIP したときのログを追加</li>
      <li>IUTEST_SKIP() << "message" に対応</li>
      <li>スキップしたテストのログ出力を修正</li>
      <li>コンパイルの通らないテストコードを許可するテスト生成マクロ(*_IGNORE)を追加</li>
    </ul>
  </li>
  <li>v1.3.0.1
    <ul>
      <li>IUTEST_THROW_ON_ASSERT_FAILURE を IUTEST_USE_THROW_ON_ASSERT_FAILURE に変更</li>
      <li>IUTEST_FRIEND_TYPED_TEST を追加</li>
      <li>乱数シードが繰り返し毎に必ず変わるように修正</li>
      <li>GTEST で始まる環境変数に対応</li>
      <li>メッセージ出力のファイル/行のフォーマットを動的に変更できるオプションを追加(--iutest_file_location)</li>
      <li>gtest モードでのビルドエラー修正</li>
      <li>IUTEST_*_FATAL_FAILURE, IUTEST_*_NONFATAL_FAILURE で lambda を利用して変数にアクセスできるように修正</li>
      <li>IUTEST_*_NO_FATAL_FAILURE が FATAL FAILURE のみで判断するように変更</li>
      <li>IUTEST_*_NO_FAILURE を追加</li>
      <li>ライブラリビルド対応</li>
      <li>CUDA 対応</li>
      <li>explicit conversion operator 対応</li>
    </ul>
  </li>
  <li>v1.2.0.2
    <ul>
      <li>IUTEST_*_EQ_COLLECTIONS アサーションを追加</li>
      <li>Android NDK 対応</li>
      <li>名前空間を提供する IUTEST_PACKAGE 追加</li>
      <li>IUTEST_*_STRNE, IUTEST_*_STRCASENE の失敗メッセージを改善</li>
      <li>プログレス出力リスナーを追加</li>
    </ul>
  </li>
  <li>v1.1.2.0
    <ul>
      <li>IUTEST_*_NO_THROW で失敗したときに例外の情報を出力するように修正</li>
      <li>printer 修正</li>
    </ul>
  </li>
  <li>v1.1.1.2
    <ul>
      <li>Windows Mobile でのビルドエラー修正</li>
      <li>IUTEST_HAS_STRINGSTREAM=0 のときのビルドエラー修正</li>
      <li>宣言と定義を分離</li>
    </ul>
  </li>
  <li>v1.1.0.0
    <ul>
      <li>v1.1.0 リリースバージョン</li>
    </ul>
  </li>
  <li>v1.0.7.1
    <ul>
      <li>2バイト文字が xml に正しく出力されない問題を修正（setlocale が必要）</li>
      <li>例外の値を検査する述語アサーションを IUTEST_*_THROW_PRED_FORMAT2 追加</li>
      <li>例外の値を検査するアサーションのログ出力を修正</li>
    </ul>
  </li>
  <li>v1.0.6.0
    <ul>
      <li>例外の値を検査するアサーションを EQ/NE/STREQ/STRCASEEQ に修正</li>
    </ul>
  </li>
  <li>v1.0.5.2
    <ul>
      <li>明示的なスキップとして IUTEST_SKIP を追加</li>
      <li>コンソール出力先を動的に変更できるように修正</li>
      <li>実行すべきテストが実行されなかった場合に失敗を出力するように修正</li>
      <li>Visual Studio UnitTest Framework で IUTEST_P,IUTEST_TYPED_TEST,IUTEST_TYPED_TEST_P が使用できるように修正(tr1)</li>
    </ul>
  </li>
  <li>v1.0.4.0
    <ul>
      <li>iutest::Pairwise を追加</li>
      <li>コードサイズ削減</li>
    </ul>
  </li>
  <li>v1.0.3.1
    <ul>
      <li>ファイルパス操作補助クラスの追加</li>
      <li>IUTEST_*_EQ で if( expected == actual ) から if( actual == expected ) に変更</li>
      <li>IUTEST_*_NO_FATAL_FAILURE に空の statement を与えても警告が出ないように修正</li>
    </ul>
  </li>
  <li>v1.0.2.0
    <ul>
      <li>例外の値を検査するアサーションを追加</li>
    </ul>
  </li>
  <li>v1.0.1.0
    <ul>
      <li>CRT セキュリティ強化関数の失敗時ハンドラに対応</li>
      <li>iutest::InitIrisUnitTest が呼ばれていない場合に警告を出すように変更</li>
    </ul>
  </li>
  <li>v1.0.0.0
    <ul>
      <li>初期リリース</li>
    </ul>
  </li>
  <li>v0.36.2.1
    <ul>
      <li>型名表記をデマングルするように修正</li>
      <li>Google Test を使用した場合でも ::std::string に対応した文字列比較アサーションを使えるように修正</li>
      <li>Google Test を使用した時に wchar_t 版の STRCASENE が使えるように修正</li>
      <li>IUTEST_THROW_ON_ASSERT_FAILURE のデフォルト値を 0 に変更</li>
      <li>IUTEST_THROW_ON_ASSERT_FAILURE が有効なとき IUTEST_*_FATAL_FAILURE が正しく動作しない問題を修正</li>
      <li>spi テスト中に break_on_failure/throw_on_failure で止まらないように修正</li>
      <li>アサーションのみの利用ができるように修正</li>
      <li>グローバルスコープ解決演算子をつけるように修正</li>
      <li>Google Test のバージョン判別を追加</li>
    </ul>
  </li>
  <li>v0.35.0.0
    <ul>
      <li>IUTEST_PMZ, IUTEST_PMZ_F テスト生成マクロを追加</li>
    </ul>
  </li>
  <li>v0.34.0.0
    <ul>
      <li>複数 IUTEST_REGISTER_TYPED_TEST_CASE_P できない不具合を修正</li>
      <li>テストが中断した際に実行されなかったテストを notrun で XML 出力するように修正</li>
      <li>--iutest_break_on_failure を有効にしデバッグなし実行をしたときにダイアログがでないように修正</li>
    </ul>
  </li>
  <li>v0.33.1.0
    <ul>
      <li>iutest::UnitTest::repeat_counter 関数を追加</li>
      <li>OnTestIterationStart/End の iteration 引数が 0 から始まるように修正</li>
      <li>QuietResultPrinter 追加</li>
      <li>util 修正</li>
    </ul>
  </li>
  <li>v0.32.0.0
    <ul>
      <li>iutest::Combine を可変長に対応</li>
      <li>IUTEST_PEEP を cv 修飾されたメンバに対応</li>
      <li>テスト全体、テストケースの経過時間の計測方法を変更</li>
    </ul>
  </li>
  <li>v0.31.2.1
    <ul>
      <li>IUTEST_STATIC_ASSERT 追加</li>
      <li>IUTEST_SCOPED_TRACE で gtest と同じ記法が使えるように修正</li>
      <li>::std::chrono::high_resolution_clock に対応</li>
      <li>iutest::PrintToString でストリーム出力できない型に対応（バイト配列を出力）</li>
      <li>テスト用乱数のシード取得を追加</li>
      <li>IUTEST_*_TRUE|FALSE で iutest::AssertionResult を受け取れるように修正</li>
      <li>--feature オプションを追加</li>
    </ul>
  </li>
  <li>v0.30.1.0
    <ul>
      <li>IUTEST_*_STREQ, IUTEST_*_STRNE を char16_t, char32_t に対応</li>
      <li>一部の環境でワイド文字列の IUTEST_*_STRCASEEQ, IUTEST_*_STRCASENE が大文字小文字が区別されていた不具合を修正</li>
      <li>nullptr に対応</li>
      <li>乱数シードを指定しなかった場合に現在時刻（ミリ秒）からシードを決定するように修正</li>
      <li>シャッフルテスト時に乱数シードをログ出力するように修正</li>
      <li>時刻取得用のコンフィグマクロを追加</li>
      <li>iutest::PrintToString でコンパイルが通らない型があったので修正</li>
      <li>EQ系アサーションのメッセージを修正</li>
    </ul>
  </li>
  <li>v0.29.1.0
    <ul>
      <li>IUTEST_INSTANTIATE_TYPED_TEST_CASE_P の型リストに単一の型(int, char...)を使用できるように修正</li>
      <li>ASSERT マクロが例外を throw するか設定する IUTEST_THROW_ON_ASSERT_FAILURE を追加(default=1) </li>
      <li>--iutest_throw_on_failure 時に致命的ではないエラーで失敗した場合 throw されない不具合を修正</li>
      <li>2回 IUTEST_RUN_ALL_TESTS したときの不具合を修正</li>
      <li>Environment の解放タイミングを修正</li>
    </ul>
  </li>
  <li>v0.28.0.1
    <ul>
      <li>iutest::Environment::SetUp などテスト以外の場所で失敗した場合に対応</li>
    </ul>
  </li>
  <li>v0.27.0.0
    <ul>
      <li>namespace を考慮した IUTEST_MAKE_SCOPED_PEEP, IUTEST_SCOPED_PEEP マクロを追加</li>
      <li>iutest::AddGlobalTestEnvironment を使うとコンパイルエラーになる問題を修正</li>
      <li>iutest::Environment は new して使うように仕様変更</li>
      <li>iutest::Environment の TearDown の実行順序を SetUp の逆順に変更</li>
    </ul>
  </li>
  <li>v0.26.2.0
    <ul>
      <li>RecordProperty でキーが重複した場合に上書きするように修正</li>
      <li>IUTEST_HAS_PEEP, IUTEST_HAS_PEEP_FUNC, IUTEST_PEEP_STATIC_FUNC コンフィグマクロを追加</li>
      <li>iutest_prod.hpp に private メンバーへのアクセス機能を追加(IUTEST_MAKE_PEEP, IUTEST_PEEP_GET etc...)</li>
      <li>IUTEST_FRIEND_TEST 不具合修正</li>
    </ul>
  </li>
  <li>v0.25.2.0
    <ul>
      <li>gtest との互換性がとれていなかった箇所を修正</li>
      <li>IUTEST_FLAG に filter を追加</li>
      <li>オプションに対応してない値を指定したときにヘルプを出力するように修正</li>
      <li>真偽値を指定するコマンドラインオプションを yes|no に対応</li>
      <li>xml 出力に type param, value param を出力するように修正</li>
      <li>RTTI が有効なときに型情報が出力されていなかった問題を修正</li>
      <li>PrintTo を tuple に対応</li>
    </ul>
  </li>
  <li>v0.24.1.0
    <ul>
      <li>Test Anything Protocol ファイル出力リスナーを追加</li>
      <li>DISABLE テストが xml に run として出力される問題を修正</li>
      <li>DISABLE テスト関係の不具合を修正</li>
      <li>IUTEST_REPORT_SKIPPED マクロでデフォルトxml出力リスナーが skip を出力するか選択できるように修正</li>
      <li>0|1 のフラグを渡すオプションに yes|no, y|n, true|false, t|f が使えるように修正</li>
      <li>--iutest_color に ANSI オプションを追加（エスケープシーケンスで色を出力）</li>
      <li>--iutest_color で大文字小文字を区別しないように修正</li>
    </ul>
  </li>
  <li>v0.23.3.0
    <ul>
      <li>IUTEST_*_SAME アサーションを追加</li>
      <li>IUTEST_*_NULL, IUTEST_*_NOTNULL アサーションを追加</li>
      <li>Test Anyting Protocol リスナーの追加</li>
      <li>デフォルトリスナーを解放したときに NULL 参照する不具合を修正</li>
      <li>テストユーティリティのテスト用に iutest_spi.hpp を追加</li>
      <li>IUTEST_*_STR* アサーションで NULL を与えて失敗させると落ちる問題を修正</li>
      <li>--iutest_throw_on_failure=1 でテスト全体を中断するように変更</li>
    </ul>
  </li>
  <li>v0.22.0.1
    <ul>
      <li>Variadic Templates 対応（iutest::Types, iutest::Values）</li>
      <li>Variadic Templates に対応した述語アサーションを追加（IUTEST_*_PRED）</li>
      <li>IUTEST_*_PRED_FORMAT を追加</li>
      <li>--iutest_throw_on_failure=1 としたとき、テスト中に例外が発生するとテスト側で catch されない不具合を修正</li>
    </ul>
  </li>
  <li>v0.21.0.1
    <ul>
      <li>IUTEST_*_NO_FATAL_FAILURE を追加</li>
      <li>STRCASEEQ, STRCASENE が ASSERT でしか使えなかった問題を修正</li>
      <li>IUTEST_*_PRED5 がコンパイルエラーになる問題を修正</li>
      <li>INFORM マクロが一部コンパイルエラーになる問題を修正</li>
      <li>gcc で例外が使えるかどうかの判定が逆になっていた問題を修正</li>
      <li>アサーションマクロに渡した式の出力を修正</li>
      <li>Visual Studio 11 対応</li>
      <li>clang対応</li>
      <li>サンプルソースを修正</li>
    </ul>
  </li>
  <li>v0.20.0.0
    <ul>
      <li>--iutest_filter を使用したときに、失敗テスト出力が出ない不具合を修正</li>
      <li>テスト、テストケース総数の取得関数が、実行してないものを含めていなかった不具合を修正</li>
      <li>テスト、テストケースの実行した（実行予定）総数の取得関数を追加</li>
      <li>IUTEST_*_STREQ 等、文字列比較マクロに NULL を渡した場合に例外が発生する不具合を修正</li>
      <li>IUTEST_RUN_ALL_TESTS の戻り値が間違っていた不具合を修正</li>
    </ul>
  </li>
  <li>v0.19.0.0
    <ul>
      <li>イベントリスナーに RecordProperty 時のイベントを追加</li>
      <li>google mock 対応</li>
      <li>IUTEST_*_STRCASE* に ::std::string をそのまま使えるように修正</li>
      <li>rvalue reference 対応</li>
    </ul>
  </li>
  <li>v0.18.1.1
    <ul>
      <li>On*End イベントは、リストの後ろから実行するように変更</li>
      <li>警告用（失敗にならない）テスト IUTEST_INFORM_*** マクロを追加</li>
      <li>iutest::TestPartResult のインターフェイスを修正</li>
      <li>エラー出力の Actual と Expected が逆になっていた不具合を修正</li>
      <li>char もしくは unsigned char の 0 をメッセージ出力する際にヌル文字にならないように修正</li>
      <li>ターミナルの色つき出力処理を修正</li>
      <li>Visual Studio 以外でビルドした場合の環境変数に対応</li>
      <li>IUTEST_ASSERT_EQ のエラー出力が、 Actual と Expected が逆になっていた不具合を修正</li>
    </ul>
  </li>
  <li>v0.17.0.0
    <ul>
      <li>.h から .hpp に変更</li>
      <li>gtest のコマンドライン引数に対応</li>
      <li>--iutest_filter オプションで *Test*-*TestA* のように除外フィルタをかけたときに正しく動作しない不具合を修正</li>
    </ul>
  </li>
  <li>v0.16.1.1
    <ul>
      <li>iutest::InitIrisUnitTest の vector 対応</li>
      <li>NaCl, ARM 対応</li>
      <li>RecordProperty の template 対応</li>
    </ul>
  </li>
  <li>v0.16.0.2
    <ul>
      <li>型アサーション 対応</li>
      <li>RecoredProperty 対応</li>
      <li>iutest::Combine 対応/li>
      <li>型をパラメータ化したテスト<に対応/li>
      <li>googletest との切り替え対応</li>
      <li>googletest との差異を吸収</li>
      <li>致命的な失敗時に throw するオプション対応( --iutest_throw_on_failure=<0|1> )</li>
      <li>経過時間の出力オプション対応( --iutest_print_time=<0|1> )</li>
      <li>実行するテストの選択オプション対応( --iutest_filter=selection )</li>
      <li>iutest::PrintToString 対応</li>
      <li>IUTEST_FLAG マクロによるオプション指定に対応</li>
      <li>繰り返しオプション対応( --iutest_repeat=count )</li>
      <li>イベントリスナー対応</li>
      <li>グローバル環境セットに対応(iutest::AddGlobalTestEnvironment)</li>
      <li>複合条件テスト用に述語アサーションのヘルパーを追加(iuutil::CmpHelperOR)</li>
      <li>型付けテスト対応</li>
      <li>テストに乱数生成機能を追加( genrand )</li>
      <li>環境変数でのテストオプション指定に対応</li>
      <li>DISABLEDテスト実行オプション対応( --iutest_also_run_disabled_tests )</li>
      <li>例外キャッチオプション対応( --iutest_catch_exceptions=<0|1> )</li>
      <li>失敗時ブレークオプション対応( --iutest_break_on_failure )</li>
      <li>シャッフルテスト対応</li>
      <li>出力カラーオプション対応( --iutest_color=<yes|no|auto> )</li>
      <li>ヘルプオプション対応( --help )</li>
      <li>パラメータテスト対応</li>
      <li>DISABLED_ に対応</li>
      <li>xml 出力に対応</li>
    </ul>
  </li>
</ul>
*/

/**
 * @example main.cpp
 * @example assertion.cpp
 * @example disabledtest.cpp
 * @example exception.cpp
 * @example fixture.cpp
 * @example matcher.cpp
 * @example parameterized.cpp
 * @example printto.cpp
 * @example simple.cpp
 * @example typed.cpp
*/

#endif // INCG_IRIS_IUTEST_VER_HPP_D65CB7A7_D2AD_40FE_8F5F_8FBF376A0010_
