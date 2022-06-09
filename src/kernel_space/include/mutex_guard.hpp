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
// File: mutex_guard.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_
#define _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_

namespace xstar
{
    /**
    * @brief This class is equivalent to std::lock_guard from STL
    */
    template <class MutextType>
    class LockGuard final
    {
    public:
        LockGuard(MutextType& object) noexcept : object_(object)
        {
            object_.lock();
        }

        LockGuard(const MutextType&) = delete;
        LockGuard(MutextType&&) = delete;

        ~LockGuard() noexcept
        {
            object_.unlock();
        }

        LockGuard& operator=(const MutextType&) = delete;
        LockGuard& operator=(MutextType&&) = delete;

    private:
        MutextType& object_;
    };

    /**
    * @brief This class is equivalent to std::unique_lock from STL
    */
    template <class MutextType>
    class UniqueLock final
    {
    public:
        UniqueLock(MutextType& object) noexcept
            : locked_(true), object_(object)
        {
            object_.lock();
        }

        UniqueLock(const MutextType&) = delete;
        UniqueLock(MutextType&&) = delete;

        ~UniqueLock() noexcept
        {
            unlock();
        }

        UniqueLock& operator=(const MutextType&) = delete;
        UniqueLock& operator=(MutextType&&) = delete;

        void lock() noexcept
        {
            if (!locked_)
            {
                object_.lock();
                locked_ = true;
            }
        }

        void unlock() noexcept
        {
            if (locked_)
            {
                object_.unlock();
                locked_ = false;
            }
        }

    private:
        bool locked_;
        MutextType& object_;
    };

} // xstar

#endif // _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_