#ifndef GAME15SCENEMENU_H
#define GAME15SCENEMENU_H

#include "game15abstractscene.h"

namespace graphics {

class Model;
using ModelPtr = std::shared_ptr<Model>;

}

namespace game {

class Game15SceneMenu : public Game15AbstractScene
{
public:
	~Game15SceneMenu();

protected:
	virtual void activate() override;
	virtual void mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton) override;

private:
	Game15SceneMenu(Game15Ptr pGame15);

	graphics::ModelPtr m_pStartButton, m_pExitButton;

	friend class Game15;
};

}

#endif // GAME15SCENEMENU_H
