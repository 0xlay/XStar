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
// File: cpplibrary.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#pragma once

#include "clibrary.hpp"


//------------------------------------------------------------------------------
// Standard operators
//------------------------------------------------------------------------------

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(size)
_IRQL_requires_max_(DISPATCH_LEVEL)
void* __cdecl operator new(_In_ size_t size);

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(size)
_IRQL_requires_max_(DISPATCH_LEVEL)
void* __cdecl operator new[](_In_ size_t size);

// For primitive types
_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete(_Inout_ void* ptr) noexcept;

// For primitive types.
_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete[](_Inout_ void* ptr) noexcept;

// For abstract types.
_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete(_Inout_ void* ptr, _In_ size_t size) noexcept;

// For abstract types.
_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete[](_Inout_ void* ptr, _In_ size_t size) noexcept;

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Placement operators
//------------------------------------------------------------------------------

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(size)
_IRQL_requires_max_(DISPATCH_LEVEL)
void* __cdecl operator new(_In_ size_t size, _In_ void* ptr);

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(size)
_IRQL_requires_max_(DISPATCH_LEVEL)
void* __cdecl operator new[](_In_ size_t size, _In_ void* ptr);

_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete(void*, void*) noexcept;

_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete[](void*, void*) noexcept;

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Only primitive types !
//------------------------------------------------------------------------------

enum class PrimitiveType
{
    PagedMemory,    ///< Allocate from paged pool memory
    NonPagedMemory  ///< Allocate from non paged pool memory
};

/**
* @brief Example: auto ptr = operator new(100, PrimitiveType::PagedMemory)
*/
void* __cdecl operator new(_In_ size_t size, _In_ PrimitiveType type);

/**
* @brief Example: auto ptr = operator new[](100, PrimitiveType::PagedMemory)
*/
void* __cdecl operator new[](_In_ size_t size, _In_ PrimitiveType type);

/**
* @brief Example: operator delete(ptr, PrimitiveType::PagedMemory)
*/
void __cdecl operator delete(_In_ void* ptr, _In_ PrimitiveType type);

/**
* @brief Example: operator delete[](ptr, PrimitiveType::PagedMemory)
*/
void __cdecl operator delete[](_In_ void* ptr, PrimitiveType type);

//------------------------------------------------------------------------------
