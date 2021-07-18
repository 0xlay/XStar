//------------------------------------------------------------------------
// $File: Exception.hpp
// $Date: 12.02.2021
// $Revision: 14.03.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#ifndef _XSTAR_USER_EXCEPTION_HPP_
#define _XSTAR_USER_EXCEPTION_HPP_

#include <Windows.h>
#include <string>
#include <exception>
#include <cstdint>

namespace xstar
{

    class WinAPIException : public std::exception
    {
    public:
        WinAPIException();
        WinAPIException(const char* msg, uint32_t lastError);
        const char* what() const override;

    private:
        std::string msg_;
    };


    std::string getLastErrorStr();


} // xstar
#endif // _XSTAR_USER_EXCEPTION_HPP_