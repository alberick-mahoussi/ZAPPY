/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Parser
*/

#include "../include/zappyMap.hpp"

Parser::Parser(int ac, char **av)
{
    _ip;
    _port = 0;
    std::string p_opt = "-p";
    std::string h_opt = "-h";
    if (ac == 3) {
        if (p_opt.compare(av[1]) != 0)
            throw Error("There must be a -p option");
        if (check_number(av[2]) == false)
            throw Error("Port must be a number");
        _port = std::stoi(av[2]);
    } else if (ac == 5) {
        if (p_opt.compare(av[1]) == 0 && check_number(av[2]) == true)
            _port = std::stoi(av[2]);
        if (p_opt.compare(av[3]) == 0 && check_number(av[4]) == true)
            _port = std::stoi(av[4]);
        if (h_opt.compare(av[1]) == 0)
            _ip = av[2];
        if (h_opt.compare(av[3]) == 0)
            _ip = av[4];
        if (_ip.empty() == true || _port == 0)
            throw Error("Error in arguments");
    } else
        throw Error("Wrong number of arguments");
    if (_ip.empty() == true)
        _ip = "127.0.0.1";
}

bool Parser::check_number(const std::string &s)
{
    for (int i = 0; s[i] != '\0'; i++) {
        if (std::isdigit(s[i]) == 0)
            return false;
    }
    return true;
}

Parser::~Parser()
{
}
