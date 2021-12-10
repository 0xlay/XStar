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
// File: meminfo.hpp
// 
// Creator: 0xlay
// 
// Environment: User mode and Kernel mode
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_COMMON_MEMINFO_HPP_
#define _XSTAR_COMMON_MEMINFO_HPP_

#include <sdkddkver.h>

namespace xstar
{

    enum VirtualMemory
    {
        SmallPage_4KB = 4'096u,           ///< Small page = 4KB
        LargePage_2MB = 2'097'152u,       ///< Large page = 2MB
        #if WINVER >= _WIN32_WINNT_WIN10
        HugePage_1GB  = 1'073'741'824     ///< Huge page = 1GB (since Windows 10 and high)
        #endif
    };

} // xstar
#endif // _XSTAR_COMMON_MEMINFO_HPP_