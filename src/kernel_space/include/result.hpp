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
#include "cruntime/cpplibrary.hpp"

namespace xstar
{
    /*
    * @brief The ResultError<Error> is the proxy object, that represents an error, if there is one.
    */
    template <class Error>
    class ResultError
    {
    public:
        ResultError(bool isError, const Error& e) 
            : isError_(isError), error(e)
        {}
        operator bool() const noexcept { return isError_; }
    private:
        bool isError_;
    public:
        const Error& error;
    };

    /*
    * @brief The Result<Some, Error> is the type implements error handling.
    */
    template <class Some, class Error>
    class Result final
    {
    public:
        Result(const Some& some) : isError_(false)
        {
            new (&some_) Some(some);
        }

        Result(Some&& some) : isError_(false)
        {
            new (&some_) Some(xstar::move(some));
        }

        Result(const Error& error) : isError_(true)
        { 
            new (&error_) Error(error);
        }

        Result(Error&& error) : isError_(true)
        {
            new (&error_) Error(xstar::move(error));
        }

        Result(const Result& rhs)
        {
            if (&rhs != this)
            {
                new (&some_) Some(rhs.some_);
                new (&error_) Error(rhs.error_);
            }
        }

        Result(Result&& rhs) noexcept
        {
            if (&rhs != this)
            {
                new (&some_) Some(xstar::move(rhs.some_));
                new (&error_) Error(xstar::move(rhs.error_));
            }
        }

        Result& operator=(const Result& rhs)
        {
            if (&rhs != this)
            {
                new (&some_) Some(rhs.some_);
                new (&error_) Error(rhs.error_);
            }

            return *this;
        }

        Result& operator=(Result&& rhs) noexcept
        {
            if (&rhs != this)
            {
                new (&some_) Some(xstar::move(rhs.some_));
                new (&error_) Error(xstar::move(rhs.error_));
            }

            return *this;
        }

        ~Result() noexcept
        {
            if (isError_)
            {
                error_.~Error();
            }
            else
            {
                some_.~Some();
            }
        }
        
        /*
        * @brief Returns error as ResultError<Error> type
        * @return ResultError<Error> type, which is a proxy object, that represents an error, if there is one.
        */
        ResultError<Error> isError()
        {
            return ResultError(isError_, error_);
        }

        /*
        * @brief If success then unwrapping Some, otherwise throw KeBugCheckEx().
        * @param[in] code(optional) - bug check code, which pass in the KeBugCheckEx function.
        * @return "Some" type, which moved from the Result<Some, Error>.
        */
        Some unwrap([[maybe_unused]] ULONG code = NO_EXCEPTION_HANDLING_SUPPORT)
        {
            if (isError_)
            {
                NT_ASSERTMSGW(L"You didn't handle xstar::Result<Error> !", FALSE);
                ::KeBugCheckEx(code, 0, 0, 0, 0);
            }
            else
            {
                return xstar::move(some_);
            }
        }

    private:
        bool isError_;
        union
        {
            Some some_;
            Error error_;
        };
    };

    /*
    * @brief The Result<const Some&, Error> is the type implements error handling.
    */
    template <class Some, class Error>
    class Result<const Some&, Error> final
    {
    public:
        Result(const Some& some) : isError_(false), some_(&some)
        { }

        Result(const Error& error) : isError_(true)
        {
            new (&error_) Error(error);
        }

        Result(Error&& error) : isError_(true)
        {
            new (&error_) Error(xstar::move(error));
        }

        Result(const Result& rhs)
        {
            if (&rhs != this)
            {
                some_ = rhs.some_;
                new (&error_) Error(rhs.error_);
            }
        }

        Result(Result&& rhs) noexcept
        {
            if (&rhs != this)
            {
                some_ = xstar::move(rhs.some_);
                new (&error_) Error(xstar::move(rhs.error_));
            }
        }

        Result& operator=(const Result& rhs)
        {
            if (&rhs != this)
            {
                some_ = rhs.some_;
                new (&error_) Error(rhs.error_);
            }

            return *this;
        }

        Result& operator=(Result&& rhs) noexcept
        {
            if (&rhs != this)
            {
                some_ = xstar::move(rhs.some_);
                new (&error_) Error(xstar::move(rhs.error_));
            }

            return *this;
        }

        ~Result() noexcept
        {
            if (isError_)
            {
                error_.~Error();
            }
        }

        /*
        * @brief Returns error as ResultError<Error> type
        * @return ResultError<Error> type, which is a proxy object, that represents an error, if there is one.
        */
        ResultError<Error> isError()
        {
            return ResultError(isError_, error_);
        }

        /*
        * @brief If success then unwrapping Some, otherwise throw KeBugCheckEx().
        * @param[in] code(optional) - bug check code, which pass in the KeBugCheckEx function.
        * @return "Some" type, which moved from the Result<Some, Error>.
        */
        const Some& unwrap([[maybe_unused]] ULONG code = NO_EXCEPTION_HANDLING_SUPPORT)
        {
            if (isError_)
            {
                NT_ASSERTMSGW(L"You didn't handle xstar::Result<Error> !", FALSE);
                ::KeBugCheckEx(code, 0, 0, 0, 0);
            }
            return *some_;
        }

    private:
        bool isError_;
        union
        {
            const Some* some_;
            Error error_;
        };
    };

    /*
    * @brief The Result<Some&, Error> is the type implements error handling.
    */
    template <class Some, class Error>
    class Result<Some&, Error> final
    {
    public:
        Result(Some& some) : isError_(false), some_(&some)
        { }

        Result(const Error& error) : isError_(true)
        {
            new (&error_) Error(error);
        }

        Result(Error&& error) : isError_(true)
        {
            new (&error_) Error(xstar::move(error));
        }

        Result(const Result& rhs)
        {
            if (&rhs != this)
            {
                some_ = rhs.some_;
                new (&error_) Error(rhs.error_);
            }
        }

        Result(Result&& rhs) noexcept
        {
            if (&rhs != this)
            {
                some_ = xstar::move(rhs.some_);
                new (&error_) Error(xstar::move(rhs.error_));
            }
        }

        Result& operator=(const Result& rhs)
        {
            if (&rhs != this)
            {
                some_ = rhs.some_;
                new (&error_) Error(rhs.error_);
            }

            return *this;
        }

        Result& operator=(Result&& rhs) noexcept
        {
            if (&rhs != this)
            {
                some_ = xstar::move(rhs.some_);
                new (&error_) Error(xstar::move(rhs.error_));
            }

            return *this;
        }

        ~Result() noexcept
        {
            if (isError_)
            {
                error_.~Error();
            }
        }

        /*
        * @brief Returns error as ResultError<Error> type
        * @return ResultError<Error> type, which is a proxy object, that represents an error, if there is one.
        */
        ResultError<Error> isError()
        {
            return ResultError(isError_, error_);
        }

        /*
        * @brief If success then unwrapping Some, otherwise throw KeBugCheckEx().
        * @param[in] code(optional) - bug check code, which pass in the KeBugCheckEx function.
        * @return "Some" type, which moved from the Result<Some, Error>.
        */
        Some& unwrap([[maybe_unused]] ULONG code = NO_EXCEPTION_HANDLING_SUPPORT)
        {
            if (isError_)
            {
                NT_ASSERTMSGW(L"You didn't handle xstar::Result<Error> !", FALSE);
                ::KeBugCheckEx(code, 0, 0, 0, 0);
            }
            return *some_;
        }

    private:
        bool isError_;
        union
        {
            Some* some_;
            Error error_;
        };
    };

} // xstar

#endif // _XSTAR_KERNEL_RESULT_HPP_
