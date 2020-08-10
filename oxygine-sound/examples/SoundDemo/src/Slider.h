#pragma once 
#include "oxygine-framework.h"
#include <functional> 

using namespace oxygine;

class Slider : public Actor {

public:
	Slider();
	void doUpdate(const UpdateState & us);
	void setValue(int percent);
	void setColor(const Color &color);
private:
	spSprite _sliderContainer;
	spSprite _sliderTop;
	spSprite _sliderMid;
	spSprite _sliderBot;
	int _percent;
	Vector2 _sliderPos;
	float _spinnerPos;
};

typedef oxygine::intrusive_ptr<Slider> spSlider;