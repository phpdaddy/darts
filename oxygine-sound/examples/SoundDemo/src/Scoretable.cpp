#include "Scoretable.h"
#include "Game.h"
#include "Globals.h"

Scoretable::Scoretable()
{
	spSprite scoreTable = new Sprite();
	scoreTable->setResAnim(gameResources.getResAnim("scoreTable"));
	Vector2 posScoreTable = Vector2(680, 25);
	scoreTable->setPosition(posScoreTable);

	addChild(scoreTable);
	_scoreTable = scoreTable;


	TextStyle fontStyle;
	fontStyle.font = gameResources.getResFont("imprint_mt_32")->getFont();
	fontStyle.color = Color::White;
	fontStyle.vAlign = TextStyle::VALIGN_MIDDLE;
	fontStyle.hAlign = TextStyle::HALIGN_CENTER;
	_fontStyle = fontStyle;

}

void Scoretable::doUpdate(const UpdateState & us)
{
}

void Scoretable::addPlayerScore(int score, int scoreLeft)
{
	if (_scoresRealPlayer.size() > 6) {
		for each (spTextField scoreText in _scoresRealPlayer)
		{
			scoreText->detach();
		}
		_scoresRealPlayer.clear();
		for each (spTextField scoreLeftText in _scoresLeftRealPlayer)
		{
			scoreLeftText->detach();
		}
		_scoresLeftRealPlayer.clear();
	}


	int row = _scoresRealPlayer.size();

	spTextField textScore = new TextField();
	textScore->setStyle(_fontStyle);
	textScore->attachTo(_scoreTable);
	textScore->setText(std::to_string(score));
	textScore->setPosition(Vector2(110, 111 + row * 45));
	_scoresRealPlayer.push_back(textScore);

	spTextField textScoreLeft = new TextField();
	textScoreLeft->setStyle(_fontStyle);
	textScoreLeft->attachTo(_scoreTable);
	textScoreLeft->setText(std::to_string(scoreLeft));
	textScoreLeft->setPosition(Vector2(62, 111 + row * 45));
	_scoresLeftRealPlayer.push_back(textScoreLeft);
}

void Scoretable::addAIScore(int score, int scoreLeft)
{
	if (_scoresAIPlayer.size() > 6) {
		for each (spTextField scoreText in _scoresAIPlayer)
		{
			scoreText->detach();
		}
		_scoresAIPlayer.clear();
		for each (spTextField scoreLeftText in _scoresLeftAIPlayer)
		{
			scoreLeftText->detach();
		}
		_scoresLeftAIPlayer.clear();
	}

	int row = _scoresAIPlayer.size();

	spTextField textScore = new TextField();
	textScore->setStyle(_fontStyle);
	textScore->attachTo(_scoreTable);
	textScore->setText(std::to_string(score));
	textScore->setPosition(Vector2(200, 111 + row * 45));
	_scoresAIPlayer.push_back(textScore);

	spTextField textScoreLeft = new TextField();
	textScoreLeft->setStyle(_fontStyle);
	textScoreLeft->attachTo(_scoreTable);
	textScoreLeft->setText(std::to_string(scoreLeft));
	textScoreLeft->setPosition(Vector2(255, 111 + row * 45));
	_scoresLeftAIPlayer.push_back(textScoreLeft);

}

void Scoretable::init(Game * game)
{
	_game = game;

	spTextField textPlayerName = new TextField();
	textPlayerName->setStyle(_fontStyle);
	textPlayerName->attachTo(_scoreTable);
	textPlayerName->setText(_game->_realPlayer->username);
	textPlayerName->setPosition(Vector2(87, 13));
	textPlayerName->setAlign(TextStyle::VALIGN_DEFAULT, TextStyle::HALIGN_MIDDLE);
	_textPlayerName = textPlayerName;

	spTextField textAIName = new TextField();
	textAIName->setStyle(_fontStyle);
	textAIName->attachTo(_scoreTable);
	textAIName->setText(_game->_aiPlayer->username);
	textAIName->setPosition(Vector2(225, 13));
	textAIName->setAlign(TextStyle::VALIGN_DEFAULT, TextStyle::HALIGN_MIDDLE);
	_textAIName = textAIName;
}

void Scoretable::switchTurn(GameTurn turn)
{
	TextStyle fontStyle;
	fontStyle = _textPlayerName->getStyle();
	fontStyle.color = Color::White;
	_textPlayerName->setStyle(fontStyle);
	_textAIName->setStyle(fontStyle);

	fontStyle = _textPlayerName->getStyle();
	fontStyle.color = Color::Firebrick;
	if (turn == GameTurn::PLAYER_TURN) {
		_textPlayerName->setStyle(fontStyle);
	}
	else {
		_textAIName->setStyle(fontStyle);
	}

}
