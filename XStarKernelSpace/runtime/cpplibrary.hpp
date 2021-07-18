//------------------------------------------------------------------------
// $File: cpplibrary.hpp
// $Date: 10.03.2021
// $Revision: 13.03.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#pragma once

#include "clibrary.hpp"


//-----------------------------------------------------------------------------
// Standard operators
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Placement operators
//-----------------------------------------------------------------------------

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


// For abstract types.
_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete(_Inout_ void* ptr, _In_ size_t size) noexcept;


// For abstract types.
_IRQL_requires_max_(DISPATCH_LEVEL)
void __cdecl operator delete[](_Inout_ void* ptr, _In_ size_t size) noexcept;

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Only primitive types !
//-----------------------------------------------------------------------------

enum class PrimitiveType
{
    PagedMemory,
    NonPagedMemory
};


void* __cdecl operator new(_In_ size_t size, _In_ PrimitiveType type);


void* __cdecl operator new[](_In_ size_t size, _In_ PrimitiveType type);


void __cdecl operator delete(_In_ void* ptr, _In_ PrimitiveType type);


void __cdecl operator delete[](_In_ void* ptr, PrimitiveType);

//-----------------------------------------------------------------------------