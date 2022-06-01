#pragma once
#include "../pch.h"
#include "named_pipe.hpp"


struct NamedPipeTest : public testing::Test
{
    static void SetUpTestCase()
    {
        server_ = new xstar::NamedPipeServer(L"\\\\.\\pipe\\XStarTestPipe", xstar::PipeDirection::InOut);
        client_ = new xstar::NamedPipeClient(L"\\\\.\\pipe\\XStarTestPipe", xstar::PipeAccess::InOut);

        client_->connect();
    }

    static void TearDownTestCase()
    {
        client_->disconnect();

        delete client_;
        delete server_;
    }

    inline static xstar::NamedPipeClient* client_ = nullptr;
    inline static xstar::NamedPipeServer* server_ = nullptr;
};
