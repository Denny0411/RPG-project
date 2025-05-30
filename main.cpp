#include <graphics.h>
#include <string>
#include <vector>
#include "Animation.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

int main()
{
	initgraph(1280, 720);

	bool running = true;

	Player player;
	ExMessage msg;
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;

	loadimage(&img_background, _T("img/Background.png"), 1280, 720);

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
		}

		player.Move();
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(player);

		cleardevice();

		putimage(0, 0, &img_background);
		player.Draw(1000 / 144);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(1000 / 144);

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	return 0;
}