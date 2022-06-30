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
// File: winapi_exception.cpp
// 
// Creator: 0xlay
// 
// Environment: User mode only
//
//------------------------------------------------------------------------------

#include "include/winapi_exception.hpp"


namespace xstar::us
{

    WinAPIException::WinAPIException()
        : msg_(getLastErrorStr()) { }

    WinAPIException::WinAPIException(const char* msg, uint32_t lastError)
        : msg_(std::string(msg) + " Error code: " + std::to_string(lastError))
    { }

    const char* WinAPIException::what() const
    {
        return msg_.c_str();
    }



    std::string getLastErrorStr()
    {
        char msg_buf[256]{ 0 };

        uint32_t lastError = GetLastError();
        if (!lastError)
            return msg_buf;

        size_t size = FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            lastError,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
            msg_buf,
            256,
            nullptr
        );
        if (!size)
            throw std::exception();

        return std::string(msg_buf, 256);
    }

} // xstar::us