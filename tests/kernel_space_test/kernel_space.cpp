#include "../cruntime/crt.hpp"
#include "kernel_space.hpp"
#include "string_test.hpp"
#include "result_test.hpp"
#include "array_test.hpp"


#ifdef ALLOC_PRAGMA

    #pragma alloc_text(PAGE, DriverEntry)

#endif


int foo()
{
    return 10;
}

extern "C" int boo()
{
    return 20;
}


static int a = foo();
static int b = boo();

struct PV
{
    PV()
    {
        call_pv();
    }
    virtual void pv() = 0;
    void call_pv()
    {
        pv();
    }
};

class Apple : public PV
{
public:
    Apple(int price) : price_(price)
    {
        KdPrint(("Apple ctor!!!\n"));
    }

    void pv() override
    { }

    void show()
    {
        KdPrint(("Apple price: %d\n", price_));
    }

    ~Apple()
    {
        KdPrint(("Apple dctor!!!\n"));
    }

private:
    int price_;
};
//Apple apple(10);

_Use_decl_annotations_
NTSTATUS DriverEntry([[maybe_unused]] PDRIVER_OBJECT DriverObject,
                     [[maybe_unused]] PUNICODE_STRING RegistryPath)
{
    _crt_init();

    KdPrint(("Driver Entry start! %d - %d\n", a, b));
    Apple apple(10);
    apple.show();

    //
    // Run all tests
    //

    XSTAR_KTEST_RUN_SUITE(ResultTest);
    XSTAR_KTEST_RUN_SUITE(ArrayTest);
    XSTAR_KTEST_RUN_SUITE(StringTest);

    _crt_deinit();
    return STATUS_FAILED_DRIVER_ENTRY;
}
