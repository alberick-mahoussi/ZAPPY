/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** playerAI
*/

#include "zappyMap.hpp"

Player::Player(Vector3 pos, Model *farmer, ModelAnimation *modelAnimations, int animCount, int orientation, int level, std::string nameOfTeam , std::string id)
{
    _farmer = farmer;
    _modelAnimations = modelAnimations;
    _animsCount = animCount;
    _playerPosition = pos;
    _animCurrentFrame = 0;
    elapsedTime = 0.0f;
    _currentAnimationIndex = 8;
    _anim = modelAnimations[0];


    _orientation = orientation;
    _team = nameOfTeam;
    _id = id;
    _level = level;
    _died = false;
    _running = false;
}

void Player::updateAnimation(std::uniform_int_distribution<int> dist)
{
    float deltaTime = GetFrameTime();
    elapsedTime += deltaTime;

    if (_running == true) {
        _currentAnimationIndex = 21;
    } else if (_running == false && _previousAnimations == 21)
        _currentAnimationIndex = 8;
    if (elapsedTime >= 15.0f && _running == false) {
        std::random_device rd;
        std::mt19937 gen(rd());
        _currentAnimationIndex = dist(gen);
        elapsedTime = 0.0f;
    }

    if (_died == true)
        _currentAnimationIndex = 0;
    if (_currentAnimationIndex != _previousAnimations) {
        _animCurrentFrame = 0;
    }

    _animCurrentFrame = (_animCurrentFrame + 1) % _modelAnimations[_currentAnimationIndex].frameCount;
    UpdateModelAnimation(*_farmer, _modelAnimations[_currentAnimationIndex], _animCurrentFrame);
    _previousAnimations = _currentAnimationIndex;
}

void Player::playerMovement(PlayerOrientation cardinal, Vector2 mapSize, int freq)
{
    const float moveDuration = 1.0f;
    const float moveSpeed = 1.0f / moveDuration;
    float movement = (freq * GetFrameTime()) / 5;
    const float moveDistance = moveSpeed * movement;

    std::uniform_int_distribution<int> anim(21, 21);

    if (cardinal == PlayerOrientation::East) {
        if (_playerPosition.x + moveDistance > mapSize.x - 0.5f)
            _playerPosition.x = -0.5f;
        if (remainingDistance <= 0.0f) {
            _playerPosition.x += moveDistance;
            remainingDistance -= moveDistance;

            _running = false;
            _playerPosition.x = round(_playerPosition.x + 0.1f);
        } else {
            _playerPosition.x += moveDistance;
            remainingDistance -= moveDistance;
        }
    } else if (cardinal == PlayerOrientation::West) {
        if (_playerPosition.x - moveDistance < -0.5f)
            _playerPosition.x = mapSize.x - 0.5f;
        if (remainingDistance <= 0.0f) {
            _playerPosition.x -= moveDistance;
            remainingDistance -= moveDistance;

            _running = false;
            _playerPosition.x = round(_playerPosition.x - 0.1f);
        } else {
            _playerPosition.x -= moveDistance;
            remainingDistance -= moveDistance;
        }
    } else if (cardinal == PlayerOrientation::North) {
        if (_playerPosition.z - moveDistance < -0.5f)
            _playerPosition.z = mapSize.y - 0.5f;
        if (remainingDistance <= 0.0f) {
            _playerPosition.z -= moveDistance;
            remainingDistance -= moveDistance;

            _running = false;
            _playerPosition.z = round(_playerPosition.z - 0.1f);
        } else {
            _playerPosition.z -= moveDistance;
            remainingDistance -= moveDistance;
        }
    } else if (cardinal == PlayerOrientation::South) {
        if (_playerPosition.z + moveDistance > mapSize.y - 0.5f)
            _playerPosition.z = - 0.5f;
        if (remainingDistance <= 0.0f) {
            _playerPosition.z += moveDistance;
            remainingDistance -= moveDistance;

            _running = false;
            _playerPosition.z = round(_playerPosition.z + 0.1f);
        } else {
            _playerPosition.z += moveDistance;
            remainingDistance -= moveDistance;
        }
    }
    updateAnimation(anim);
}

Player::~Player()
{
}