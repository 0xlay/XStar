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
// File: named_pipe.cpp
// 
// Creator: 0xlay
// 
// Envivroment: User mode only
//
//------------------------------------------------------------------------------

#include "named_pipe.hpp"

using namespace xstar;


//------------------------------------------------------------------------------
// NamedPipeServer
//------------------------------------------------------------------------------

NamedPipeServer::NamedPipeServer(
    LPCTSTR name,
    PipeDircetion direct
)
    : name_(name)
{
    pipe_ = CreateNamedPipe(
        name_.c_str(),
        static_cast<DWORD>(direct),
        PipeMode::ReadMsg | PipeMode::WriteMsg | PipeMode::Wait,
        PIPE_UNLIMITED_INSTANCES,
        SmallPage_4KB, SmallPage_4KB,
        0/*time-out 50ms*/, 
        nullptr
    );
}



NamedPipeServer::NamedPipeServer(
    LPCTSTR name,
    PipeDircetion direct,
    DWORD outBufSize,
    DWORD inpBufSize
)
{
    pipe_ = CreateNamedPipe(
        name_.c_str(),
        static_cast<DWORD>(direct),
        PipeMode::ReadMsg | PipeMode::WriteMsg | PipeMode::Wait,
        PIPE_UNLIMITED_INSTANCES,
        outBufSize, inpBufSize,
        0/*time-out 50ms*/, 
        nullptr
    );
}



NamedPipeServer::NamedPipeServer(
    LPCTSTR name,
    PipeDircetion direct,
    PipeMode mode,
    DWORD outBufSize,
    DWORD inpBufSize,
    DWORD maxInstances,
    DWORD timeOut,
    LPSECURITY_ATTRIBUTES security
)
{
    pipe_ = CreateNamedPipe(
        name_.c_str(),
        static_cast<DWORD>(direct),
        static_cast<DWORD>(mode),
        maxInstances,
        outBufSize, inpBufSize,
        timeOut, 
        security
    );
}



NamedPipeServer::~NamedPipeServer()
{
    DisconnectNamedPipe(pipe_);
    CloseHandle(pipe_);
}



void NamedPipeServer::connect()
{
    if (!ConnectNamedPipe(pipe_, nullptr))
        throw WinAPIException();
}



void NamedPipeServer::disconnect()
{
    if (!DisconnectNamedPipe(pipe_))
        throw WinAPIException();
}



size_t NamedPipeServer::write(const std::string& buf)
{
    DWORD bytes = 0;
    
    if (!WriteFile(
        pipe_,
        buf.c_str(),
        static_cast<DWORD>(buf.length() * sizeof(char)),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }

    return bytes;
}



size_t NamedPipeServer::write(const std::wstring& buf)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        buf.c_str(),
        static_cast<DWORD>(buf.length() * sizeof(wchar_t)),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }

    return bytes;
}



size_t NamedPipeServer::write(const char* buf, uint32_t size)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        buf,
        size,
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }

    return bytes;
}



size_t NamedPipeServer::write(const wchar_t* buf, uint32_t size)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        buf,
        size * sizeof(wchar_t),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }

    return bytes;
}



size_t NamedPipeServer::write(int value)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        &value,
        sizeof(int),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }

    return bytes;
}



size_t NamedPipeServer::read(const std::unique_ptr<char []>& buf, uint32_t size)
{
    DWORD bytes = 0;

    if (!ReadFile(pipe_, buf.get(), size, &bytes, nullptr))
        throw WinAPIException();

    return bytes;
}



size_t NamedPipeServer::read(const std::unique_ptr<wchar_t[]>& buf, uint32_t size)
{
    DWORD bytes = 0;

    if (!ReadFile(pipe_, buf.get(), size * sizeof(wchar_t), &bytes, nullptr))
        throw WinAPIException();

    return bytes;
}



size_t NamedPipeServer::read(int& value)
{
    DWORD bytes = 0;

    if (!ReadFile(pipe_, &value, sizeof(int), &bytes, nullptr))
        throw WinAPIException();

    return bytes;
}


PipeInfo_t NamedPipeServer::getInfo()
{
    PipeInfo_t info{ 0 };
    if (!GetNamedPipeInfo(
        pipe_,
        &info.flags,
        &info.outBufSize, 
        &info.inBufSize,
        &info.maxInstances
    ))
    {
        throw WinAPIException();
    }

    return info;
}



void NamedPipeServer::setState(PipeMode mode, DWORD maxBytes, DWORD maxTimeout)
{
    DWORD mode_ = static_cast<DWORD>(mode);
    LPDWORD maxBytes_ = nullptr, maxTimeout_= nullptr;

    if (maxBytes != 0)
        maxBytes_ = &maxBytes;
    if (maxTimeout != 0)
        maxTimeout_ = &maxTimeout;
 
    if (!SetNamedPipeHandleState(pipe_, &mode_, maxBytes_, maxTimeout_))
        throw WinAPIException();
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// NamedPipeClient
//------------------------------------------------------------------------------

NamedPipeClient::NamedPipeClient(LPCTSTR name, PipeAccess access)
    : name_(name), pipe_(nullptr), access_(access)
{ }



NamedPipeClient::~NamedPipeClient()
{
    CloseHandle(pipe_);
}



void NamedPipeClient::connect()
{
    pipe_ = CreateFile(
        name_.c_str(), 
        static_cast<DWORD>(access_), 
        0, 
        nullptr, 
        OPEN_EXISTING, 
        0, 
        nullptr
    );
    if (pipe_ == INVALID_HANDLE_VALUE)
        throw WinAPIException();
}



size_t NamedPipeClient::write(std::string buf)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        buf.c_str(),
        static_cast<DWORD>(buf.length() * sizeof(char)),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }

    return bytes;
}



size_t NamedPipeClient::read(const std::unique_ptr<char[]>& buf, uint32_t size)
{
    DWORD bytes = 0;

    if (!ReadFile(pipe_, buf.get(), size, &bytes, nullptr))
        throw WinAPIException();

    return bytes;
}



PipeInfo_t NamedPipeClient::getInfo()
{
    PipeInfo_t info{ 0 };
    if (!GetNamedPipeInfo(
        pipe_,
        &info.flags,
        &info.outBufSize,
        &info.inBufSize,
        &info.maxInstances
    ))
    {
        throw WinAPIException();
    }

    return info;
}



void NamedPipeClient::setState(PipeMode mode, DWORD maxBytes, DWORD maxTimeout)
{
    DWORD mode_ = static_cast<DWORD>(mode);
    LPDWORD maxBytes_ = nullptr, maxTimeout_ = nullptr;

    if (maxBytes != 0)
        maxBytes_ = &maxBytes;
    if (maxTimeout != 0)
        maxTimeout_ = &maxTimeout;

    if (!SetNamedPipeHandleState(pipe_, &mode_, maxBytes_, maxTimeout_))
        throw WinAPIException();
}
//------------------------------------------------------------------------------