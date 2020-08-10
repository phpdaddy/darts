#pragma once 
#include "oxygine-framework.h"
#include <functional> 
#include "Globals.h"

using namespace oxygine;
class Game;
class Scoretable : public Actor {

public:
	Scoretable();
	void doUpdate(const UpdateState & us);
	void addPlayerScore(int score, int scoreLeft);
	void addAIScore(int score, int scoreLeft);
	void init(Game *game);
	void switchTurn(GameTurn turn);
private:
	spSprite _scoreTable;
	Game * _game;
	TextStyle _fontStyle;
	std::vector<spTextField> _scoresRealPlayer;
	std::vector<spTextField> _scoresLeftRealPlayer;
	std::vector<spTextField> _scoresAIPlayer;
	std::vector<spTextField> _scoresLeftAIPlayer;
	spTextField _textPlayerName;
	spTextField _textAIName;
};

typedef oxygine::intrusive_ptr<Scoretable> spScoretable;