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

namespace xstar::us
{

    namespace _internal
    {
        template <typename Handle>
        inline void CloseSmartHandle(Handle object)
        {
            static_assert(false, "Type isn't supported!");
        }

        template <>
        inline void CloseSmartHandle(HANDLE object)
        {
            CloseHandle(object);
        }

        template <>
        inline void CloseSmartHandle(SC_HANDLE object)
        {
            CloseServiceHandle(object);
        }

        template <>
        inline void CloseSmartHandle(HWND object)
        {
            CloseWindow(object);
        }

        template <>
        inline void CloseSmartHandle(HMODULE object)
        {
            FreeLibrary(object);
        }
    }



    /**
    * @brief The SmartHandle is a wrapper above handle which use idiom RAII
    * 
    * @warning The SmartHandle supports HWND, HANDLE, SC_HANDLE 
    */
    template <class Handle>
    class SmartHandle final
    {
    public:
        SmartHandle() noexcept;
        SmartHandle(Handle object) noexcept;
        ~SmartHandle() noexcept;

        SmartHandle(SmartHandle&& other) noexcept;
        SmartHandle& operator=(SmartHandle&& other) noexcept;

        SmartHandle(const SmartHandle&) = delete;
        SmartHandle& operator=(const SmartHandle&) = delete;

        Handle getHandle() const noexcept;
        Handle operator*() const noexcept;

    private:
        Handle object_;
    };

    template <class Handle>
    SmartHandle<Handle>::SmartHandle() noexcept
        : object_(nullptr)
    { }

    template <class Handle>
    SmartHandle<Handle>::SmartHandle(Handle object) noexcept
        : object_(object)
    { }

    template<class Handle>
    SmartHandle<Handle>::SmartHandle(SmartHandle<Handle>&& other) noexcept
    {
        object_ = other.hObject_;
        other.object_ = nullptr;
    }

    template <class Handle>
    SmartHandle<Handle>::~SmartHandle() noexcept
    {
        if (object_)
            _internal::CloseSmartHandle(object_);
    }

    template <class Handle>
    SmartHandle<Handle>& SmartHandle<Handle>::operator=(SmartHandle<Handle>&& other) noexcept
    {
        std::swap(object_, other.object_);
        return *this;
    }

    template <class Handle>
    Handle SmartHandle<Handle>::getHandle() const noexcept
    {
        return object_;
    }

    template <class Handle>
    Handle SmartHandle<Handle>::operator*() const noexcept
    {
        return object_;
    }

} // xstar::us
#endif // _XSTAR_USER_SMART_HANDLE_HPP_
