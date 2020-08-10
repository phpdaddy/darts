#include "Game.h"
#include <windows.h>

Game::Game() {
	Dartboard::init();
	spSprite background = new Sprite();
	spSprite dartboard = new Sprite();

	background->setResAnim(gameResources.getResAnim("background"));
	dartboard->setResAnim(gameResources.getResAnim("dartboard"));

	Vector2 posDartboard = getStage()->getSize() / 2 - dartboard->getSize() / 2;
	posDartboard.x = 60;
	dartboard->setPosition(posDartboard);

	Vector2 posBackground = getStage()->getSize() / 2 - background->getSize() / 2;
	background->setPosition(posBackground);

	addChild(background);
	_background = background;

	addChild(dartboard);
	_dartboard = dartboard;

	addEventListener(TouchEvent::CLICK, CLOSURE(this, &Game::screenClick));
	addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Game::screenTouchDown));


	spScoretable scoreTable = new Scoretable();
	_scoreTable = scoreTable;
	_scoreTable->setPriority(1);
	addChild(_scoreTable);

	spSlider slider = new Slider();
	_slider = slider;
	_slider->setPriority(1);
	addChild(_slider);

	spTarget target = new Target();
	_target = target;

	addChild(_target);

	Set *set = new Set();
	_sets.push_back(set);

	Leg *leg = new Leg();
	set->legs.push_back(leg);

	Turn *turn = new Turn();
	leg->_turns.push_back(turn);

	_realPlayer = new RealPlayer();
	_realPlayer->username = "Player";

	_aiPlayer = new AI();
	_aiPlayer->username = "AI"; 

	_aiStartShoot = false;

	srand(time(NULL));

	// for fast testing
	/*Throw* pThrow = new Throw();
	pThrow->player = _aiPlayer;
	pThrow->_score = 280;
	_sets[0]->getCurrentLeg()->getCurrentTurn()->_aiThrows.push_back(pThrow);


	pThrow = new Throw();
	pThrow->player = _aiPlayer;
	pThrow->_score = 280;
	_sets[0]->getCurrentLeg()->getCurrentTurn()->_playerThrows.push_back(pThrow);*/
}
void Game::init() {
	_target->init(this);
	_scoreTable->init(this);

	_turn = GameTurn::PLAYER_TURN;
	cleanBoard();
}

void Game::screenTouchDown(Event* ev) {
	if (_target->_aim->getVisible() && _turn == GameTurn::PLAYER_TURN && !_cleanboard) {
		_target->startForceSelection();
		log::messageln("screenTouchDown");
	}
}

void Game::cleanBoard()
{
	_cleanboard = true;
	if (_darts.size() == 0) {
		_scoreTable->switchTurn(_turn);
		_cleanboard = false;
		return;
	}
	spTweenQueue tweenQueue = new TweenQueue();
	tweenQueue->setDelay(300);
	tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &Game::dartDisappear));
	_darts[0]->addTween(tweenQueue);
}


void Game::dartDisappear(Event* ev) {
	removeChild(_darts[0]);
	_darts.erase(_darts.begin());
	sfxPlayer.play(gameResources.get("dartspullout"));
	sfxPlayer.setVolume(0.8f);
	cleanBoard();
}

void Game::screenClick(Event* ev) {
	if (_target->_aim->getVisible() && _turn == GameTurn::PLAYER_TURN && !_cleanboard) {
		log::messageln("SHOOT %f", _target->getThrowCoord().y);
		Sprite *dart = new Sprite();
		dart->setResAnim(gameResources.getResAnim("dart"));
		Vector2 posDart = _target->getThrowCoord();
		dart->setPosition(posDart);
		dart->setAnchorX(0.5);
		dart->setAnchorY(0.5);
		spTweenQueue tweenQueue = new TweenQueue();
		Vector2 destScale = Vector2(0.4, 0.4);

		tweenQueue->add(Sprite::TweenScale(destScale), 100, 1);

		dart->addTween(tweenQueue);

		tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &Game::shootTweenQueueEnd));

		addChild(dart);
		_darts.push_back(dart);

		Vector2 dartboardCenter = Vector2(getStage()->getSize() / 2);
		dartboardCenter.x = _dartboard->getPosition().x + _dartboard->getSize().x / 2;
		int score = Dartboard::calcScore(posDart, dartboardCenter);

		_target->stopForceSelection();

		if (_sets[0]->getCurrentLeg()->getCurrentTurn()->_playerThrows.size() < 3) {

			Throw* pThrow = new Throw();
			pThrow->player = _realPlayer;
			pThrow->_score = score;
			_sets[0]->getCurrentLeg()->getCurrentTurn()->_playerThrows.push_back(pThrow);

			int scoreLeft = 301 - _sets[0]->getCurrentLeg()->getScoreRealPlayer();
			if (scoreLeft > 0) {
				_scoreTable->addPlayerScore(score, scoreLeft);
			}
			 
			if (scoreLeft < 0) {
				_sets[0]->getCurrentLeg()->getCurrentTurn()->_playerThrows.erase(_sets[0]->getCurrentLeg()->getCurrentTurn()->_playerThrows.begin()
					+ _sets[0]->getCurrentLeg()->getCurrentTurn()->_playerThrows.size() - 1);
				_turn = GameTurn::AI_TURN;
				cleanBoard();
				_aiStartShoot = true; 
				return;
			}
			if (scoreLeft == 0)
			{
				log::messageln("WIN");
			}
		}
		if ((_sets[0]->getCurrentLeg()->getCurrentTurn()->_playerThrows.size() > 2)) {
			_turn = GameTurn::AI_TURN;
			cleanBoard();
			_aiStartShoot = true;
		}
	}
}

