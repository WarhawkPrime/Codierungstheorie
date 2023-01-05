//
// Created by Dennis on 27/10/2022.
//
#define CUSTOM_RC 0

#define DOCTEST_CONFIG_IMPLEMENT

#include <Header Files/doctest.h>

#include "Header Files/EGFTests.h"
#include "Header Files/HelperTests.h"
#include "Header Files/ModularPolynomArithmeticTests.h"
#include "Header Files/PolynomTests.h"

TEST_SUITE("Praktikum 1 tests" * doctest::description("functional tests")) {
    TEST_CASE("Test test") { CHECK(true == true); }
}

int main(int argc, char **argv) {
    doctest::Context context;

    // defaults
    context.setOption("order-by", "name"); // sort the test cases by their name
#if (defined(CMAKE_BUILD_TYPE) && (CMAKE_BUILD_TYPE == Release))
    context.setOption("reporters", "junit");
    context.setOption("out", "report.xml");
#endif
    // Relevant for the fuzzy tests
    context.setOption("abort-after", 100);

    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks",
                      true); // don't break in the debugger when assertions fail

    int res = context.run(); // run

    if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;           // propagate the result of the tests

    return res + CUSTOM_RC; // the result from doctest is propagated here as well
}