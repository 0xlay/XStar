//------------------------------------------------------------------------
// $File: PagedMemory.hpp
// $Date: 13.03.2021
// $Revision: 13.03.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#pragma once

#include "clibrary.hpp"

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
    ASSERT(ptr != nullptr);
    ASSERT(size > 0);
    UNREFERENCED_PARAMETER(size);
    vfree(ptr);
}
