#include <graphics.h>
#include "Animation.h"

Atlas* atlas_player_left = nullptr;
Atlas* atlas_player_right = nullptr;
Atlas* atlas_enemy_left = nullptr;
Atlas* atlas_enemy_right = nullptr;

Atlas::Atlas(LPCTSTR path, int num)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < num; i++)
	{
		_stprintf_s(path_file, path, i);

		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
}

Atlas::~Atlas()
{
	for (size_t i = 0; i < frame_list.size(); i++)
		delete frame_list[i];
}

Animation::Animation(Atlas* atlas, int interval)
{
	anim_atlas = atlas;
	interval_ms = interval;
}

void Animation::Play(int x, int y, int delta)
{
	timer += delta;
	if (timer >= interval_ms)
	{
		index_frame = (index_frame + 1) % anim_atlas->frame_list.size();
		timer = 0;
	}

	putimage_alpha(x, y, anim_atlas->frame_list[index_frame]);
}