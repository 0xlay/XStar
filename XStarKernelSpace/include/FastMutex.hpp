//------------------------------------------------------------------------
// $File: FastMutex.hpp
// $Date: 20.02.2021
// $Revision: 14.03.2021
// $Creator: 0xlay
//------------------------------------------------------------------------

#ifndef _XSTAR_KERNEL_FAST_MUTEX_HPP_
#define _XSTAR_KERNEL_FAST_MUTEX_HPP_

#include <wdm.h>
#include "runtime.hpp"


namespace xstar
{
    class FastMutex : public NonPagedMemory
    {
    public:
        _IRQL_requires_max_(DISPATCH_LEVEL)
        void Init();
        
        _IRQL_raises_(APC_LEVEL)
        _IRQL_saves_global_(OldIrql, mutex_)
        _IRQL_requires_max_(APC_LEVEL)
        void Lock();

        _IRQL_restores_global_(OldIrql, mutex_)
        _IRQL_requires_(APC_LEVEL)
        void Unlock();

    private:
        FAST_MUTEX mutex_; // Always, non paged pool
    };


    _Use_decl_annotations_
    void FastMutex::Init()
    {
        ExInitializeFastMutex(&mutex_);
    }


    _Use_decl_annotations_
    void FastMutex::Lock()
    {
        ExAcquireFastMutex(&mutex_);
    }


    _Use_decl_annotations_
    void FastMutex::Unlock()
    {
        ExReleaseFastMutex(&mutex_);
    }

}


#endif // _XSTAR_KERNEL_FAST_MUTEX_HPP_
