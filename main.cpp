#include <graphics.h>
#include <string>
#include <vector>
#include "Animation.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#pragma comment(lib, "Winmm.lib")

// 生成新的敵人
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

// 更新子彈位置
void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
	const double TANGENT_SPEED = 0.0055; // 切線速度
	const double NORMAL_SPEED = 0.0045; // 法線速度
	double radian_interval = 2 * 3.14159 / bullet_list.size(); // 子彈之間的弧度間隔
	POINT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount() * NORMAL_SPEED);

	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i; // 當前子彈所在弧度值
		bullet_list[i].position.x = player_position.x + player.FRAME_WIDTH / 2 + (int)(radius * sin(radian));
		bullet_list[i].position.y = player_position.y + player.FRAME_HEIGHT / 2 + (int)(radius * cos(radian));
	}
}

void DrawPlayerScore(int score)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("得分：%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}

int main()
{
	initgraph(1280, 720);

	atlas_player_left = new Atlas(_T("image/player_left_%d.png"), 7);
	atlas_player_right = new Atlas(_T("image/player_right_%d.png"), 7);
	atlas_enemy_left = new Atlas(_T("image/enemy_left_%d.png"), 5);
	atlas_enemy_right = new Atlas(_T("image/enemy_right_%d.png"), 5);

	mciSendString(_T("open music/BGM.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open music/hit.mp3 alias hit"), NULL, 0, NULL);

	mciSendString(_T("play bgm repeat"), NULL, 0, NULL);

	bool running = true;

	int score = 0;
	Player player;
	ExMessage msg;
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;
	std::vector<Bullet> bullet_list(3);

	loadimage(&img_background, _T("image/Background.png"), 1280, 720);

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
		}

		player.Move();
		UpdateBullets(bullet_list, player);
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(player);

		// 檢測敵人和玩家的碰撞
		for (Enemy* enemy : enemy_list)
		{
			if (enemy->CheckPlayerCollision(player))
			{
				static TCHAR text[128];
				_stprintf_s(text, _T("最終得分：%d 分"), score);
				MessageBox(GetHWnd(), text, _T("遊戲結束"), MB_OK);
				running = false;
				break;
			}
		}

		// 檢測子彈和敵人的碰撞
		for (Enemy* enemy : enemy_list)
		{
			for (const Bullet& bullet : bullet_list)
			{
				if (enemy->CheckBulletCollision(bullet))
				{
					mciSendString(_T("stop hit"), NULL, 0, NULL);
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					enemy->Hurt();
					score++;
				}
			}
		}

		// 移除死亡的敵人
		for (size_t i = 0; i < enemy_list.size(); i++)
		{
			Enemy* enemy = enemy_list[i];
			if (!enemy->CheckAlive())
			{
				std::swap(enemy_list[i], enemy_list.back());
				enemy_list.pop_back();
				delete enemy;
			}
		}

		cleardevice();

		putimage(0, 0, &img_background);
		player.Draw(1000 / 144);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(1000 / 144);
		for (const Bullet& bullet : bullet_list)
			bullet.Draw();
		DrawPlayerScore(score);

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	delete atlas_player_left;
	delete atlas_player_right;
	delete atlas_enemy_left;
	delete atlas_enemy_right;

	EndBatchDraw();

	return 0;
}