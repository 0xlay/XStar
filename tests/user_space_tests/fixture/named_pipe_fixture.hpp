#pragma once
#include "../pch.h"
#include "include/named_pipe.hpp"


struct NamedPipeTest : public testing::Test
{
    static void SetUpTestCase()
    {
        server_ = new xstar::us::NamedPipeServer(L"\\\\.\\pipe\\XStarTestPipe", xstar::us::PipeDirection::InOut);
        client_ = new xstar::us::NamedPipeClient(L"\\\\.\\pipe\\XStarTestPipe", xstar::us::PipeAccess::InOut);

        client_->connect();
    }

    static void TearDownTestCase()
    {
        client_->disconnect();

        delete client_;
        delete server_;
    }

    inline static xstar::us::NamedPipeClient* client_ = nullptr;
    inline static xstar::us::NamedPipeServer* server_ = nullptr;
};
