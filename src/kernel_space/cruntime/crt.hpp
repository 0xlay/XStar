#pragma once
#include <ntddk.h>

//
// Macros
//

#define _CRT_ALLOC(section) \
    extern "C" __declspec(allocate(section))

#define CRTAPI extern "C"

//
// Types
//
using _PVFV = void(__cdecl*)();
using _PIFV = int(__cdecl*)();

CRTAPI int _crt_init();
CRTAPI void _crt_deinit();