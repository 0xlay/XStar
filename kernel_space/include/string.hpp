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
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_STRING_HPP_
#define _XSTAR_KERNEL_STRING_HPP_

#include "allocator.hpp"

namespace xstar
{

    /*
     *
     * @brief The CharTraits is class which describes properties for BasicString
     *
     */
    template<class T>
    struct CharTraits
    {
        using CharType = T;
        using ArgType = const CharType*;
        using Reference = CharType&;
        using ConstReference = const CharType&;
        using Pointer = CharType*;
        using ConstPointer = const CharType*;
        using Iterator = CharType*;
        using ConstIterator = const CharType*;
        using SizeType = size_t;

        static constexpr SizeType size = sizeof(CharType);

        static constexpr void assign(CharType& dst, const CharType& src) noexcept
        {
            dst = src;
        }

        static SizeType length(ArgType str)
        {
            SizeType len = 0;
            for (; str[len] != 0; ++len);
            return len;
        }

        static void copy(Pointer dst, ArgType src, SizeType numOfElem)
        {
            memcpy(dst, src, numOfElem * size);
        }

        static int compare(ArgType lhs, ArgType rhs)
        {
            int flag = 0;

            for (SizeType i = 0; lhs[i] != 0 || rhs[i] != 0; ++i)
            {
                if (lhs[i] < rhs[i])
                {
                    --flag;
                    break;
                }
                if (lhs[i] > rhs[i])
                {
                    ++flag;
                    break;
                }
            }

            return flag;
        }

    };

    /*
     *
     * @brief The BasicString is class which implements string for kernel-mode.
     *
     */
    template <
        class CharT,
        class Traits,
        class Allocator
    >
    class BasicString final
    {
    public:
        using CharTraits = Traits;
        using CharType = typename  CharTraits::CharType;
        using ArgType = typename CharTraits::ArgType;
        using Reference = typename CharTraits::Reference;
        using ConstReference = typename CharTraits::ConstReference;
        using Pointer = typename CharTraits::Pointer;
        using ConstPointer = typename CharTraits::ConstPointer;
        using Iterator = typename CharTraits::Iterator;
        using ConstIterator = typename CharTraits::ConstIterator;
        using SizeType = typename CharTraits::SizeType;

        //
        // Constructors
        //

        BasicString()
            : size_(0)
        { }

        explicit BasicString(size_t size)
            : size_(size)
        {
            allocator_.allocate(size_);
        }

        BasicString(ArgType arg)
            : size_(CharTraits::length(arg) + 1)
        {
            allocator_.allocate(size_);
            CharTraits::copy(allocator_.get(), arg, size_);
        }

        BasicString(const BasicString& other)
        {
            if (other != *this)
            {
                size_ = other.size_;
                allocator_ = other.allocator_;
            }
        }

        BasicString(BasicString&& other) noexcept
        {
            if (other != *this)
            {
                size_ = move(other.size_);
                allocator_ = move(other.allocator_);
            }
        }

        //
        // Destructor
        //

        ~BasicString()
        {
            allocator_.deallocate();
        }

        //
        // Operators
        //

        BasicString& operator=(const BasicString& other)
        {
            if (other != *this)
            {
                size_ = other.size_;
                allocator_ = other.allocator_;
            }
            return *this;
        }

        BasicString& operator=(BasicString&& other) noexcept
        {
            if (other != *this)
            {
                size_ = move(other.size_);
                allocator_ = move(other.allocator_);
            }
            return *this;
        }

        Reference operator[](SizeType i) noexcept
        {
            return allocator_.get()[i];
        }

        Reference operator[](SizeType i) const noexcept
        {
            return allocator_.get()[i];
        }

        BasicString& operator+(const BasicString& rhs)
        {
            SizeType curSize = size();
            size_ += rhs.size();

            if (size_ <= capacity())
            {
                CharTraits::copy(allocator_.get() + curSize,
                                 rhs.allocator_.get(),
                                 rhs.size() + 1);
            }
            else
            {
                Allocator tmpAllocator;
                tmpAllocator.allocate(size_);
                CharTraits::copy(tmpAllocator.get(),
                                 allocator_.get(),
                                 curSize);
                CharTraits::copy(tmpAllocator.get() + curSize,
                                 rhs.allocator_.get(),
                                 rhs.size() + 1);
                allocator_ = move(tmpAllocator);
            }

            return *this;
        }

        BasicString& operator+=(const BasicString& rhs)
        {
            return (*this + rhs);
        }

        bool operator==(const BasicString& rhs) const noexcept
        {
            return (CharTraits::compare(cbegin(), rhs.cbegin()) == 0);
        }

        bool operator!=(const BasicString& rhs) const noexcept
        {
            return !(cbegin() == rhs.cbegin());
        }

        bool operator<(const BasicString& rhs) const noexcept
        {
            return (CharTraits::compare(cbegin(), rhs.cbegin()) < 0);
        }

        bool operator>(const BasicString& rhs) const noexcept
        {
            return (CharTraits::compare(cbegin(), rhs.cbegin()) > 0);
        }

        bool operator<=(const BasicString& rhs) const noexcept
        {
            return (CharTraits::compare(cbegin(), rhs.cbegin()) <= 0);
        }

        bool operator>=(const BasicString& rhs) const noexcept
        {
            return (CharTraits::compare(cbegin(), rhs.cbegin()) >= 0);
        }

        //
        // Size
        //

        [[nodiscard]] SizeType capacity() const noexcept
        {
            return allocator_.size();
        }

        [[nodiscard]] SizeType size() const noexcept
        {
            return size_ - 1; /* without '\0' */
        }

        //
        // Iterators
        //

        [[nodiscard]] Iterator begin() noexcept
        {
            return allocator_.get();
        }

        [[nodiscard]] Iterator end() noexcept
        {
            return allocator_.get() + size();
        }

        [[nodiscard]] ConstIterator cbegin() const noexcept
        {
            return allocator_.get();
        }

        [[nodiscard]] ConstIterator cend() const noexcept
        {
            return allocator_.get() + size();
        }

    //
    // Private data
    //

    private:
        SizeType size_;
        Allocator allocator_;
    };

    //
    // Aliases
    //

    template <POOL_TYPE poolType>
    using String = BasicString<
        char,
        CharTraits<char>,
        DefaultAllocator<char, AllocTraits<char, poolType>>
    >;

    template <POOL_TYPE poolType>
    using WideString = BasicString<
        wchar_t,
        CharTraits<wchar_t>,
        DefaultAllocator<wchar_t, AllocTraits<wchar_t, poolType>>
    >;

} // xstar

#endif // _XSTAR_KERNEL_STRING_HPP_
