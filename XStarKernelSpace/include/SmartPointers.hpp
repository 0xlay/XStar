//------------------------------------------------------------------------
// $File: SmartPointers.hpp
// $Date: 17.03.2021
// $Revision: 17.03.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_SMART_POINTERS_HPP_
#define _XSTAR_KERNEL_SMART_POINTERS_HPP_

#include "runtime.hpp"

namespace xstar
{
    // UniquePointer is using windows exception. You will need using operator __try, __except
    template <class T>
    class UniquePointer
    {
    public:
        UniquePointer();
        UniquePointer(T* pointer);
        ~UniquePointer();

        UniquePointer(const UniquePointer<T>&) = delete;
        UniquePointer<T>& operator = (const UniquePointer<T>&) = delete;

        T* getPointer() const;
        void release();
        void reset(T* pointer);

    private:
        T* pointer_;
    };


    // TODO: Add shared_ptr, and weak_ptr
}

#endif // _XSTAR_KERNEL_SMART_POINTERS_HPP_