void Game::shootTweenQueueEnd(Event*)
{
	sfxPlayer.play(gameResources.get("dartsound1"));
	sfxPlayer.setVolume(1);


	log::messageln("Got it");
}

void Game::doUpdate(const UpdateState & us)
{
	if (_aiStartShoot && _turn == GameTurn::AI_TURN) {
		_aiStartShoot = false;

		spTweenQueue tweenQueue = new TweenQueue();
		tweenQueue->setDelay(2000);
		tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &Game::_aiStartShootTween));
		addTween(tweenQueue);
	}
}

void Game::_aiStartShootTween(Event*) {

	log::messageln("SHOOT %f", _target->getThrowCoord().y);
	Sprite *dart = new Sprite();
	dart->setResAnim(gameResources.getResAnim("dart"));
	Vector2 posDart = _target->getRandomCoord();
	dart->setPosition(posDart);
	dart->setAnchorX(0.5);
	dart->setAnchorY(0.5);

	spTweenQueue tweenQueue = new TweenQueue();
	Vector2 destScale = Vector2(0.4, 0.4);

	tweenQueue->add(Sprite::TweenScale(destScale), 100, 1);
	dart->addTween(tweenQueue);


	tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &Game::shootAITweenQueueEnd));


	addChild(dart);
	_darts.push_back(dart);

	Vector2 dartboardCenter = Vector2(getStage()->getSize() / 2);
	dartboardCenter.x = _dartboard->getPosition().x + _dartboard->getSize().x / 2;
	int score = Dartboard::calcScore(posDart, dartboardCenter);

	if (_sets[0]->getCurrentLeg()->getCurrentTurn()->_aiThrows.size() < 3) {

		Throw* pThrow = new Throw();
		pThrow->player = _aiPlayer;
		pThrow->_score = score;
		_sets[0]->getCurrentLeg()->getCurrentTurn()->_aiThrows.push_back(pThrow);
		int scoreLeft = 301 - _sets[0]->getCurrentLeg()->getScoreAIPlayer();

		if (scoreLeft > 0) {
			_scoreTable->addAIScore(score, scoreLeft);
		}
	}
}

void Game::shootAITweenQueueEnd(Event*)
{
	sfxPlayer.play(gameResources.get("dartsound1"));
	sfxPlayer.setVolume(0.8f);

	log::messageln("Got it");

	int scoreLeft = 301 - _sets[0]->getCurrentLeg()->getScoreAIPlayer();
	if (scoreLeft < 0) {
		_sets[0]->getCurrentLeg()->getCurrentTurn()->_aiThrows.erase(_sets[0]->getCurrentLeg()->getCurrentTurn()->_aiThrows.begin()
			+ _sets[0]->getCurrentLeg()->getCurrentTurn()->_aiThrows.size() - 1);
		_turn = GameTurn::PLAYER_TURN;
		cleanBoard();
		_sets[0]->getCurrentLeg()->nextTurn();
		return;
	}
	if (scoreLeft == 0)
	{
		log::messageln("WIN");
	}


	if ((_sets[0]->getCurrentLeg()->getCurrentTurn()->_aiThrows.size() > 2)) {

		_turn = GameTurn::PLAYER_TURN;
		cleanBoard();
		_sets[0]->getCurrentLeg()->nextTurn();
		return;
	}

	spTweenQueue tweenQueue = new TweenQueue();
	tweenQueue->setDelay(2000);
	tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &Game::_aiStartShootTween));
	addTween(tweenQueue);
}

Game::~Game() {
}
