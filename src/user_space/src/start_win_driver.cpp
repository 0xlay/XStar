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
// File: start_win_driver.cpp
// 
// Creator: 0xlay
// 
// Environment: User mode only
//
//------------------------------------------------------------------------------

#include "start_win_driver.hpp"


namespace xstar
{
    //-------------------------------------------------------------
    // Complexity: O(1)
    // Parameters: 
    //	service name
    //	computer name: default = nullptr
    //	database name: default = nullptr
    //	service access: default = SERVICE_ALL_ACCESS
    //-------------------------------------------------------------
    StartWinDriver::StartWinDriver(
        const wchar_t* serviceName,
        const wchar_t* pcName,
        const wchar_t* dbName,
        uint32_t access
    )
        : serviceName_(serviceName), ServiceStatus_{ 0 }
    {
        SCM_ = OpenSCManager(pcName, dbName, SC_MANAGER_ALL_ACCESS);
        if (!SCM_.getHandle())
            throw WinAPIException();


        fullServicePath_.reserve(MAX_PATH);
        uint32_t cntBytes = GetFullPathNameW(
            (serviceName_ + L".sys").c_str(),
            static_cast<DWORD>(fullServicePath_.capacity()),
            &fullServicePath_[0],
            nullptr
        );
        if (cntBytes == 0)
            throw WinAPIException();


        service_ = OpenService(SCM_.getHandle(), serviceName_.c_str(), access);
        if (!service_.getHandle())
        {
            service_ = CreateService(
                SCM_.getHandle(),
                serviceName_.c_str(), serviceName_.c_str(),
                access | DELETE,
                SERVICE_KERNEL_DRIVER,
                SERVICE_DEMAND_START,
                SERVICE_ERROR_IGNORE,
                fullServicePath_.c_str(),
                nullptr, nullptr, nullptr, nullptr, nullptr
            );
            if (!service_.getHandle())
                throw WinAPIException();


            serviceCreated_ = true;
        }


        if (!StartService(service_.getHandle(), 0, nullptr))
            throw WinAPIException();
    }

    //-------------------------------------------------------------
    // Complexity: O(1)
    // Parameters: service name and service access
    //-------------------------------------------------------------
    StartWinDriver::StartWinDriver(const wchar_t* serviceName, uint32_t access)
        : StartWinDriver(serviceName, nullptr, nullptr, access)
    { }

    //-------------------------------------------------------------
    // Complexity: O(1)
    //-------------------------------------------------------------
    StartWinDriver::~StartWinDriver()
    {
        if (ServiceStatus_.dwCurrentState != SERVICE_STOPPED)
            Control(SERVICE_CONTROL_STOP);

        if (serviceCreated_)
            DeleteService(service_.getHandle());
    }


    //-------------------------------------------------------------
    // Complexity:	O(1)
    // Parameter:	service control constant (SERVICE_CONTROL_STOP)
    //-------------------------------------------------------------
    void StartWinDriver::Control(uint32_t control)
    {
        if (!ControlService(service_.getHandle(), control, &ServiceStatus_))
            throw WinAPIException();
    }

    //-------------------------------------------------------------
    // Complexity: O(1)
    //-------------------------------------------------------------
    const wchar_t* StartWinDriver::getName() const noexcept
    {
        return serviceName_.c_str();
    }

    //-------------------------------------------------------------
    // Complexity: O(1)
    //-------------------------------------------------------------
    const wchar_t* StartWinDriver::getPath() const noexcept
    {
        return fullServicePath_.c_str();
    }



} // xstar
