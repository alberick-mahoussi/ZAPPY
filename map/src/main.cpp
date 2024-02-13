/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** main
*/

#include "Threads.hpp"
#include "zappyMap.hpp"
#include <sstream>
#include <fcntl.h>
#define FLT_MAX     340282346638528859811704183484516925440.0f

void Window::cameraController()
{
    //Controller Zoom IN/Zoom OUT
    if (IsKeyDown(KEY_E)) _camera.target.y -= 0.1f;
    if (IsKeyDown(KEY_Q)) _camera.target.y += 0.1f;
    //Controller UP/Down
    if (IsKeyDown(KEY_F)) _camera.position.y -= 0.1f;
    if (IsKeyDown(KEY_R)) _camera.position.y += 0.1f;
    //Controller Right/Left
    if (IsKeyDown(KEY_A)) _camera.position.x -= 0.1f;
    if (IsKeyDown(KEY_A)) _camera.target.x -= 0.1f;
    if (IsKeyDown(KEY_D)) _camera.position.x += 0.1f;
    if (IsKeyDown(KEY_D)) _camera.target.x += 0.1f;
    //Controller Front/Back
    if (IsKeyDown(KEY_W)) _camera.position.z -= 0.1f;
    if (IsKeyDown(KEY_W)) _camera.target.z -= 0.1f;
    if (IsKeyDown(KEY_S)) _camera.position.z += 0.1f;
    if (IsKeyDown(KEY_S)) _camera.target.z += 0.1f;
    if (_camera.position.x < 0.0f || _camera.target.x < 0.0f)
    {
        _camera.position.x = 0.0f;
        _camera.target.x = 0.0f;
    }
    if (_camera.position.x > _mapSize.x - 0.5 || _camera.target.x > _mapSize.x - 0.5)
    {
        _camera.position.x = _mapSize.x - 0.5;
        _camera.target.x = _mapSize.x - 0.5;
    }
    if (_camera.target.y < -30.0f)
        _camera.target.y = -30.0f;
    if (_camera.target.y > 10.0f)
        _camera.target.y = 10.0f;
    if (_camera.position.y < 3.0f)
        _camera.position.y = 3.0f;
    if (_camera.position.y > 15.0f)
        _camera.position.y = 15.0f;
}

void Window::zappyMap()
{
}

void Window::DisplayMenu()
{
    std::uniform_int_distribution<int> dist(8, 10);

    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(_background, 0, 0, WHITE);

        BeginMode3D(_camera);
            _playerList.find("Menu")->second.updateAnimation(dist);
            _playerList.find("Menu")->second._farmer->transform = MatrixRotateXYZ(Vector3 {0, DEG2RAD * 1, 0});
            DrawModelEx(*_playerList.find("Menu")->second._farmer,  _playerList.find("Menu")->second.getPlayerPos(), (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 0.003f, 0.003f, 0.003f}, WHITE);
            _islandMenu.transform = MatrixRotateXYZ(Vector3 {0, DEG2RAD * -90, 0});
            DrawModel(_islandMenu, {1, 1, 1}, 0.5f, WHITE);
        EndMode3D();
        DrawTexture(_sprite.find("title")->second._button, _sprite.find("title")->second.btnBounds.x, _sprite.find("title")->second.btnBounds.y, WHITE);
        DrawTextureRec(_sprite.find("play")->second._button, _sprite.find("play")->second.sourceRec, (Vector2){_sprite.find("play")->second.btnBounds.x, _sprite.find("play")->second.btnBounds.y}, WHITE);

        DrawTextureRec(_sprite.find("btnHtp")->second._button, _sprite.find("btnHtp")->second.sourceRec, (Vector2){_sprite.find("btnHtp")->second.btnBounds.x, _sprite.find("btnHtp")->second.btnBounds.y}, WHITE);
        if (_sprite.find("btnOn")->second.btnAction == false)
            DrawTextureRec(_sprite.find("btnOn")->second._button, _sprite.find("btnOn")->second.sourceRec, (Vector2){_sprite.find("btnOn")->second.btnBounds.x, _sprite.find("btnOn")->second.btnBounds.y}, WHITE);
        else
            DrawTextureRec(_sprite.find("btnOff")->second._button, _sprite.find("btnOff")->second.sourceRec, (Vector2){_sprite.find("btnOff")->second.btnBounds.x, _sprite.find("btnOff")->second.btnBounds.y}, WHITE);
        DrawTextureRec(_sprite.find("exit")->second._button, _sprite.find("exit")->second.sourceRec, (Vector2){_sprite.find("exit")->second.btnBounds.x, _sprite.find("exit")->second.btnBounds.y}, WHITE);
    EndDrawing();
}

