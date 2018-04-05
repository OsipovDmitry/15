#ifndef GAME15SCENEVICTORY_H
#define GAME15SCENEVICTORY_H

#include "game15abstractscene.h"

namespace graphics {

class Model;
using ModelPtr = std::shared_ptr<Model>;

}

namespace game15 {

class Game15SceneVictory : public Game15AbstractScene
{
public:
	~Game15SceneVictory();

protected:
	virtual void activate() override;
	virtual void mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton) override;

private:
	Game15SceneVictory(Game15Ptr pGame15);

	graphics::ModelPtr m_pVictoryButton;

	friend class Game15;
};

}

#endif // GAME15SCENEVICTORY_H
