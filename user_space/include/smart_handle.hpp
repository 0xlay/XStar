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
// File: smart_handle.hpp
// 
// Creator: 0xlay
// 
// Environment: User mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_USER_SMART_HANDLE_HPP_
#define _XSTAR_USER_SMART_HANDLE_HPP_


#include <Windows.h>
#include <algorithm>

namespace xstar
{

    //=========================================================
    // CloseSH needed for correct close handle.
    // Supported: HWND, HANDLE, SC_HANDLE.
    //=========================================================
    template <class T>
    class CloseSH
    {
    public:
        static void CloseSmartHandle(T hObject)
        { }
    };

    //---------------------------------------------------------
    // Partial specialization
    //---------------------------------------------------------

    template <>
    class CloseSH<HANDLE>
    {
    public:
        static void CloseSmartHandle(HANDLE hObject)
        {
            CloseHandle(hObject);
        }
    };

    template <>
    class CloseSH<SC_HANDLE>
    {
    public:
        static void CloseSmartHandle(SC_HANDLE hObject)
        {
            CloseServiceHandle(hObject);
        }
    };

    template <>
    class CloseSH<HWND>
    {
    public:
        static void CloseSmartHandle(HWND hObject)
        {
            CloseWindow(hObject);
        }
    };

    //---------------------------------------------------------



    //=========================================================
    // SmartHandle supported: HWND, HANDLE, SC_HANDLE
    //=========================================================
    template <class T>
    class SmartHandle final
    {
    public:
        SmartHandle() noexcept;
        SmartHandle(T hObject) noexcept;
        SmartHandle(SmartHandle&& other) noexcept;
        ~SmartHandle();

        SmartHandle(const SmartHandle&) = delete;
        void operator=(const SmartHandle&) = delete;

        void operator=(T hObject);
        SmartHandle& operator=(SmartHandle&& other) noexcept;

        T getHandle() const noexcept;

    private:
        T hObject_;
    };



    //---------------------------------------------------------
    // Complexity: O(1)
    //---------------------------------------------------------
    template <class T>
    SmartHandle<T>::SmartHandle() noexcept
        : hObject_(nullptr)
    { }

    //---------------------------------------------------------
    // Complexity: O(1)
    //---------------------------------------------------------
    template <class T>
    SmartHandle<T>::SmartHandle(T hObject) noexcept
        : hObject_(hObject)
    { }

    //---------------------------------------------------------
    // Complexity: O(1)
    //---------------------------------------------------------
    template<class T>
    SmartHandle<T>::SmartHandle(SmartHandle&& other) noexcept
    {
        hObject_ = other.hObject_;
        other.hObject_ = nullptr;
    }

    //---------------------------------------------------------
    // Complexity: O(1)
    //---------------------------------------------------------
    template <class T>
    SmartHandle<T>::~SmartHandle()
    {
        if (hObject_)
            CloseSH<T>::CloseSmartHandle(hObject_);
    }


    //---------------------------------------------------------
    // Complexity: O(1)
    //---------------------------------------------------------
    template <class T>
    void SmartHandle<T>::operator=(T hObject)
    {
        if (hObject_)
        {
            CloseSH<T>::CloseSmartHandle(hObject_);
            hObject_ = hObject;
        }
        else
        {
            hObject_ = hObject;
        }
    }

    //---------------------------------------------------------
    // Complexity: O(1)
    //---------------------------------------------------------
    template <class T>
    SmartHandle<T>& SmartHandle<T>::operator=(SmartHandle&& other) noexcept
    {
        std::swap(hObject_, other.hObject_);
        return *this;
    }


    //---------------------------------------------------------
    // Complexity: O(1)
    //---------------------------------------------------------
    template <class T>
    T SmartHandle<T>::getHandle() const noexcept
    {
        return hObject_;
    }



} // xstar
#endif // _XSTAR_USER_SMART_HANDLE_HPP_
