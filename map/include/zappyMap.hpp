/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** zappyMap
*/

#ifndef ZAPPYMAP_HPP_
#define ZAPPYMAP_HPP_

#include "raylib.h"
#include <iostream>
#include "raymath.h"
#include <random>
#include <array>
#include <unordered_map>
#include <stack>
#include "Server.hpp"
#include <memory>
#include <stdbool.h>
#include <cstring>
#include "Error.hpp"
#include "Parser.hpp"

enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver
};

enum class PlayerOrientation {
    North = 1,
    East = 2,
    South = 3,
    West = 4
};


class Game {
    public:
        void PushState(GameState state) {
            _stateStack.push(state);
        }
        void PopState() {
            if (!_stateStack.empty()) {
                _stateStack.pop();
            }
        }
        GameState GetCurrentState() const {
            if (!_stateStack.empty()) {
                return _stateStack.top();
            }
            return GameState::Menu;
        }
    private:
        std::stack<GameState> _stateStack;
};

class Button {
    public:
        Button(const char *fileName, int posx, int posy, float width, float height, int winSizeX, int winSizeY);
        ~Button() = default;

        Button(const Button& other) = delete;
        Button& operator=(const Button& other) = delete;

        Button(Button&& other) noexcept : btnState(other.btnState),
            btnAction(other.btnAction),
            _button(other._button),
            sourceRec(other.sourceRec),
            btnBounds(other.btnBounds)
        {
            other._button = {0};
        }
    // private:
        int btnState;
        int btnAction;
        Texture2D _button;
        Rectangle sourceRec;
        Rectangle btnBounds;
};

typedef struct Tile {
    int eggs;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    Tile() : eggs(0), food(0), linemate(0), deraumere(0), sibur(0), mendiane(0), phiras(0), thystame(0) {
    }
} Tile_t;

class Player {
	public:
		Player(Vector3 pos, Model *farmer, ModelAnimation *modelAnimations, int animCount, int orientation, int level, std::string nameOfTeam , std::string id);
		~Player();
        void updateAnimation(std::uniform_int_distribution<int> dist);

        Model *_farmer;

        Vector3 getPlayerPos() {
            return _playerPosition;
        };

        void playerMovement(PlayerOrientation, Vector2 mapSize, int freq);

        Player(const Player& other) = delete;
        Player& operator=(const Player& other) = delete;

        Player(Player&& other) noexcept : _playerPosition(other._playerPosition),
            _farmer(other._farmer),
            _modelAnimations(other._modelAnimations),
            _anim(other._anim),
            _animsCount(other._animsCount),
            _animCurrentFrame(other._animCurrentFrame),
            _currentAnimationIndex(other._currentAnimationIndex),
            _orientation(other._orientation),
            _team(other._team),
            _id(other._id),
            _level(other._level),
            _running(other._running),
            _previousAnimations(other._previousAnimations),
            _inventory(other._inventory),
            _died(other._died),
            remainingDistance(other.remainingDistance),
            elapsedTime(other.elapsedTime)
        {
            other._farmer = nullptr;
        }

        int getOrientation() {
            return _orientation;
        }

        void setOrientation(int orientation) {
            _orientation = orientation;
        }

        int getLevel() {
            return _level;
        }

        void setLevel(int level) {
            _level = level;
        }

        std::string getTeam() {
            return _team;
        }

        void setPlayerPos(Vector2 pos) {
            _playerPosition.x = pos.x;
            _playerPosition.z = pos.y;
        }

        void setRunning() {
            _running = true;
            remainingDistance++;
        }

        bool getRunning() {
            return _running;
        }

        void setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame) {
            _inventory.food = food;
            _inventory.linemate = linemate;
            _inventory.deraumere = deraumere;
            _inventory.sibur = sibur;
            _inventory.mendiane = mendiane;
            _inventory.phiras = phiras;
            _inventory.thystame = thystame;
        }

        Tile getInventory() {
            return _inventory;
        }

        void setDied() {
            _died = true;
        }

    private:
        Vector3 _playerPosition;
        ModelAnimation *_modelAnimations;
        ModelAnimation _anim;
        unsigned int _animsCount;
        unsigned int _animCurrentFrame;
        float elapsedTime;
        int _currentAnimationIndex;
        int _previousAnimations;
        float remainingDistance;

        std::string _team;
        int _level;
        int _orientation;
        std::string _id;
        bool _running;
        Tile _inventory;

        bool _died;
};

class BgMusic {
    public:
        BgMusic();
        ~BgMusic();
        void updateMusic();
        void pauseMusic();
        void resumeMusic();
    private:
        Music _music;
};

struct Coordinate {
    int x;
    int y;

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

struct CoordinateHasher {
    std::size_t operator()(const Coordinate& coord) const {
        return std::hash<int>{}(coord.x) ^ (std::hash<int>{}(coord.y) << 1);
    }
};

class Window {
	public:
		Window(const int screenWidth, const int screenHeight, float map_x, float map_y);
		~Window();
        void initZappy();
        void gameLoop(Server *serv);
        void cameraController();
        void zappyMap();
        void initButton();
        void checkSound(BgMusic*);
        void checkBtns(Game*);
        void DisplayMenu();
        void UpdateGameplay();
        void setCameraGame();
        // void HandleServerInput();
        Vector2 checkRayCollisionWithIsland(float regionStartX, float regionStartY, float regionEndX, float regionEndY);
        Server *serv;

        //Protocole
        void parseStdServer(std::string string);
        void setMapSize(std::string string);
        void setContentOfTile(std::string string);
        void connexionPlayer(std::string string);
        void playerPosition(std::string string);
        void playerLevel(std::string string);
        void playerInventory(std::string string);
        void ressourceCollecting(std::string string);
        void ressourceDropping(std::string string);
        void deathPlayer(std::string string);
        // void broadcast(std::string string);
        // void startIncantation(std::string string);
        // void endIncantation(std::string string);
        void timeUnitRequest(std::string string);
        bool _ended;
        int _freq;

    private:
        bool _initZappy;
        std::unordered_map<Coordinate, Tile, CoordinateHasher> mapTile;
        int _keyGen;
        std::mt19937 _gen;

        Camera3D _camera;
        Texture2D _background;
        Model _islandMenu;
        Model _island;
        std::vector<int> _mapGeneration;
        std::unordered_map<std::string, Button> _sprite;
        std::unordered_map<std::string, Player> _playerList;

        Vector2 _mapSize;
        Model _farmer;
        ModelAnimation *_modelAnimations;
        unsigned int _animsCount;
        Rectangle _infoMenu;

        Ray _ray;
        RayCollision _collision;
        Matrix _islandTransform;
        float startX;
        int endX;
        float startY;
        int endY;

        Model _food;
        Model _gem;
        Model _egg;

        bool _getInfoMenu;
        Vector2 _hit;

        bool isDropdownActive = false;
        int selectedCharacterIndex = 0;
        std::vector<std::string> characters = {"case"};
        Rectangle _dropDownMenu;
};

class mapTile {
    public:
        mapTile() {};
        ~mapTile() = default;
    private:
};

#endif /* !ZAPPYMAP_HPP_ */
