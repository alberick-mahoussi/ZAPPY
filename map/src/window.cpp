/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** window
*/

#include "zappyMap.hpp"

Window::Window(const int screenWidth, const int screenHeight, float map_x, float map_y)
{
    InitWindow(screenWidth, screenHeight, "Zappy");
    InitAudioDevice();
    Image background = LoadImage("images/sprites/background.png");
    ImageResize(&background, screenWidth, screenHeight);
    _background= LoadTextureFromImage(background);
    _ended = false;
    _freq = 0;

    _initZappy = false;

    _camera = { 0 };
    _camera.position = (Vector3){ 1, 2, 5};
    _camera.target = (Vector3){ 1, 1.0f, 0 };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 75.0f;
    _camera.projection = CAMERA_PERSPECTIVE;

    _mapSize.x = map_x;
    _mapSize.y = map_y;

    _animsCount = 0;

    _farmer = LoadModel("images/farmer3D/Engineer.glb");
    _modelAnimations = LoadModelAnimations("images/farmer3D/Engineer.glb", &_animsCount);

    _playerList.emplace("Menu", Player(Vector3{ 1, 1.3, 4}, &_farmer, _modelAnimations, _animsCount, 1, 0, "", ""));

    _island = LoadModel("images/island3d/island.obj");
    Texture2D _texture = LoadTexture("images/island3d/grassland.png");
    SetMaterialTexture(&_island.materials[0], MATERIAL_MAP_DIFFUSE, _texture);

    _islandMenu = LoadModel("../images/main_menu/beach_island/scene.gltf");

    _sprite.emplace("play", Button("images/main_menu/buttons/play_button.png", (screenWidth * 0.3), (screenHeight), (screenWidth * 0.175), (screenHeight * 0.3), screenWidth, screenHeight));
    _sprite.emplace("btnHtp", Button("images/main_menu/buttons/howtoplay_button.png", (screenWidth * 0.5), (screenHeight), (screenWidth * 0.175), (screenHeight * 0.3), screenWidth, screenHeight));
    _sprite.emplace("exit", Button("images/main_menu/buttons/exit_button.png", (screenWidth * 0.7), (screenHeight), (screenWidth * 0.175), (screenHeight * 0.3), screenWidth, screenHeight));
    _sprite.emplace("btnOn", Button("images/main_menu/buttons/soundon_button.png", (screenWidth * 0.9625), (screenHeight * 0.13), (screenWidth * 0.05), (screenHeight * 0.225), screenWidth, screenHeight));
    _sprite.emplace("btnOff", Button("images/main_menu/buttons/soundoff_button.png", (screenWidth * 0.9625), (screenHeight * 0.13), (screenWidth * 0.05), (screenHeight * 0.225), screenWidth, screenHeight));
    _sprite.emplace("title", Button("images/main_menu/sprites/zappyTitle.png", (screenWidth / 2), (screenHeight * 0.15f), (screenWidth * 0.6), (screenHeight * 0.255), screenWidth, screenHeight));

    _sprite.emplace("yellow", Button("images/sprites/yellowGem.png", (screenWidth / 2) + (screenWidth * 0.05f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));
    _sprite.emplace("green", Button("images/sprites/greenGem.png", (screenWidth / 2) - (screenWidth * 0.05f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));
    _sprite.emplace("purpul", Button("images/sprites/purpulGem.png", (screenWidth / 2) + (screenWidth * 0.15f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));
    _sprite.emplace("cyan", Button("images/sprites/cyanGem.png", (screenWidth / 2) - (screenWidth * 0.15f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));
    _sprite.emplace("blue", Button("images/sprites/blueGem.png", (screenWidth / 2) - (screenWidth * 0.25f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));
    _sprite.emplace("red", Button("images/sprites/redGem.png", (screenWidth / 2) + (screenWidth * 0.25f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));

    _sprite.emplace("meat", Button("images/sprites/meat.png", (screenWidth / 2) + (screenWidth * 0.35f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));
    _sprite.emplace("dofus", Button("images/sprites/dofus.png", (screenWidth / 2) - (screenWidth * 0.35f), (screenHeight * 0.87f), (screenHeight * 0.115f), (screenHeight * 0.115f), screenWidth, screenHeight));

    _infoMenu = { 0, (screenHeight * 0.8f), (screenWidth * 1.0f),  (screenHeight * 0.2f)};

    endX = _mapSize.x - 1 + 0.5f;
    endY = _mapSize.y - 1 + 0.5f;
    startX = 0.5f;
    startY = 0.5f;

    _food = LoadModel("images/meat/test/scene.gltf");
    _egg = LoadModel("images/dofus_emeraude/scene.gltf");
    _gem = LoadModel("images/gemStone/scene.gltf");

    _getInfoMenu = false;
    _hit = {0,0};
    _dropDownMenu = {10, 10, (screenWidth * 0.15f), (screenHeight * 0.05f)};


    std::random_device rd;
    _keyGen = rd();
    _gen.seed(_keyGen);

    SetTargetFPS(60);
}

Window::~Window()
{
    _sprite.clear();
    _playerList.clear();
    UnloadTexture(_background);
    UnloadModel(_farmer);
    UnloadModel(_island);
    UnloadModel(_islandMenu);
    UnloadModel(_food);
    UnloadModel(_egg);
    UnloadModel(_gem);
    CloseAudioDevice();
    CloseWindow();
}

void Window::checkSound(BgMusic* _sound)
{
    Vector2 mousePoint = GetMousePosition();

    if (_sprite.find("play")->second.btnAction == false) {
        if (CheckCollisionPointRec(mousePoint, _sprite.find("btnOn")->second.btnBounds)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                _sprite.find("btnOn")->second.btnState = 2;
            else
                _sprite.find("btnOn")->second.btnState = 1;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (_sprite.find("btnOn")->second.btnAction == true) {
                    _sprite.find("btnOn")->second.btnAction = false;
                    _sound->resumeMusic();
                } else {
                    _sprite.find("btnOn")->second.btnAction = true;
                    _sound->pauseMusic();
                }
            }
        } else
            _sprite.find("btnOn")->second.btnState = 0;
        _sprite.find("btnOn")->second.sourceRec.y = (_sprite.find("btnOff")->second.btnState) * (_sprite.find("btnOff")->second._button.height / 3);
        if (CheckCollisionPointRec(mousePoint, _sprite.find("btnOff")->second.btnBounds)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                _sprite.find("btnOff")->second.btnState = 2;
            else
                _sprite.find("btnOff")->second.btnState = 1;
        } else
            _sprite.find("btnOff")->second.btnState = 0;
        _sprite.find("btnOff")->second.sourceRec.y = (_sprite.find("btnOff")->second.btnState) * (_sprite.find("btnOff")->second._button.height / 3);
    }
}

void Window::setCameraGame()
{
    _camera = { 0 };
    _camera.position = (Vector3){ (_mapSize.x/2) - 0.5f, 10, _mapSize.y};
    _camera.target = (Vector3){ _mapSize.x/2 - 0.5f, 1.0f, _mapSize.y/2 };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 55.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
}

void Window::checkBtns(Game *game)
{
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, _sprite.find("play")->second.btnBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            _sprite.find("play")->second.btnState = 2;
        else
            _sprite.find("play")->second.btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            setCameraGame();
            game->PushState(GameState::Playing);
        }
    } else
        _sprite.find("play")->second.btnState = 0;
    _sprite.find("play")->second.sourceRec.y = (_sprite.find("play")->second.btnState) * (_sprite.find("play")->second._button.height / 3);
    if (CheckCollisionPointRec(mousePoint, _sprite.find("exit")->second.btnBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            _sprite.find("exit")->second.btnState = 2;
        else
            _sprite.find("exit")->second.btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            _sprite.find("exit")->second.btnAction = true;
    } else
        _sprite.find("exit")->second.btnState = 0;
    _sprite.find("exit")->second.sourceRec.y = (_sprite.find("exit")->second.btnState) * (_sprite.find("exit")->second._button.height / 3);
    if (CheckCollisionPointRec(mousePoint, _sprite.find("btnHtp")->second.btnBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            _sprite.find("btnHtp")->second.btnState = 2;
        else
            _sprite.find("btnHtp")->second.btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            _sprite.find("btnHtp")->second.btnAction = true;
    } else
        _sprite.find("btnHtp")->second.btnState = 0;
    _sprite.find("btnHtp")->second.sourceRec.y = (_sprite.find("btnHtp")->second.btnState) * (_sprite.find("btnHtp")->second._button.height / 3);
}
