#pragma once
#include "oxygine-framework.h"
#include <functional>

using namespace oxygine;

class Menu : public Actor
{
public:
	spSprite _menuBackground;
	spSprite _background;
	spSprite _dartboard;
	spSprite  _buttonPlay;
	spTextField _textPlay;
	spSprite _buttonExit;
	spTextField _textExit;
	spSprite  _buttonResume;
	spTextField _textResume;
    spSprite _buttonTryAgain;
	spTextField _textTryAgain;
    spTextField _textWinner;
	Menu();
	~Menu();
private:
};
typedef oxygine::intrusive_ptr<Menu> spMenu;