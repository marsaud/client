#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <SDL/SDL.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Connection.h"
#include "UpMessage.h"
#include "DownMessage.h"

#include "Position.h"
#include "Player.h"

#include "StateController.h"
#include "MovementController.h"
#include "ActionController.h"
#include "ActionProcessor.h"
#include "MovementProcessor.h"

#include "TileDisplayZone.h"
#include "ZoneDisplayZone.h"

class Client
{
    public:
        Client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint, SDL_Surface* screen);
        virtual ~Client();

    protected:
    private:
        void connect(boost::asio::ip::tcp::endpoint& endpoint);
        void handle_connect(Connection::connection_ptr connection, const boost::system::error_code& error);
        void wait_for_data();
        void handle_read(const boost::system::error_code& error);
        void m_drive_events();
        void m_handle_events();
        void handle_write(const boost::system::error_code& error);

        Player* m_player;
        StaticWorld* m_world;
        StateController::State m_state;
        SDL_Surface* m_screen;
        ZoneDisplayZone* m_zoneDisplayZone;

        boost::asio::io_service& m_io_service;
        boost::asio::deadline_timer m_timer;
        Connection::connection_ptr m_connection;
        UpMessage m_upMessage;
        DownMessage m_downMessage;
};

#endif // CLIENT_H
