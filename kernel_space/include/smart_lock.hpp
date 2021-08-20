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
// File: smart_lock.hpp
// 
// Creator: 0xlay
// 
// Envivroment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_
#define _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_

namespace xstar
{
    /**
    * \brief This class is equivalent to lock_guard from STL
    */
    template <class T>
    class SmartLock
    {
    public:
        SmartLock(T& object) : object_(object)
        {
            object_.Lock();
        }
        ~SmartLock()
        {
            object_.Unlock();
        }

    private:
        T& object_;
    };

}

#endif // _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_