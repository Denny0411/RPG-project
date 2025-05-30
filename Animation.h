#ifndef ANIMATION_H
#define ANIMATION_H
#pragma comment(lib, "Msimg32.lib")
#include <graphics.h>
#include <vector>

class Animation
{
public:
	Animation(LPCTSTR path, int num, int interval);
	~Animation();

	void putimage_alpha(int x, int y, IMAGE* img);
	void Play(int x, int y, int delta);

private:
	int timer = 0; // 動畫計時器
	int index_frame = 0; // 動畫幀索引
	int interval_ms = 0;
	std::vector<IMAGE*> frame_list;
};

#endif