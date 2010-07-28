#include "FileServer.h"
#include "VirtioBlock.h"

using namespace MonAPI;

int main(int argc, char* argv[])
{
    VirtioBlock v;
    v.test();

    if (monapi_notify_server_start("INIT") != M_OK)
    {
        exit(-1);
    }

    FileServer server;
    if (server.initializeFileSystems() != MONA_SUCCESS)
    {
        _printf("fileserver filesystem initialize error\n");
        exit(1);
    }
    server.messageLoop();

    return 0;
}
