#include <algorithm>

#include "glm/gtc/matrix_transform.hpp"

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsscenelayer.h"
#include "graphicsmodel.h"

#include "meshdata.h"
#include "game15.h"
#include "game15scenegame.h"

namespace game15 {

Game15SceneGame::~Game15SceneGame()
{
}

void Game15SceneGame::activate()
{
	m_pGame15.lock()->graphicsController()->setCurrentScene(m_pGraphicsScene);
}

void Game15SceneGame::update(uint64_t time, uint32_t dt)
{
	auto pGame15 = m_pGame15.lock();
	if (!pGame15)
		return;

	const glm::vec4 lightPos(m_gameConst/2 * glm::cos(time*0.001f), 2.0f, m_gameConst/2 * glm::sin(time*0.001f), 1.0f);
	m_pGraphicsScene->layer(graphics::SceneLayerId::Objects)->setParam("u_lightPos", lightPos);


	m_pGraphicsScene->setViewMatrix(
				glm::translate(glm::mat4x4(), glm::vec3(0,0,-m_cameraDist)) *
				glm::rotate(glm::mat4x4(), glm::radians(m_cameraLat), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(glm::mat4x4(), glm::radians(m_cameraLong), glm::vec3(0.0f, 1.0f, 0.0f)));

	if (m_state == State::Animation) {
		m_animation.lifeTime -= dt;
		auto finishAnim = false;
		if (m_animation.lifeTime <= 0) {
			m_animation.lifeTime = 0;
			finishAnim = true;
		}
		for (size_t i = 0; i < m_animation.blocks.size(); ++i) {
			glm::vec2 newPos = m_animation.blockPoses[i] + m_animation.dir * (1.0f - (float)m_animation.lifeTime/(float)s_animTime);
			m_animation.blocks[i]->setPosition(glm::vec3(newPos.x, 0.0f, newPos.y));
		}
		if (finishAnim) {
			m_animation.blockPoses.clear();
			m_animation.blocks.clear();
			m_state = State::Wait;
			calibrate();
			if (checkWin()) {
				pGame15->setCurrentScene(GameSceneId::Victory);
			}
		}
	}
}

void Game15SceneGame::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
	auto pGame15 = m_pGame15.lock();
	if (!pGame15)
		return;

	auto pGUIObject = m_pGraphicsScene->layer(graphics::SceneLayerId::GUI)->selectModel(x, y);
	auto pGameObject = m_pGraphicsScene->layer(graphics::SceneLayerId::Objects)->selectModel(x, y);

	if (pGUIObject == m_pToMenuButton) {
		pGame15->setCurrentScene(GameSceneId::Menu);
		return;
	}

	auto objIter = std::find(m_table.begin(), m_table.end(), pGameObject);
	if (leftButton && (m_state == State::Wait) && (pGameObject && (objIter != m_table.end()))) {
		int32_t objX = (std::distance(m_table.begin(), objIter)) % m_gameConst;
		int32_t objY = (std::distance(m_table.begin(), objIter)) / m_gameConst;
		int32_t emptyX, emptyY;
		findEmpty(emptyX, emptyY);
		bool flag = false;
		if (m_table[objY*m_gameConst+emptyX] == nullptr) {
			flag = true;
			if (emptyX > objX) {
				m_animation.dir = glm::vec2(1.0f,0.0f);
				for (int32_t j = objX; j < emptyX; ++j) {
					auto pBlock = m_table[objY*m_gameConst+j];
					m_animation.blocks.push_back(pBlock);
					m_animation.blockPoses.push_back(glm::vec2(pBlock->position().x, pBlock->position().z));
				}
				for (int32_t j = emptyX; j > objX; --j)
					m_table[objY*m_gameConst+j] = m_table[objY*m_gameConst+(j-1)];
				m_table[objY*m_gameConst+objX] = nullptr;
			}
			else if (emptyX < objX) {
				m_animation.dir = glm::vec2(-1.0f,0.0f);
				for (int32_t j = objX; j > emptyX; --j) {
					auto pBlock = m_table[objY*m_gameConst+j];
					m_animation.blocks.push_back(pBlock);
					m_animation.blockPoses.push_back(glm::vec2(pBlock->position().x, pBlock->position().z));
				}
				for (int32_t j = emptyX; j < objX; ++j)
					m_table[objY*m_gameConst+j] = m_table[objY*m_gameConst+(j+1)];
				m_table[objY*m_gameConst+objX] = nullptr;
			}
		}
		else if (m_table[emptyY*m_gameConst+objX] == nullptr) {
			flag = true;
			if (emptyY > objY) {
				m_animation.dir = glm::vec2(0.0f,1.0f);
				for (int32_t j = objY; j < emptyY; ++j) {
					auto pBlock = m_table[j*m_gameConst+objX];
					m_animation.blocks.push_back(pBlock);
					m_animation.blockPoses.push_back(glm::vec2(pBlock->position().x, pBlock->position().z));
				}
				for (int32_t j = emptyY; j > objY; --j)
					m_table[j*m_gameConst+objX] = m_table[(j-1)*m_gameConst+objX];
				m_table[objY*m_gameConst+objX] = nullptr;
			}
			else if (emptyY < objY) {
				m_animation.dir = glm::vec2(0.0f,-1.0f);
				for (int32_t j = objY; j > emptyY; --j) {
					auto pBlock = m_table[j*m_gameConst+objX];
					m_animation.blocks.push_back(pBlock);
					m_animation.blockPoses.push_back(glm::vec2(pBlock->position().x, pBlock->position().z));
				}
				for (int32_t j = emptyY; j < objY; ++j)
					m_table[j*m_gameConst+objX] = m_table[(j+1)*m_gameConst+objX];
				m_table[objY*m_gameConst+objX] = nullptr;
			}
		}

		if (flag) {
			m_animation.lifeTime = s_animTime;
			m_state = State::Animation;
		}

		return;
	}
}

void Game15SceneGame::mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton)
{
	if (righrButton) {
		m_cameraLat += dy;
		m_cameraLong += dx;

		if (m_cameraLat < 0.0f) m_cameraLat = 0.0f;
		if (m_cameraLat > 90.0f) m_cameraLat = 90.0f;

		while (m_cameraLong < 0.0f) m_cameraLong += 360.0f;
		while (m_cameraLong > 360.0f) m_cameraLong -= 360.0f;
	}
}

