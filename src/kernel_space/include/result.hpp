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
// File: result.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_RESULT_HPP_
#define _XSTAR_KERNEL_RESULT_HPP_

#include <ntddk.h>

namespace xstar
{

    template <class Some, class Error>
    class Result final
    {
    public:
        Result() : isError_(false)
        { }

        bool isError() const
        {
            return isError_;
        }

        Result& some(Some&& some)
        {
            isError_ = false;
            u.some_ = xstar::forward<Some>(some);
            return *this;
        }

        Result& error(Error&& error)
        {
            isError_ = true;
            u.error_ = xstar::forward<Error>(error);
            return *this;
        }

        Some unwrap([[maybe_unused]] ULONG code = NO_EXCEPTION_HANDLING_SUPPORT)
        {
            if (isError_)
            {
                NT_ASSERTMSGW(L"You didn't handle xstar::Result<Error> !", FALSE);
                ::KeBugCheckEx(code, 0, 0, 0, 0);
            }
            else
            {
                return xstar::move(u.some_);
            }
        }

    private:
        bool isError_;
        union
        {
            Some some_;
            Error error_;
        } u;
    };

} // xstar

#endif // _XSTAR_KERNEL_RESULT_HPP_
