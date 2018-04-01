#include "glm/gtc/matrix_transform.hpp"

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsmodel.h"

#include "game15.h"
#include "game15scenegame.h"

namespace game {

Game15SceneGame::~Game15SceneGame()
{

}

void Game15SceneGame::activate()
{
	m_pGame15.lock()->graphicsController()->setCurrentScene(m_pGraphicsScene);
}

void Game15SceneGame::update(uint64_t time, uint32_t dt)
{
	m_pGraphicsScene->setViewMatrix(
				glm::translate(glm::mat4x4(), glm::vec3(0,0,-m_cameraDist)) *
				glm::rotate(glm::mat4x4(), glm::radians(m_cameraLat), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(glm::mat4x4(), glm::radians(m_cameraLong), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Game15SceneGame::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
	m_pGraphicsScene->selectObject(graphics::SceneLayer::Objects, x, y);
}

void Game15SceneGame::mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton)
{
	m_cameraLat += dy;
	m_cameraLong += dx;

	if (m_cameraLat < 0.0f) m_cameraLat = 0.0f;
	if (m_cameraLat > 90.0f) m_cameraLat = 90.0f;

	while (m_cameraLong < 0.0f) m_cameraLong += 360.0f;
	while (m_cameraLong > 360.0f) m_cameraLong -= 360.0f;
}

void Game15SceneGame::mouseWheel(int32_t dir)
{
	m_cameraDist -= dir;
}

Game15SceneGame::Game15SceneGame(Game15Ptr pGame15) :
	Game15AbstractScene(pGame15),
	m_cameraLat(45.0f),
	m_cameraLong(330.0f),
	m_cameraDist(5.0f),
	m_gameConst(0)
{
}

void Game15SceneGame::initialize(int32_t gameConst)
{
	if (m_gameConst) {
		m_table.clear();
		m_pGraphicsScene->clear();
		m_gameConst = gameConst;
	}

	auto pGame15 = m_pGame15.lock();

	m_pGraphicsScene->addModel(graphics::SceneLayer::Background, pGame15->material(GameMaterialId::Background), pGame15->mesh(GameMeshId::QuadXY));

	for (auto i = 0; i < gameConst*gameConst-1; ++i) {
		auto pBlockModel = m_pGraphicsScene->addModel(graphics::SceneLayer::Objects, pGame15->material(static_cast<GameMaterialId>(static_cast<int>(GameMaterialId::Block0)+i)), pGame15->mesh(GameMeshId::Block));
		pBlockModel->setPosition(glm::vec3(i%gameConst-gameConst/2.0f+0.5f, 0, i/gameConst-gameConst/2.0f+0.5f));
		m_table.push_back(pBlockModel);
	}
	m_table.push_back(nullptr);
}

}
