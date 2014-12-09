#include <iostream>
#include <boost/asio.hpp>

#include <SDL/SDL.h>

#include "Client.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

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

	std::cout << std::endl;

	return 0;
}
