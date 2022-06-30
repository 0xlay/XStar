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

namespace xstar::us
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

    /*
    * @brief The getLastErrorStr() function converts code from
    * the getLastError() function to string message
    * 
    * @return an error message
    */
    std::string getLastErrorStr();

} // xstar::us
#endif // _XSTAR_USER_EXCEPTION_HPP_