Vector2 Window::checkRayCollisionWithIsland(float regionStartX, float regionStartY, float regionEndX, float regionEndY)
{
    if (regionEndX - regionStartX <= 1) {
        return { regionStartX, regionStartY };
    } else if (regionEndY - regionStartY <= 1) {
        float midX = round((regionStartX + regionEndX) / 2.0f);

        RayCollision regionHitInfo = GetRayCollisionBox(_ray, (BoundingBox){ (Vector3){ regionStartX -0.5f, 0.4f, regionStartY -0.5f}, (Vector3){ midX -0.5f, 0.4f, regionEndY -0.5f } });
        if (regionHitInfo.hit) {
            return checkRayCollisionWithIsland(regionStartX, regionStartY, midX, regionEndY);
        } else {
            return checkRayCollisionWithIsland(midX, regionStartY, regionEndX, regionEndY);
        }

    } else if (regionEndY != regionStartY) {
        float midY = round((regionStartY + regionEndY) / 2.0f);

        RayCollision regionHitInfo = GetRayCollisionBox(_ray, (BoundingBox){ (Vector3){ regionStartX -0.5f, 0.4f, regionStartY -0.5f}, (Vector3){ regionEndX -0.5f, 0.4f, midY -0.5f } });
        if (regionHitInfo.hit) {
            return checkRayCollisionWithIsland(regionStartX, regionStartY, regionEndX, midY);
        } else {
            return checkRayCollisionWithIsland(regionStartX, midY, regionEndX, regionEndY);
        }
    }
    return { regionStartX, regionStartY };
}

char* ConcatenateIntegersAsCharArray(int num1, int num2)
{
    std::string result = "[" + std::to_string(num1) + " : " + std::to_string(num2) + "]";
    char* charArray = new char[result.length() + 1];
    std::strcpy(charArray, result.c_str());
    return charArray;
}

