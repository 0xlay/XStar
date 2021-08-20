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
// Envivroment: User mode only
//
//------------------------------------------------------------------------------

#ifndef _XSTAR_USER_NAMED_PIPE_HPP_
#define _XSTAR_USER_NAMED_PIPE_HPP_

#include <string>
#include <memory>

#include <Windows.h>
#include <tchar.h>

#include "winapi_exception.hpp"
#include "meminfo.hpp"

namespace xstar
{

//------------------------------------------------------------------------------

    enum class PipeDircetion : DWORD
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

    inline DWORD operator | (PipeDircetion rvalue, PipeDircetion lvalue)
    {
        return static_cast<DWORD>(rvalue) | static_cast<DWORD>(lvalue);
    }

    inline DWORD operator | (DWORD rvalue, PipeDircetion lvalue)
    {
        return rvalue | static_cast<DWORD>(lvalue);
    }

    inline DWORD operator | (PipeDircetion rvalue, DWORD lvalue)
    {
        return static_cast<DWORD>(rvalue) | lvalue;
    }

    inline DWORD operator + (PipeDircetion rvalue, PipeDircetion lvalue)
    {
        return static_cast<DWORD>(rvalue) + static_cast<DWORD>(lvalue);
    }

    inline DWORD operator + (DWORD rvalue, PipeDircetion lvalue)
    {
        return rvalue + static_cast<DWORD>(lvalue);
    }

    inline DWORD operator + (PipeDircetion rvalue, DWORD lvalue)
    {
        return static_cast<DWORD>(rvalue) + lvalue;
    }

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

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

    inline DWORD operator | (PipeMode rvalue, PipeMode lvalue)
    {
        return static_cast<DWORD>(rvalue) | static_cast<DWORD>(lvalue);
    }

    inline DWORD operator | (DWORD rvalue, PipeMode lvalue)
    {
        return rvalue | static_cast<DWORD>(lvalue);
    }

    inline DWORD operator | (PipeMode rvalue, DWORD lvalue)
    {
        return static_cast<DWORD>(rvalue) | lvalue;
    }

    inline DWORD operator + (PipeMode rvalue, PipeMode lvalue)
    {
        return static_cast<DWORD>(rvalue) + static_cast<DWORD>(lvalue);
    }

    inline DWORD operator + (DWORD rvalue, PipeMode lvalue)
    {
        return rvalue + static_cast<DWORD>(lvalue);
    }

    inline DWORD operator + (PipeMode rvalue, DWORD lvalue)
    {
        return static_cast<DWORD>(rvalue) + lvalue;
    }

//------------------------------------------------------------------------------

    enum class PipeAccess : DWORD
    {
        Write = GENERIC_WRITE,
        Read  = GENERIC_READ,
        InOut = GENERIC_READ | GENERIC_WRITE
    };

    typedef struct PipeInfo
    {
        DWORD flags;
        DWORD outBufSize;
        DWORD inBufSize;
        DWORD maxInstances;
    } PipeInfo_t;

//------------------------------------------------------------------------------

    class NamedPipeServer
    {
    public:
        NamedPipeServer(
            LPCTSTR name,
            PipeDircetion direct
        );

        NamedPipeServer(
            LPCTSTR name,
            PipeDircetion direct,
            DWORD outBufSize,
            DWORD inpBufSize
        );

        NamedPipeServer(
            LPCTSTR name,
            PipeDircetion direct,
            PipeMode mode,
            DWORD outBufSize = SmallPage_4KB,
            DWORD inpBufSize = SmallPage_4KB,
            DWORD maxInstances = PIPE_UNLIMITED_INSTANCES,
            DWORD timeOut = 0 /*default time-out 50ms*/,
            LPSECURITY_ATTRIBUTES security = nullptr
        );

        ~NamedPipeServer();

        void connect();
        void disconnect();

        size_t write(const std::string& buf);
        size_t write(const std::wstring& buf);
        size_t write(const char* buf, uint32_t size);
        size_t write(const wchar_t* buf, uint32_t size);
        size_t write(int value);

        size_t read(const std::unique_ptr<char[]>& buf, uint32_t size);
        size_t read(const std::unique_ptr<wchar_t[]>& buf, uint32_t size);
        size_t read(int& value);

        PipeInfo_t getInfo();
        void setState(PipeMode mode, DWORD maxBytes = 0, DWORD maxTimeout = 0);
        // PeekNamedPipe

    private:
        #ifdef UNICODE
        std::wstring name_;
        #else
        std::string name_;
        #endif

        HANDLE pipe_;
    };

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

    class NamedPipeClient
    {
    public:
        NamedPipeClient(LPCTSTR name, PipeAccess access);
        ~NamedPipeClient();
        
        void connect();

        size_t write(std::string buf);
        size_t read(const std::unique_ptr<char[]>& buf, uint32_t size);

        PipeInfo_t getInfo();
        void setState(PipeMode mode, DWORD maxBytes = 0, DWORD maxTimeout = 0);

    private:
        #ifdef UNICODE
        std::wstring name_;
        #else
        std::string name_;
        #endif

        PipeAccess access_;
        HANDLE pipe_;
    };

//------------------------------------------------------------------------------

} // xstar
#endif // _XSTAR_USER_NAMED_PIPE_HPP_
