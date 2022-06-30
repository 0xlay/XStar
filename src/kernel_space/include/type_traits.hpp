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
// File: type_traits.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_TYPE_TRAITS_HPP_
#define _XSTAR_KERNEL_TYPE_TRAITS_HPP_

namespace xstar::ks
{
    //--------------------------------------------------------------------------
    //
    // Is referenced check
    //
    //--------------------------------------------------------------------------

    template <class>
    inline constexpr bool IsLvalueReference = false;

    template <class T>
    inline constexpr bool IsLvalueReference<T&> = true;

    template <class>
    inline constexpr bool IsRvalueReference = false;

    template <class T>
    inline constexpr bool IsRvalueReference<T&&> = true;

    //--------------------------------------------------------------------------
    //
    // Remove reference
    //
    //--------------------------------------------------------------------------

    template <class T>
    struct RemoveReference
    {
        using Type = T;
        using ConstRefType = const T;
    };

    template <class T>
    struct RemoveReference<T&>
    {
        using Type = T;
        using ConstRefType = const T&;
    };

    template <class T>
    struct RemoveReference<T&&>
    {
        using Type = T;
        using ConstRefType = const T&&;
    };

    template <class T>
    using RemoveRef = typename RemoveReference<T>::Type;

    //--------------------------------------------------------------------------
    //
    // Move operator
    //
    //--------------------------------------------------------------------------

    template <typename T>
    [[nodiscard]] constexpr RemoveRef<T>&& move(T&& arg) noexcept
    {
        return static_cast<RemoveRef<T>&&>(arg);
    }

    //--------------------------------------------------------------------------
    //
    // Forward operator
    //
    //--------------------------------------------------------------------------

    //
    // Forward an lvalue as either an lvalue or an rvalue
    //

    template <typename T>
    [[nodiscard]] constexpr T&& forward(RemoveRef<T>& arg) noexcept
    { 
        return static_cast<T&&>(arg);
    }

    //
    // Forward an rvalue as an rvalue
    //

    template <typename T>
    [[nodiscard]] constexpr T&& forward(RemoveRef<T>&& arg) noexcept
    { 
        static_assert(!IsLvalueReference<T>, "bad forward call");
        return static_cast<T&&>(arg);
    }

} // xstar::ks

#endif // _XSTAR_KERNEL_TYPE_TRAITS_HPP_
