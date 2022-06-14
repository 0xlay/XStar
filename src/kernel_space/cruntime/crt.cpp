#include "crt.hpp"

//
// Create sections
//

#pragma section(".CRT$XIA", read) // Begin 'C' init section
#pragma section(".CRT$XIZ", read) // End 'C' init section

#pragma section(".CRT$XCA", read) // Begin 'C++' constructor section
#pragma section(".CRT$XCZ", read) // End 'C++' constructor section

#pragma section(".CRT$XPA", read) // Begin 'C' pre-terminator section
#pragma section(".CRT$XPZ", read) // End 'C' pre-terminator section

#pragma section(".CRT$XTA", read) // Begin 'C' terminator section
#pragma section(".CRT$XTZ", read) // End 'C' terminator section

//
// Put .CRT section into .rdata section
//

#pragma comment(linker, "/merge:.CRT=.rdata")

//
// Allocate memory for segments
//

_CRT_ALLOC(".CRT$XIA") _PIFV __xi_a[] = { nullptr };
_CRT_ALLOC(".CRT$XIZ") _PIFV __xi_z[] = { nullptr };

_CRT_ALLOC(".CRT$XCA") _PVFV __xc_a[] = { nullptr };
_CRT_ALLOC(".CRT$XCZ") _PVFV __xc_z[] = { nullptr };

_CRT_ALLOC(".CRT$XPA") _PVFV __xp_a[] = { nullptr };
_CRT_ALLOC(".CRT$XPZ") _PVFV __xp_z[] = { nullptr };

_CRT_ALLOC(".CRT$XTA") _PVFV __xt_a[] = { nullptr };
_CRT_ALLOC(".CRT$XTZ") _PVFV __xt_z[] = { nullptr };

class ExitTable final
{
    // TODO: We will should think about of the optimal algorithm, for allocating table! 
public:
    void create(size_t exitTableSize)
    {
        table_ = static_cast<_PVFV*>(ExAllocatePoolWithTag(
            static_cast<POOL_TYPE>(NonPagedPool | POOL_RAISE_IF_ALLOCATION_FAILURE),
            exitTableSize,
            _CRT_POOL_TAG
        ));
        RtlZeroMemory(table_, exitTableSize);
    }

    void registerFunction(_PVFV function)
    {
        // If i >= exitTableSize than call BSOD
        table_[i] = function;
        ++i;
    }

    void destruct() noexcept
    {
        if (i > 0)
        {
            --i;
            while (true)
            {
                (*table_[i])();
                if (!i) break;
                --i;
            }
        }
        ExFreePoolWithTag(table_, _CRT_POOL_TAG);
    }

private:
    _PVFV* table_ = nullptr;
    size_t i = 0;
};

ExitTable g_ExitTable;


//
// Call C++ constructors
//
CRTAPI static void _initterm(_PVFV* begin, _PVFV* end)
{
    //
    // Walk the table of function pointers, and run functions.
    //

    while (begin != end)
    {
        if (*begin)
        {
            (**begin)();
        }
        ++begin;
    }
}

//
// Call C initializations
//
CRTAPI static int _initterm_e(_PIFV* begin, _PIFV* end)
{
    int result = 0;

    //
    // Walk the table of function pointers, and run functions.
    //

    while (begin != end && result == 0)
    {
        if (*begin)
        {
            result = (**begin)();
        }
        ++begin;
    }
    return result;
}

//
// Call CRT initializations
//
CRTAPI int _crt_init(size_t exitTableSize)
{
    g_ExitTable.create(exitTableSize);

    //
    // Call C initializations
    //

    const int result = _initterm_e(__xi_a, __xi_z);
    if (result != 0)
    {
        return result;
    }

    //
    // Call C++ constructors
    //

    _initterm(__xc_a, __xc_z);
    return 0;
}

//
// Call CRT deinitializations
//
CRTAPI void _crt_deinit()
{
    g_ExitTable.destruct();
    _initterm(__xp_a, __xp_z);
    _initterm(__xt_a, __xt_z);
}

//
// Pure call
//
CRTAPI int __cdecl _purecall()
{
#ifdef DBG
    __debugbreak();
#else
    ::KeBugCheckEx(NO_EXCEPTION_HANDLING_SUPPORT, 0, 0, 0, 0);
#endif
    return 0;
}

//
// Init table
//
CRTAPI int __cdecl atexit(_PVFV function)
{
    g_ExitTable.registerFunction(function);
    return 0;
}
