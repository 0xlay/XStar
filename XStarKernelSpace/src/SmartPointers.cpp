//------------------------------------------------------------------------
// $File: SmartPointers.cpp
// $Date: 17.03.2021
// $Revision: 17.03.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#include "SmartPointers.hpp"

namespace xstar
{
    template <class T>
    UniquePointer<T>::UniquePointer()
        : pointer_(nullptr)
    { }



    template <class T>
    UniquePointer<T>::UniquePointer(T* pointer)
        : pointer_(pointer)
    {
        if (pointer_ == nullptr)
            ExRaiseAccessViolation();
    }



    template <class T>
    UniquePointer<T>::~UniquePointer()
    {
        free(static_cast<void*>(pointer_));
    }



    template <class T>
    T* UniquePointer<T>::getPointer() const
    {
        return pointer_;
    }



    template <class T>
    void UniquePointer<T>::release()
    {
        free(static_cast<void*>(pointer_));
    }



    template <class T>
    void UniquePointer<T>::reset(T* pointer)
    {
        free(static_cast<void*>(pointer_));
        pointer_ = pointer;
        if (pointer_ == nullptr)
            ExRaiseAccessViolation();
    }

}