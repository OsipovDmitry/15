#include "abstractgame.h"

namespace game {

AbstractGame::~AbstractGame()
{
}

graphics::ControllerPtr AbstractGame::graphicsController() const
{
    return m_pRenderer;
}

AbstractGame::AbstractGame(graphics::ControllerPtr pRenderer) :
    m_pRenderer(pRenderer)
{
}

void AbstractGame::update(uint64_t time, uint32_t dt)
{
    (void)time;
    (void)dt;
}

void AbstractGame::mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton)
{
    (void)x;
    (void)y;
    (void)dx;
    (void)dy;
    (void)leftButton;
    (void)righrButton;
}

void AbstractGame::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
    (void)x;
    (void)y;
    (void)leftButton;
    (void)righrButton;
}

void AbstractGame::mouseWheel(int32_t dir)
{
    (void)dir;
}



}
