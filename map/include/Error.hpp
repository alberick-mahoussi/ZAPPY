/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <iostream>
#include "zappyMap.hpp"

class Error : public std::exception {
    public:
        Error(const std::string &error) {_message = error;}
        ~Error() {};
        const char *what() const noexcept {return (_message.c_str());}
        std::string _message;
};


#endif /* !ERROR_HPP_ */
