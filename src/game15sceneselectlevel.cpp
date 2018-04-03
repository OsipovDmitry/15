#include <algorithm>

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsmodel.h"

#include "game15sceneselectlevel.h"

namespace game {

Game15SceneSelectLevel::~Game15SceneSelectLevel()
{
}

void Game15SceneSelectLevel::activate()
{
	m_pGame15.lock()->graphicsController()->setCurrentScene(m_pGraphicsScene);
}

void Game15SceneSelectLevel::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
	auto pGame15 = m_pGame15.lock();
	if (!pGame15)
		return;

	auto pGUIObject = m_pGraphicsScene->selectObject(graphics::SceneLayer::GUI, x, y);

	if (pGUIObject == m_backButton) {
		pGame15->setCurrentScene(GameSceneId::Menu);
	}

	auto buttonIter = std::find(m_levelButtons.begin(), m_levelButtons.end(), pGUIObject);
	if (buttonIter != m_levelButtons.end()) {
		int32_t level = 2 + std::distance(m_levelButtons.begin(), buttonIter);
		pGame15->initGame(level);
		pGame15->setCurrentScene(GameSceneId::Game);
	}
}

Game15SceneSelectLevel::Game15SceneSelectLevel(Game15Ptr pGame15) :
	Game15AbstractScene(pGame15)
{
	m_pGraphicsScene->addModel(graphics::SceneLayer::Background, pGame15->material(GameMaterialId::Background), pGame15->mesh(GameMeshId::QuadXY));


	for (int32_t i = 0; i < s_numLevels; ++i) {
		auto pButton = m_pGraphicsScene->addModel(graphics::SceneLayer::GUI,
												  pGame15->material(static_cast<GameMaterialId>(static_cast<int32_t>(GameMaterialId::Button2x2)+i)),
												  pGame15->mesh(GameMeshId::Button));
		pButton->setPosition(glm::vec3((i%3-1)*0.45f, -(i/3-1)*0.25f, 0.0f));
		m_levelButtons[i] = pButton;
	}

	m_backButton = m_pGraphicsScene->addModel(graphics::SceneLayer::GUI, pGame15->material(GameMaterialId::ButtonBack), pGame15->mesh(GameMeshId::Button));
	m_backButton->setPosition(glm::vec3(0.0f, -0.7f, 0.0f));
}

}
