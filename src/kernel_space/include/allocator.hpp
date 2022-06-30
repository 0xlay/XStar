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
#include "meminfo.hpp"
#include "algorithms.hpp"


namespace xstar::ks
{

    /*
     *
     * @brief The AllocTraits is class which describes properties for allocator
     *
     */
    template <class DataType, POOL_TYPE type>
    struct AllocTraits
    {
        using ValueType = DataType;
        using Pointer = ValueType*;
        using ConstPointer = const Pointer;
        using SizeType = size_t;

        enum {Size = sizeof(ValueType)};
        enum {PoolTag = _XSTAR_LIBRARY_TAG_};
        enum {PoolType = type | 16 /*throw exception if allocate was failed */ };
    };

    /*
     *
     * @brief The DefaultAllocator is class which implements simple allocator for
     * kernel-mode
     *
     */
    template <class DataType, class Traits>
    class DefaultAllocator final
    {
    public:
        using AllocTraits = Traits;
        using ValueType = typename AllocTraits::ValueType;
        using Pointer = typename AllocTraits::Pointer;
        using ConstPointer = typename AllocTraits::ConstPointer;
        using SizeType = typename AllocTraits::SizeType;

        //
        // Constructors
        //

        DefaultAllocator() noexcept
            : size_(0), data_(nullptr)
        {}

        DefaultAllocator(const DefaultAllocator& allocator)
        {
            if (allocator != *this)
            {
                size_ = allocator.size();
                allocate(size_);
                memcpy(data_, allocator.get(), size_ * AllocTraits::Size);
            }
        }

        DefaultAllocator(DefaultAllocator&& allocator) noexcept
            : DefaultAllocator()
        {
            if (allocator != *this)
            {
                swap(data_, allocator.data_);
                swap(size_, allocator.size_);
            }
        }

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
            if (allocator != *this)
            {
                deallocate();

                swap(data_, allocator.data_);
                swap(size_, allocator.size_);
            }
            return *this;
        }

        DefaultAllocator& operator=(const DefaultAllocator& allocator)
        {
            if (allocator != *this)
            {
                deallocate();
                size_ = allocator.size();
                allocate(size_);
                memcpy(data_, allocator.get(), size_ * AllocTraits::Size);
            }
            return *this;
        }

        //
        // Public methods
        //

        Pointer allocate(size_t size)
        {
            if (data_)
            {
                deallocate();
            }

            size_t pageSize = 0;
            size_t sizeInBytes = size * AllocTraits::Size;
            while (pageSize < sizeInBytes)
            {
                pageSize += SmallPage_4KB;
            }
            sizeInBytes = pageSize;

            size_ = sizeInBytes / AllocTraits::Size;
#pragma warning(push)
#pragma warning(disable : 4996)
            data_ = static_cast<Pointer>(
                ExAllocatePoolWithTag(static_cast<POOL_TYPE>(AllocTraits::PoolType),
                                      sizeInBytes,
                                      AllocTraits::PoolTag)
            );
#pragma warning(pop)
            return data_;
        }

        void deallocate() noexcept
        {
            if (data_)
            {
                ExFreePoolWithTag(data_, AllocTraits::PoolTag);
                size_ = 0;
                data_ = nullptr;
            }
        }

        [[nodiscard]] SizeType size() const noexcept
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
        SizeType size_;
        Pointer data_;
    };
    
    //
    // Equal and non-equal operators
    //

    template <class DataType, class Traits>
    bool operator== (const DefaultAllocator<DataType, Traits>& lhs,
        const DefaultAllocator<DataType, Traits>& rhs)
    {
        return lhs.get() == rhs.get();
    }

    template <class DataType, class Traits>
    bool operator!= (const DefaultAllocator<DataType, Traits>& lhs,
        const DefaultAllocator<DataType, Traits>& rhs)
    {
        return lhs.get() != rhs.get();
    }

} // xstar::ks
