#include <iostream>
#include <boost/asio.hpp>

#include <SDL/SDL.h>

#include "Client.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(640, 400, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    MovementProcessor::init();

	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);



		Client client(io_service, endpoint);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	MovementProcessor::free();

	return 0;
}
