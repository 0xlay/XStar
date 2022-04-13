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
// File: clibrary.cpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#include "clibrary.hpp"


//------------------------------------------------------------------------------
// Non paged memory
//------------------------------------------------------------------------------

_Use_decl_annotations_
void* __cdecl malloc(size_t size) noexcept
{
    ASSERT(size != 0);

    #if (NTDDI_VERSION >= NTDDI_WIN10_VB) // minimum Windows 10 2004
    PMEMBLOCK memoryBlock = static_cast<PMEMBLOCK>(
        ExAllocatePool2(
            POOL_FLAG_NON_PAGED | POOL_FLAG_CACHE_ALIGNED,
            size + sizeof(MEMBLOCK),
            _XSTAR_LIBRARY_TAG_
        )
    );
    #else // deprecated in Windows 10 2004
    PMEMBLOCK memoryBlock = static_cast<PMEMBLOCK>(
        ExAllocatePoolWithTag(
            NonPagedPoolNxCacheAligned, // alignment
            size + sizeof(MEMBLOCK),
            _C_LIBRARY_TAG_
        )
    );
    #endif

    if (!memoryBlock)
        return nullptr;

    memoryBlock->size = size;
    memoryBlock->data = getDataPointer(memoryBlock);
    return memoryBlock->data;
}

_Use_decl_annotations_
void __cdecl free(void* ptr) noexcept
{
    if (ptr)
    {
        ExFreePoolWithTag(
            getBasePointer(ptr), /* returns the base address of an instance of a structure */
            _XSTAR_LIBRARY_TAG_
        );
        ptr = nullptr;
    }
}

_Use_decl_annotations_
void* __cdecl calloc(size_t num, size_t size) noexcept
{
    size_t size_ = num * size;
    ASSERT(size_ != 0);

    void* ptr = malloc(size_);
    if (!ptr)
        return nullptr;
    
    return RtlZeroMemory(ptr, size_);
}

_Use_decl_annotations_
void* __cdecl realloc(void* ptr, size_t new_size) noexcept
{
    size_t current_size = reinterpret_cast<PMEMBLOCK>(getBasePointer(ptr))->size;
    if (current_size <= new_size)
        return ptr;

    free(ptr);
    ptr = malloc(new_size);
    return ptr;
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Paged memory
//-----------------------------------------------------------------------------

_Use_decl_annotations_
void* vmalloc(size_t size) noexcept
{
    PAGED_CODE();
    ASSERT(size != 0);

    #if (NTDDI_VERSION >= NTDDI_WIN10_VB) // minimum Windows 10 2004
    PMEMBLOCK memoryBlock = static_cast<PMEMBLOCK>(
        ExAllocatePool2(
            POOL_FLAG_PAGED | POOL_FLAG_CACHE_ALIGNED,
            size + sizeof(MEMBLOCK),
            _XSTAR_LIBRARY_TAG_
        )
    );
    #else // deprecated in Windows 10 2004
    PMEMBLOCK memoryBlock = static_cast<PMEMBLOCK>(
        ExAllocatePoolWithTag(
            PagedPoolCacheAligned, // alignment
            size + sizeof(MEMBLOCK),
            _C_LIBRARY_TAG_
        )
    );
    #endif
    if (!memoryBlock)
        return nullptr;
    
    memoryBlock->size = size;
    memoryBlock->data = getDataPointer(memoryBlock);
    return memoryBlock->data;
}

_Use_decl_annotations_
void __cdecl vfree(void* ptr) noexcept
{
    PAGED_CODE();
    free(ptr);
}

_Use_decl_annotations_
void* __cdecl vcalloc(size_t num, size_t size) noexcept
{
    PAGED_CODE();
    size_t size_ = num * size;
    ASSERT(size_ != 0);

    void* ptr = vmalloc(size_);
    if (!ptr)
        return nullptr;

    return RtlZeroMemory(ptr, size_);
}

_Use_decl_annotations_
void* __cdecl vrealloc(void* ptr, size_t new_size) noexcept
{
    PAGED_CODE();
    size_t current_size = reinterpret_cast<PMEMBLOCK>(getBasePointer(ptr))->size;
    if (current_size <= new_size)
        return ptr;

    vfree(ptr);
    ptr = vmalloc(new_size);
    return ptr;
}

//------------------------------------------------------------------------------
