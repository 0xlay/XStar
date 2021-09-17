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


#define XSTAR_PIPE_OPERATOR_OR(T1, T2)\
inline DWORD operator | (T1 lhs, T2 rhs)\
{\
    return static_cast<DWORD>(lhs) | static_cast<DWORD>(rhs);\
}

#define XSTAR_PIPE_OPERATOR_PLUS(T1, T2)\
inline DWORD operator + (T1 lhs, T2 rhs)\
{\
    return static_cast<DWORD>(lhs) + static_cast<DWORD>(rhs);\
}


namespace xstar
{

//------------------------------------------------------------------------------

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

    XSTAR_PIPE_OPERATOR_OR(PipeDirection, PipeDirection)
    XSTAR_PIPE_OPERATOR_OR(DWORD, PipeDirection)
    XSTAR_PIPE_OPERATOR_OR(PipeDirection, DWORD)

    XSTAR_PIPE_OPERATOR_PLUS(PipeDirection, PipeDirection)
    XSTAR_PIPE_OPERATOR_PLUS(DWORD, PipeDirection)
    XSTAR_PIPE_OPERATOR_PLUS(PipeDirection, DWORD)

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

    XSTAR_PIPE_OPERATOR_OR(PipeMode, PipeMode)
    XSTAR_PIPE_OPERATOR_OR(DWORD, PipeMode)
    XSTAR_PIPE_OPERATOR_OR(PipeMode, DWORD)

    XSTAR_PIPE_OPERATOR_PLUS(PipeMode, PipeMode)
    XSTAR_PIPE_OPERATOR_PLUS(DWORD, PipeMode)
    XSTAR_PIPE_OPERATOR_PLUS(PipeMode, DWORD)

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

    class NamedPipeServer final
    {
    public:
        NamedPipeServer(
            LPCTSTR name,
            PipeDirection direct
        );

        NamedPipeServer(
            LPCTSTR name,
            PipeDirection direct,
            DWORD outBufSize,
            DWORD inpBufSize
        );

        NamedPipeServer(
            LPCTSTR name,
            PipeDirection direct,
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

    class NamedPipeClient final
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
