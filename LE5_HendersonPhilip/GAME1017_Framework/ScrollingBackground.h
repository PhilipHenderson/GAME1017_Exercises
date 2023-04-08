#ifndef __SCROLLINGBACKGROUND_H__
#define __SCROLLINGBACKGROUND_H__
#include "GameObject.h"
#include "Background.h"
#include <vector>

class ScrollingBackground : public GameObject
{
public:
	ScrollingBackground();
	~ScrollingBackground();
	void Update();
	void Render();
	void SetSpeeds(float back = 0.5f, float mid = 1.0f, float fore = 1.5f);
private:
	std::vector<Background*> m_backgrounds;
};

#endif