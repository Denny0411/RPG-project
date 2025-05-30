#ifndef PLAYER_H
#define PLAYER_H
#include <graphics.h>
#include "Animation.h"

class Player
{
public:
	Player();
	~Player();

	void ProcessEvent(const ExMessage& msg);
	void Move();
	void Draw(int delta);
	const POINT& GetPosition() const;

private:
	const int SPEED = 3;
	const int FRAME_WIDTH = 96;
	const int FRAME_HEIGHT = 96;
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	POINT position = { 500, 500 };
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
};

#endif