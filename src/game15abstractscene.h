#ifndef GAME15ABSTRACTSCENE_H
#define GAME15ABSTRACTSCENE_H

#include <memory>

namespace graphics {

class Scene;
using ScenePtr = std::shared_ptr<Scene>;

}

namespace game15 {

class Game15;
using Game15Ptr = std::shared_ptr<Game15>;
using Game15WPtr = std::weak_ptr<Game15>;

class Game15AbstractScene {
public:
    virtual ~Game15AbstractScene();

protected:
    Game15AbstractScene(Game15Ptr pGame15);

    virtual void activate();
    virtual void update(uint64_t time, uint32_t dt);
    virtual void mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton);
    virtual void mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton);
    virtual void mouseWheel(int32_t dir);

    Game15WPtr m_pGame15;
    graphics::ScenePtr m_pGraphicsScene;

    friend class Game15;

};

}

#endif // GAME15ABSTRACTSCENE_H
