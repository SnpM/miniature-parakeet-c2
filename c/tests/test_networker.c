#include "networker.h"
#include "munit.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char TEST_IP[] = "127.0.0.1";
const int TEST_PORT = 4444;

static MunitResult test_client2server() {

    char crib[] = "teongdlalseoint";

    //use fork to connect to our server
    int fork_id = fork();
    
    if (fork_id < 0) {
        perror("fork bad");
        exit(EXIT_FAILURE);
    }
    else if (fork_id == 0)
    {
        //forked
        NetworkClient nclient = networker_connect(TEST_IP,TEST_PORT);
        send_message(nclient.client_fd, crib);
    }
    else {
        NetworkServer nserver = networker_host(TEST_IP, TEST_PORT);
        char recv_buffer[0x1000];
        while(1){
            int numbytes = network_poll(nserver.connection_fd, recv_buffer, 0x1000);
            printf("%s",recv_buffer);

        }
        munit_assert_string_equal(crib,recv_buffer);
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