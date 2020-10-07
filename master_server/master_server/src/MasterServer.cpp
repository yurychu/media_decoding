
#include <master_server/MasterServer.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace bs_prog_opt = boost::program_options;

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


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
    // Sends a WebSocket message and prints the response
    try
    {
        auto const host = "echo.websocket.org";
        auto const port = "80";
        auto const text = "Hello, world!\n";

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        net::connect(ws.next_layer(), results.begin(), results.end());

        // Set a decorator to change the User-Agent of the handshake
        ws.set_option(websocket::stream_base::decorator(
        [](websocket::request_type& req){
            req.set(http::field::user_agent,
            std::string(BOOST_BEAST_VERSION_STRING) +
            " websocket-client-coro");
        }));

        // Perform the websocket handshake
        ws.handshake(host, "/");

        // Send the message
        ws.write(net::buffer(std::string(text)));

        // This buffer will hold the incoming message
        beast::flat_buffer buffer;

        // Read a message into our buffer
        ws.read(buffer);

        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);

        // If we get here then the connection is closed gracefully

        // The make_printable() function helps print a ConstBufferSequence
        std::cout << beast::make_printable(buffer.data()) << std::endl;
    }
    catch(std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
