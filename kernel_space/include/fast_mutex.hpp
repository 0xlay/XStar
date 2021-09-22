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
// File: fast_mutex.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_FAST_MUTEX_HPP_
#define _XSTAR_KERNEL_FAST_MUTEX_HPP_

#include <wdm.h>


namespace xstar
{
    /**
    * @brief This wrapper over FAST_MUTEX.
    */
    class FastMutex final
    {
    public:
        _IRQL_requires_max_(DISPATCH_LEVEL)
        void Init();
        
        _IRQL_raises_(APC_LEVEL)
        _IRQL_saves_global_(OldIrql, mutex_)
        _IRQL_requires_max_(APC_LEVEL)
        void Lock();

        _IRQL_restores_global_(OldIrql, mutex_)
        _IRQL_requires_(APC_LEVEL)
        void Unlock();

    private:
        FAST_MUTEX mutex_; // Always, non paged pool
    };

    /**
    * @warning IRQL <= DISPATCH_LEVEL
    */
    _Use_decl_annotations_
    void FastMutex::Init()
    {
        ExInitializeFastMutex(&mutex_);
    }

    /**
    * @warning IRQL <= APC_LEVEL
    */
    _Use_decl_annotations_
    void FastMutex::Lock()
    {
        ExAcquireFastMutex(&mutex_);
    }

    /**
    * @warning IRQL == APC_LEVEL
    */
    _Use_decl_annotations_
    void FastMutex::Unlock()
    {
        ExReleaseFastMutex(&mutex_);
    }

}

#endif // _XSTAR_KERNEL_FAST_MUTEX_HPP_
