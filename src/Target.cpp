#include "Globals.h"
#include "Target.h"
#include "Game.h"

Target::Target() {
	_counter = 0;
	_targetOffsetSpread = 30;
	_offsetX = 0;
	_offsetY = 0;
	_realOffsetX = 0;
	_realOffsetY = 0;

	spSprite aim = new Sprite();

	Vector2 posAim = getStage()->getSize() / 2 - aim->getSize() / 2;
	aim->setPosition(posAim);

	aim->setResAnim(gameResources.getResAnim("aim"));
	_aim = aim;
	_aimPosition = posAim;
	addChild(_aim);

	_forceIncrement = 8;
	_forceSelection = false;

	_counterSlider = 0;
	_delaySliderFall = false;

	_forcefallSpeed = 2;

	_startForceY = -100;
	_forceRange = 200;

	_force.y = 100;
}
void Target::init(Game *game) {
	_game = game;

}
void Target::doUpdate(const UpdateState &us) {
	_counter++;
	float speed = 800.0f * (us.dt / 1000.0f);
	int x = 0, y = 0;
	const Uint32 ms = SDL_GetMouseState(&x, &y);

	if (_counter >= 10) {
		_offsetX = rand() % _targetOffsetSpread - _targetOffsetSpread / 2;
		_offsetY = rand() % _targetOffsetSpread - _targetOffsetSpread / 2;
		_counter = 0; 
	}
	float floatingSpeed = 0.4f;
	_realOffsetX += (_realOffsetX > _offsetX) ? -floatingSpeed : floatingSpeed;
	_realOffsetY += (_realOffsetY > _offsetY) ? -floatingSpeed : floatingSpeed;

	_aimPosition.x = x - _aim->getSize().x / 2 + _realOffsetX;
	_aimPosition.y = y - _aim->getSize().y / 2 + _realOffsetY;


	if (_aimPosition.x > getStage()->getSize().x / 8 * 5) {
		_aimPosition.x = getStage()->getSize().x / 8 * 5;
	}
	if (x - _aim->getSize().x / 2 > getStage()->getSize().x / 8 * 5) {
		_aim->setVisible(false);
	}
	else {
		_aim->setVisible(true);
	}

	_aim->setPosition(_aimPosition);

	if (_forceSelection) {
		_force.y -= _forceIncrement;
	}
	else {
		if (_delaySliderFall && _counterSlider < 15) {
			_counterSlider++;
		}
		else if (_delaySliderFall) {
			_delaySliderFall = false;
			_counterSlider = 0;
		}
		if (!_delaySliderFall) {
			_force.y += _forcefallSpeed;

		}
	}

	if (_force.y < _startForceY) {
		_forceIncrement = -abs(_forceIncrement);
		_force.y = _startForceY;
	}
	if (_force.y > _startForceY + _forceRange) {
		_forceIncrement = abs(_forceIncrement);
		_force.y = _startForceY + _forceRange;
	}

	spSlider slider = _game->_slider;

	int value = -_force.y / _forceRange * 100 + 50;
	slider->setValue(value);

	if (value <= 40 && value >= 0)
	{
		slider->setColor(Color::Orange);
	}
	else if (value <= 80 && value > 40)
	{
		slider->setColor(Color::Lime);
	}
	else {
		slider->setColor(Color::OrangeRed);
	}

	slider->setAlpha(value * 2);

	//log::messageln("offset %d  %d", _offsetX,_offsetY);
	//log::messageln("offset %d  %d", _offsetX, _offsetY);

}
Vector2 Target::getThrowCoord() {
	return _aimPosition + _aim->getSize() / 2 + _force;
}

Vector2 Target::getRandomCoord() {
	Vector2 origin = Vector2(_game->_dartboard->getPosition().x+ _game->_dartboard->getSize().x / 2, _game->_dartboard->getPosition().y + _game->_dartboard->getSize().y / 2);
	Vector2 rp = getRandomPointFromCircle(_game->_dartboard->getSize().x/2.5f, origin.x,origin.y);
	return rp;
}


Vector2 Target::getRandomPointFromCircle(float _radius, float orginnX, float originY)
{
	float nextFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float angle = nextFloat * M_PI * 2;
	nextFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float radius = nextFloat * _radius;
	float x = orginnX + radius * cos(angle);
	float y = originY + radius * sin(angle);
	return Vector2(x, y);
}
void Target::startForceSelection()
{
	_forceSelection = true;
	_force.y = _startForceY + _forceRange;
}

void Target::stopForceSelection()
{
	_forceSelection = false;
	_delaySliderFall = true;
}
