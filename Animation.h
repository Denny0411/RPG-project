#ifndef ANIMATION_H
#define ANIMATION_H
#include <graphics.h>
#include <vector>
#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

class Atlas
{
public:
	Atlas(LPCTSTR path, int num);
	~Atlas();

public:
	std::vector<IMAGE*> frame_list;
};

extern Atlas* atlas_player_left;
extern Atlas* atlas_player_right;
extern Atlas* atlas_enemy_left;
extern Atlas* atlas_enemy_right;

class Animation
{
public:
	Animation(Atlas* atlas, int interval);
	~Animation() = default;

	void Play(int x, int y, int delta);

private:
	int timer = 0; // 動畫計時器
	int index_frame = 0; // 動畫幀索引
	int interval_ms = 0;

private:
	Atlas* anim_atlas;
};

#endif