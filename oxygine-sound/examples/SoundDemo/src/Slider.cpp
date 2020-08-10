#include "Globals.h"
#include "Slider.h"

Slider::Slider()
{
	spSprite sliderContainer = new Sprite();
	spSprite sliderTop = new Sprite();
	spSprite sliderMid = new Sprite();
	spSprite sliderBot = new Sprite();
	sliderContainer->setResAnim(gameResources.getResAnim("slider_container"));
	sliderTop->setResAnim(gameResources.getResAnim("slider_top"));
	sliderMid->setResAnim(gameResources.getResAnim("slider_mid"));
	sliderBot->setResAnim(gameResources.getResAnim("slider_bot"));

	Vector2 sliderPos = Vector2(getStage()->getSize().x / 23, getStage()->getSize().y / 4 * 3) - sliderContainer->getSize() / 2;
	_sliderPos = sliderPos;

	_spinnerPos = 160;

	sliderContainer->setPosition(_sliderPos);
	_sliderContainer = sliderContainer;
	addChild(_sliderContainer);

	sliderTop->setPosition(Vector2(_sliderPos.x, _sliderPos.y + _spinnerPos));
	_sliderTop = sliderTop;
	addChild(_sliderTop);

	sliderMid->setPosition(Vector2(_sliderPos.x, _sliderPos.y + _spinnerPos + 15));
	_sliderMid = sliderMid;
	addChild(_sliderMid);

	sliderBot->setPosition(Vector2(_sliderPos.x, _sliderPos.y + _spinnerPos + 30));
	_sliderBot = sliderBot;
	addChild(_sliderBot);

	_percent = 0;
}

void Slider::doUpdate(const UpdateState & us)
{

	_sliderBot->setPosition(Vector2(_sliderPos.x, _sliderPos.y + _spinnerPos + 40));


	_sliderMid->setScaleY(-_percent / 12.f);
	_sliderMid->setPosition(Vector2(_sliderPos.x, _sliderPos.y + _spinnerPos + 40));

	_sliderTop->setPosition(Vector2(_sliderPos.x, _sliderPos.y + _spinnerPos + 23.89f - _percent / 100.f * 183));
}

void Slider::setValue(int percent)
{
	_percent = percent;
}

void Slider::setColor(const Color & color)
{
	_sliderBot->setColor(color);
	_sliderTop->setColor(color);
	_sliderMid->setColor(color);
	_sliderContainer->setColor(color);
}
