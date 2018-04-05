#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsscenelayer.h"
#include "graphicsmodel.h"

#include "game15.h"
#include "game15scenemenu.h"

namespace game {

Game15SceneMenu::~Game15SceneMenu()
{
}

void Game15SceneMenu::activate()
{
	m_pGame15.lock()->graphicsController()->setCurrentScene(m_pGraphicsScene);
}

void Game15SceneMenu::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
	auto pGame15 = m_pGame15.lock();
	if (!pGame15)
		return;

	auto pGUIObject = m_pGraphicsScene->layer(graphics::SceneLayerId::GUI)->selectModel(x, y);

	if (pGUIObject == m_pStartButton) {
		pGame15->setCurrentScene(GameSceneId::SelectLevel);
		return;
	}
	else if (pGUIObject == m_pExitButton) {
		pGame15->exit();
		return;
	}
}

Game15SceneMenu::Game15SceneMenu(Game15Ptr pGame15) :
	Game15AbstractScene(pGame15)
{
	m_pGraphicsScene->layer(graphics::SceneLayerId::Background)->addModel(pGame15->material(GameMaterialId::Background), pGame15->mesh(GameMeshId::QuadXY));

	m_pStartButton = m_pGraphicsScene->layer(graphics::SceneLayerId::GUI)->addModel(pGame15->material(GameMaterialId::ButtonStart), pGame15->mesh(GameMeshId::Button));
	m_pStartButton->setPosition(glm::vec3(0.0f, 0.13f, 0.0f));

	m_pExitButton = m_pGraphicsScene->layer(graphics::SceneLayerId::GUI)->addModel(pGame15->material(GameMaterialId::ButtonExit), pGame15->mesh(GameMeshId::Button));
	m_pExitButton->setPosition(glm::vec3(0.0f, -0.13f, 0.0f));
}


}
