#ifndef GAME15SCENESELECTLEVEL_H
#define GAME15SCENESELECTLEVEL_H

#include "game15abstractscene.h"
#include "game15.h"

namespace graphics {

class Model;
using ModelPtr = std::shared_ptr<Model>;

}

namespace game15 {

class Game15SceneSelectLevel : public Game15AbstractScene
{
public:
	~Game15SceneSelectLevel();

protected:
	virtual void activate() override;
	virtual void mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton) override;

private:
	Game15SceneSelectLevel(Game15Ptr pGame15);

	static const int32_t s_numLevels = 9;
	std::array<graphics::ModelPtr, s_numLevels> m_levelButtons;
	graphics::ModelPtr m_backButton;

	friend class Game15;
};

}

#endif // GAME15SCENESELECTLEVEL_H
