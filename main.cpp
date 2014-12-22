#include <iostream>
#include <boost/asio.hpp>

#include <SDL/SDL.h>

#include "Client.h"
#include "init.h"

int main()
{
    SDL_Surface* screen = NULL;
    TTF_Font* font = NULL;

    initVideo(640, 400, "fonts/coure.fon", 22, screen, font);

	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);

		Client client(io_service, endpoint, screen);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	quitVideo(screen, font);

	return 0;
}
