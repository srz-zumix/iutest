//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_genparams_from_file.hpp
 * @brief       iris unit test parameter generator from file
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_GENPARAMS_FROM_FILE_HPP_81CDA6E7_945B_4F72_873B_104264DF7132_
#define INCG_IRIS_IUTEST_GENPARAMS_FROM_FILE_HPP_81CDA6E7_945B_4F72_873B_104264DF7132_

#if IUTEST_HAS_CSVPARAMS

namespace iutest {
namespace detail
{

/**
 * @brief   csv ファイルからのパラメータ生成器
 * @tparam T    = パラメータ型
*/
template<typename T>
class iuCsvFileParamsGenerator : public iuValuesInParamsGenerator<T>
{
    typedef ::std::vector<T> params_t;
public:
    /**
     * @brief   コンストラクタ
     * @param [in]  path        = ファイルパス
     * @param [in]  delimiter   = 区切り文字
    */
    explicit iuCsvFileParamsGenerator(const ::std::string& path, char delimiter = ',')
        : iuValuesInParamsGenerator<T>(ReadParams(path, delimiter))
    {
    }

private:
    void AppendParams(params_t& params, const ::std::string& data)
    {
        if( StringIsBlank(data) )
        {
            return;
        }
        T param;
        if( !StringToValue(data, param) )
        {
            return;
        }
        params.push_back(param);
    }
    params_t ReadParams(const ::std::string& path, char delimiter = ',')
    {
        params_t params;
        IFile* fp = detail::IFileSystem::New();
        if( (fp != NULL) && fp->Open(path.c_str(), IFile::OpenRead) )
        {
            const ::std::string dataset = fp->ReadAll();
            ::std::string::size_type prev = 0;
            ::std::string::size_type pos = 0;
            while( static_cast<void>(pos = dataset.find(delimiter, prev)), pos != ::std::string::npos )
            {
                const ::std::string data = dataset.substr(prev, pos - prev);
                AppendParams(params, data);
                ++pos;
                prev = pos;
            }
            AppendParams(params, dataset.substr(prev));

            if( params.empty() )
            {
                IUTEST_LOG_(WARNING) << "Empty params file \"" << path << "\".";
            }
        }
        else
        {
            IUTEST_LOG_(WARNING) << "Unable to open file \"" << path << "\".";
        }
        detail::IFileSystem::Free(fp);
        return params;
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif

#endif // INCG_IRIS_IUTEST_GENPARAMS_FROM_FILE_HPP_81CDA6E7_945B_4F72_873B_104264DF7132_
