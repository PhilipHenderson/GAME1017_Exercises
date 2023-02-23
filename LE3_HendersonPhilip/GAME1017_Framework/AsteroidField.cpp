#include "AsteroidField.h"
#include "Engine.h"
#include "EventManager.h"
#include "MathManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

Asteroid::Asteroid(SDL_Rect s, SDL_FRect d) : Sprite(s, d), 
	m_angle(0.0), m_radius(33.0), m_size(3)
{
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	m_rotSpeed = (1.0 + rand() % 5) * (rand() % 2 * 2.0 - 1.0); // -1 or 1
	MAMA::SetDeltas(MAMA::Deg2Rad((rand() % 360) - 90.0), m_dx, m_dy, 2.0f, 2.0f);
}

void Asteroid::Update()
{
	// Rotate and move object.
	m_angle += m_rotSpeed;
	m_center.x += (float)m_dx;
	m_center.y += (float)m_dy;
	// Wrap on screen.
	if (m_center.x < -m_dst.w / 2) m_center.x = kWidth + m_dst.w / 2;
	else if (m_center.x > kWidth + m_dst.w / 2) m_center.x = 0 - m_dst.w / 2;
	else if (m_center.y < -m_dst.h / 2) m_center.y = kHeight + m_dst.h / 2;
	else if (m_center.y > kHeight + m_dst.h / 2) m_center.y = 0 - m_dst.h / 2;
	// Update dest rectangle.
	m_dst.x = m_center.x - m_dst.w / 2;
	m_dst.y = m_center.y - m_dst.h / 2;
}

void Asteroid::Render()
{
	SDL_SetTextureColorMod(TEMA::GetTexture("sprites"), 255-m_rMod, 255-m_gMod, 255-m_bMod);
	SDL_RenderCopyExF(REMA::GetRenderer(), TEMA::GetTexture("sprites"),
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
	SDL_SetTextureColorMod(TEMA::GetTexture("sprites"), 255, 255, 255); // Resetting it so not all sprites are tinted this way.
}

Uint8* Asteroid::GetColMods()
{
	Uint8 mods[3] = { m_rMod, m_gMod, m_bMod };
	return mods;
}

void Asteroid::SetColMods(Uint8 r, Uint8 g, Uint8 b)
{
	m_rMod = r; m_gMod = g; m_bMod = b;
}

short Asteroid::GetSize()
{
	return m_size;
}

void Asteroid::SetSize(short size)
{
	m_size = size;
}

void Asteroid::UpdateDeltas(double angle)
{
	MAMA::SetDeltas(MAMA::Deg2Rad(angle - 90.0), m_dx, m_dy, 2.0f, 2.0f);
}

void Asteroid::Split(std::vector<Asteroid*>& asteroids)
{
	if (m_size > 1)
	{
		// Create two new asteroids with size one level lower.
		for (int i = 0; i < 2; i++)
		{
			Asteroid* newAsteroid = new Asteroid(m_src, m_dst);
			newAsteroid->SetSize(m_size - 1);
			newAsteroid->SetColMods(m_rMod, m_gMod, m_bMod);
			newAsteroid->UpdateDeltas(m_angle + 90.0 * (i == 0 ? -1 : 1));
			newAsteroid->m_radius = m_radius * 0.67f;
			newAsteroid->m_dst.w = m_dst.w * 0.67f;
			newAsteroid->m_dst.h = m_dst.h * 0.67f;
			asteroids.push_back(newAsteroid);
		}
	}
	SetEnabled(false);
}

AsteroidField::AsteroidField(unsigned int sz) : GameObject({ 0,0,0,0 }), m_size(sz)
{
	for (int i = 0; i < m_size; i++)
	{
		m_asteroids.push_back(new Asteroid({ 539, 0, 61, 66 },
			{ 25.0f + rand() % 901, (i % 2 == 0 ? 25.0f : 600.0f) + (rand() % 76),
			61.0f, 66.0f }));
		m_asteroids.back()->SetColMods((rand() % 129), (rand() % 129), (rand() % 129));
		m_asteroids.back()->SetSize(3);
	}
	m_asteroids.shrink_to_fit();
}

AsteroidField::~AsteroidField()
{
	for (auto a : m_asteroids)
	{
		delete a;
		a = nullptr; // ;)
	}
	m_asteroids.clear();
}

void AsteroidField::Update()
{
	std::vector<Asteroid*> newAsteroids;
	for (unsigned int i = 0; i < m_asteroids.size(); i++)
	{
		if (m_asteroids[i]->GetEnabled() == false)
		{
			// Split asteroid and add new ones to vector.
			m_asteroids[i]->Split(newAsteroids);

			delete m_asteroids[i];
			m_asteroids[i] = nullptr;
			m_asteroids.erase(m_asteroids.begin() + i);
			m_asteroids.shrink_to_fit();
			i--;
		}
		else
		{
			m_asteroids[i]->Update();
		}
	}

	// Add new asteroids to field.
	for (auto a : newAsteroids)
	{
		if (a->GetSize() > 0)
		{
			m_asteroids.push_back(a);
		}
		else
		{
			delete a;
		}
	}
}



void AsteroidField::Render()
{
	for (const auto a : m_asteroids)
		a->Render();
}