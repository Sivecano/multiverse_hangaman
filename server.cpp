#include "SDL2/SDL_net.h"
#include <iostream>
#include "common.cpp"

int main(int argc, char* argv[])
{

    SDLNet_Init();

    IPaddress self;

    if (SDLNet_ResolveHost(&self, NULL, 8888) == -1)
    {
        std::cout << "we couldn't become Server :(\n" << SDLNet_GetError() << "\n";
        return 1;
    }

    TCPsocket serv = SDLNet_TCP_Open(&self);
    if (!serv)
    {
        std::cout<< "connection failed : " << SDLNet_GetError() << "\n";
        return 2;
    }

    TCPsocket client;
    std::cout << "trying to connect.... ";
    std::cout.flush();
    while (!(client = SDLNet_TCP_Accept(serv)));


    std::string word;
    bool running;
    int lives = 0;
    std::string guesses;
    char guess;

    std::cout << "we did it!\n";

    running = true;
    int8_t status;
    SDLNet_TCP_Send(client, &running, 1);

    while (running)
    {
        std::cout << "give a new word : ";
        std::cin >> word;
        guesses.resize(word.length());
        uint8_t len = word.length() + 1;
        send(client, &len, 1);
        std::fill_n(guesses.begin(), word.length(), '_');
        lives = 8;

        std::cout << "guesses: ";
        while(lives > 0 && status < 1)
        {
            send(client, guesses.c_str(), len);
            recieve(client, &guess, 1);
            int i = word.find(guess);
            bool gotem = false;
            std::cout << guess  << " ";
            std::cout.flush();
            while (i != std::string::npos)
            {
                gotem = true;
                guesses[i] = guess;
                i = word.find(guess);
            }

            status = gotem ? status = guesses.find('_') == std::string::npos : -1;
            send(client, &status, 1);
        }

        send(client, (void*)word.c_str(), len);
        std::cout << "wanna play another round? [Y/N]";
        char ans;
        std::cin >> ans;
        running = ans == 'y' || ans == 'Y';

        send(client, (void*)&running, 1);
    }

    std::cout << "game ended";

    return 0;
}