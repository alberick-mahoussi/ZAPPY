/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <iostream>
#include "zappyMap.hpp"

class Parser {
    public:
        Parser(int ac, char **av);
        ~Parser();
        bool check_number(const std::string &s);
        int get_port() {return _port;}
        std::string get_ip() {return _ip;}
        int _port;
        std::string _ip;
    protected:
    private:
};

#endif /* !PARSER_HPP_ */
