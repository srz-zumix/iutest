//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_assertion.ipp
 * @brief       iris unit test assertion diagnostics
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_ASSERTION_IPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_
#define INCG_IRIS_IUTEST_ASSERTION_IPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_

#include "../iutest_assertion.hpp"
#include <map>
#include <vector>

namespace iutest {
namespace internal
{

inline ::std::vector< ::std::string> StringDiffLines(const ::std::string& value)
{
    ::std::vector< ::std::string> lines;
    size_t begin = 0;
    size_t limit = value.size();
    if( limit > 2 && value[0] == '"' && value[limit - 1] == '"' )
    {
        begin = 1;
        --limit;
    }
    for( size_t pos = begin; pos + 1 < limit; ++pos )
    {
        if( value[pos] != '\\' )
        {
            continue;
        }
        ++pos;
        if( pos + 1 < limit && value[pos] == 'n' )
        {
            lines.push_back(value.substr(begin, pos - begin - 1));
            begin = pos + 1;
        }
    }
    lines.push_back(value.substr(begin, limit - begin));
    return lines;
}

IUTEST_IPP_INLINE ::std::string CreateStringDiff(const ::std::string& left, const ::std::string& right)
{
    if( left.empty() || right.empty()
        || (left.find("\\n") == ::std::string::npos && right.find("\\n") == ::std::string::npos) )
    {
        return ::std::string();
    }
    const ::std::vector< ::std::string> lhs = StringDiffLines(left);
    const ::std::vector< ::std::string> rhs = StringDiffLines(right);
    if( lhs.size() == 1 && rhs.size() == 1 )
    {
        return ::std::string();
    }
    // Bound diagnostic work so a large failed assertion still reports its original values.
    const size_t max_cells = 1048576;
    if( rhs.size() >= max_cells || lhs.size() >= max_cells / (rhs.size() + 1) )
    {
        return ::std::string();
    }

    // Compare interned line IDs, not potentially long strings, in the edit matrix.
    ::std::vector<size_t> lhs_ids, rhs_ids;
    {
        ::std::map< ::std::string, size_t> ids;
        for( int side = 0; side < 2; ++side )
        {
            const ::std::vector< ::std::string>& lines = side == 0 ? lhs : rhs;
            ::std::vector<size_t>& line_ids = side == 0 ? lhs_ids : rhs_ids;
            for( size_t i = 0; i < lines.size(); ++i )
            {
                size_t& id = ids[lines[i]];
                if( id == 0 ) { id = ids.size(); }
                line_ids.push_back(id);
            }
        }
    }

    enum { common, erase, insert, change };
    const size_t width = rhs.size() + 1;
    ::std::vector<unsigned char> moves((lhs.size() + 1) * width, common);
    ::std::vector<double> previous(width), current(width);
    for( size_t col = 1; col < width; ++col )
    {
        previous[col] = static_cast<double>(col);
        moves[col] = insert;
    }
    for( size_t row = 1; row <= lhs.size(); ++row )
    {
        current[0] = static_cast<double>(row);
        moves[row * width] = erase;
        for( size_t col = 1; col < width; ++col )
        {
            unsigned char move = common;
            double cost = previous[col - 1];
            if( lhs_ids[row - 1] != rhs_ids[col - 1] )
            {
                // Match GoogleTest's edit selection, including replacement tie-breaking.
                if( current[col - 1] < previous[col] && current[col - 1] < cost )
                {
                    move = insert;
                    cost = current[col - 1] + 1;
                }
                else if( previous[col] < current[col - 1] && previous[col] < cost )
                {
                    move = erase;
                    cost = previous[col] + 1;
                }
                else
                {
                    move = change;
                    cost += 1.00001;
                }
            }
            current[col] = cost;
            moves[row * width + col] = move;
        }
        previous.swap(current);
    }

    ::std::vector<unsigned char> path;
    size_t row = lhs.size(), col = rhs.size();
    while( row != 0 || col != 0 )
    {
        const unsigned char move = moves[row * width + col];
        path.push_back(move);
        if( move != insert ) { --row; }
        if( move != erase ) { --col; }
    }
    ::std::reverse(path.begin(), path.end());

    iu_global_format_stringstream output;
    row = col = 0;
    size_t cursor = 0;
    const size_t context = 2;
    while( cursor < path.size() )
    {
        while( cursor < path.size() && path[cursor] == common )
        {
            ++cursor;
            ++row;
            ++col;
        }
        if( cursor == path.size() ) { break; }
        const size_t prefix = (::std::min)(row, context);
        const size_t left_start = row - prefix + 1, right_start = col - prefix + 1;
        size_t left_count = prefix, right_count = prefix;
        ::std::string body, removed, added;
        for( size_t i = row - prefix; i < row; ++i )
        {
            body += " " + lhs[i] + "\n";
        }
        size_t suffix = 0;
        while( cursor < path.size() )
        {
            if( suffix >= context )
            {
                size_t next = cursor;
                while( next < path.size() && path[next] == common ) { ++next; }
                if( next == path.size() || next - cursor >= context ) { break; }
            }
            const unsigned char move = path[cursor++];
            if( move == common )
            {
                body += removed + added + " " + lhs[row] + "\n";
                removed.clear();
                added.clear();
                ++suffix;
            }
            else
            {
                suffix = 0;
                if( move != insert ) { removed += "-" + lhs[row] + "\n"; }
                if( move != erase ) { added += "+" + rhs[col] + "\n"; }
            }
            if( move != insert ) { ++row; ++left_count; }
            if( move != erase ) { ++col; ++right_count; }
        }
        output << "@@ -" << left_start;
        if( left_count != 1 ) { output << "," << left_count; }
        output << " +" << right_start;
        if( right_count != 1 ) { output << "," << right_count; }
        output << " @@\n" << body << removed << added;
    }
    return "\nWith diff:\n" + output.str();
}

}   // end of namespace internal
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_ASSERTION_IPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_
