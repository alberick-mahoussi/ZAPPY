/*
** EPITECH PROJECT, 2023
** map
** File description:
** Threads
*/

#include "Threads.hpp"
#include <pthread.h>

void my_thread(Window *win)
{
    while (win->_ended == false) {
        win->serv->gui_loop();
        if (FD_ISSET(win->serv->_sockfd, &win->serv->_fds))
            win->parseStdServer(win->serv->read_client());
    }
}

void *wrapper(void *arg)
{
    Window *win = static_cast<Window*>(arg);
    my_thread(win);
    return nullptr;
}

void Threads::callthreads(Window *zappyMap)
{
    pthread_t communication;
    pthread_t test;
    pthread_create(&communication, nullptr, wrapper, zappyMap);
    zappyMap->gameLoop(zappyMap->serv);
    pthread_join(communication, nullptr);
}

Threads::Threads(Window *zappyMap)
{
    callthreads(zappyMap);
}

Threads::~Threads()
{
}
