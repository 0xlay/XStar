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
// File: symbolic_link.hpp
// 
// Creator: 0xlay
// 
// Environment: Kernel mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_SYMBOLIC_LINK_HPP_
#define _XSTAR_KERNEL_SYMBOLIC_LINK_HPP_

#include <ntddk.h>
#include  <ntstrsafe.h>
#include "algorithms.hpp"
#include "cruntime/cpplibrary.hpp"
#include "meminfo.hpp"

namespace xstar
{

    /*
     * @brief The SymbolicLink is the interface for working with symbolic links.
     * @warning It must creates on the IRQL == PASSIVE_LEVEL.
     * @warning The SymbolicLink constructor generating exception, and we must handled with __try/__except.
     */
    template <POOL_TYPE type = PagedPool, ULONG tag = _XSTAR_LIBRARY_TAG_>
    class SymbolicLink final
    {
    public:

        //
        // Constructors
        //

        SymbolicLink(const wchar_t* symbolicName, const wchar_t* deviceName)
        {
            if (symbolicName == nullptr || deviceName == nullptr)
            {
                ExRaiseStatus(STATUS_ACCESS_VIOLATION);
            }

            symbolicName_.Buffer = static_cast<PWCH>(ExAllocatePoolWithTag(
                static_cast<POOL_TYPE>(type | 16), SmallPage_4KB, tag
            ));
            RtlZeroMemory(symbolicName_.Buffer, SmallPage_4KB);
            symbolicName_.MaximumLength = SmallPage_4KB;

            deviceName_.Buffer = static_cast<PWCH>(ExAllocatePoolWithTag(
                static_cast<POOL_TYPE>(type | 16), SmallPage_4KB, tag
            ));
            RtlZeroMemory(deviceName_.Buffer, SmallPage_4KB);
            deviceName_.MaximumLength = SmallPage_4KB;

            RtlUnicodeStringCopyString(&symbolicName_, symbolicName);
            RtlUnicodeStringCopyString(&deviceName_, deviceName);

            const NTSTATUS status = IoCreateSymbolicLink(&symbolicName_, &deviceName_);
            if (!NT_SUCCESS(status))
            {
                ExRaiseStatus(status);
            }
        }

        SymbolicLink(const SymbolicLink&) = delete;

        SymbolicLink(SymbolicLink&& other) noexcept
        {
            if (&other != this)
            {
                other.swap(*this);
            }
        }

        //
        // Destructor
        //

        ~SymbolicLink() noexcept
        {
            IoDeleteSymbolicLink(&symbolicName_);
            if (symbolicName_.Buffer)
            {
                ExFreePoolWithTag(symbolicName_.Buffer, tag);
            }
            if (deviceName_.Buffer)
            {
                ExFreePoolWithTag(deviceName_.Buffer, tag);
            }
        }

        //
        // Operators
        //

        SymbolicLink& operator=(const SymbolicLink&) = delete;

        SymbolicLink& operator=(SymbolicLink&& other) noexcept
        {
            if (&other != this)
            {
                other.swap(*this);
            }
            return *this;
        }

        void* operator new(size_t size)
        {
            return ExAllocatePoolWithTag(static_cast<POOL_TYPE>(type | 16), size, tag);
        }

        void operator delete(void* ptr)
        {
            if (ptr)
            {
                ExFreePoolWithTag(ptr, tag);
            }
        }

        //
        // Accessors
        //
        [[nodiscard]]
        PUNICODE_STRING name() noexcept
        {
            return &symbolicName_;
        }

        [[nodiscard]]
        PUNICODE_STRING deviceName() noexcept
        {
            return &deviceName_;
        }

        [[nodiscard]]
        const PUNICODE_STRING name() const noexcept
        {
            return (const PUNICODE_STRING)&symbolicName_;
        }

        [[nodiscard]]
        const PUNICODE_STRING deviceName() const noexcept
        {
            return (const PUNICODE_STRING)&deviceName_;
        }

    private:
        void swap(SymbolicLink& other) noexcept
        {
            xstar::swap(symbolicName_, other.symbolicName_);
            xstar::swap(deviceName_, other.deviceName_);
        }

    private:
        UNICODE_STRING symbolicName_{};
        UNICODE_STRING deviceName_{};
    };

} // xstar

#endif // _XSTAR_KERNEL_SYMBOLIC_LINK_HPP_
