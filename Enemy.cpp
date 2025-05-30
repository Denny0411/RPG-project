#include "Enemy.h"

Enemy::Enemy()
{
	anim_left = new Animation(_T("img/enemy_left_%d.png"), 6, 45);
	anim_right = new Animation(_T("img/enemy_right_%d.png"), 6, 45);

	enum class SpawnEdge
	{
		Up = 0,
		Down,
		Left,
		Right
	};

	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case SpawnEdge::Up:
		position.x = rand() % WINDOW_WIDTH;
		position.y = -FRAME_HEIGHT;
		break;
	case SpawnEdge::Down:
		position.x = rand() % WINDOW_WIDTH;
		position.y = WINDOW_HEIGHT;
		break;
	case SpawnEdge::Left:
		position.x = -FRAME_WIDTH;
		position.y = rand() % WINDOW_HEIGHT;
		break;
	case SpawnEdge::Right:
		position.x = WINDOW_WIDTH;
		position.y = rand() % WINDOW_HEIGHT;
		break;
	}
}

Enemy::~Enemy()
{
	delete anim_left;
	delete anim_right;
}

bool Enemy::CheckBulletCollision(const Bullet& bullet)
{
	return false;
}

bool Enemy::CheckPlayerCollision(const Player& player)
{
	return false;
}

void Enemy::Move(const Player& player)
{
	const POINT& player_position = player.GetPosition();
	int dir_x = player_position.x - position.x;
	int dir_y = player_position.y - position.y;
	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len_dir != 0)
	{
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_x / len_dir;
		position.x += (int)(SPEED * normalized_x);
		position.y += (int)(SPEED * normalized_y);
	}
}

void Enemy::Draw(int delta)
{
	if (facing_left)
		anim_left->Play(position.x, position.y, delta);
	else
		anim_right->Play(position.x, position.y, delta);
}