void Window::UpdateGameplay()
{
    std::uniform_int_distribution<int> idle(8, 10);
    _collision.distance = FLT_MAX;
    _collision.hit = false;
    Color cursorColor = WHITE;

    _ray = GetMouseRay(GetMousePosition(), _camera);
    std::array<int, 4> values = {540, 90, 1, -90};
    std::uniform_real_distribution<float> distRessources(-0.25f, 0.25f);

    RayCollision islandHitInfo = { 0 };

    float searchRadius = 1.0f;

    float regionStartX = 0;
    float regionStartY = 0;
    float regionEndX = _mapSize.y;
    float regionEndY = _mapSize.x;

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(_background, 0, 0, WHITE);
        BeginMode3D(_camera);
            int index = 0;
            _gen.seed(_keyGen);
            for (float i = 0; i != _mapSize.y; i++) {
                for (float j = 0; j != _mapSize.x; j++) {
                    _island.transform = MatrixRotateXYZ(Vector3 {0, DEG2RAD * _mapGeneration.at(index), 0});
                    DrawModel(_island, {i, 0.4f, j}, 0.51, WHITE);
                    DrawCubeWires({i, 0.50f, j}, 1.0f, 0.0f, 1.0f, BLACK);

                    Coordinate coord{static_cast<int>(i), static_cast<int>(j)};

                    if (mapTile.count(coord) > 0) {
                        float posX = distRessources(_gen);
                        float poxY = distRessources(_gen);
                        if (mapTile[coord].food > 0) {
                            _food.transform = MatrixRotateXYZ(Vector3 {0, DEG2RAD * ((i + j) * 24), 0});
                            DrawModel(_food, {posX + i, 0.5f, poxY + j}, 0.125f, WHITE);
                        }
                        posX = distRessources(_gen);
                        poxY = distRessources(_gen);
                        if (mapTile[coord].eggs > 0) {
                            _egg.transform = MatrixRotateXYZ(Vector3 {DEG2RAD * -90, 0, 0});
                            DrawModel(_egg, {posX + i, 0.5f, poxY + j}, 0.125f, WHITE);
                        }

                        posX = distRessources(_gen);
                        poxY = distRessources(_gen);
                        if (mapTile[coord].linemate > 0) {
                            _gem.transform = MatrixRotateXYZ(Vector3 {DEG2RAD * -90, 0, DEG2RAD * ((i + j) * 24)});
                            DrawModel(_gem, {posX + i, 0.5f, poxY + j}, 0.3f, BLUE);
                        }
                        posX = distRessources(_gen);
                        poxY = distRessources(_gen);
                        if (mapTile[coord].deraumere > 0) {
                            _gem.transform = MatrixRotateXYZ(Vector3 {DEG2RAD * -90, 0, DEG2RAD * ((i + j) * 24)});
                            DrawModel(_gem, {posX + i, 0.5f, poxY + j}, 0.3f, SKYBLUE);
                        }
                        posX = distRessources(_gen);
                        poxY = distRessources(_gen);
                        if (mapTile[coord].sibur > 0) {
                            _gem.transform = MatrixRotateXYZ(Vector3 {DEG2RAD * -90, 0, DEG2RAD * ((i + j) * 24)});
                            DrawModel(_gem, {posX + i, 0.5f, poxY + j}, 0.3f, GREEN);
                        }
                        posX = distRessources(_gen);
                        poxY = distRessources(_gen);
                        if (mapTile[coord].mendiane > 0) {
                            _gem.transform = MatrixRotateXYZ(Vector3 {DEG2RAD * -90, 0, DEG2RAD * ((i + j) * 24)});
                            DrawModel(_gem, {posX + i, 0.5f, poxY + j}, 0.3f, YELLOW);
                        }
                        posX = distRessources(_gen);
                        poxY = distRessources(_gen);
                        if (mapTile[coord].phiras > 0) {
                            _gem.transform = MatrixRotateXYZ(Vector3 {DEG2RAD * -90, 0, DEG2RAD * ((i + j) * 24)});
                            DrawModel(_gem, {posX + i, 0.5f, poxY + j}, 0.3f, WHITE);
                        }
                        posX = distRessources(_gen);
                        poxY = distRessources(_gen);
                        if (mapTile[coord].thystame > 0) {
                            _gem.transform = MatrixRotateXYZ(Vector3 {DEG2RAD * -90, 0, DEG2RAD * ((i + j) * 24)});
                            DrawModel(_gem, {posX + i, 0.5f, poxY + j}, 0.3f, RED);
                        }
                    } else {
                        for (int i = 0; i != 8; i ++) {
                            float posX = distRessources(_gen);
                            float poxY = distRessources(_gen);
                        }
                    }

                    index++;
                }
            }
            for (auto &player : _playerList) {
                if (player.second.getPlayerPos().y == 0.5f) {
                    if (player.second.getRunning() == true) {
                        player.second.playerMovement(static_cast<PlayerOrientation>(player.second.getOrientation()), _mapSize, _freq);
                    } else {
                        player.second.updateAnimation(idle);
                    }
                    player.second._farmer->transform = MatrixRotateXYZ(Vector3 {0, DEG2RAD * values[player.second.getOrientation() - 1], 0});
                    DrawModelEx(*player.second._farmer,  player.second.getPlayerPos(), (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 0.004f, 0.004f, 0.004f}, WHITE);
                }
            }
            index = 0;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                RayCollision regionHitInfo = GetRayCollisionBox(_ray, (BoundingBox){ (Vector3){ regionStartX - 0.5f, 0.4f, regionStartY - 0.5f}, (Vector3){ regionEndX - 0.5f, 0.4f, regionEndY - 0.5f} });
                if (regionHitInfo.hit) {
                    _hit = checkRayCollisionWithIsland(regionStartX, regionStartY, regionEndX, regionEndY);
                    float gridX = static_cast<float>(std::max(0.0f, round(_hit.x)));
                    float gridY = static_cast<float>(std::max(0.0f, round(_hit.y)));
                    characters.clear();
                    std::string message = "Case: [" + std::to_string(static_cast<int>(gridX)) + " : " + std::to_string(static_cast<int>(gridY)) + "]";
                    characters.push_back(message);
                    selectedCharacterIndex = 0;
                    for (auto &player : _playerList) {
                        if (static_cast<int>(player.second.getPlayerPos().x + 0.5f) == static_cast<int>(gridX) && static_cast<int>(player.second.getPlayerPos().z + 0.5f) == static_cast<int>(gridY)) {
                            characters.push_back(player.first);
                        }
                    }
                    _getInfoMenu = true;
                } else {
                    if (_getInfoMenu == true) {
                        if (isDropdownActive) {
                            for (int i = 0; i < characters.size(); i++) {
                                float optionX = _dropDownMenu.x;
                                float optionY = _dropDownMenu.y + _dropDownMenu.height + (i * _dropDownMenu.height);
                                float optionWidth = _dropDownMenu.width;
                                float optionHeight = 50;


                                if (CheckCollisionPointRec(GetMousePosition(), { optionX, optionY, optionWidth, optionHeight })) {
                                    selectedCharacterIndex = i;
                                    isDropdownActive = false;
                                    break;
                                }
                            }
                        } else {
                            if (CheckCollisionPointRec(GetMousePosition(), _dropDownMenu)) {
                                isDropdownActive = true;
                            } else
                                _getInfoMenu = false;
                        }
                    } else {
                        _getInfoMenu = false;
                    }
                }
            }
            DrawBoundingBox((BoundingBox){ (Vector3){ regionStartX - 0.5f, 0.4f, regionStartY - 0.5f}, (Vector3){ regionEndX - 0.5f, 0.4f, regionEndY - 0.5f} }, BLACK);
        EndMode3D();

        if (_sprite.find("btnOn")->second.btnAction == false)
            DrawTextureRec(_sprite.find("btnOn")->second._button, _sprite.find("btnOn")->second.sourceRec, (Vector2){_sprite.find("btnOn")->second.btnBounds.x, _sprite.find("btnOn")->second.btnBounds.y}, WHITE);
        else
            DrawTextureRec(_sprite.find("btnOff")->second._button, _sprite.find("btnOff")->second.sourceRec, (Vector2){_sprite.find("btnOff")->second.btnBounds.x, _sprite.find("btnOff")->second.btnBounds.y}, WHITE);

        if (_getInfoMenu == true) {
            Color color = { 0, 0, 0, 128 };
            DrawRectangleRec(_infoMenu, color);
            DrawTexture(_sprite.find("cyan")->second._button, _sprite.find("cyan")->second.btnBounds.x, _sprite.find("cyan")->second.btnBounds.y, WHITE);
            DrawTexture(_sprite.find("red")->second._button, _sprite.find("red")->second.btnBounds.x, _sprite.find("red")->second.btnBounds.y, WHITE);
            DrawTexture(_sprite.find("blue")->second._button, _sprite.find("blue")->second.btnBounds.x, _sprite.find("blue")->second.btnBounds.y, WHITE);
            DrawTexture(_sprite.find("green")->second._button, _sprite.find("green")->second.btnBounds.x, _sprite.find("green")->second.btnBounds.y, WHITE);
            DrawTexture(_sprite.find("yellow")->second._button, _sprite.find("yellow")->second.btnBounds.x, _sprite.find("yellow")->second.btnBounds.y, WHITE);
            DrawTexture(_sprite.find("purpul")->second._button, _sprite.find("purpul")->second.btnBounds.x, _sprite.find("purpul")->second.btnBounds.y, WHITE);
            DrawTexture(_sprite.find("meat")->second._button, _sprite.find("meat")->second.btnBounds.x, _sprite.find("meat")->second.btnBounds.y, WHITE);

            Coordinate coord{static_cast<int>(_hit.x), static_cast<int>(_hit.y)};

            DrawText(ConcatenateIntegersAsCharArray(_hit.x, _hit.y) ,_infoMenu.x + 10, _infoMenu.y + 10, 30, WHITE);

            DrawRectangle(_dropDownMenu.x, _dropDownMenu.y, _dropDownMenu.width, _dropDownMenu.height, isDropdownActive ? GREEN : GREEN);
            DrawText(characters[selectedCharacterIndex].c_str(), _dropDownMenu.x + _dropDownMenu.x, _dropDownMenu.y + _dropDownMenu.y, 40, BLACK);
            if (isDropdownActive) {
                for (int i = 0; i < characters.size(); i++) {
                    DrawRectangle(_dropDownMenu.x, _dropDownMenu.y + _dropDownMenu.height + (i * _dropDownMenu.height), _dropDownMenu.width, _dropDownMenu.height, (selectedCharacterIndex == i) ? GREEN : WHITE);
                    DrawText(characters[i].c_str(), _dropDownMenu.x + _dropDownMenu.x, _dropDownMenu.y + _dropDownMenu.height + (i * _dropDownMenu.height) + _dropDownMenu.y, 40, BLACK);
                }
            }

            if (selectedCharacterIndex > 0) {
                auto it = _playerList.find(characters[selectedCharacterIndex]);
                if (it != _playerList.end()) {
                    std::string message = "Name: " + it->first;
                    DrawText(message.c_str(),_infoMenu.x + 10, _infoMenu.y + 50, 35, WHITE);
                    message = "Level: " + std::to_string(static_cast<int>(it->second.getLevel()));
                    DrawText(message.c_str(),_infoMenu.x + 10, _infoMenu.y + 90, 35, WHITE);
                    message = "Team: " + it->second.getTeam();
                    DrawText(message.c_str(),_infoMenu.x + 10, _infoMenu.y + 130, 35, WHITE);
                    message = std::to_string(it->second.getInventory().linemate);
                    DrawText(message.c_str() , _sprite.find("blue")->second.btnBounds.x + (_sprite.find("blue")->second.sourceRec.width / 2.0f) - 5, _sprite.find("blue")->second.btnBounds.y + _sprite.find("blue")->second.sourceRec.height * 3.25f, 30, WHITE);
                    message = std::to_string(it->second.getInventory().deraumere);
                    DrawText(message.c_str() , _sprite.find("cyan")->second.btnBounds.x + (_sprite.find("cyan")->second.sourceRec.width / 2.0f) - 5, _sprite.find("cyan")->second.btnBounds.y + _sprite.find("cyan")->second.sourceRec.height * 3.25f, 30, WHITE);
                    message = std::to_string(it->second.getInventory().sibur);
                    DrawText(message.c_str() , _sprite.find("green")->second.btnBounds.x + (_sprite.find("green")->second.sourceRec.width / 2.0f) - 5, _sprite.find("green")->second.btnBounds.y + _sprite.find("green")->second.sourceRec.height * 3.25f, 30, WHITE);
                    message = std::to_string(it->second.getInventory().mendiane);
                    DrawText(message.c_str() , _sprite.find("yellow")->second.btnBounds.x + (_sprite.find("yellow")->second.sourceRec.width / 2.0f) - 5, _sprite.find("yellow")->second.btnBounds.y + _sprite.find("yellow")->second.sourceRec.height * 3.25f, 30, WHITE);
                    message = std::to_string(it->second.getInventory().phiras);
                    DrawText(message.c_str() , _sprite.find("purpul")->second.btnBounds.x + (_sprite.find("purpul")->second.sourceRec.width / 2.0f) - 5, _sprite.find("purpul")->second.btnBounds.y + _sprite.find("purpul")->second.sourceRec.height * 3.25f, 30, WHITE);
                    message = std::to_string(it->second.getInventory().thystame);
                    DrawText(message.c_str() , _sprite.find("red")->second.btnBounds.x + (_sprite.find("red")->second.sourceRec.width / 2.0f) - 5, _sprite.find("red")->second.btnBounds.y + _sprite.find("red")->second.sourceRec.height * 3.25f, 30, WHITE);
                    message = std::to_string(it->second.getInventory().food);
                    DrawText(message.c_str() , _sprite.find("meat")->second.btnBounds.x + (_sprite.find("meat")->second.sourceRec.width / 2.0f) - 5, _sprite.find("meat")->second.btnBounds.y + _sprite.find("meat")->second.sourceRec.height * 3.25f, 30, WHITE);
                }
            } else {
                std::string message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].eggs : 0);
                DrawText(message.c_str() , _sprite.find("dofus")->second.btnBounds.x + (_sprite.find("dofus")->second.sourceRec.width / 2.0f) - 5, _sprite.find("dofus")->second.btnBounds.y + _sprite.find("dofus")->second.sourceRec.height * 3.25f, 30, WHITE);
                DrawTexture(_sprite.find("dofus")->second._button, _sprite.find("dofus")->second.btnBounds.x, _sprite.find("dofus")->second.btnBounds.y, WHITE);
                message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].linemate : 0);
                DrawText(message.c_str() , _sprite.find("blue")->second.btnBounds.x + (_sprite.find("blue")->second.sourceRec.width / 2.0f) - 5, _sprite.find("blue")->second.btnBounds.y + _sprite.find("blue")->second.sourceRec.height * 3.25f, 30, WHITE);
                message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].deraumere : 0);
                DrawText(message.c_str() , _sprite.find("cyan")->second.btnBounds.x + (_sprite.find("cyan")->second.sourceRec.width / 2.0f) - 5, _sprite.find("cyan")->second.btnBounds.y + _sprite.find("cyan")->second.sourceRec.height * 3.25f, 30, WHITE);
                message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].sibur : 0);
                DrawText(message.c_str() , _sprite.find("green")->second.btnBounds.x + (_sprite.find("green")->second.sourceRec.width / 2.0f) - 5, _sprite.find("green")->second.btnBounds.y + _sprite.find("green")->second.sourceRec.height * 3.25f, 30, WHITE);
                message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].mendiane : 0);
                DrawText(message.c_str() , _sprite.find("yellow")->second.btnBounds.x + (_sprite.find("yellow")->second.sourceRec.width / 2.0f) - 5, _sprite.find("yellow")->second.btnBounds.y + _sprite.find("yellow")->second.sourceRec.height * 3.25f, 30, WHITE);
                message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].phiras : 0);
                DrawText(message.c_str() , _sprite.find("purpul")->second.btnBounds.x + (_sprite.find("purpul")->second.sourceRec.width / 2.0f) - 5, _sprite.find("purpul")->second.btnBounds.y + _sprite.find("purpul")->second.sourceRec.height * 3.25f, 30, WHITE);
                message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].thystame : 0);
                DrawText(message.c_str() , _sprite.find("red")->second.btnBounds.x + (_sprite.find("red")->second.sourceRec.width / 2.0f) - 5, _sprite.find("red")->second.btnBounds.y + _sprite.find("red")->second.sourceRec.height * 3.25f, 30, WHITE);
                message = std::to_string((mapTile.count(coord) > 0) ? mapTile[coord].food : 0);
                DrawText(message.c_str() , _sprite.find("meat")->second.btnBounds.x + (_sprite.find("meat")->second.sourceRec.width / 2.0f) - 5, _sprite.find("meat")->second.btnBounds.y + _sprite.find("meat")->second.sourceRec.height * 3.25f, 30, WHITE);
            }
        }
    EndDrawing();
}

