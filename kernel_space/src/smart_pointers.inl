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
// File: smart_pointers.inl
// 
// Creator: 0xlay
// 
// Envivroment: Kernel mode only
//
//------------------------------------------------------------------------------

#include "smart_pointers.hpp"

namespace xstar
{
    template <class T>
    UniquePointer<T>::UniquePointer()
        : pointer_(nullptr)
    { }

    template <class T>
    UniquePointer<T>::UniquePointer(T* pointer)
        : pointer_(pointer)
    {
        if (pointer_ == nullptr)
            ExRaiseAccessViolation();
    }

    template <class T>
    UniquePointer<T>::~UniquePointer()
    {
        free(static_cast<void*>(pointer_));
    }

    template <class T>
    UniquePointer<T>::UniquePointer(UniquePointer<T>&& other) noexcept
    {
        swap(pointer_, other.pointer_);
    }

    template <class T>
    UniquePointer<T>& UniquePointer<T>::operator = (UniquePointer&& other) noexcept
    {
        swap(pointer_, other.pointer_);
        return *this;
    }

    template <class T>
    T& UniquePointer<T>::operator*()
    {
        return *pointer_;
    }

    template <class T>
    T* UniquePointer<T>::operator->()
    {
        return pointer_;
    }

    template <class T>
    T* UniquePointer<T>::getPointer() const
    {
        return pointer_;
    }

    template <class T>
    void UniquePointer<T>::release()
    {
        free(static_cast<void*>(pointer_));
    }

    template <class T>
    void UniquePointer<T>::reset(T* pointer)
    {
        free(static_cast<void*>(pointer_));
        pointer_ = pointer;
        if (pointer_ == nullptr)
            ExRaiseAccessViolation();
    }

}