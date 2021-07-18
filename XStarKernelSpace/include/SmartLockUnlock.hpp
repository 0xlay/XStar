//------------------------------------------------------------------------
// $File: SmartLockUnlock.hpp
// $Date: 20.02.2021
// $Revision: 20.02.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_
#define _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_

namespace xstar
{
    template <class T>
    class SmartLockUnlock
    {
    public:
        SmartLockUnlock(T& object) : object_(object)
        {
            object_.Lock();
        }
        ~SmartLockUnlock()
        {
            object_.Unlock();
        }

    private:
        T& object_;
    };

}


#endif // _XSTAR_KERNEL_SMART_LOCK_UNLOCK_HPP_