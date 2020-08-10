#pragma once
#include "oxygine-framework.h"
#include <functional>
#include "SoundPlayer.h"
#include "SoundSystem.h"
#include "SoundInstance.h"

using namespace oxygine;

enum GameState {
	MAIN_MENU,
	GAME
};


enum GameTurn {
	PLAYER_TURN,
	AI_TURN
};

extern GameState gameState;
extern Resources gameResources;
extern SoundPlayer sfxPlayer;
extern SoundPlayer musicPlayer;


