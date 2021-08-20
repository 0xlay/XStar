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
// File: paged_memory.hpp
// 
// Creator: 0xlay
// 
// Envivroment: Kernel mode only
//
//------------------------------------------------------------------------------

#pragma once

#include "clibrary.hpp"

/**
* 
* \brief This class implements new and delete operators to allocate paged 
* memory.
* 
* \warning IRQL <= APC_LEVEL
* 
*/
class PagedMemory
{
public:
    _IRQL_requires_max_(APC_LEVEL)
    void* operator new(_In_ size_t size);

    _IRQL_requires_max_(APC_LEVEL)
    void* operator new[](_In_ size_t size);

    _IRQL_requires_max_(APC_LEVEL)
    void operator delete(_Inout_ void* ptr) noexcept;

    _IRQL_requires_max_(APC_LEVEL)
    void operator delete[](_Inout_ void* ptr) noexcept;

    _IRQL_requires_max_(APC_LEVEL)
    void operator delete(_Inout_ void* ptr, _In_ size_t size) noexcept;

    _IRQL_requires_max_(APC_LEVEL)
    void operator delete[](_Inout_ void* ptr, _In_ size_t size) noexcept;
};


_Use_decl_annotations_
inline void* PagedMemory::operator new(size_t size)
{
    return vmalloc(size);
}

_Use_decl_annotations_
inline void* PagedMemory::operator new[](size_t size)
{
    return vmalloc(size);
}

_Use_decl_annotations_
inline void PagedMemory::operator delete(void* ptr) noexcept
{
    vfree(ptr);
}

_Use_decl_annotations_
inline void PagedMemory::operator delete[](void* ptr) noexcept
{
    vfree(ptr);
}

_Use_decl_annotations_
inline void PagedMemory::operator delete(void* ptr, size_t size) noexcept
{
    ASSERT(ptr != nullptr);
    ASSERT(size > 0);
    UNREFERENCED_PARAMETER(size);
    vfree(ptr);
}

_Use_decl_annotations_
inline void PagedMemory::operator delete[](void* ptr, size_t size) noexcept
{
    ASSERTMSG(L"Paged", ptr != nullptr);
    ASSERT(size > 0);
    UNREFERENCED_PARAMETER(size);
    vfree(ptr);
}
