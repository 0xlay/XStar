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

namespace xstar::us
{

#ifdef _UNICODE
    
    #define $T L""      // @brief This macro is need for UNICODE string
    #define $Tc(x) L##x // @brief This macro is need for UNICODE symbol

    using tstring                  = std::wstring;
    using tstring_view             = std::wstring_view;
    using tchar                    = wchar_t;

    using tstringbuf               = std::wstringbuf;
    using tstringstream            = std::wstringstream;
    using tistringstream           = std::wistringstream;
    using tostringstream           = std::wostringstream;

    inline auto& tcin              = std::wcin;
    inline auto& tcout             = std::wcout;
    inline auto& tcerr             = std::wcerr;
    inline auto& tclog             = std::wclog;
    inline auto& _Ptr_tcin         = std::_Ptr_wcin;
    inline auto& _Ptr_tcout        = std::_Ptr_wcout;
    inline auto& _Ptr_tcerr        = std::_Ptr_wcerr;
    inline auto& _Ptr_tclog        = std::_Ptr_wclog;



    inline tstring to_tstring(int val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(float val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(double val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(long long val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(long val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(unsigned long long val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(unsigned long val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(unsigned int val)
    {
        return std::to_wstring(val);
    }

    inline tstring to_tstring(long double val)
    {
        return std::to_wstring(val);
    }

#else

    #define $T ""    // @brief This macro is need for ASCII string
    #define $Tc(x) x // @brief This macros is need for ASCII symbol

    using tstring                  = std::string;
    using tstring_view             = std::string_view;
    using tchar                    = char;

    using tstringbuf               = std::stringbuf;
    using tstringstream            = std::stringstream;
    using tistringstream           = std::istringstream;
    using tostringstream           = std::ostringstream;

    inline auto& tcin              = std::cin;
    inline auto& tcout             = std::cout;
    inline auto& tcerr             = std::cerr;
    inline auto& tclog             = std::clog;
    inline auto& _Ptr_tcin         = std::_Ptr_cin;
    inline auto& _Ptr_tcout        = std::_Ptr_cout;
    inline auto& _Ptr_tcerr        = std::_Ptr_cerr;
    inline auto& _Ptr_tclog        = std::_Ptr_clog;



    inline tstring to_tstring(int val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(float val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(double val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(long long val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(long val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(unsigned long long val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(unsigned long val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(unsigned int val)
    {
        return std::to_string(val);
    }

    inline tstring to_tstring(long double val)
    {
        return std::to_string(val);
    }

#endif

    /*
    * @brief The '_ts' tag creates tstring
    */
    inline tstring operator ""_ts(const tchar* str, const size_t size)
    {
        return tstring(str, size);
    }

    /*
    * @brief The '_tsv' tag creates tstring_view
    */
    inline tstring_view operator ""_tsv(const tchar* str, const size_t size)
    {
        return tstring_view(str, size);
    }

} // xstar::us

#endif // _XSTAR_USER_TSTRING_HPP_
