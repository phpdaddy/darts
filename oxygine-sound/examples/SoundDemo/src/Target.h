#pragma once 
#include "oxygine-framework.h"
#include <functional>  

using namespace oxygine;
class Game;
class Target : public Actor {

public:
	Target();
	void init(Game* game);
	void doUpdate(const UpdateState & us);
	Vector2 getThrowCoord();
	Vector2 getRandomCoord();
	Vector2 getRandomPointFromCircle(float _radius, float orginnX, float originY);
	void startForceSelection();
	void stopForceSelection();
	spSprite _aim;
private:
	int _counter;
	int _targetOffsetSpread;
	int _offsetX;
	int _offsetY;
	float _realOffsetX;
	float _realOffsetY;
	Vector2 _aimPosition;
	Vector2 _force;
	bool _forceSelection;
	float _forceIncrement;
	Game * _game;
	bool _delaySliderFall;
	int _counterSlider;
	float _forcefallSpeed;
	float _startForceY;
	float _forceRange;
};

typedef oxygine::intrusive_ptr<Target> spTarget;