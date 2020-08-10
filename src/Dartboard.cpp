#include "Dartboard.h"

void Dartboard::init() {

	_scores.push_back(6);
	_scores.push_back(13);
	_scores.push_back(4);
	_scores.push_back(18);
	_scores.push_back(1);
	_scores.push_back(20);
	_scores.push_back(5);
	_scores.push_back(12);
	_scores.push_back(9);
	_scores.push_back(14);
	_scores.push_back(11);
	_scores.push_back(8);
	_scores.push_back(16);
	_scores.push_back(7);
	_scores.push_back(19);
	_scores.push_back(3);
	_scores.push_back(17);
	_scores.push_back(2);
	_scores.push_back(15);
	_scores.push_back(10);

	for (int i = 0; i < 20; i++) {
		_ranges.push_back(Range(Dartboard::RANGE_WIDTH*i - Dartboard::RANGE_WIDTH / 2, Dartboard::RANGE_WIDTH*i + Dartboard::RANGE_WIDTH / 2, _scores[i]));
	}
}

int Dartboard::calcScore(Vector2 posDart, Vector2 screenCenter) {
	Vector2 direction = posDart - screenCenter;
	float angle = 0;

	if (direction.y <= 0)
		angle = -atan2f(direction.y, direction.x) * 180 / M_PI; 
	else
		angle = 180 + atan2f(direction.y, -direction.x) * 180 / M_PI;
	int score = 0;
	for (int i = 0; i < 20; i++) {
		if (angle <= _ranges[i].end && angle>_ranges[i].start) {
			
			if (direction.length() >= 0 && direction.length() < 8) {
				score = 50;
			}
			else if (direction.length() >= 8 && direction.length() < 18) {
				score = 25;
			}
			else if (direction.length() >= 18 && direction.length() < 109) {
				score = _ranges[i].score;
			}
			else if (direction.length() >= 109 && direction.length() < 115) {
				score = _ranges[i].score * 3;
			}
			else if (direction.length() >= 115 && direction.length() < 177) {
				score = _ranges[i].score;
			}
			else if (direction.length() >= 177 && direction.length() < 190) {
				score = _ranges[i].score * 2;
			}
			else {
				score = 0;
			}
			log::messageln("Score:   %d", score);
			log::messageln("Score:   %f %f", direction.x, direction.y);
		}
	}
	return score;
}
 

std::vector<Range> Dartboard::_ranges;
std::vector<int> Dartboard::_scores;