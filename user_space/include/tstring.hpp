//------------------------------------------------------------------------------
// ╔═╗╔═╗╔═══╗╔════╗╔═══╗╔═══╗
// ╚╗╚╝╔╝║╔═╗║║╔╗╔╗║║╔═╗║║╔═╗║
//  ╚╗╔╝ ║╚══╗╚╝║║╚╝║║ ║║║╚═╝║
//  ╔╝╚╗ ╚══╗║  ║║  ║╚═╝║║╔╗╔╝
// ╔╝╔╗╚╗║╚═╝║  ║║  ║╔═╗║║║║╚╗
// ╚═╝╚═╝╚═══╝  ╚╝  ╚╝ ╚╝╚╝╚═╝
// 
// Copyright Ⓒ 0xlay. All rights reserved.
// 
// This source file is licensed under the terms of MIT license.
// For details, please read the LICENSE file.
// 
// File: tstring.hpp
// 
// Creator: 0xlay
// 
// Environment: User mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_USER_TSTRING_HPP_
#define _XSTAR_USER_TSTRING_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <tchar.h>

namespace xstar
{

#ifdef _UNICODE
    
    // @brief This macro is need for UNICODE string
    #define $T L""
    
    using tstring           = std::wstring;
    using tstring_view      = std::wstring_view;
    using tchar             = wchar_t;

    using tstringbuf        = std::wstringbuf;
    using tstringstream     = std::wstringstream;
    using tistringstream    = std::wistringstream;
    using tostringstream    = std::wostringstream;

    auto& tcin              = std::wcin;
    auto& tcout             = std::wcout;
    auto& tcerr             = std::wcerr;
    auto& tclog             = std::wclog;
    auto& _Ptr_tcin         = std::_Ptr_wcin;
    auto& _Ptr_tcout        = std::_Ptr_wcout;
    auto& _Ptr_tcerr        = std::_Ptr_wcerr;
    auto& _Ptr_tclog        = std::_Ptr_wclog;

#else

    // @brief This macro is need for ASCII string
    #define $T ""

    using tstring           = std::string;
    using tstring_view      = std::string_view;
    using tchar             = char;

    using tstringbuf        = std::stringbuf;
    using tstringstream     = std::stringstream;
    using tistringstream    = std::istringstream;
    using tostringstream    = std::ostringstream;

    auto& tcin              = std::cin;
    auto& tcout             = std::cout;
    auto& tcerr             = std::cerr;
    auto& tclog             = std::clog;
    auto& _Ptr_tcin         = std::_Ptr_cin;
    auto& _Ptr_tcout        = std::_Ptr_cout;
    auto& _Ptr_tcerr        = std::_Ptr_cerr;
    auto& _Ptr_tclog        = std::_Ptr_clog;

#endif

    inline tstring operator ""_ts(const tchar* str, const size_t size)
    {
        return tstring(str, size);
    }

    inline tstring_view operator ""_tsv(const tchar* str, const size_t size)
    {
        return tstring_view(str, size);
    }

}

#endif // _XSTAR_USER_TSTRING_HPP_
