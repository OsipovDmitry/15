#include "graphicscontroller.h"
#include "graphicsscene.h"

#include "game15abstractscene.h"
#include "game15.h"

namespace game {

Game15AbstractScene::~Game15AbstractScene()
{
	m_pGraphicsScene->clear();
}

Game15AbstractScene::Game15AbstractScene(Game15Ptr pGame15) :
	m_pGame15(pGame15),
	m_pGraphicsScene(pGame15->graphicsController()->createScene())
{

}

void Game15AbstractScene::activate()
{

}

void Game15AbstractScene::update(uint64_t time, uint32_t dt)
{
	(void)time;
	(void)dt;
}

void Game15AbstractScene::mouseClick(int32_t x, int32_t y, bool leftButton, bool righrButton)
{
	(void)x;
	(void)y;
	(void)leftButton;
	(void)righrButton;
}

void Game15AbstractScene::mouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, bool leftButton, bool righrButton)
{
	(void)x;
	(void)y;
	(void)dx;
	(void)dy;
	(void)leftButton;
	(void)righrButton;
}

void Game15AbstractScene::mouseWheel(int32_t dir)
{
	(void)dir;
}



}
