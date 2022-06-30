#include "pch.h"

TEST(SmartHandleTests, SmartHadnle__HWND__Test) 
{
    using namespace xstar::us;

    SmartHandle<HWND> hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        $T"#32769", /*The class for the desktop window*/
        nullptr, 
        WS_VISIBLE,
        0, 
        0, 
        0, 
        0, 
        nullptr, 
        nullptr, 
        nullptr, 
        nullptr
    );
    EXPECT_NE(hwnd.getHandle(), nullptr);
    EXPECT_NE(*hwnd, nullptr);
}

TEST(SmartHandleTests, SmartHadnle__HANDLE__Test)
{
    using namespace xstar::us;

    SmartHandle<HANDLE> handle = CreateEvent(nullptr, true, true, nullptr);
    EXPECT_NE(handle.getHandle(), nullptr);
    EXPECT_NE(*handle, nullptr);
}

TEST(SmartHandleTests, SmartHandle__SC_HADNLE__Test)
{
    using namespace xstar::us;

    SmartHandle<SC_HANDLE> serviceHandle = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    EXPECT_NE(serviceHandle.getHandle(), nullptr);
    EXPECT_NE(*serviceHandle, nullptr);
}

TEST(SmartHandleTests, SmartHandle__HMODULE__Test)
{
    using namespace xstar::us;

    SmartHandle<HMODULE> moduleHandle = LoadLibrary($T"kernel32.dll");
    EXPECT_NE(moduleHandle.getHandle(), nullptr);
    EXPECT_NE(*moduleHandle, nullptr);
}
