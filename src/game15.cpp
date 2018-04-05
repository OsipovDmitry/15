#include <QImage>
#include <QPainter>
#include <QStaticText>
#include <QFontMetrics>
#include <QApplication>

#include "glm/gtc/matrix_transform.hpp"

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsmodel.h"

#include "game15.h"
#include "meshdata.h"
#include "game15scenegame.h"
#include "game15scenemenu.h"
#include "game15sceneselectlevel.h"
#include "game15scenevictory.h"

namespace game {

namespace {
const std::array<QString, static_cast<size_t>(GameMaterialId::ButtonCount)-static_cast<size_t>(GameMaterialId::ButtonStart)> buttonLabels {
	"Start",
	"To menu",
	"Back",
	"Exit",
	"2x2", "3x3", "4x4", "5x5", "6x6", "7x7", "8x8", "9x9", "10x10",
	"Victory"
};
}

Game15::Game15(graphics::ControllerPtr pRenderer) :
	AbstractGame(pRenderer)
{
}

void Game15::initialize()
{
	m_materials[static_cast<size_t>(GameMaterialId::Background)] = m_pRenderer->createMaterial(":/res/background.jpg");
	m_materials[static_cast<size_t>(GameMaterialId::Wood)] = m_pRenderer->createMaterial(":/res/wood.png");
	for (size_t i = 0; i < static_cast<size_t>(GameMaterialId::BlockCount)-static_cast<size_t>(GameMaterialId::Block0); ++i) {
		QImage image(":/res/block.png");
		QPainter painter(&image);
		QFont font = painter.font();
		font.setPixelSize(128);
		font.setBold(true);
		painter.setFont(font);
		painter.setPen(QColor(255,102,156));
		QFontMetrics fontMetrics(font);
		const QString str = QString::number(i+1);
		painter.drawStaticText((image.width()-fontMetrics.width(str))/2, (image.height()-fontMetrics.height())/2, QStaticText(str));
		m_materials[static_cast<size_t>(GameMaterialId::Block0)+i] = m_pRenderer->createMaterial(image);
	}

	for (size_t i = 0; i < static_cast<size_t>(GameMaterialId::ButtonCount)-static_cast<size_t>(GameMaterialId::ButtonStart); ++i) {
		QImage image(":/res/button.png");
		QPainter painter(&image);
		QFont font = painter.font();
		font.setPixelSize(52);
		font.setBold(true);
		painter.setFont(font);
		painter.setPen(QColor(0,0,0));
		QFontMetrics fontMetrics(font);
		const QString str = buttonLabels[i];
		painter.drawStaticText((image.width()-fontMetrics.width(str))/2, (image.height()-fontMetrics.height())/2, QStaticText(str));
		m_materials[static_cast<size_t>(GameMaterialId::ButtonStart)+i] = m_pRenderer->createMaterial(image);
	}

	m_meshes[static_cast<size_t>(GameMeshId::QuadXY)] = m_pRenderer->createMesh(quadXYVertices, quadXYIndices);
	m_meshes[static_cast<size_t>(GameMeshId::Block)] = m_pRenderer->createMesh(blockVertices, blockIndices);
	m_meshes[static_cast<size_t>(GameMeshId::Button)] = m_pRenderer->createMesh(buttonVertices, buttonIndices);

	auto pGameScene = new Game15SceneGame(shared_from_this());
	m_scenes[static_cast<size_t>(GameSceneId::Game)] = std::unique_ptr<Game15AbstractScene>(pGameScene);

	auto pMenuScene = new Game15SceneMenu(shared_from_this());
	m_scenes[static_cast<size_t>(GameSceneId::Menu)] = std::unique_ptr<Game15AbstractScene>(pMenuScene);

	auto pSelectLevelScene = new Game15SceneSelectLevel(shared_from_this());
	m_scenes[static_cast<size_t>(GameSceneId::SelectLevel)] = std::unique_ptr<Game15AbstractScene>(pSelectLevelScene);

	auto pVictoryScene = new Game15SceneVictory(shared_from_this());
	m_scenes[static_cast<size_t>(GameSceneId::Victory)] = std::unique_ptr<Game15AbstractScene>(pVictoryScene);

	pGameScene->initialize(4);
	setCurrentScene(GameSceneId::Game);
}

Game15::~Game15()
{
	int i =123;
}

graphics::MaterialPtr Game15::material(GameMaterialId id) const
{
	return m_materials[static_cast<size_t>(id)];
}

graphics::MeshPtr Game15::mesh(GameMeshId id) const
{
	return m_meshes[static_cast<size_t>(id)];
}

void Game15::initGame(int32_t gameConst)
{
	auto pGameScene = std::dynamic_pointer_cast<Game15SceneGame>(m_scenes[static_cast<size_t>(GameSceneId::Game)]);
	if (pGameScene)
		pGameScene->initialize(gameConst);
}

void Game15::exit()
{
	QApplication::exit(0);
}

void Game15::setCurrentScene(GameSceneId id)
{
	m_currentSceneId = id;
	m_scenes[static_cast<size_t>(m_currentSceneId)]->activate();
}

Game15Ptr Game15::createGame15(graphics::ControllerPtr pRenderer)
{
	auto pGame15 = Game15Ptr(new Game15(pRenderer));
	pGame15->initialize();
	return pGame15;
}

void Game15::update(uint64_t time, uint32_t dt)
{
	m_scenes[static_cast<size_t>(m_currentSceneId)]->update(time, dt);
}

void Game15::mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton)
{
	m_scenes[static_cast<size_t>(m_currentSceneId)]->mouseMove(x, y, dx, dy, leftButton, righrButton);
}

void Game15::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
	m_scenes[static_cast<size_t>(m_currentSceneId)]->mouseClick(x, y, leftButton, righrButton);
}

void Game15::mouseWheel(int32_t dir)
{
	m_scenes[static_cast<size_t>(m_currentSceneId)]->mouseWheel(dir);
}

}
