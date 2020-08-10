#include "Menu.h"
#include "Globals.h"

Menu::Menu() {
	spSprite menuBackground = new Sprite();  
	//spSprite background = new Sprite();
	//spSprite dartboard = new Sprite();
	spSprite buttonPlay = new Sprite();
	spSprite buttonExit = new Sprite();
	spSprite buttonResume = new Sprite(); 
	spTextField textPlay = new TextField();
	spTextField textExit = new TextField();
	spTextField textResume = new TextField();

	menuBackground->setResAnim(gameResources.getResAnim("menuBackground"));
	//background->setResAnim(gameResources.getResAnim("background"));
	//dartboard->setResAnim(gameResources.getResAnim("dartboard"));


	buttonPlay->setResAnim(gameResources.getResAnim("button_transparent"));
	buttonExit->setResAnim(gameResources.getResAnim("button_transparent"));
	buttonResume->setResAnim(gameResources.getResAnim("button_transparent"));


	Vector2 posButtonPlay = Vector2(482, 270);
	buttonPlay->setPosition(posButtonPlay);

	Vector2 posButtonExit = Vector2(478, 360);
	buttonExit->setPosition(posButtonExit);

	Vector2 posButtonResume = Vector2(480, 270);
	buttonResume->setPosition(posButtonResume);


	TextStyle style;
	style.font = gameResources.getResFont("imprint_mt_62")->getFont();
	style.color = Color::White;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;

	textPlay->setPosition(buttonPlay->getSize() / 2.1);
	textPlay->attachTo(buttonPlay);
	textPlay->setStyle(style);
	textPlay->setText("PLAY");
	_textPlay = textPlay;

	textExit->setPosition(buttonExit->getSize() / 2);
	textExit->attachTo(buttonExit);
	textExit->setStyle(style);
	textExit->setText("EXIT");
	_textExit = textExit;

	textResume->setPosition(buttonResume->getSize() / 2.1);
	textResume->attachTo(buttonResume);
	textResume->setStyle(style);
	textResume->setText("RESUME");
	_textResume = textResume;

	Vector2 posMenuBackground = getStage()->getSize() / 2 - menuBackground->getSize() / 2;
	menuBackground->setPosition(posMenuBackground);

	addChild(menuBackground);
	_menuBackground = menuBackground;

	_buttonPlay = buttonPlay;
	_buttonExit = buttonExit;
	_buttonResume = buttonResume; 

	addChild(_buttonPlay);

	addChild(_buttonExit);

	addChild(_buttonResume);

	_buttonResume->setVisible(false);

	_menuBackground->setPriority(1);
	_buttonPlay->setPriority(1);
	_buttonExit->setPriority(1);
	_buttonResume->setPriority(1);
}
 

Menu::~Menu() {

} 
