﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_factory.hpp
 * @brief       iris unit test テストファクトリー ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_FACTORY_HPP_9C2B4B94_95A0_479A_9C9D_43FB31845A73_
#define INCG_IRIS_IUTEST_FACTORY_HPP_9C2B4B94_95A0_479A_9C9D_43FB31845A73_

namespace iutest {

//======================================================================
// declare
class Test;

namespace detail
{

//======================================================================
// class
/**
 * @internal
 * @brief   テスト生成クラスインターフェース
*/
class iuFactoryBase
{
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(iuFactoryBase);
public:
    iuFactoryBase() IUTEST_CXX_NOEXCEPT_SPEC {}
    virtual ~iuFactoryBase() {}
public:
    virtual auto_ptr<Test> Create() = 0;
};

/**
 * @internal
 * @brief   テスト生成クラス
 * @tparam  Tester  = テストクラス
*/
template<class Tester>
class iuFactory IUTEST_CXX_FINAL : public iuFactoryBase
{
public:
    virtual auto_ptr<Test> Create() IUTEST_CXX_OVERRIDE
    {
        auto_ptr<Test> p( new Tester() );
        return p;
    }
};

/**
 * @internal
 * @brief   パラメータセットテスト生成クラスインターフェース
 * @tparam  ParamType   = パラメータの型
*/
template<typename ParamType>
class iuParamTestFactoryBase : public iuFactoryBase
{
public:
    iuParamTestFactoryBase() : m_param() {}
    explicit iuParamTestFactoryBase(ParamType param) : m_param(param) {}
public:
    void                SetParam(ParamType param) { m_param = param; }
    const ParamType&    GetParam()      const { return m_param; }
protected:
    ParamType m_param;
};


/**
 * @internal
 * @brief   パラメータセットテスト生成クラス
 * @tparam  Tester  = テストクラス
*/
template<class Tester>
class iuParamTestFactory IUTEST_CXX_FINAL : public iuParamTestFactoryBase<typename Tester::ParamType>
{
    typedef typename Tester::ParamType ParamType;
    typedef iuParamTestFactoryBase<ParamType> _Mybase;
public:
    iuParamTestFactory() IUTEST_CXX_DEFAULT_FUNCTION
    explicit iuParamTestFactory(ParamType param) : _Mybase(param) {}

public:
    virtual auto_ptr<Test> Create() IUTEST_CXX_OVERRIDE
    {
        Tester::SetParam(&this->m_param);
        auto_ptr<Test> p( new Tester() );
        return p;
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_FACTORY_HPP_9C2B4B94_95A0_479A_9C9D_43FB31845A73_
