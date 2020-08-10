#include "oxygine-framework.h"
#include <functional>
#include "Globals.h"
#include "Menu.h"
#include "Game.h"

using namespace oxygine;

GameState   gameState;
Resources gameResources;
SoundPlayer sfxPlayer;
SoundPlayer musicPlayer;


class MainActor : public Actor
{
	spGame game = new Game();
	spMenu menu = new Menu();
public:

	MainActor()
	{

		menu->_buttonPlay->addClickListener(CLOSURE(this, &MainActor::buttonPlayClicked));
		menu->_buttonExit->addClickListener(CLOSURE(this, &MainActor::buttonExitClicked));
		menu->_buttonResume->addClickListener(CLOSURE(this, &MainActor::buttonResumeClicked));
		menu->_buttonTryAgain->addClickListener(CLOSURE(this, &MainActor::buttonTryAgainClicked));

		game->init();

		addChild(game);
		addChild(menu);
		gameState = GameState::GAME;

		game->setPriority(0);
		menu->setPriority(1);

		musicPlayer.play(gameResources.get("casinomusic"));
		musicPlayer.setVolume(0.15f);
	}


	void MainActor::buttonPlayClicked(Event* event)
	{
		menu->_textPlay->setScale(1.0f);
		spTweenQueue tweenQueue = new TweenQueue();
		tweenQueue->add(Actor::TweenScale(1.1f), 150, 1, false);
		menu->_textPlay->addTween(tweenQueue);
		tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &MainActor::buttonPlayTweenQueueEnd));

		menu->_menuBackground->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonPlay->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonExit->addTween(Sprite::TweenAlpha(0), 500, 1, false);

		sfxPlayer.play(gameResources.get("buttonclicksound"));
		sfxPlayer.setVolume(0.3f);


		log::messageln("play");
	}

	void MainActor::buttonPlayTweenQueueEnd(Event* event) {
		menu->setVisible(false);
		gameState = GameState::GAME;
	}

	void MainActor::buttonExitClicked(Event* event)
	{
		menu->_textExit->setScale(1.0f);
		spTweenQueue tweenQueue = new TweenQueue();
		tweenQueue->add(Actor::TweenScale(1.1f), 150, 1, false);
		menu->_textExit->addTween(tweenQueue);
		tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &MainActor::buttonExitTweenQueueEnd));


		menu->_buttonPlay->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonResume->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonExit->addTween(Sprite::TweenAlpha(0), 500, 1, false);

		sfxPlayer.play(gameResources.get("buttonclicksound"));
		sfxPlayer.setVolume(0.3f);


		log::messageln("play");
	}


	void MainActor::buttonResumeClicked(Event* event)
	{
		menu->_textResume->setScale(1.0f);
		spTweenQueue tweenQueue = new TweenQueue();
		tweenQueue->add(Actor::TweenScale(1.1f), 150, 1, false);
		menu->_textResume->addTween(tweenQueue);
		tweenQueue->addEventListener(TweenQueue::EVENT_LOOP_END, CLOSURE(this, &MainActor::buttonPlayTweenQueueEnd));

		menu->_menuBackground->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonResume->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonExit->addTween(Sprite::TweenAlpha(0), 500, 1, false);

		sfxPlayer.play(gameResources.get("buttonclicksound"));
		sfxPlayer.setVolume(0.3f);

		log::messageln("resume");
	}


	void MainActor::buttonExitTweenQueueEnd(Event*)
	{
		core::requestQuit();
	}


	void MainActor::buttonTryAgainClicked(Event*)
	{
		removeChild(game);
		game = new Game();
		game->init();
		game->setPriority(0);
		addChild(game);

		menu->_menuBackground->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonTryAgain->addTween(Sprite::TweenAlpha(0), 500, 1, false);
		menu->_buttonExit->addTween(Sprite::TweenAlpha(0), 500, 1, false); 

		menu->_textTryAgain->setScale(1.0f);
		spTweenQueue tweenQueue = new TweenQueue();
		tweenQueue->add(Actor::TweenScale(1.1f), 150, 1, false);
		menu->_textTryAgain->addTween(tweenQueue);
		
		sfxPlayer.play(gameResources.get("buttonclicksound"));
		sfxPlayer.setVolume(0.3f);

		gameState = GameState::GAME;
	}


	void doUpdate(const UpdateState &us)
	{
		if (gameState == GameState::GAME) {
			const Uint8* kb = SDL_GetKeyboardState(0);

			if (game->_sets[0]->getCurrentLeg()->getWinner() == GameTurn::AI_TURN ||
				game->_sets[0]->getCurrentLeg()->getWinner() == GameTurn::PLAYER_TURN) {
				log::messageln("gamestate legwin");


				menu->setVisible(true);

				menu->_buttonTryAgain->setAlpha(0);
				menu->_buttonTryAgain->addTween(Sprite::TweenAlpha(255), 500, 1, false);

				menu->_buttonExit->setAlpha(0);
				menu->_buttonExit->addTween(Sprite::TweenAlpha(255), 500, 1, false);

				menu->_menuBackground->addTween(Sprite::TweenAlpha(255), 500, 1, false);
				menu->_buttonPlay->setVisible(false);
				menu->_buttonResume->setVisible(false);
				menu->_buttonTryAgain->setVisible(true);

				menu->_textWinner->setVisible(true);
				string winner = (game->_sets[0]->getCurrentLeg()->getWinner() == GameTurn::AI_TURN) ? game->_aiPlayer->username : game->_realPlayer->username;
				winner += " wins!";
				menu->_textWinner->setText(winner);

				gameState = GameState::MAIN_MENU;

			}
			if (kb[SDL_SCANCODE_ESCAPE]) {
				log::messageln("gamestate game");


				menu->setVisible(true);
				menu->_textWinner->setVisible(false);

				menu->_buttonResume->setAlpha(0);
				menu->_buttonResume->addTween(Sprite::TweenAlpha(255), 500, 1, false);

				menu->_buttonExit->setAlpha(0);
				menu->_buttonExit->addTween(Sprite::TweenAlpha(255), 500, 1, false);

				menu->_menuBackground->addTween(Sprite::TweenAlpha(255), 500, 1, false);
				menu->_buttonPlay->setVisible(false);
				menu->_buttonResume->setVisible(true);

				gameState = GameState::MAIN_MENU;
			}
		}
	}


};




//declare spMainActor as intrusive_ptr holder of MainActor
typedef oxygine::intrusive_ptr<MainActor> spMainActor;
//you could use DECLARE_SMART preprocessor definition it does the same:
//DECLARE_SMART(MainActor, spMainActor)

void app_preinit() {}

//called from main.cpp
void app_init()
{
	//initialize our sound system with 16 channels

	SoundSystem::create()->init(16);

	//initialize SoundPlayer
	SoundPlayer::initialize();
	//sfxPlayer.setResources(&gameResources);

	//load xml file with resources definition
	gameResources.loadXML("res.xml");


	//lets create our client code simple actor
	//spMainActor was defined above as smart intrusive pointer
	spMainActor actor = new MainActor;

	//and add it to Stage as child
	getStage()->addChild(actor);
}


//called each frame from main.cpp
void app_update()
{
	SoundSystem::instance->update();
	//sfxPlayer.update();
}

//called each frame from main.cpp
void app_destroy()
{
	//free previously loaded resources
	gameResources.free();
}