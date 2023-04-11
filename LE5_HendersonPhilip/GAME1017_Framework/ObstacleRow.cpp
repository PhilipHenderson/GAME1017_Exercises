#include "ObstacleRow.h"
#include "RenderManager.h"

enum class ObstacleType
{
    Spikes,
    Platform,
    BuzzSaw
};

ObstacleRow::ObstacleRow() : m_gapCtr(0), m_gapMax(3)
{
    // Create the vector now.
    for (int i = 0; i < 9; i++)
    {
        m_obstacles.push_back(new Obstacle({ 100.0f * i, 384.0f, 128.0f, 128.0f }, false, { 0, 0, 115, 100 }, "obstacle"));
    }
    m_obstacles.shrink_to_fit();
}

void ObstacleRow::Update()
{
    // When the first obstacle goes completely off-screen.
    if (m_obstacles[0]->GetPos().x <= -128.0f)
    {
        // Pop the first obstacle off
        delete m_obstacles[0];
        m_obstacles[0] = nullptr;
        m_obstacles.erase(m_obstacles.begin()); // "Pop_front"

        if (m_gapCtr % m_gapMax == 0) // Only create a new obstacle when m_gapCtr is a multiple of m_gapMax.
        {
            // Add a new obstacle to the end.
            ObstacleType newObstacleType = static_cast<ObstacleType>(m_gapCtr / m_gapMax % 3);

            if (newObstacleType == ObstacleType::Spikes)
            {
                m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }, true, { 0, 0, 115, 100 }, "obstacle"));
            }
            else if (newObstacleType == ObstacleType::Platform)
            {
                m_obstacles.push_back(new Obstacle({ 1024.0f, 0.0f, 128.0f, 428.0f }, true, { 150, 0, 280, 400 }, "obstacle"));
            }
            else if (newObstacleType == ObstacleType::BuzzSaw)
            {
                m_obstacles.push_back(new Obstacle({ 1024.0f, 413.0f, 128.0f, 100.0f }, true, { 0, 264, 149, 100 }, "obstacle"));
            }
        }
        else // Create a blank space with no obstacle.
        {
            m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }, false, { 0, 0, 0, 0 }, "obstacle"));
        }

        m_gapCtr++;
        m_obstacles.shrink_to_fit();
    }

    // Scroll the obstacles
    for (const auto obstacle : m_obstacles)
        obstacle->Update();
}


void ObstacleRow::Render()
{
    // Blue line under obstacles.
    SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 255);
    SDL_RenderDrawLine(REMA::GetRenderer(), 0, 512, 1024, 512);
    // Render the obstacles.
    for (const auto obstacle : m_obstacles)
        obstacle->Render();
}
