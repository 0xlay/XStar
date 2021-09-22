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
// File: winapi_exception.hpp
// 
// Creator: 0xlay
// 
// Environment: User mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_USER_EXCEPTION_HPP_
#define _XSTAR_USER_EXCEPTION_HPP_

#include <Windows.h>
#include <string>
#include <exception>
#include <cstdint>

namespace xstar
{

    class WinAPIException : public std::exception
    {
    public:
        WinAPIException();
        WinAPIException(const char* msg, uint32_t lastError);
        const char* what() const override;

    private:
        std::string msg_;
    };


    std::string getLastErrorStr();


} // xstar
#endif // _XSTAR_USER_EXCEPTION_HPP_