void Game15SceneGame::mouseWheel(int32_t dir)
{
	m_cameraDist -= dir;
	if (m_cameraDist < m_gameConst/1.4f+1)
		m_cameraDist = m_gameConst/1.4f+1;
	if (m_cameraDist > m_gameConst * 5)
		m_cameraDist = m_gameConst * 5;
}

Game15SceneGame::Game15SceneGame(Game15Ptr pGame15) :
	Game15AbstractScene(pGame15),
	m_gameConst(0)
{
}

void Game15SceneGame::initialize(int32_t gameConst)
{
	if (m_gameConst) {
		m_table.clear();
		m_pGraphicsScene->clear();
	}

	m_gameConst = gameConst;
	auto pGame15 = m_pGame15.lock();
	auto pRenderer = pGame15->graphicsController();

	m_pGraphicsScene->layer(graphics::SceneLayerId::Background)->addModel(pGame15->material(GameMaterialId::Background), pGame15->mesh(GameMeshId::QuadXY));
	m_pGraphicsScene->layer(graphics::SceneLayerId::Objects)->addModel(pGame15->material(GameMaterialId::Wood), pRenderer->createMesh(tableVertices(gameConst), tableIndices));

	m_pToMenuButton = m_pGraphicsScene->layer(graphics::SceneLayerId::GUI)->addModel(pGame15->material(GameMaterialId::ButtonToMenu), pGame15->mesh(GameMeshId::Button));
	m_pToMenuButton->setPosition(glm::vec3(0.75f, 0.85f, 0.0f));

	for (auto i = 0; i < gameConst*gameConst-1; ++i) {
		auto pBlockModel = m_pGraphicsScene->layer(graphics::SceneLayerId::Objects)->addModel(pGame15->material(static_cast<GameMaterialId>(static_cast<uint32_t>(GameMaterialId::Block0)+i)), pGame15->mesh(GameMeshId::Block));
		pBlockModel->setUserData(i);
		m_table.push_back(pBlockModel);
	}
	m_table.push_back(nullptr);

	for (int32_t i = 0; i < 1000; ++i)
		shuffle();

	while (checkWin())
		shuffle();

	calibrate();

	m_cameraLat = 45.0f;
	m_cameraLong = 330.0f;
	m_cameraDist = m_gameConst/1.2f+1;
	m_state = State::Wait;
}

void Game15SceneGame::shuffle()
{
	int32_t emptyX, emptyY;
	findEmpty(emptyX, emptyY);
	if (rand()%2)
		moveTable(emptyX, rand()%m_gameConst);
	else
		moveTable(rand()%m_gameConst, emptyY);
}

void Game15SceneGame::moveTable(int32_t objX, int32_t objY)
{
	int32_t emptyX, emptyY;
	findEmpty(emptyX, emptyY);
	if (m_table[objY*m_gameConst+emptyX] == nullptr) {
		if (emptyX > objX) {
			for (int32_t j = emptyX; j > objX; --j)
				m_table[objY*m_gameConst+j] = m_table[objY*m_gameConst+(j-1)];
			m_table[objY*m_gameConst+objX] = nullptr;
		}
		else if (emptyX < objX) {
			for (int32_t j = emptyX; j < objX; ++j)
				m_table[objY*m_gameConst+j] = m_table[objY*m_gameConst+(j+1)];
			m_table[objY*m_gameConst+objX] = nullptr;
		}
	}
	else if (m_table[emptyY*m_gameConst+objX] == nullptr) {
		if (emptyY > objY) {
			for (int32_t j = emptyY; j > objY; --j)
				m_table[j*m_gameConst+objX] = m_table[(j-1)*m_gameConst+objX];
			m_table[objY*m_gameConst+objX] = nullptr;
		}
		else if (emptyY < objY) {
			for (int32_t j = emptyY; j < objY; ++j)
				m_table[j*m_gameConst+objX] = m_table[(j+1)*m_gameConst+objX];
			m_table[objY*m_gameConst+objX] = nullptr;
		}
	}
}

void Game15SceneGame::findEmpty(int32_t& x, int32_t& y)
{
	for (int32_t i = 0; i < m_gameConst*m_gameConst; ++i) {
		if (m_table[i] == nullptr) {
			x = i % m_gameConst;
			y = i / m_gameConst;
			return;
		}
	}
	x = -1;
	y = -1;
}

bool Game15SceneGame::checkWin() const
{
	if (m_table.back() != nullptr)
		return false;

	for (auto iter = m_table.begin(); iter != m_table.end()-1; ++iter) {
		auto pBlock = *iter;
		if (pBlock->userData() != std::distance(m_table.begin(), iter))
			return false;
	}

	return true;
}

void Game15SceneGame::calibrate()
{
	for (int i = 0; i < m_gameConst*m_gameConst; ++i) {
		if (m_table[i] == nullptr)
			continue;
		m_table[i]->setPosition(glm::vec3(i%m_gameConst-m_gameConst/2.0f+0.5f, 0, i/m_gameConst-m_gameConst/2.0f+0.5f));
	}
}

}
