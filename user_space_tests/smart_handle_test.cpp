#include "pch.h"

TEST(SmartHandleTests, SmartHadnle__HWND__Test) 
{
    xstar::SmartHandle<HWND> hwnd = CreateWindowEx(
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
    xstar::SmartHandle<HANDLE> handle = CreateEvent(nullptr, true, true, nullptr);
    EXPECT_NE(handle.getHandle(), nullptr);
    EXPECT_NE(*handle, nullptr);
}

TEST(SmartHandleTests, SmartHandle__SC_HADNLE__Test)
{
    xstar::SmartHandle<SC_HANDLE> serviceHandle = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    EXPECT_NE(serviceHandle.getHandle(), nullptr);
    EXPECT_NE(*serviceHandle, nullptr);
}