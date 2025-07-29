#include "executor.h"
#include "munit.h"


static MunitResult test_execute(){
    munit_assert_true(1);
    return MUNIT_OK;
}

//https://nemequ.github.io/munit/#tests-and-suites
MunitTest executor_tests[] = {
  {
    "/execute", /* name */
    test_execute, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  //end of array
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};