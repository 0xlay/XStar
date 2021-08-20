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
// File: start_win_driver.hpp
// 
// Creator: 0xlay
// 
// Envivroment: User mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_USER_START_WIN_DRIVER_HPP_
#define _XSTAR_USER_START_WIN_DRIVER_HPP_


#include <Windows.h>
#include <string>
#include <cstdint>
#include <exception>


#include "smart_handle.hpp"
#include "winapi_exception.hpp"


namespace xstar
{

    class StartWinDriver
    {
        using EntryPoint = LPSERVICE_MAIN_FUNCTIONW;

    public:
        StartWinDriver(
            const wchar_t* serviceName,
            const wchar_t* pcName = nullptr,
            const wchar_t* dbName = nullptr,
            uint32_t access = SERVICE_ALL_ACCESS
        );
        StartWinDriver(const wchar_t* serviceName, uint32_t access);
        ~StartWinDriver();


        StartWinDriver(const StartWinDriver&) = delete;
        void operator=(const StartWinDriver&) = delete;
        StartWinDriver(StartWinDriver&&) = delete;
        StartWinDriver& operator=(StartWinDriver&&) = delete;


        //---------------------------------------------------------
        // Methods for communication with service
        //---------------------------------------------------------
        void Control(uint32_t control);
        const wchar_t* getName() const noexcept;
        const wchar_t* getPath() const noexcept;


    private:
        std::wstring serviceName_;
        std::wstring fullServicePath_;

        SmartHandle<SC_HANDLE> SCM_;
        SmartHandle<SC_HANDLE> service_;

        SERVICE_STATUS ServiceStatus_;
        bool serviceCreated_ = false;
    };



} // xstar
#endif // _XSTAR_USER_START_WIN_DRIVER_HPP_
