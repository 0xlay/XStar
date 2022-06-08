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
// File: array.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_ARRAY_HPP_
#define _XSTAR_KERNEL_ARRAY_HPP_

#include "result.hpp"
#include "algorithms.hpp"

namespace xstar
{

    template <class T, size_t N>
    struct Array
    {
        using ValueType = T;
        using SizeType = size_t;
        using Reference = ValueType&;
        using ConstReference = const ValueType&;
        using Pointer = ValueType*;
        using ConstPointer = const ValueType*;
        using Iterator = ValueType*;
        using ConstIterator = const ValueType*;

        //
        // Operators
        //

        [[nodiscard]]
        constexpr Reference operator[](SizeType pos)
        {
            return __Array[pos];
        }

        [[nodiscard]]
        constexpr ConstReference operator[](SizeType pos) const
        {
            return __Array[pos];
        }

        //
        // Operations
        //

        constexpr void swap(Array& other) noexcept
        {
            xstar::swap(*this, other);
        }

        constexpr void fill(const ValueType& value) noexcept
        {
            __fill(value, 0);
        }

        //
        // Accessors
        //

        [[nodiscard]]
        constexpr Result<Reference, NTSTATUS> at(SizeType pos) noexcept
        {
            if (pos < N) { return Result<Reference, NTSTATUS>(__Array[pos]); }
            return Result<Reference, NTSTATUS>(STATUS_ACCESS_VIOLATION);
        }

        [[nodiscard]]
        constexpr Result<ConstReference, NTSTATUS> at(SizeType pos) const noexcept
        {
            if (pos < N) { return Result<ConstReference, NTSTATUS>(__Array[pos]); }
            return Result<ConstReference, NTSTATUS>(STATUS_ACCESS_VIOLATION);
        }

        [[nodiscard]]
        constexpr Reference front() noexcept
        {
            return __Array[0];
        }

        [[nodiscard]]
        constexpr ConstReference front() const noexcept
        {
            return __Array[0];
        }

        [[nodiscard]]
        constexpr Reference back() noexcept
        {
            return __Array[N - 1];
        }

        [[nodiscard]]
        constexpr ConstReference back() const noexcept
        {
            return __Array[N - 1];
        }

        [[nodiscard]]
        constexpr Pointer data() noexcept
        {
            return __Array;
        }

        [[nodiscard]]
        constexpr ConstPointer data() const noexcept
        {
            return __Array;
        }

        //
        // Iterators
        //

        [[nodiscard]]
        constexpr Iterator begin() noexcept
        {
            return __Array;
        }

        [[nodiscard]]
        constexpr Iterator end() noexcept
        {
            return __Array + N;
        }

        [[nodiscard]]
        constexpr ConstIterator cbegin() const noexcept
        {
            return __Array;
        }

        [[nodiscard]]
        constexpr ConstIterator cend() const noexcept
        {
            return __Array + N;
        }

        //
        // TODO: Add Reverse Iterator
        //

        //
        // Capacity
        //

        [[nodiscard]]
        constexpr SizeType size() const noexcept
        {
            return N;
        }

        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return !N;
        }

        T __Array[N];

    private:
        constexpr void __fill(const ValueType& value, SizeType pos)
        {
            if (pos >= N) return;
            __Array[pos] = value;
            __fill(value, ++pos);
        }
    };


    //
    // For StructHack
    //
    template <class T>
    struct Array<T, 0>
    {
        using ValueType = T;
        using SizeType = size_t;
        using Reference = ValueType&;
        using ConstReference = const ValueType&;
        using Pointer = ValueType*;
        using ConstPointer = const ValueType*;
        using Iterator = ValueType*;
        using ConstIterator = const ValueType*;

        //
        // Operators
        //

        [[nodiscard]]
        constexpr Reference operator[](SizeType)
        {
            return 0;
        }

        [[nodiscard]]
        constexpr ConstReference operator[](SizeType) const
        {
            return 0;
        }

        //
        // Operations
        //

        constexpr void swap(Array&) noexcept
        { }

        constexpr void fill(const ValueType&) noexcept
        { }


        //
        // Accessors
        //

        [[nodiscard]]
        constexpr Result<Reference, NTSTATUS> at(SizeType) noexcept
        {
            return Result<Reference, NTSTATUS>(STATUS_ACCESS_VIOLATION);
        }

        [[nodiscard]]
        constexpr Result<ConstReference, NTSTATUS> at(SizeType) const noexcept
        {
            return Result<ConstReference, NTSTATUS>(STATUS_ACCESS_VIOLATION);
        }

        [[nodiscard]]
        constexpr Reference front() noexcept
        {
            return __Array[0];
        }

        [[nodiscard]]
        constexpr ConstReference front() const noexcept
        {
            return __Array[0];
        }

        [[nodiscard]]
        constexpr Reference back() noexcept
        {
            return __Array[0];
        }

        [[nodiscard]]
        constexpr ConstReference back() const noexcept
        {
            return __Array[0];
        }

        [[nodiscard]]
        constexpr Pointer data() noexcept
        {
            return nullptr;
        }

        [[nodiscard]]
        constexpr ConstPointer data() const noexcept
        {
            return nullptr;
        }

        //
        // Iterators
        //

        [[nodiscard]]
        constexpr Iterator begin() noexcept
        {
            return nullptr;
        }

        [[nodiscard]]
        constexpr Iterator end() noexcept
        {
            return nullptr;
        }

        [[nodiscard]]
        constexpr ConstIterator cbegin() const noexcept
        {
            return nullptr;
        }

        [[nodiscard]]
        constexpr ConstIterator cend() const noexcept
        {
            return nullptr;
        }

        //
        // TODO: Add Reverse Iterator
        //

        //
        // Capacity
        //

        [[nodiscard]]
        constexpr SizeType size() const noexcept
        {
            return 0;
        }

        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return true;
        }

        T __Array[1];
    };

    template <class T, size_t N>
    bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) noexcept
    {
        bool status = false;

        do
        {
            if (lhs.size() != rhs.size())
            {
                break;
            }

            for (size_t i = 0; i < lhs.size(); ++i)
            {
                if (lhs[i] != rhs[i])
                {
                    break;
                }
            }

            status = true;

        } while (false);

        return status;
    }

    template <class T, size_t N>
    bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

} // xstar

#endif // _XSTAR_KERNEL_ARRAY_HPP_
