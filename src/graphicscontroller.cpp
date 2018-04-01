#include <QGLContext>
#include <QGLFunctions>

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsmesh.h"
#include "graphicsmaterial.h"

namespace graphics {

Controller::Controller(QGLContext* pGLContext) :
	m_pGLContext(pGLContext),
	m_pCurrentScene()
{
	glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

Controller::~Controller()
{
	int i = 123;
}

QGLContext *Controller::context() const
{
	return m_pGLContext;
}

const int32_t *Controller::viewport() const
{
	return static_cast<const int32_t*>(m_viewport);
}

ScenePtr Controller::createScene()
{
	return ScenePtr(new Scene(shared_from_this()));
}

MaterialPtr Controller::createMaterial(const std::string& filename)
{
	return MaterialPtr(new Material(shared_from_this(), filename));
}

MaterialPtr Controller::createMaterial(const QImage& image)
{
	return MaterialPtr(new Material(shared_from_this(), image));
}

MeshPtr Controller::createMesh(const std::vector<float>& vertices, const std::vector<uint32_t> indices)
{
	return MeshPtr(new Mesh(shared_from_this(), vertices, indices));
}

void Controller::setCurrentScene(ScenePtr pScene)
{
	m_pCurrentScene = pScene;
}

void Controller::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto pCurrentScene = m_pCurrentScene.lock();
	if (pCurrentScene)
		pCurrentScene->render();
}

void Controller::resize(int32_t width, int32_t height)
{
	m_viewport[0] = 0;
	m_viewport[1] = 0;
	m_viewport[2] = width;
	m_viewport[3] = height;

	glViewport(0, 0, width, height);
}

}
