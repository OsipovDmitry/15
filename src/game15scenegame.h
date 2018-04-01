#ifndef GAME15SCENEGAME_H
#define GAME15SCENEGAME_H

#include <vector>

#include "game15abstractscene.h"

namespace graphics {

class Model;
using ModelPtr = std::shared_ptr<Model>;

}

namespace game {

class Game15SceneGame : public Game15AbstractScene
{
public:
	~Game15SceneGame();

protected:
	virtual void activate() override;
	virtual void update(uint64_t time, uint32_t dt) override;
	virtual void mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton) override;
	virtual void mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton) override;
	virtual void mouseWheel(int32_t dir) override;

private:
	Game15SceneGame(Game15Ptr pGame15);
	void initialize(int32_t gameConst);

	std::vector<graphics::ModelPtr> m_table;
	float m_cameraLat, m_cameraLong, m_cameraDist;
	int32_t m_gameConst;

	friend class Game15;
};

}

#endif // GAME15SCENEGAME_H
