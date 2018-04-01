#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <memory>

namespace graphics {

class Controller;
using ControllerPtr = std::shared_ptr<Controller>;

}

namespace game {

class AbstractGame
{
public:
    virtual ~AbstractGame();

    graphics::ControllerPtr graphicsController() const;

protected:
    AbstractGame(graphics::ControllerPtr pRenderer);

    virtual void update(uint64_t time, uint32_t dt);
    virtual void mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton);
    virtual void mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton);
    virtual void mouseWheel(int32_t dir);

    graphics::ControllerPtr m_pRenderer;

    friend class GameWidget;
};

}

#endif // ABSTRACTGAME_H
