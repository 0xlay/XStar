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
// File: iterators.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_ITERATORS_HPP_
#define _XSTAR_KERNEL_ITERATORS_HPP_

namespace xstar::ks
{

    //
    // Tags
    //

    struct InputIteratorTag                                   {};
    struct OutputIteratorTag                                  {};
    struct ForwardIteratorTag : InputIteratorTag              {};
    struct BidirectionalIteratorTag : ForwardIteratorTag      {};
    struct RandomAccessIteratorTag : BidirectionalIteratorTag {};
    struct ContiguousIteratorTag : RandomAccessIteratorTag    {};

    //
    // Traits
    //

    template <class It>
    struct IteratorTraits
    {
        using ValueType = typename It::ValueType;
        using Pointer = typename It::Pointer;
        using Reference = typename It::Reference;
        using IteratorCategory = typename It::IteratorCategory;
    };
    
    ////////////////////////////////////////////////////////////////////////////////
    //
    // The InputIterator
    //
    // Valid expressions: ++a, b++, a == b, a != b, *a, a->member
    //
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class InputIterator
    {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using ConstPointer = const T*;
        using ConstReference = const T&;
        using IteratorCategory = InputIteratorTag;

        InputIterator(T* value) : value_(value)
        { }

        InputIterator(const T* value) : value_(const_cast<T*>(value))
        { }

        InputIterator& operator++() noexcept
        {
            ++value_;
            return *this;
        }

        InputIterator operator++(int) const noexcept
        {
            InputIterator temp = *this;
            ++*this;
            return temp;
        }

        const InputIterator& operator++() const noexcept
        {
            ++value_;
            return *this;
        }

        ConstReference operator*() const
        {
            return *value_;
        }

        ConstPointer operator->() const
        {
            return value_;
        }

        bool operator==(const InputIterator& rhs) const noexcept
        {
            return value_ == rhs.value_;
        }

        bool operator!=(const InputIterator& rhs) const noexcept
        {
            return value_ != rhs.value_;
        }

    protected:
        mutable T* value_;
    };

    ////////////////////////////////////////////////////////////////////////////////
    //
    // The OutputIterator
    //
    // Valid expressions: ++a, b++, *a = 1, a->member = 2
    //
    ////////////////////////////////////////////////////////////////////////////////
    
    template <class T>
    class OutputIterator
    {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using ConstPointer = const T*;
        using ConstReference = const T&;
        using IteratorCategory = OutputIteratorTag;

        OutputIterator(T* value) : value_(value)
        { }

        OutputIterator(const T* value) : value_(const_cast<T*>(value))
        { }

        OutputIterator& operator++() noexcept
        {
            ++value_;
            return *this;
        }

        OutputIterator operator++(int) const noexcept
        {
            OutputIterator temp = *this;
            ++*this;
            return temp;
        }

        const OutputIterator& operator++() const noexcept
        {
            ++value_;
            return *this;
        }

        Reference operator*()
        {
            return *value_;
        }

        Pointer operator->()
        {
            return value_;
        }

    protected:
        mutable T* value_;
    };

    ////////////////////////////////////////////////////////////////////////////////
    //
    // The ForwardIterator
    //
    // Valid expressions:
    //   ++a, b++, a == b, a != b, *a, a->member, *a = 1, a->member = 2
    //
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class ForwardIterator : public InputIterator<T>
    {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using ConstPointer = const T*;
        using ConstReference = const T&;
        using IteratorCategory = ForwardIteratorTag;

        ForwardIterator(T* value) : InputIterator<T>(value)
        { }

        ForwardIterator(const T* value) : InputIterator<T>(value)
        { }

        Reference operator*()
        {
            return *this->value_;
        }

        Pointer operator->()
        {
            return this->value_;
        }

        using InputIterator<T>::operator*;
        using InputIterator<T>::operator->;
    };

