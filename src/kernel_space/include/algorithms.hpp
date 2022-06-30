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
// File: algorithms.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_ALGORITHMS_HPP_
#define _XSTAR_KERNEL_ALGORITHMS_HPP_

#include "type_traits.hpp"

namespace xstar::ks
{

    template <typename T>
    void swap(T& firstValue, T& secondValue) noexcept
    {
        T tempValue = move(firstValue);
        firstValue = move(secondValue);
        secondValue = move(tempValue);
    }

} // xstar::ks

#endif // _XSTAR_KERNEL_ALGORITHMS_HPP_
