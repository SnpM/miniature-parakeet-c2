#include "executor.h"
#include "munit.h"
#include <stdio.h>
#include <string.h>


static MunitResult test_execute(){

    //build the command
    char crib[] = "asdfnweoihaoihf";
    char command[] = "echo ";
    size_t full_command_size = sizeof(command) + sizeof(crib) + 1;
    char full_command[full_command_size];
    strncpy(full_command, command, sizeof(full_command));
    strncat(full_command, crib, sizeof(full_command) - strlen(full_command) - 1);

    //run the command
    char* result = execute(full_command);
    //terminate command to cut off newline
    result[sizeof(crib)-1] = '\0';

    //asserts
    munit_assert_not_null(result);
    munit_assert_string_equal(result, crib);

    free(result);
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