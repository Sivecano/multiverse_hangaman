//
// Created by sivecano on 27/03/2021.
//

#include <exception>
#include <stdexcept>

template<typename type>
void recieve(TCPsocket sock, type* data, int bytes)
{
    if (SDLNet_TCP_Recv(sock, (void*)data, bytes) <= 0)
        throw std::runtime_error("we lost connection or something went horribly wrong\n");
}
template<typename type>
void send(TCPsocket sock, type* data, int bytes)
{
    if (SDLNet_TCP_Recv(sock, (void*)data, bytes) < bytes)
        throw std::runtime_error("we lost connection or something went horribly wrong\n");
}