#ifndef ENEMY_H
#define ENEMY_H
#include <graphics.h>
#include "Animation.h"
#include "Bullet.h"
#include "Player.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	bool CheckBulletCollision(const Bullet& bullet);
	bool CheckPlayerCollision(const Player& player);
	void Move(const Player& player);
	void Draw(int delta);
	void Hurt();
	bool CheckAlive();

private:
	const int SPEED = 2;
	const int FRAME_WIDTH = 48;
	const int FRAME_HEIGHT = 32;
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

private:
	Animation* anim_left;
	Animation* anim_right;
	POINT position = { 0, 0 };
	bool facing_left = false;
	bool alive = true;
};

#endif