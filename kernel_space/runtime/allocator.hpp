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
// File: allocator.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#pragma once

#include <wdm.h>
#include "types.hpp"
#include "meminfo.hpp"
#include "algorithms.hpp"


namespace xstar
{

    /*
     *
     * @brief The DefaultAllocator is class which implements simple allocator for
     * kernel-mode.
     *
     */
    template <class DataType, POOL_TYPE type, Tag tag>
    class DefaultAllocator final
    {
    public:
        using Pointer = DataType*;
        using ConstPointer = const Pointer;

        //
        // Constructors
        //

        DefaultAllocator() noexcept
            : size_(0), data_(nullptr)
        {}

        DefaultAllocator(DefaultAllocator&& allocator) noexcept
            : DefaultAllocator()
        {
            swap(data_, allocator.data_);
            swap(size_, allocator.size_);
        }

        DefaultAllocator(const DefaultAllocator& allocator) = delete;

        //
        // Destructor
        //

        ~DefaultAllocator() noexcept
        {
            deallocate();
        }

        //
        // Public operators
        //

        DefaultAllocator& operator=(DefaultAllocator&& allocator) noexcept
        {
            deallocate();

            swap(data_, allocator.data_);
            swap(size_, allocator.size_);

            return *this;
        }

        DefaultAllocator& operator=(const DefaultAllocator& allocator) = delete;

        //
        // Public methods
        //

        [[nodiscard]] Pointer allocate(size_t size) noexcept
        {
            if (data_)
            {
                deallocate();
            }

            size_t pageSize = 0;
            while (pageSize < size)
            {
                pageSize += SmallPage_4KB;
            }

            size_ = pageSize;
            data_ = ExAllocatePoolWithTag(type, size_, tag);

            return data_;
        }

        void deallocate() noexcept
        {
            if (data_)
            {
                ExFreePoolWithTag(data_, tag);
                size_ = 0;
                data_ = nullptr;
            }
        }

        [[nodiscard]] size_t size() const noexcept
        {
            return size_;
        }

        [[nodiscard]] ConstPointer get() const noexcept
        {
            return data_;
        }

        [[nodiscard]] Pointer get() noexcept
        {
            return data_;
        }

    //
    // Private data
    //

    private:
        size_t size_;
        Pointer data_;
    };

} // xstar
