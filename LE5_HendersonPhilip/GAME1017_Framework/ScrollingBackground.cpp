#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground()
{
	m_backgrounds.reserve(10);
	m_backgrounds.push_back(new Background({0,0,1024,768}, { 0.0f,0.0f,1024.0f,768.0f } , 1.0f));
	m_backgrounds.push_back(new Background({0,0,1024,768}, { 1024.0f,0.0f,1024.0f,768.0f } , 1.0f));

	m_backgrounds.push_back(new Background({1024,0,256,512}, { 0.0f,0.0f,256.0f,512.0f } , 1.5f));
	m_backgrounds.push_back(new Background({1024,0,256,512}, { 256.0f,0.0f,256.0f,512.0f } , 1.5f));
	m_backgrounds.push_back(new Background({1024,0,256,512}, { 512.0f,0.0f,256.0f,512.0f } , 1.5f));
	m_backgrounds.push_back(new Background({1024,0,256,512}, { 768.0f,0.0f,256.0f,512.0f } , 1.5f));
	m_backgrounds.push_back(new Background({1024,0,256,512}, { 1024.0f,0.0f,256.0f,512.0f } , 1.5f));

	m_backgrounds.push_back(new Background({1024,512,512,256}, { 0.0f,512.0f,512.0f,256.0f } , 2.0f));
	m_backgrounds.push_back(new Background({1024,512,512,256}, { 512.0f,512.0f,512.0f,256.0f } , 2.0f));
	m_backgrounds.push_back(new Background({1024,512,512,256}, { 1024.0f,512.0f,512.0f,256.0f } , 2.0f));
}

ScrollingBackground::~ScrollingBackground()
{
	for (auto background : m_backgrounds)
	{
		delete background;
		background = nullptr;
	}
	m_backgrounds.clear();
}

void ScrollingBackground::Update()
{
	for (const auto background : m_backgrounds)
		background->Update();
}

void ScrollingBackground::Render()
{
	for (const auto background : m_backgrounds)
		background->Render();
}

void ScrollingBackground::SetSpeeds(const float back, const float mid, const float fore)
{
	m_backgrounds[0]->SetSpeed(back);
	m_backgrounds[1]->SetSpeed(back);

	m_backgrounds[2]->SetSpeed(mid);
	m_backgrounds[3]->SetSpeed(mid);
	m_backgrounds[4]->SetSpeed(mid);
	m_backgrounds[5]->SetSpeed(mid);
	m_backgrounds[6]->SetSpeed(mid);

	m_backgrounds[7]->SetSpeed(fore);
	m_backgrounds[8]->SetSpeed(fore);
	m_backgrounds[9]->SetSpeed(fore);
}
