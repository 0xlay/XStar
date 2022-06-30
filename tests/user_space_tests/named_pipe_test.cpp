#include "pch.h"
#include "fixture/named_pipe_fixture.hpp"


TEST_F(NamedPipeTest, WriteAndReadString)
{
    std::string sourceServer = "Hello from Server!";
    std::string sourceClient = "Hello from Client!";
    std::string destinationServer;
    std::string destinationClient;


    server_->write(sourceServer);
    client_->read(destinationClient);

    client_->write(sourceClient);
    server_->read(destinationServer);


    EXPECT_EQ(sourceServer, destinationClient);
    EXPECT_EQ(sourceClient, destinationServer);
}


TEST_F(NamedPipeTest, WriteAndReadWideString)
{
    std::wstring sourceServer = L"Hello from Server!";
    std::wstring sourceClient = L"Hello from Client!";
    std::wstring destinationServer;
    std::wstring destinationClient;


    server_->write(sourceServer);
    client_->read(destinationClient);

    client_->write(sourceClient);
    server_->read(destinationServer);


    EXPECT_EQ(sourceServer, destinationClient);
    EXPECT_EQ(sourceClient, destinationServer);
}


TEST_F(NamedPipeTest, WriteAndReadVectorOfBytes)
{
    std::vector<char> sourceServer = { 'S', 'e', 'r', 'v', 'e', 'r' };
    std::vector<char> sourceClient = { 'C', 'l', 'i', 'e', 'n', 't' };
    std::vector<char> destinationServer;
    std::vector<char> destinationClient;


    server_->write(sourceServer);
    client_->read(destinationClient);

    client_->write(sourceClient);
    server_->read(destinationServer);


    EXPECT_EQ(sourceServer, destinationClient);
    EXPECT_EQ(sourceClient, destinationServer);
}


TEST_F(NamedPipeTest, WriteAndReadInteger)
{
    int sourceServer = 1;
    int sourceClient = 2;
    int destinationServer;
    int destinationClient;


    server_->write(sourceServer);
    client_->read(destinationClient);

    client_->write(sourceClient);
    server_->read(destinationServer);


    EXPECT_EQ(sourceServer, destinationClient);
    EXPECT_EQ(sourceClient, destinationServer);
}


TEST_F(NamedPipeTest, ClientSetAndGetPipeState)
{
    using namespace xstar::us;

    PipeMode mode = PipeMode::ReadMsg;

    client_->setState(mode);
    PipeState state = client_->getState();

    EXPECT_EQ(state.mode, mode);
    EXPECT_NE(state.curInstances, 0);
}


TEST_F(NamedPipeTest, ServertSetAndGetPipeState)
{
    using namespace xstar::us;

    PipeMode mode = PipeMode::NoWait | PipeMode::ReadByte;

    server_->setState(mode);
    PipeState state = server_->getState();

    EXPECT_EQ(state.mode, mode);
    EXPECT_NE(state.curInstances, 0);
}
