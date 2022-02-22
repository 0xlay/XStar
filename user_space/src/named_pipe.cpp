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



////////////////////////////////////////////////////////////////////////////////
//
// The PipeIO implementation
//
////////////////////////////////////////////////////////////////////////////////

void PipeIO::connectToPipe(HANDLE pipe, DWORD maxNumOfChar)
{
    pipe_ = pipe;
    maxNumOfChar_ = maxNumOfChar;
}


void PipeIO::write(const std::string& buf)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        buf.c_str(),
        static_cast<DWORD>(buf.length()) * sizeof(char),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }
}


void PipeIO::write(const std::wstring& buf)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        buf.c_str(),
        static_cast<DWORD>(buf.length()) * sizeof(wchar_t),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }
}


void PipeIO::write(const std::vector<char>& msg)
{
    DWORD bytes = 0;

    if (!WriteFile(
        pipe_,
        &msg[0],
        msg.size(),
        &bytes,
        nullptr
    ))
    {
        throw WinAPIException();
    }
}


void PipeIO::write(int value)
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
}


void PipeIO::read(std::string& msg)
{
    msg.resize(maxNumOfChar_);
    DWORD bytes = 0;

    if (!ReadFile(pipe_, &msg[0], msg.size(), &bytes, nullptr))
    {
        throw WinAPIException();
    }

    msg.resize(bytes);
}


void PipeIO::read(std::wstring& msg)
{
    msg.resize(maxNumOfChar_);
    DWORD bytes = 0;

    if (!ReadFile(pipe_, &msg[0], msg.size(), &bytes, nullptr))
    {
        throw WinAPIException();
    }

    msg.resize(bytes / sizeof(wchar_t));
}


void PipeIO::read(std::vector<char>& msg)
{
    msg.resize(maxNumOfChar_);
    DWORD bytes = 0;

    if (!ReadFile(pipe_, &msg[0], msg.size(), &bytes, nullptr))
    {
        throw WinAPIException();
    }

    msg.resize(bytes);
}


void PipeIO::read(int& value)
{
    DWORD bytes = 0;

    if (!ReadFile(pipe_, &value, sizeof(int), &bytes, nullptr))
    {
        throw WinAPIException();
    }
}


PipeInfo PipeIO::getInfo() const
{
    PipeInfo info{ };
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


void PipeIO::setState(PipeMode mode)
{
    DWORD mode_ = static_cast<DWORD>(mode);

    if (!SetNamedPipeHandleState(pipe_, &mode_, nullptr, nullptr))
    {
        throw WinAPIException();
    }
}


PipeState PipeIO::getState() const
{
    PipeState state;
    if (!::GetNamedPipeHandleStateW(
        pipe_,
        reinterpret_cast<LPDWORD>(&state.mode),
        &state.curInstances,
        nullptr,
        nullptr,
        nullptr,
        0
    ))
    {
        throw WinAPIException();
    }

    return state;
}



////////////////////////////////////////////////////////////////////////////////
//
// The NamedPipeServer implementation
//
////////////////////////////////////////////////////////////////////////////////

NamedPipeServer::NamedPipeServer(
    std::wstring_view name,
    PipeDirection direct,
    DWORD bufSize
)
    : name_(name)
{
    pipe_ = CreateNamedPipeW(
        name_.c_str(),
        static_cast<DWORD>(direct),
        static_cast<DWORD>(PipeMode::ReadMsg | PipeMode::WriteMsg | PipeMode::Wait),
        PIPE_UNLIMITED_INSTANCES,
        bufSize, bufSize,
        0/*time-out 50ms*/, 
        nullptr
    );
    if (pipe_ == INVALID_HANDLE_VALUE)
    {
        throw WinAPIException();
    }

    connectToPipe(pipe_, bufSize);
}


NamedPipeServer::NamedPipeServer(
    std::wstring_view name,
    PipeDirection direct,
    PipeMode mode,
    DWORD bufSize,
    DWORD maxInstances,
    DWORD timeOut,
    LPSECURITY_ATTRIBUTES security
)
    : name_(name)
{
    pipe_ = CreateNamedPipeW(
        name_.c_str(),
        static_cast<DWORD>(direct),
        static_cast<DWORD>(mode),
        maxInstances,
        bufSize, bufSize,
        timeOut, 
        security
    );
    if (pipe_ == INVALID_HANDLE_VALUE)
    {
        throw WinAPIException();
    }

    connectToPipe(pipe_, bufSize);
}


NamedPipeServer::~NamedPipeServer() noexcept
{
    stopWait();
    CloseHandle(pipe_);
}


void NamedPipeServer::wait()
{
    if (!ConnectNamedPipe(pipe_, nullptr))
    {
        throw WinAPIException();
    }
}


void NamedPipeServer::stopWait() noexcept
{
    DisconnectNamedPipe(pipe_);
}



////////////////////////////////////////////////////////////////////////////////
//
// The NamedPipeClient implementation
//
////////////////////////////////////////////////////////////////////////////////

NamedPipeClient::NamedPipeClient(
    std::wstring_view name, 
    PipeAccess access, 
    DWORD bufSize
)
    : name_(name), pipe_(nullptr), access_(access), bufSize_(bufSize)
{ }


NamedPipeClient::~NamedPipeClient() noexcept
{
    disconnect();
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
    {
        throw WinAPIException();
    }

    connectToPipe(pipe_, bufSize_);
}


void NamedPipeClient::disconnect() noexcept
{
    CloseHandle(pipe_);
}
