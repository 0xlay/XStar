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
// File: cpplibrary.cpp
// 
// Creator: 0xlay
// 
// Envivroment: Kernel mode only
//
//------------------------------------------------------------------------------

#include "cpplibrary.hpp"


//------------------------------------------------------------------------------
// Standard operators
//------------------------------------------------------------------------------

_Use_decl_annotations_
void* __cdecl operator new(size_t size)
{
    return malloc(size);
}


_Use_decl_annotations_
void* __cdecl operator new[](size_t size)
{
    return malloc(size);
}


_Use_decl_annotations_
void __cdecl operator delete(void* ptr) noexcept
{
    free(ptr);
}


_Use_decl_annotations_
void __cdecl operator delete[](void* ptr) noexcept
{
    free(ptr);
}


// For abstract types.
_Use_decl_annotations_
void __cdecl operator delete(void* ptr, size_t size) noexcept
{
    ASSERT(ptr != nullptr);
    ASSERT(size > 0);
    UNREFERENCED_PARAMETER(size);
    free(ptr);
}

// For abstract types.
_Use_decl_annotations_
void __cdecl operator delete[](void* ptr, size_t size) noexcept
{
    ASSERT(ptr != nullptr);
    ASSERT(size > 0);
    UNREFERENCED_PARAMETER(size);
    free(ptr);
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Placement operators
//------------------------------------------------------------------------------

_Use_decl_annotations_
void* __cdecl operator new(size_t size, void* ptr)
{
    ASSERT(ptr != nullptr);
    ASSERT(size > 0);
    UNREFERENCED_PARAMETER(size);
    return ptr;
}

_Use_decl_annotations_
void* __cdecl operator new[](size_t size, void* ptr)
{
    ASSERT(ptr != nullptr);
    ASSERT(size > 0);
    UNREFERENCED_PARAMETER(size);
    return ptr;
}

_Use_decl_annotations_
void __cdecl operator delete(void*, void*) noexcept
{
    return;
}

_Use_decl_annotations_
void __cdecl operator delete[](void*, void*) noexcept
{ 
    return; 
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Only primitive types !
//------------------------------------------------------------------------------

_Use_decl_annotations_
void* __cdecl operator new(size_t size, PrimitiveType type)
{
    if (type == PrimitiveType::PagedMemory)
    {
        return vmalloc(size);
    }
    else if (type == PrimitiveType::NonPagedMemory)
    {
        return malloc(size);
    }
    ASSERT(false);
    return nullptr;
}

_Use_decl_annotations_
void* __cdecl operator new[](size_t size, PrimitiveType type)
{
    if (type == PrimitiveType::PagedMemory)
    {
        return vmalloc(size);
    }
    else if (type == PrimitiveType::NonPagedMemory)
    {
        return malloc(size);
    }
    ASSERT(false);
    return nullptr;
}

_Use_decl_annotations_
void __cdecl operator delete(void* ptr, PrimitiveType type)
{
    if (type == PrimitiveType::PagedMemory)
    {
        return vfree(ptr);
    }
    else if (type == PrimitiveType::NonPagedMemory)
    {
        return free(ptr);
    }
    ASSERT(false);
}

_Use_decl_annotations_
void __cdecl operator delete[](void* ptr, PrimitiveType type)
{
    if (type == PrimitiveType::PagedMemory)
    {
        return vfree(ptr);
    }
    else if (type == PrimitiveType::NonPagedMemory)
    {
        return free(ptr);
    }
    ASSERT(false);
}

//------------------------------------------------------------------------------