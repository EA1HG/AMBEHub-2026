#include "client/AMBEHubClient.h"

int main()
{
    AMBEHubClient client;

    if (!client.connect("127.0.0.1", 62031))
        return 1;

    if (!client.hello())
        return 1;

    if (!client.ping())
        return 1;

    return 0;
}