    ////////////////////////////////////////////////////////////////////////////////
    //
    // The BidirectionalIterator
    //
    // Valid expressions:
    //   ++a, b++, --a, b--, a == b, a != b, *a, a->member, *a = 1, a->member = 2
    //
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class BidirectionalIterator : public ForwardIterator<T>
    {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using ConstPointer = const T*;
        using ConstReference = const T&;
        using IteratorCategory = BidirectionalIteratorTag;

        BidirectionalIterator(T* value) : ForwardIterator<T>(value)
        { }

        BidirectionalIterator(const T* value) : ForwardIterator<T>(value)
        { }

        BidirectionalIterator& operator--() noexcept
        {
            --this->value_;
            return *this;
        }

        BidirectionalIterator operator--(int) const noexcept
        {
            OutputIterator temp = *this;
            --*this;
            return temp;
        }

        const BidirectionalIterator& operator--() const noexcept
        {
            --this->value_;
            return *this;
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    //
    // The RandomAccessIterator
    //
    // Valid expressions:
    //   ++a, b++, --a, b--, a == b, a != b, *a, a->member, *a = 1, a->member = 2, []
    //
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class RandomAccessIterator : public BidirectionalIterator<T>
    {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using ConstPointer = const T*;
        using ConstReference = const T&;
        using IteratorCategory = RandomAccessIteratorTag;

        RandomAccessIterator(T* value) : BidirectionalIterator<T>(value)
        { }

        RandomAccessIterator(const T* value) : BidirectionalIterator<T>(value)
        { }

        Reference operator[](size_t i)
        {
            return this->value_[i];
        }

        ConstReference operator[](size_t i) const
        {
            return this->value_[i];
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    //
    // The ContiguousIterator
    //
    // Valid expressions: from the RandomAccessIterator
    //
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class ContiguousIterator : public RandomAccessIterator<T>
    {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using ConstPointer = const T*;
        using ConstReference = const T&;
        using IteratorCategory = ContiguousIteratorTag;

        ContiguousIterator(T* value) : RandomAccessIterator<T>(value)
        { }

        ContiguousIterator(const T* value) : RandomAccessIterator(value)
        { }

    };

    ////////////////////////////////////////////////////////////////////////////////
    //
    // The ReverseIterator
    //
    ////////////////////////////////////////////////////////////////////////////////

    template <class RandomIterator>
    class ReverseIterator final
    {
    public:
        using ValueType = typename RandomIterator::ValueType;
        using Pointer = ValueType*;
        using Reference = ValueType&;
        using ConstPointer = const ValueType*;
        using ConstReference = const ValueType&;

        ReverseIterator(RandomIterator value) : value_(value)
        { }

        ReverseIterator& operator++() noexcept
        {
            --value_;
            return *this;
        }

        ReverseIterator operator++(int) const noexcept
        {
            ReverseIterator temp = *this;
            --*this;
            return temp;
        }

        const ReverseIterator& operator++() const noexcept
        {
            --value_;
            return *this;
        }


        ReverseIterator& operator--() noexcept
        {
            ++value_;
            return *this;
        }

        ReverseIterator operator--(int) const noexcept
        {
            ReverseIterator temp = *this;
            ++*this;
            return temp;
        }

        const ReverseIterator& operator--() const noexcept
        {
            ++value_;
            return *this;
        }

        Reference operator*()
        {
            return (*this->value_);
        }

        Pointer operator->()
        {
            return (*value_);
        }

        ConstReference operator*() const
        {
            return (*value_);
        }

        ConstPointer operator->() const
        {
            return (*value_);
        }

        bool operator==(const ReverseIterator& rhs) const noexcept
        {
            return value_ == rhs.value_;
        }

        bool operator!=(const ReverseIterator& rhs) const noexcept
        {
            return value_ != rhs.value_;
        }

    private:
        mutable RandomIterator value_;
    };

} // xstar::ks

#endif // _XSTAR_KERNEL_ITERATORS_HPP_
