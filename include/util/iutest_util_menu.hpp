//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_util_menu.hpp
 * @brief       iris unit test テスト メニュー生成 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_MENU_HPP_52925DE1_A4AE_4CCB_B524_8E97AA73E03D_
#define INCG_IRIS_IUTEST_UTIL_MENU_HPP_52925DE1_A4AE_4CCB_B524_8E97AA73E03D_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_util_tests.hpp"
// IWYU pragma: end_exports

#if defined(IUTEST_OS_WINDOWS)
#include <windows.h>
#include <map>

namespace iuutil
{

//======================================================================
// class
/**
 * @brief   メニュークラス
*/
class TestMenu
{
    typedef ::std::map<WORD, const ::iutest::TestInfo*> TestInfoMap;
    typedef ::std::map<WORD, const ::iutest::TestSuite*> TestSuiteMap;
    WORD m_nID;
    const WORD m_nIDTop;
    HMENU m_hRootMenu;
    TestInfoMap m_TestInfoList;
    TestSuiteMap m_TestSuiteList;
public:
    explicit TestMenu(WORD nIDTop) : m_nIDTop(nIDTop), m_nID(nIDTop), m_hRootMenu(NULL) {}
public:
    bool Create(HMENU hMenu)
    {
        if( hMenu == NULL )
        {
            return false;
        }
        if( m_hRootMenu == NULL )
        {
            if( !Create() )
            {
                return false;
            }
        }
        return AppendPopup(hMenu, "TestList", m_hRootMenu);
    }
    bool Create()
    {
        // テストを列挙
        HMENU hRoot = CreateMenu();
        if( hRoot == NULL )
        {
            return false;
        }

        Append(hRoot, "以下をすべて実行", m_nID);
        ++m_nID;

        ::iutest::UnitTest* pUnitTest = ::iutest::UnitTest::GetInstance();
        const int testsuite_count = pUnitTest->total_test_suite_count();
        for( int i=0; i < testsuite_count; ++i )
        {
            const ::iutest::TestSuite* pTestSuite = pUnitTest->GetTestSuite(i);
            const int test_count = pTestSuite->total_test_count();
            HMENU hTestSuite = AppendPopup(hRoot, pTestSuite->name());
            Append(hTestSuite, "以下をすべて実行", m_nID);
#if IUTEST_HAS_STD_EMPLACE
            m_TestSuiteList.emplace(m_nID, pTestSuite);
#else
            m_TestSuiteList.insert( ::std::pair<WORD, const ::iutest::TestSuite*>(m_nID, pTestSuite) );
#endif
            ++m_nID;
            for( int j=0; j < test_count; ++j )
            {
                const ::iutest::TestInfo* pTestInfo = pTestSuite->GetTestInfo(j);
                Append(hTestSuite, pTestInfo->name(), m_nID);
#if IUTEST_HAS_STD_EMPLACE
                m_TestInfoList.emplace(m_nID, pTestInfo);
#else
                m_TestInfoList.insert(::std::pair<WORD, const ::iutest::TestInfo*>(m_nID, pTestInfo));
#endif
                ++m_nID;
            }
        }
        m_hRootMenu = hRoot;
        return true;
    }

    bool OnCommand(WORD wID)
    {
        if( wID == m_nIDTop )
        {
            ::iutest::IUTEST_FLAG(filter) = "*";
            return IUTEST_RUN_ALL_TESTS() == 0 ? true : false;
        }

        {
            TestInfoMap::iterator it = m_TestInfoList.find(wID);
            if( it != m_TestInfoList.end() )
            {
                ::iutest::IUTEST_FLAG(filter) = TestFullName(it->second);
                return IUTEST_RUN_ALL_TESTS() == 0 ? true : false;
            }
        }
        {
            TestSuiteMap::iterator it = m_TestSuiteList.find(wID);
            if( it != m_TestSuiteList.end() )
            {
                ::std::string filter = it->second->name();
                filter += ".*";
                ::iutest::IUTEST_FLAG(filter) = filter;
                return IUTEST_RUN_ALL_TESTS() == 0 ? true : false;
            }
        }
        return true;
    }

    bool TrackPopupMenu(HWND hWnd, POINT point)
    {
        if ( !::TrackPopupMenu(m_hRootMenu
            , TPM_LEFTALIGN | TPM_BOTTOMALIGN
            , point.x, point.y
            , 0
            , hWnd
            , NULL
        ) )
        {
            return false;
        }
        return true;
    }

private:
    static bool Append(HMENU hMenu, const char* lpszName, WORD nID)
    {
        char str[256];
        MENUITEMINFOA mii = {0};
        mii.cbSize      = sizeof(mii);
        mii.fMask       = MIIM_ID | MIIM_TYPE;
        mii.fType       = MFT_STRING;
        mii.dwTypeData  = str;
        mii.wID         = nID;
        strcpy_s(str, lpszName);
        const int num = ::GetMenuItemCount(hMenu);
        if( !::InsertMenuItemA(hMenu, num, TRUE, &mii) )
        {
            return false;
        }
        return true;
    }
    static bool AppendPopup(HMENU hMenu, const char* lpszName, HMENU hSubMenu)
    {
        char str[256];
        MENUITEMINFOA mii = {0};
        mii.cbSize      = sizeof(mii);
        mii.fMask       = MIIM_ID | MIIM_TYPE | MIIM_SUBMENU;
        mii.fType       = MFT_STRING;
        mii.dwTypeData  = str;
        mii.hSubMenu    = hSubMenu;
        strcpy_s(str, lpszName);
        const int num = ::GetMenuItemCount(hMenu);
        if( !::InsertMenuItemA(hMenu, num, TRUE, &mii) )
        {
            return false;
        }
        return true;
    }
    static HMENU AppendPopup(HMENU hMenu, const char* lpszName)
    {
        HMENU hSubMenu = CreateMenu();
        if( !AppendPopup(hMenu, lpszName, hSubMenu) )
        {
            DestroyMenu(hSubMenu);
            return NULL;
        }
        return hSubMenu;
    }
};

}   // end of namespace iuutil

#endif

#endif // INCG_IRIS_IUTEST_MENU_TESTS_HPP_52925DE1_A4AE_4CCB_B524_8E97AA73E03D_
