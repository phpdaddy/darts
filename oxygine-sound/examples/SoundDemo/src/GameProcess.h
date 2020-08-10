#pragma once
#include "oxygine-framework.h"
#include <functional>   

class Player {
public:
	string username;
};

class Throw {
public:
	int _score;
	Player *player;
};

class Turn {
public:
	std::vector<Throw*> _playerThrows;
	std::vector<Throw*> _aiThrows;
};

class Leg {
public:
	std::vector<Turn*> _turns;
	bool _finished;
	Turn* getCurrentTurn() {
		return _turns[_currentTurn];
	}
	Player* getWinner() {};
	Leg() {
		_currentTurn = 0;
	}

	// возвращает сумму очков игрока на данном этапе
	int getScoreRealPlayer() {
		int score = 0;
		for each (Turn* turn in _turns)
		{
			for each (Throw* _throw in turn->_playerThrows)
			{
				score+= _throw->_score;
			}
		}
		return score;
	}


	// возвращает сумму очков AI на данном этапе
	int getScoreAIPlayer() {
		int score = 0;
		for each (Turn* turn in _turns)
		{
			for each (Throw* turn in turn->_aiThrows)
			{
				score += turn->_score;
			}
		}
		return score;
	}

	// добавить новый ход в очередь ходов
	void nextTurn() {
		_currentTurn++;
		Turn *turn = new Turn();
		_turns.push_back(turn);
	}

private:
	int _currentTurn;
};

class Set {
public:
	std::vector<Leg*> legs;
	bool finished;
	Leg* getCurrentLeg() {
		return legs[currentLeg];
	}
	Player *getWinner() {};
	Set() {
		currentLeg = 0;
	}
private:
	int currentLeg;
};
