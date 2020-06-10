
#include <master_server/MasterServer.hpp>

int main(int argc, char * argv [])
{
    md::MasterServer serv { argc, argv };
    return serv.start();
}
