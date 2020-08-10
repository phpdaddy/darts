#pragma once
#include "oxygine-framework.h"
#include <functional>
#include "Globals.h"
#include "Range.h"
#include "Dartboard.h"
#include "Target.h"
#include "Slider.h"
#include "Scoretable.h"
#include "GameProcess.h"
#include "AI.h"
using namespace oxygine;

class Game : public Actor
{
public:
	spSprite _background;
	spSprite _dartboard;
	spScoretable _scoreTable;
	Vector2 _force;
	std::vector<spSprite> _darts; 
	spTarget _target;
	spSlider _slider;
	std::vector<Set *> _sets;
	RealPlayer *_realPlayer;
	AI *_aiPlayer;

	Game();
	void init();
	void screenClick(Event* ev);  
	void shootTweenQueueEnd(Event*);
	void doUpdate(const UpdateState & us);
	void _aiStartShootTween(Event *);
	void shootAITweenQueueEnd(Event *);
	~Game();
private:
	bool _cleanboard;
	bool _aiStartShoot;
	GameTurn _turn;
	int _dartDisappearIndex;
	void screenTouchDown(Event* ev);
	void cleanBoard( );
	void dartDisappear(Event* ev);
};
typedef oxygine::intrusive_ptr<Game> spGame;