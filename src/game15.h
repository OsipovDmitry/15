#ifndef GAME15_H
#define GAME15_H

#include <array>

#include "abstractgame.h"

namespace graphics {

class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Material;
using MaterialPtr = std::shared_ptr<Material>;

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

}

namespace game15 {

enum class GameMaterialId : uint32_t {
    Background,
	Wood,
    Block0,
	BlockCount = Block0 + 99,
	ButtonStart,
	ButtonToMenu,
	ButtonBack,
	ButtonExit,
	Button2x2,
	Button3x3,
	Button4x4,
	Button5x5,
	Button6x6,
	Button7x7,
	Button8x8,
	Button9x9,
	Button10x10,
	ButtonVictory,
	ButtonCount,
    Count,
};

enum class GameMeshId : uint32_t {
	QuadXY,
    Block,
	Button,
    Count,
};

enum class GameSceneId : uint32_t {
	Menu,
	SelectLevel,
    Game,
	Victory,
    Count
};

class Game15AbstractScene;
using Game15AbstractScenePtr = std::shared_ptr<Game15AbstractScene>;

class Game15;
using Game15Ptr = std::shared_ptr<Game15>;

class Game15 : public game::AbstractGame, public std::enable_shared_from_this<Game15> {
public:
    ~Game15();

    graphics::MaterialPtr material(GameMaterialId id) const;
    graphics::MeshPtr mesh(GameMeshId id) const;

	void initGame(int32_t gameConst);
	void exit();
    void setCurrentScene(GameSceneId id);

    static Game15Ptr createGame15(graphics::ControllerPtr pRenderer);

protected:
    virtual void update(uint64_t time, uint32_t dt) override;
    virtual void mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton) override;
    virtual void mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton) override;
    virtual void mouseWheel(int32_t dir) override;

private:
    Game15(graphics::ControllerPtr pRenderer);
    void initialize();

    std::array<graphics::MaterialPtr, static_cast<size_t>(GameMaterialId::Count)> m_materials;
    std::array<graphics::MeshPtr, static_cast<size_t>(GameMeshId::Count)> m_meshes;
    std::array<Game15AbstractScenePtr, static_cast<size_t>(GameSceneId::Count)> m_scenes;

    GameSceneId m_currentSceneId;

};


}

#endif // GAME15_H
