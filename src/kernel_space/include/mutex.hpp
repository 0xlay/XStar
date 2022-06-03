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
// File: mutex.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_MUTEX_HPP_
#define _XSTAR_KERNEL_MUTEX_HPP_

#include <ntddk.h>

namespace xstar
{
    
    /*
    * @brief The IMutex is an interface for mutexs.
    */
    struct IMutex
    {
        virtual void init() = 0;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual ~IMutex() = default;
    };

    /*
    * @brief The KMutext is the wrapper over KMUTEX.
    * @warning For this object always allocate memory from a non paged pool.
    */
    class KMutex final : public IMutex
    {
    public:
        _IRQL_requires_max_(HIGH_LEVEL)
        void init() override;

        _IRQL_requires_max_(DISPATCH_LEVEL)
        void lock() override;

        _IRQL_requires_max_(DISPATCH_LEVEL)
        void unlock() override;

    private:
        KMUTEX mutex_;
    };

    /*
    * @brief The FastMutext is the wrapper over FAST_MUTEX.
    * @warning For this object always allocate memory from a non paged pool.
    */
    class FastMutex final : public IMutex
    {
    public:
        _IRQL_requires_max_(DISPATCH_LEVEL)
        void init() override;

        _IRQL_raises_(APC_LEVEL)
        _IRQL_saves_global_(OldIrql, mutex_)
        _IRQL_requires_max_(APC_LEVEL)
        void lock() override;

        _IRQL_restores_global_(OldIrql, mutex_)
        _IRQL_requires_(APC_LEVEL)
        void unlock() override;

    private:
        FAST_MUTEX mutex_;
    };

} // xstar

#endif // _XSTAR_KERNEL_MUTEX_HPP_