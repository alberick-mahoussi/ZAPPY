/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Protocole
*/

#include <iostream>
#include <sstream>
#include <string>
#include "zappyMap.hpp"

void Window::setMapSize(std::string string)
{
    std::stringstream ss(string);
    std::string token;

    ss >> token;
    ss >> token;
    float width = std::stof(token);
    ss >> token;
    float height = std::stof(token);
    _mapSize.x = width;
    _mapSize.y = height;
}

int count_newline(std::string string)
{
    int res = 0;
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == '\n')
            res++;
    return res;
}

void Window::setContentOfTile(std::string string)
{
    std::stringstream ss(string);
    std::string token;
    int i = 0;
    int final = count_newline(string);

    while (i != final) {
        ss >> token;
        ss >> token;
        int width = std::stoi(token);
        ss >> token;
        int height = std::stoi(token);
        ss >> token;
        int food = std::stoi(token);
        ss >> token;
        int linemate = std::stoi(token);
        ss >> token;
        int deraumere = std::stoi(token);
        ss >> token;
        int sibur = std::stoi(token);
        ss >> token;
        int mendiane = std::stoi(token);
        ss >> token;
        int phiras = std::stoi(token);
        ss >> token;
        int thystame = std::stoi(token);
        Coordinate coord = {width, height};
        mapTile[coord].food = food;
        mapTile[coord].linemate = linemate;
        mapTile[coord].deraumere = deraumere;
        mapTile[coord].sibur = sibur;
        mapTile[coord].mendiane = mendiane;
        mapTile[coord].phiras = phiras;
        mapTile[coord].thystame = thystame;
        i++;
    }
}

void Window::connexionPlayer(std::string string)
{
    std::stringstream ss(string);
    std::string token;

    ss >> token;
    ss >> token;
    std::string player = token;
    ss >> token;
    float width = std::stof(token);
    ss >> token;
    float height = std::stof(token);
    ss >> token;
    int orientation = std::stoi(token);
    ss >> token;
    int level = std::stoi(token);
    ss >> token;
    std::string nameOfTeam = token;
    _playerList.emplace(player, Player(Vector3{width, 0.5, height}, &_farmer, _modelAnimations, _animsCount, orientation, level, nameOfTeam, player));
    serv->send_req("plv " + player + "\n");
    serv->send_req("pin " + player + "\n");
}

void Window::playerPosition(std::string string)
{
    std::stringstream ss(string);
    std::string token;
    std::array<int, 4> values = {1, 90, -90, 540};

    ss >> token;
    ss >> token;
    auto it = _playerList.find("#" + token);
    if (it != _playerList.end()) {
        ss >> token;
        float width = std::stof(token);
        ss >> token;
        float height = std::stof(token);
        ss >> token;
        int orientation = std::stoi(token);
        if (width == static_cast<int>(it->second.getPlayerPos().x + 0.5f) && height == static_cast<int>(it->second.getPlayerPos().z + 0.5f)) {
            it->second.setOrientation(orientation);
        } else {
            it->second.setRunning();
        }
    }
}

void Window::playerLevel(std::string string)
{
    std::stringstream ss(string);
    std::string token;

    ss >> token;
    ss >> token;
    auto it = _playerList.find("#" + token);
    if (it != _playerList.end()) {
        ss >> token;
        int level = std::stoi(token);
        it->second.setLevel(level);
    }
}

void Window::playerInventory(std::string string)
{
    std::stringstream ss(string);
    std::string token;

    ss >> token;
    ss >> token;
    auto it = _playerList.find("#" + token);
    if (it != _playerList.end()) {
        ss >> token;
        ss >> token;
        ss >> token;
        int food = std::stoi(token);
        ss >> token;
        int linemate = std::stoi(token);
        ss >> token;
        int deraumere = std::stoi(token);
        ss >> token;
        int sibur = std::stoi(token);
        ss >> token;
        int mendiane = std::stoi(token);
        ss >> token;
        int phiras = std::stoi(token);
        ss >> token;
        int thystame = std::stoi(token);

        it->second.setInventory(food, linemate, deraumere, sibur, mendiane, phiras, thystame);
    }
}

// void expulsion(int playerNumber)
// {

// }

// void Window::broadcast(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     auto it = _playerList.find("#" + token);
//     if (it != _playerList.end()) {
//         ss >> token;

//         std::string message = token;
//     }
// }

// void Window::startIncantation(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;
    
//     ss >> token;
//     ss >> token;
//     int width = std::stoi(token);
//     ss >> token;
//     int height = std::stoi(token);
//     ss >> token;
//     int level = std::stoi(token);
//     while (token != "\n") {
//         ss >> token;
//         auto it = _playerList.find("#" + token);
//         if (it != _playerList.end()) {
//             it->second.setLevel(level + 1);
//             it->second.setIncantation();
//         }
//     }
// }

// void Window::endIncantation(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int width = std::stoi(token);
//     ss >> token;
//     int height = std::stoi(token);
//     ss >> token;
//         auto it = _playerList.find("#" + token);
//         if (it != _playerList.end()) {
//             it->second.setIncantation();
//         }
//     int incantationResult = std::stoi(token);
// }

