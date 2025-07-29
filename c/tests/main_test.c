#define MUNIT_ENABLE_ASSERT_ALIASES
#include "../munit/munit.h"
#include "stdio.h"
#include "../include/executor.h"

//defined in test_executor.c
extern MunitTest executor_tests[];


static MunitSuite suites[] = {

  //executor suite
  {
    "/executor", /* name */
    executor_tests, /* tests */
    NULL, /* suites */
    1, /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
  },

  //EOF array
  {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE}

  };

static MunitSuite main_suite = {
  "/main", /* name */
  NULL, /* tests */
  suites, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char **argv)
{
    return munit_suite_main(&main_suite, NULL, argc, argv);
}
