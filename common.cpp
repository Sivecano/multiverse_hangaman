//
// Created by sivecano on 27/03/2021.
//

#include "SDL2/SDL_net.h"
#include <exception>
#include <stdexcept>

template<typename type>
void recieve(TCPsocket sock, type* data, int bytes)
{
    if (SDLNet_TCP_Recv(sock, (void*)data, bytes) <= 0){
        std::cout << "Error "<< SDLNet_GetError() << "\n";
        throw std::runtime_error("error in reviece\n");
    }

}
template<typename type>
void send(TCPsocket sock, type* data, int bytes)
{
    if (SDLNet_TCP_Send(sock, (void*)data, bytes) < bytes) {
        std::cout << "Error "<< SDLNet_GetError() << "\n";
        throw std::runtime_error("error in send\n");
    }
}