#include "networker.h"
#include "munit.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char TEST_IP[] = "127.0.0.1";
const int TEST_PORT = 4444;

static MunitResult test_client2server() {

    //use fork to connect to our server
    int fork_id = fork();
    
    if (fork_id < 0) {
        perror("fork bad");
        exit(EXIT_FAILURE);
    }
    else if (fork_id == 0)
    {
        //forked
        networker_connect(TEST_IP,TEST_PORT);
        exit(EXIT_FAILURE);
    }
    else {
        networker_host(TEST_IP, TEST_PORT);
    }

}

static MunitResult test_server2client () {

}


//https://nemequ.github.io/munit/#tests-and-suites
MunitTest networker_tests[] = {
  {"/client2server",test_client2server,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL},
  //end of array
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};