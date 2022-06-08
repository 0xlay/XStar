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
// File: initializer_list.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_INITIALIZER_LIST_HPP_
#define _XSTAR_KERNEL_INITIALIZER_LIST_HPP_

namespace xstar
{

    template <class T>
    class InitializerList
    {
    public:
        using ValueType = T;
        using SizeType = size_t;
        using Iterator = const ValueType*;
        using ConstIterator = const ValueType*;

        constexpr InitializerList() noexcept : begin_(nullptr), end_(nullptr)
        { }

        constexpr InitializerList(ConstIterator begin, ConstIterator end) noexcept
            : begin_(begin), end_(end)
        { }

        [[nodiscard]]
        constexpr Iterator begin() const noexcept
        {
            return begin_;
        }

        [[nodiscard]]
        constexpr Iterator end() const noexcept
        {
            return end_;
        }

        [[nodiscard]]
        constexpr ConstIterator cbegin() const noexcept
        {
            return begin_;
        }

        [[nodiscard]]
        constexpr ConstIterator cend() const noexcept
        {
            return end_;
        }

        [[nodiscard]]
        constexpr SizeType size() const noexcept
        {
            return static_cast<SizeType>(end_ - begin_);
        }

    private:
        ConstIterator begin_;
        ConstIterator end_;
    };

} // xstar

#endif // _XSTAR_KERNEL_INITIALIZER_LIST_HPP_
