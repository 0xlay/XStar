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
// File: named_pipe.hpp
// 
// Creator: 0xlay
// 
// Environment: User mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_USER_NAMED_PIPE_HPP_
#define _XSTAR_USER_NAMED_PIPE_HPP_

#include <string>
#include <memory>
#include <vector>

#include <Windows.h>
#include <tchar.h>

#include "winapi_exception.hpp"
#include "meminfo.hpp"


namespace xstar
{

    ////////////////////////////////////////////////////////////////////////////
    //
    // The PipeDirection
    //
    ////////////////////////////////////////////////////////////////////////////

    enum class PipeDirection : DWORD
    {
        In           = PIPE_ACCESS_INBOUND,
        Out          = PIPE_ACCESS_OUTBOUND,
        InOut        = PIPE_ACCESS_DUPLEX,

        Exclusive    = FILE_FLAG_FIRST_PIPE_INSTANCE,

        WriteThrough = FILE_FLAG_WRITE_THROUGH,
        Overlapped   = FILE_FLAG_OVERLAPPED,

        WriteOwner   = WRITE_OWNER,
        WriteACL     = WRITE_DAC,
        WriteSACL    = ACCESS_SYSTEM_SECURITY
    };

    inline PipeDirection operator | (PipeDirection lhs, PipeDirection rhs)
    {
        return static_cast<PipeDirection>((DWORD)lhs | (DWORD)rhs);
    }



    ////////////////////////////////////////////////////////////////////////////
    //
    // The PipeMode
    //
    ////////////////////////////////////////////////////////////////////////////

    enum class PipeMode : DWORD
    {
        WriteByte     = PIPE_TYPE_BYTE,
        ReadByte      = PIPE_READMODE_BYTE,

        WriteMsg      = PIPE_TYPE_MESSAGE,
        ReadMsg       = PIPE_READMODE_MESSAGE,

        Wait          = PIPE_WAIT,
        NoWait        = PIPE_NOWAIT,

        AcceptClients = PIPE_ACCEPT_REMOTE_CLIENTS,
        RejectClients = PIPE_REJECT_REMOTE_CLIENTS
    };

    inline PipeMode operator | (PipeMode lhs, PipeMode rhs)
    {
        return static_cast<PipeMode>((DWORD)lhs | (DWORD)rhs);
    }



    ////////////////////////////////////////////////////////////////////////////
    //
    // The PipeAccess
    //
    ////////////////////////////////////////////////////////////////////////////

    enum class PipeAccess : DWORD
    {
        Write = GENERIC_WRITE,
        Read  = GENERIC_READ,
        InOut = GENERIC_READ | GENERIC_WRITE
    };

    struct PipeInfo
    {
        DWORD flags;
        DWORD outBufSize;
        DWORD inBufSize;
        DWORD maxInstances;
    };

    struct PipeState
    {
        PipeMode mode;
        DWORD curInstances;
    };



    ////////////////////////////////////////////////////////////////////////////
    //
    // The PipeIO
    //
    ////////////////////////////////////////////////////////////////////////////

    class PipeIO
    {
    public:
        void connectToPipe(HANDLE pipe, DWORD maxNumOfChar = SmallPage_4KB);
        virtual ~PipeIO() = default;

        void write(const std::string& msg);
        void write(const std::wstring& msg);
        void write(const std::vector<char>& msg);
        void write(int value);

        void read(std::string& msg);
        void read(std::wstring& msg);
        void read(std::vector<char>& vector);
        void read(int& value);

        [[nodiscard]] PipeInfo getInfo() const;

        /*
         * @brief The setState method must set only PipeMode::ReadMsg,
         * PipeMode::ReadByte, PipeMode::Wait, PipeMode::NoWait.
         */
        void setState(PipeMode mode);
        [[nodiscard]] PipeState getState() const;

    private:
        HANDLE pipe_ = nullptr;
        DWORD maxNumOfChar_ = 0;
    };



    ////////////////////////////////////////////////////////////////////////////
    //
    // The NamedPipeServer
    //
    ////////////////////////////////////////////////////////////////////////////

    class NamedPipeServer final : public PipeIO
    {
    public:
        NamedPipeServer(
            std::wstring_view name,
            PipeDirection direct,
            DWORD bufSize
        );

        NamedPipeServer(
            std::wstring_view name,
            PipeDirection direct,
            PipeMode mode = PipeMode::ReadMsg | PipeMode::WriteMsg | PipeMode::Wait,
            DWORD bufSize = SmallPage_4KB,
            DWORD maxInstances = PIPE_UNLIMITED_INSTANCES,
            DWORD timeOut = 0 /*default time-out 50ms*/,
            LPSECURITY_ATTRIBUTES security = nullptr
        );

        ~NamedPipeServer() noexcept;

        void wait();
        void stopWait() noexcept;

    private:
        std::wstring name_;
        HANDLE pipe_;
    };



    ////////////////////////////////////////////////////////////////////////////
    //
    // The NamedPipeClient
    //
    ////////////////////////////////////////////////////////////////////////////

    class NamedPipeClient final : public PipeIO
    {
    public:
        NamedPipeClient(
            std::wstring_view name, 
            PipeAccess access, 
            DWORD bufSize = SmallPage_4KB
        );
        ~NamedPipeClient() noexcept;
        
        void connect();
        void disconnect() noexcept;

    private:
        std::wstring name_;
        HANDLE pipe_;
        PipeAccess access_;
        DWORD bufSize_;
    };

} // xstar
#endif // _XSTAR_USER_NAMED_PIPE_HPP_
