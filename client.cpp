//
// Created by sivecano on 27/03/2021.
//
#include "SDL2/SDL_net.h"
#include <iostream>
#include "stdint.h"
#include "common.cpp"

const std::string hangman[] =
        {
        "      _______\n",
        "     |/      |\n",
        "     |      (_)\n",
        "     |      \\|/\n",
        "     |       |\n",
        "     |      / \\\n",
        "     |\n",
        " ____|___"

        };


int main(int argc, char* argv[])
{
    IPaddress serveraddress;
    std::string hostname;
    std::cout << "specify hostname: ";
    std::cin >> hostname;

    if (SDLNet_ResolveHost(&serveraddress, hostname.c_str(), 8888) == -1)
    {
        std::cout << "we couldn't find the server :(\n" << SDLNet_GetError() << "\n";
        return 1;
    }

    TCPsocket server = SDLNet_TCP_Open(&serveraddress);
    if (!server)
    {
        std::cout<< "couldn't connect to server : " << SDLNet_GetError() << "\n";
        return 2;
    }

    std::cout << "we are connected\n";
    int misses = 0;
    char guess;
    uint8_t len;
    bool running;
    int8_t status = 0; // 0 is a correct guess, 1 is a win and -1 a miss
    char* word;

    recieve(server, &running, 1);


    while(running)
    {
        std::cout << "\nstarting round...\n\n";
        misses = 0;
        recieve(server, &len, 1);
        word = new char[len];
        status = 0;
        while (misses < 8 && status < 1)
        {
            recieve(server, word, len);
            std::cout << word << "\n";
            std::cout << "your guess: ";
            std::cout.flush();
            std::cin >> guess;
            send(server, &guess, 1);
            recieve(server, &status, 1);

            misses -= status;

            for (int i = 0; i < misses; i++) std::cout << hangman[i];
        }

        recieve(server, word, len);
        std::cout << "the word was: " << word << "\n";
        if (status)
            std::cout << "YOU WIN\n";
        else
            std::cout << "YOU LOSE\n";

        std::cout << "waiting for server... ";

        recieve(server, &running, 1);
    }

    std::cout << "game stopped\n";

    return 0;
}
