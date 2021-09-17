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
// File: clibrary.hpp
// 
// Creator: 0xlay
// 
// Envivroment: Kernel mode only
//
//------------------------------------------------------------------------------

#pragma once

#include <ntddk.h>


#define _C_LIBRARY_TAG_ 'RATS' // STAR

/**
* @brief This macro gets a pointer to base in the MEMBLOCK structure
*/
#define getBasePointer(data_ptr)\
 (static_cast<char*>(data_ptr) - sizeof(size_t))

/**
* @brief This macro gets a pointer to data in the MEMBLOCK structure
*/
#define getDataPointer(base_ptr)\
 (reinterpret_cast<char*>(base_ptr) + sizeof(size_t))


#pragma pack(push, 1)
typedef struct _MEMBLOCK
{
    size_t size;
    void* data;
} MEMBLOCK, *PMEMBLOCK;
#pragma pack(pop)


EXTERN_C_START

//------------------------------------------------------------------------------
// Non paged memory
//------------------------------------------------------------------------------

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(size)
_IRQL_requires_max_(DISPATCH_LEVEL)
void* __cdecl malloc(_In_ size_t size) noexcept;

_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl free(_Inout_ void* ptr) noexcept;

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(size)
_IRQL_requires_max_(DISPATCH_LEVEL)
void* __cdecl calloc(_In_ size_t num, _In_ size_t size) noexcept;

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(new_size)
_IRQL_requires_max_(DISPATCH_LEVEL)
void* __cdecl realloc(_Inout_ void* ptr, _In_ size_t new_size) noexcept;

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Paged memory
//------------------------------------------------------------------------------

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_ 
_Post_writable_size_(size)
_IRQL_requires_max_(APC_LEVEL)
void* vmalloc(_In_ size_t size) noexcept;

_IRQL_requires_max_(APC_LEVEL)
void __cdecl vfree(_Inout_ void* ptr) noexcept;

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(size)
_IRQL_requires_max_(APC_LEVEL)
void* __cdecl vcalloc(_In_ size_t num, _In_ size_t size) noexcept;

__drv_when(return != 0, __drv_allocatesMem(ptr))
_Check_return_
_Post_writable_size_(new_size)
_IRQL_requires_max_(APC_LEVEL)
void* __cdecl vrealloc(_Inout_ void* ptr, _In_ size_t new_size) noexcept;

//------------------------------------------------------------------------------

EXTERN_C_END


#ifdef ALLOC_PRAGMA

#pragma alloc_text(PAGE, vmalloc)
#pragma alloc_text(PAGE, vfree)
#pragma alloc_text(PAGE, vcalloc)
#pragma alloc_text(PAGE, vrealloc)

#endif
