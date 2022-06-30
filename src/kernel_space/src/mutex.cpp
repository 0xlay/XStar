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
// File: mutex.cpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#include "include/mutex.hpp"

namespace xstar::ks
{

    //--------------------------------------------------------------------------
    //
    // KMutex
    //
    //--------------------------------------------------------------------------

    /*
    * @warning IRQL == Any level
    */
    _Use_decl_annotations_
    void KMutex::init()
    {
        KeInitializeMutex(&mutex_, 0);
    }
    
    /*
    * @warning IRQL <= DISPATCH_LEVEL
    */
    _Use_decl_annotations_
    void KMutex::lock()
    {
        KeWaitForSingleObject(&mutex_, Executive, KernelMode, FALSE, nullptr);
    }

    /*
    * @warning IRQL <= DISPATCH_LEVEL
    */
    _Use_decl_annotations_
    void KMutex::unlock()
    {
        KeReleaseMutex(&mutex_, FALSE);
    }

    //--------------------------------------------------------------------------
    //
    // FastMutex
    //
    //--------------------------------------------------------------------------

    /*
    * @warning IRQL <= DISPATCH_LEVEL
    */
    _Use_decl_annotations_
    void FastMutex::init()
    {
        ExInitializeFastMutex(&mutex_);
    }

    /*
    * @warning IRQL <= APC_LEVEL
    */
    _Use_decl_annotations_
    void FastMutex::lock()
    {
        ExAcquireFastMutex(&mutex_);
    }

    /*
    * @warning IRQL == APC_LEVEL
    */
    _Use_decl_annotations_
    void FastMutex::unlock()
    {
        ExReleaseFastMutex(&mutex_);
    }

} // xstar::ks
