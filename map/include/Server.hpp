/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netdb.h>
#include <iostream>
#include <signal.h>
#include "zappyMap.hpp"

class Server {
    public:
        Server(int port, std::string ip);
        ~Server();
        void send_msg();
        std::string read_client();
        void send_req(std::string msg);
        void gui_loop();
        std::string _message;
        fd_set _fds;
        int _sockfd;
};

#endif /* !SERVER_HPP_ */
