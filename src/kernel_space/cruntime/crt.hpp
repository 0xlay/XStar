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
// File: crt.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#pragma once
#include <ntddk.h>

//
// Macros
//

#define _CRT_POOL_TAG 'trCX'

#define _CRT_ALLOC(section) \
    extern "C" __declspec(allocate(section))

#define CRTAPI extern "C"

//
// Types
//
using _PVFV = void(__cdecl*)();
using _PIFV = int(__cdecl*)();


CRTAPI int _crt_init(size_t exitTableSize = PAGE_SIZE);
CRTAPI void _crt_deinit();
