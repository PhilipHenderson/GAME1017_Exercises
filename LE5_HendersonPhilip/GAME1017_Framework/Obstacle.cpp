#include "Obstacle.h"
#include "RenderManager.h"
#include "TextureManager.h"

Obstacle::Obstacle(const SDL_FRect dst, bool hasImage, const SDL_Rect src, const char* key)
	:m_hasImage(hasImage), m_pImage(nullptr)
{
	m_pos = { dst.x, dst.y };
	if (m_hasImage)
	{
		// Load texture from file and store it in m_pImage.
		m_pImage = new Image(src, dst, key);
	}
}


Obstacle::~Obstacle()
{
	if (m_hasImage)
	{
		delete m_pImage;
		m_pImage = nullptr;
	}
}

void Obstacle::Update()
{
	m_pos.x -= kScrollSpeed;
	if (m_hasImage) // Or m_pImage != nullptr
	{
		// Update the Image's destination rect x.
		m_pImage->GetDst()->x = m_pos.x;
	}
}

void Obstacle::Render()
{
	if (m_hasImage && m_pImage)
	{
		SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture("obstacle"),
			m_pImage->GetSrc(), m_pImage->GetDst());
	}
}

