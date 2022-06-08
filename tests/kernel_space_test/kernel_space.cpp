#include "kernel_space.hpp"
#include "string_test.hpp"
#include "result_test.hpp"
#include "array_test.hpp"

#ifdef ALLOC_PRAGMA

    #pragma alloc_text(PAGE, DriverEntry)

#endif

_Use_decl_annotations_
NTSTATUS DriverEntry([[maybe_unused]] PDRIVER_OBJECT DriverObject,
                     [[maybe_unused]] PUNICODE_STRING RegistryPath)
{
    KdPrint(("Driver Entry start!\n"));

    //
    // Run all tests
    //

    XSTAR_KTEST_RUN_SUITE(ResultTest);
    XSTAR_KTEST_RUN_SUITE(ArrayTest);
    XSTAR_KTEST_RUN_SUITE(StringTest);

    return STATUS_FAILED_DRIVER_ENTRY;
}
