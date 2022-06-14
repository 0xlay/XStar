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
// File: nonpaged_memory.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#pragma once

#include "cruntime/clibrary.hpp"

namespace xstar
{

    /**
    *
    * @brief This class implements new and delete operators to allocate non
    * paged memory.
    *
    * @warning IRQL <= DISPATCH_LEVEL
    *
    */
    class NonPagedMemory
    {
    public:
        _IRQL_requires_max_(DISPATCH_LEVEL)
        void* operator new(_In_ size_t size);

        _IRQL_requires_max_(DISPATCH_LEVEL)
        void* operator new[](_In_ size_t size);

        _IRQL_requires_max_(DISPATCH_LEVEL)
        void operator delete(_Inout_ void* ptr) noexcept;

        _IRQL_requires_max_(DISPATCH_LEVEL)
        void operator delete[](_Inout_ void* ptr) noexcept;

        _IRQL_requires_max_(DISPATCH_LEVEL)
        void operator delete(_Inout_ void* ptr, _In_ size_t size) noexcept;

        _IRQL_requires_max_(DISPATCH_LEVEL)
        void operator delete[](_Inout_ void* ptr, _In_ size_t size) noexcept;

        virtual ~NonPagedMemory() = default;
    };


    _Use_decl_annotations_
    inline void* NonPagedMemory::operator new(size_t size)
    {
        return malloc(size);
    }

    _Use_decl_annotations_
    inline void* NonPagedMemory::operator new[](_In_ size_t size)
    {
        return malloc(size);
    }

    _Use_decl_annotations_
    inline void NonPagedMemory::operator delete(_Inout_ void* ptr) noexcept
    {
        free(ptr);
    }

    _Use_decl_annotations_
    inline void NonPagedMemory::operator delete[](_Inout_ void* ptr) noexcept
    {
        free(ptr);
    }

    _Use_decl_annotations_
    inline void NonPagedMemory::operator delete(_Inout_ void* ptr, _In_ size_t size) noexcept
    {
        ASSERT(ptr != nullptr);
        ASSERT(size > 0);
        UNREFERENCED_PARAMETER(size);
        free(ptr);
    }

    _Use_decl_annotations_
    inline void NonPagedMemory::operator delete[](_Inout_ void* ptr, _In_ size_t size) noexcept
    {
        ASSERT(ptr != nullptr);
        ASSERT(size > 0);
        UNREFERENCED_PARAMETER(size);
        free(ptr);
    }

} // xstar
