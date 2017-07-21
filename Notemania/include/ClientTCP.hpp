#ifndef NOMA_CLIENTTCP_HPP_
#define NOMA_CLIENTTCP_HPP_

#include <SFML/Network.hpp>
#include <cstring>

namespace noma
{
    struct dataPackage
        {
            std::string login;
            std::string password;
            int mapid;
            int record;
        };

    bool send_data_package (dataPackage buff);
} // namespace noma

#endif // NOMA_CLIENTTCP_HPP_
