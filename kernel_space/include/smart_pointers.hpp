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
// File: smart_pointers.hpp
// 
// Creator: 0xlay
// 
// Envivroment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_SMART_POINTERS_HPP_
#define _XSTAR_KERNEL_SMART_POINTERS_HPP_

#include "runtime.hpp"
#include "algorithms.hpp"

namespace xstar
{
    /**
    *
    * @brief UniquePointer is using windows exception.You will need using 
    * operator __try, __except
    * 
    */
    template <class T>
    class UniquePointer final
    {
    public:
        UniquePointer();
        UniquePointer(T* pointer);
        ~UniquePointer();

        UniquePointer(UniquePointer&& other) noexcept;
        UniquePointer& operator=(UniquePointer&& other) noexcept;

        UniquePointer(const UniquePointer&) = delete;
        UniquePointer& operator=(const UniquePointer&) = delete;

        T& operator*();
        T* operator->();

        T* getPointer() const;
        void release();
        void reset(T* pointer);

    private:
        T* pointer_;
    };

    /// @todo Add SharedPointer, and WeakPointer
}

#include "smart_pointers.inl"

#endif // _XSTAR_KERNEL_SMART_POINTERS_HPP_
