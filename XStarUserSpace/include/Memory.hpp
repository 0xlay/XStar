//------------------------------------------------------------------------
// File: Memory.hpp
// Date: 02.05.2021
// Revision: 02.05.2021
// Creator: 0xlay
// Description: 
//------------------------------------------------------------------------

#ifndef _XSTAR_USER_MEMORY_HPP_
#define _XSTAR_USER_MEMORY_HPP_

#include <Windows.h>

namespace xstar
{

    enum VirtualMemory
    {
        SmallPage_4KB = 4'096u,
        LargePage_2MB = 2'097'152u,

        #if WINVER >= _WIN32_WINNT_WIN10
        HugePage_1GB = 1'073'741'824
        #endif
    };

} // xstar
#endif // _XSTAR_USER_MEMORY_HPP_