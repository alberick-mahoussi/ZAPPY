/*
** EPITECH PROJECT, 2022
** Button.cpp
** File description:
** Button.cpp
*/

#include "zappyMap.hpp"

Button::Button(const char *fileName, int posx, int posy, float width,
float height, int winSizeX, int winSizeY)
{
    Image img = LoadImage(fileName);
    ImageResize(&img, width, height);
    this->_button = LoadTextureFromImage(img);
    this->sourceRec = {0, 0, width, height / 3};
    this->btnAction = false;
    this->btnBounds = {(float)posx - (_button.width / 2.0f) , (float)posy - (_button.height / 2.0f), (float)_button.width, (float)_button.height / 3};
}
