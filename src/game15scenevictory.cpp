#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsscenelayer.h"
#include "graphicsmodel.h"

#include "game15.h"
#include "game15scenevictory.h"

namespace game15 {

Game15SceneVictory::~Game15SceneVictory()
{

}

void Game15SceneVictory::activate()
{
	m_pGame15.lock()->graphicsController()->setCurrentScene(m_pGraphicsScene);
}

void Game15SceneVictory::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
	auto pGame15 = m_pGame15.lock();
	if (!pGame15)
		return;

	auto pGUIObject = m_pGraphicsScene->layer(graphics::SceneLayerId::GUI)->selectModel(x, y);

	if (pGUIObject == m_pVictoryButton) {
		pGame15->setCurrentScene(GameSceneId::Menu);
		return;
	}
}

Game15SceneVictory::Game15SceneVictory(Game15Ptr pGame15) :
	Game15AbstractScene(pGame15)
{
	m_pGraphicsScene->layer(graphics::SceneLayerId::Background)->addModel(pGame15->material(GameMaterialId::Background), pGame15->mesh(GameMeshId::QuadXY));

	m_pVictoryButton = m_pGraphicsScene->layer(graphics::SceneLayerId::GUI)->addModel(pGame15->material(GameMaterialId::ButtonVictory), pGame15->mesh(GameMeshId::Button));
	m_pVictoryButton->setPosition(glm::vec3(0.0f, 0.3f, 0.0f));
}


}
