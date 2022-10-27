//
// Created by Dennis on 27/10/2022.
//
#define DOCTEST_CONFIG_IMPLEMENT
#include <Header Files/doctest.h>

#include "Header Files/Helper.h"

TEST_SUITE("Helper Functions for further understanding" * doctest::description("optional"))
{
    TEST_CASE("Hamming Distance")
    {
        int a = 3;
        int b = 5;

        CHECK(calc_hamming_distance(a, b) == 2);
    }
}



TEST_SUITE("Praktikum 1 tests" * doctest::description("functional tests"))
{
    TEST_CASE("Test test")
    {
    CHECK(true == true);
    }
}



int main(int argc, char** argv) {
    doctest::Context context;

    // defaults
    context.setOption("order-by", "name");            // sort the test cases by their name
    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

    int res = context.run(); // run

    if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests
}