#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
#include "Primitives.h"

class Background : public Image
{
public:
	Background(const SDL_Rect src, const SDL_FRect dst, float speed);
	void Update();
	void Render();
	void SetSpeed(float speed);
private:
	float m_scrollSpeed; // Forno, pixels per frame.
	float m_startX, m_endX;
};

#endif