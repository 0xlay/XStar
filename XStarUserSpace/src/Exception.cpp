//------------------------------------------------------------------------
// $File: Exception.cpp
// $Date: 12.02.2021
// $Revision: 14.03.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#include "Exception.hpp"


namespace xstar
{

    WinAPIException::WinAPIException()
        : msg_(getLastErrorStr()) { }

    //---------------------------------------------------------
    // Complexity:	O(1)
    // Parameter:	message and last error = GetLastError();
    //---------------------------------------------------------
    WinAPIException::WinAPIException(const char* msg, uint32_t lastError)
        : msg_(msg + std::string(msg) + std::to_string(lastError))
    { }


    //---------------------------------------------------------
    // Complexity:	O(1)
    // Return:		error message
    //---------------------------------------------------------
    const char* WinAPIException::what() const
    {
        return msg_.c_str();
    }



    //---------------------------------------------------------
    // Complexity:	O(n^2)
    // Return:		error message
    //---------------------------------------------------------
    std::string getLastErrorStr()
    {
        char msg_buf[256]{ 0 };

        uint32_t lastError = GetLastError();
        if (!lastError)
            return msg_buf;

        size_t size = FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            lastError,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
            msg_buf,
            256,
            nullptr
        );
        if (!size)
            throw std::exception();

        return std::string(msg_buf, 256);
    }



} // xstar