void Window::ressourceDropping(std::string string)
{
    std::stringstream ss(string);
    std::string token;
    ss >> token;
    ss >> token;
    auto it = _playerList.find("#" + token);
    if (it != _playerList.end())
        serv->send_req("bct " + std::to_string(static_cast<int>(it->second.getPlayerPos().x)) + " " + std::to_string(static_cast<int>(it->second.getPlayerPos().z)) + "\n");
    serv->send_req("pin #" + token + "\n");
}

void Window::ressourceCollecting(std::string string)
{
    std::stringstream ss(string);
    std::string token;
    ss >> token;
    ss >> token;
    auto it = _playerList.find("#" + token);
    if (it != _playerList.end())
        serv->send_req("bct " + std::to_string(static_cast<int>(it->second.getPlayerPos().x)) + " " + std::to_string(static_cast<int>(it->second.getPlayerPos().z)) + "\n");
    serv->send_req("pin #" + token + "\n");
}

void Window::deathPlayer(std::string string)
{
    std::stringstream ss(string);
    std::string token;
    ss >> token;
    ss >> token;
    auto it = _playerList.find("#" + token);
    if (it != _playerList.end()) {
        it->second.setDied();
    }
}

// void eggLayer(int playerNumber)
// {

// }

// void eggLaid(int eggNumber, int playerNumber, int width, int height)
// {

// }

// void playerConnexionEgg(int eggNumber)
// {

// }

// void deathEgg(int eggNumber)
// {

// }

void Window::timeUnitRequest(std::string string)
{
    std::stringstream ss(string);
    std::string token;

    ss >> token;
    ss >> token;
    std::string timeUnit = token;
    _freq = std::stoi(timeUnit);
}

// void timeUnitModification(std::string timeUnit)
// {

// }

// void endOfGame(std::string nameOfTeam)
// {

// }

// void messageFromServer(std::string message)
// {

// }

// void unknownCommand()
// {

// }

// void commandParameter()
// {

// }

// void Pex(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int playerNumber = std::stoi(token);
//     expulsion(playerNumber);
// }

// void Pfk(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int playerNumber = std::stoi(token);
//     eggLayer(playerNumber);
// }

// void Pdr(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int playerNumber = std::stoi(token);
//     ss >> token;
//     int ressourceNumber = std::stoi(token);
//     ressourceDropping(playerNumber, ressourceNumber);
// }

// void Pdi(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int playerNumber = std::stoi(token);
//     deathPlayer(playerNumber);
// }

// void Enw(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int eggNumber = std::stoi(token);
//     ss >> token;
//     int playerNumber = std::stoi(token);
//     ss >> token;
//     int width = std::stoi(token);
//     ss >> token;
//     int height = std::stoi(token);
//     eggLaid(eggNumber, playerNumber, width, height);
// }

// void Ebo(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int eggNumber = std::stoi(token);
//     playerConnexionEgg(eggNumber);
// }

// void Edi(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     int eggNumber = std::stoi(token);
//     deathEgg(eggNumber);
// }

// void Sst(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     std::string timeUnit = token;
//     timeUnitModification(timeUnit);
// }

// void Seg(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     std::string nameOfTeam = token;
//     endOfGame(nameOfTeam);
// }

// void Smg(std::string string)
// {
//     std::stringstream ss(string);
//     std::string token;

//     ss >> token;
//     ss >> token;
//     std::string message = token;
//     messageFromServer(message);
// }

// void Suc(std::string string)
// {
//     unknownCommand();
// }

// void Sbp(std::string string)
// {
//     commandParameter();
// }

void Window::parseStdServer(std::string string)
{
    std::stringstream ss(string);
    std::string token;

    ss >> token;
    if (token == "msz")
        setMapSize(string);
    else if (token == "bct")
        setContentOfTile(string);
    else if (token == "pnw")
        connexionPlayer(string);
    else if (token == "ppo")
        playerPosition(string);
    else if (token == "plv")
        playerLevel(string);
    else if (token == "pin")
        playerInventory(string);
    // else if (token == "pex")
    //     Pex(string);
    // else if (token == "pbc")
    //     broadcast(string);
    // else if (token == "pic")
    //     startIncantation(string);
    // else if (token == "pie")
        // endIncantation(string);
    // else if (token == "pfk")
    //     Pfk(string);
    else if (token == "pdr")
        ressourceDropping(string);
    else if (token == "pgt")
        ressourceCollecting(string);
    else if (token == "pdi")
        deathPlayer(string);
    // else if (token == "enw")
    //     Enw(string);
    // else if (token == "ebo")
    //     Ebo(string);
    // else if (token == "edi")
    //     Edi(string);
    else if (token == "sgt")
        timeUnitRequest(string);
    // else if (token == "sst")
    //     Sst(string);
    // else if (token == "seg")
    //     Seg(string);
    // else if (token == "smg")
    //     Smg(string);
    // else if (token == "suc")
    //     Suc(string);
    // else if (token == "sbp")
    //     Sbp(string);
}
