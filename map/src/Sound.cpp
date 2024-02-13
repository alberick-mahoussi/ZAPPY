/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Sound
*/

#include "zappyMap.hpp"

BgMusic::BgMusic()
{
    _music = LoadMusicStream("images/main_menu/music.mp3");
    PlayMusicStream(_music);
}

void BgMusic::updateMusic()
{
    UpdateMusicStream(_music);
}

void BgMusic::pauseMusic()
{
    PauseMusicStream(_music);
}

void BgMusic::resumeMusic()
{
    ResumeMusicStream(_music);
}

BgMusic::~BgMusic()
{
    UnloadMusicStream(_music);
}