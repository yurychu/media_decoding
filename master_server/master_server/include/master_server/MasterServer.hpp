#pragma once


namespace md
{

    class MasterServer
    {
    private:

    public:
        MasterServer(int argc, char * argv []);
        ~MasterServer() = default;

        int start();

    };

}
