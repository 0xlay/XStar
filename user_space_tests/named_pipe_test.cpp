#include "pch.h"

TEST(NamedPipeTests, NamaedPipe__Default__Test)
{
    using namespace xstar;

    auto name = $T"\\\\.\\pipe\\XStarTestPipe";
    NamedPipeServer server(name, PipeDirection::InOut);

    NamedPipeClient client(name, PipeAccess::InOut);
    client.connect();

    std::string msg = "Hello world!";
    std::uint32_t bytes = client.write(msg);

    auto resMsg = std::make_unique<char[]>(bytes + sizeof(char));
    server.read(resMsg, bytes);

    EXPECT_EQ(std::string(resMsg.get()), msg);
}

// TODO: Add more tests