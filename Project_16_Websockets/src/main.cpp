#include <iostream>
#include "boost/asio.hpp"
#include "boost/asio/ts/buffer.hpp"
#include "boost/asio/ts/internet.hpp"

#include <chrono>
#include <thread>

std::vector<char> vBuffer(1*1024);

void GrabSomeData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if(!ec)
            {
                std::cout << "\n\nRead " << length << " bytes\n\n";

                for(size_t i = 0; i < length; i++)
                    std::cout << vBuffer[i];
                
                GrabSomeData(socket);
            }
        }
    );
}

int main()
{
    boost::system::error_code ec;

    // Create a "context" - platform specific interface
    boost::asio::io_context context;

    // Get the address of somewhere we wish to connect to
    boost::asio::ip::tcp::endpoint server_endpoint(boost::asio::ip::make_address("93.184.215.14", ec), 80);

    // Create a socket, the context will deliver the implementation
    boost::asio::ip::tcp::socket socket(context);

    // Tell socket to try and connect
    socket.connect(server_endpoint, ec);

    if(!ec)
    {
        std::cout << "Connected!" << std::endl;
    }
    else
    {
        std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
    }

    if(socket.is_open())
    {
        GrabSomeData(socket);

        std::string sRequest =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

            /*GET /chat HTTP/1.1
            Host: example.com:8000
            Upgrade: websocket
            Connection: Upgrade
            Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
            Sec-WebSocket-Version: 13*/

        socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);

        /*socket.wait(socket.wait_read);

        size_t bytes = socket.available();
        std::cout << "Bytes Available: " << bytes << std::endl;

        if(bytes > 0)
        {
            std::vector<char> vBuffer(bytes);
            socket.read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()), ec);

            for(auto c: vBuffer)
                std::cout << c;
        }*/
        std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    }

    return 0;
}