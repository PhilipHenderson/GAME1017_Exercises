#include "Background.h"

Background::Background(const SDL_Rect src, const SDL_FRect dst, float speed)
	:Image(src, dst, "temple"), m_scrollSpeed(speed)
{
	m_startX = m_dst.x; // or sdt,x or GetDst()->x
	m_endX = m_startX - m_dst.w;
}

void Background::Update()
{
	// Chech it journey is over.
	if (m_dst.x <= m_endX)
		m_dst.x = m_startX;
	// schroll the background
	m_dst.x -= m_scrollSpeed;
}

void Background::Render()
{
	Image::Render();
}

void Background::SetSpeed(float speed)
{
	m_scrollSpeed = speed;
}
