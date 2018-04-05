#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLContext>

#include "gamewidget.h"
#include "graphicscontroller.h"
#include "abstractgame.h"

#include <iostream>

namespace game {

GameWidget::GameWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	m_pTimer(new QTimer(this)),
	m_pRenderer(),
	m_pGame(),
	m_startTime(QDateTime::currentMSecsSinceEpoch()),
	m_lastUpdateTime(0)
{
	QSurfaceFormat format;
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setSamples(16);
	setFormat(format);

	connect(m_pTimer, SIGNAL(timeout()), SLOT(update()));
	m_pTimer->start(16);

	resize(512, 512);
}

GameWidget::~GameWidget()
{
	int i = 123;
}

graphics::ControllerPtr GameWidget::graphicsController() const
{
	return m_pRenderer;
}

void GameWidget::setGame(AbstractGamePtr pGame)
{
	m_pGame = pGame;
}

void GameWidget::initializeGL()
{
	m_pRenderer = std::make_shared<graphics::Controller>(context());
}

void GameWidget::resizeGL(int w, int h)
{
	m_pRenderer->resize(w, h);
}

void GameWidget::paintGL()
{
	uint64_t time = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch() - m_startTime);
	uint32_t dt = time - m_lastUpdateTime;
	m_lastUpdateTime = time;

	auto pGame = m_pGame.lock();
	if (pGame)
		pGame->update(time, dt);

	m_pRenderer->render();
}

void GameWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
	int32_t dx = pEvent->x() - m_mouseX;
	int32_t dy = pEvent->y() - m_mouseY;
	m_mouseX = pEvent->x();
	m_mouseY = pEvent->y();

	auto pGame = m_pGame.lock();
	if (pGame)
		pGame->mouseMove(m_mouseX, m_mouseY, dx, dy, pEvent->buttons() & Qt::LeftButton, pEvent->buttons() & Qt::RightButton);
}

void GameWidget::mousePressEvent(QMouseEvent* pEvent)
{
	m_mouseX = pEvent->x();
	m_mouseY = pEvent->y();

	context()->makeCurrent(context()->surface());
	auto pGame = m_pGame.lock();
	if (pGame)
		pGame->mouseClick(m_mouseX, m_mouseY, pEvent->buttons() & Qt::LeftButton, pEvent->buttons() & Qt::RightButton);
}

void GameWidget::wheelEvent(QWheelEvent* pEvent)
{
	auto pGame = m_pGame.lock();
	if (pGame)
		pGame->mouseWheel(pEvent->angleDelta().y() / 120);
}

}
