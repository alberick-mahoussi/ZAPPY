/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Server
*/

#include "../include/zappyMap.hpp"
#include <stdlib.h>
#include <string.h>

Server::Server(int port, std::string ip)
{
    struct hostent *host;
    struct sockaddr_in address;
    std::string buffer;
    _message = '\0';

    if ((host = gethostbyname(ip.c_str())) == NULL)
        throw Error("Error with host");
    if ((_sockfd = socket(AF_INET, SOCK_STREAM, 0))  == -1)
        throw Error("Error with socket");
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (connect(_sockfd, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) != 0)
        throw Error("Error with connection");
}

void Server::gui_loop()
{
        FD_ZERO(&_fds);
        FD_SET(STDIN_FILENO, &_fds);
        FD_SET(_sockfd, &_fds);
        select(_sockfd + 1, &_fds, NULL, NULL, NULL);
}

void Server::send_req(std::string msg)
{
    write(_sockfd, msg.c_str(), msg.length());
}

void Server::send_msg()
{
    char *buf = (char*)calloc(100 + 1, sizeof(char));
    int read_value = 0;

    read_value = read(0, buf, 100);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    if (buf[strlen(buf) - 1] == '\r')
        buf[strlen(buf) - 1] = '\0';
    write(_sockfd, buf, strlen(buf));
    free(buf);
}

std::string Server::read_client()
{
    int len = 0;
    char *buffer = (char*)malloc(sizeof(char) * 10000);
    std::string res;

    len = read(_sockfd, buffer, 10000);
    buffer[len] = '\0';
    if (!len) {
        close(_sockfd);
        exit(0);
    }
    for (int i = 0; i != strlen(buffer); i++)
        if (buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
    res = buffer;
    free(buffer);
    return res;
}

Server::~Server()
{
}