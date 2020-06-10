
#include <master_server/MasterServer.hpp>

#include <iostream>

#include <boost/program_options.hpp>

namespace bs_prog_opt = boost::program_options;

md::MasterServer::MasterServer(int argc, char * argv [])
{
    try {
        bs_prog_opt::options_description desc{"Options"};
        desc.add_options()
                ("help,h", "Show help");

        // to add use: --help or -h (one character)

        bs_prog_opt::variables_map vm;
        bs_prog_opt::store(
                bs_prog_opt::parse_command_line(argc, argv, desc),
                vm
        );
        bs_prog_opt::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
        }

    } catch (const bs_prog_opt::error &ex) {
        std::cerr << ex.what() << std::endl;
            // (usually is: "unrecognised option '--some_opt'")
    }

}

int md::MasterServer::start()
{
    return 0;
}
