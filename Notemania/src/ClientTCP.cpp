#include "ClientTCP.hpp"

namespace noma
{
    bool send_data_package (dataPackage buff)
    {
        sf::TcpSocket socket;
        sf::Socket::Status status = socket.connect("localhost", 8080);

        if (status != sf::Socket::Done)
            return false;

        std::string dataBuff;
        
        dataBuff+=buff.login+","+buff.password+","+std::to_string(buff.mapid)+","+std::to_string(buff.record);

        const char* data; data = dataBuff.c_str();

        if (socket.send(data, strlen(data)) != sf::Socket::Done)
            return false;

        return true;
    }
} // namespace noma