void Window::initZappy()
{
    if (_initZappy == false) {
        serv->send_req("mct\n");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::array<int, 4> values = {1, 90, -90, 540};
        _initZappy = true;

        for (float i = 0; i != _mapSize.y; i++)
            for (float j = 0; j != _mapSize.x; j++) {
                std::uniform_int_distribution<int> distribution(0, values.size() - 1);
                int randomNumber = distribution(gen);
                _mapGeneration.push_back(values[randomNumber]);
        }
        serv->send_req("sgt\n");
    }
}

void Window::gameLoop(Server *serv)
{
    Game game;
    BgMusic _sound = BgMusic();

    while (!WindowShouldClose()) {
        initZappy();
        GameState currentState = game.GetCurrentState();
        _sound.updateMusic();
        checkSound(&_sound);
        switch (currentState) {
            case GameState::Menu:
                DisplayMenu();
                checkBtns(&game);
                break;
            case GameState::Playing:
                cameraController();
                UpdateGameplay();
                break;
            case GameState::Paused:
                break;
            case GameState::GameOver:
                break;
        }
        if (_sprite.find("exit")->second.btnState == 2)
            break;
    }
    _ended = true;
    serv->send_req("jreiuhriuezb\n");
}

int main(int ac, char **av)
{
    Parser parse(ac, av);
    std::string msg;
    bool test = true;
    float map_x;
    float map_y;
    Server serv(parse.get_port(), parse.get_ip());
    serv.send_req("GRAPHIC\n");
    sleep(1);
    serv.send_req("msz\n");
    while (1) {
        serv.gui_loop();
        if (FD_ISSET(serv._sockfd, &serv._fds)) {
            msg = serv.read_client();
            std::stringstream ss(msg);
            std::string token;
            ss >> token;
            if (token == "msz") {
                ss >> token;
                map_x = std::stof(token);
                ss >> token;
                map_y = std::stof(token);
                break;
            }
        }
    }
    Window zappyMap(1920, 1080, map_x, map_y);
    zappyMap.serv = &serv;
    Threads thread(&zappyMap);
}
