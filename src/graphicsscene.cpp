#include "glm/gtc/matrix_transform.hpp"

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsscenelayer.h"

namespace graphics {

Scene::~Scene()
{
}

void Scene::clear()
{
	for (auto pLayer: m_layers)
		pLayer->clear();
}

SceneLayerPtr Scene::layer(SceneLayerId id)
{
	return m_layers[static_cast<int32_t>(id)];
}

void Scene::setViewMatrix(const glm::mat4x4& value)
{
	m_layers[static_cast<int32_t>(SceneLayerId::Objects)]->setViewMatrix(value);
}


Scene::Scene(ControllerPtr pController) :
	m_pController(pController)
{
	m_layers[static_cast<size_t>(SceneLayerId::Background)] = SceneLayerPtr(new SceneLayer(pController, ProgramId::Rectangle));
	m_layers[static_cast<size_t>(SceneLayerId::Objects)] = SceneLayerPtr(new SceneLayer(pController, ProgramId::Object));
	m_layers[static_cast<size_t>(SceneLayerId::GUI)] = SceneLayerPtr(new SceneLayer(pController, ProgramId::Rectangle));
}

void Scene::render() const
{
	for (int32_t i = 0; i < static_cast<int32_t>(SceneLayerId::Count); ++i) {
		auto id = static_cast<SceneLayerId>(i);
		m_layers[i]->setProjMatrix(projMatrix(id));
		m_layers[i]->enableDepthTest(depthTestState(id));
		m_layers[i]->render();
	}
}

glm::mat4x4 Scene::projMatrix(SceneLayerId layer) const
{
	auto viewport = m_pController->viewport();

	switch (layer) {
		case SceneLayerId::Background : return glm::mat4x4();
		case SceneLayerId::Objects: return glm::perspective(0.4f*glm::pi<float>(), (float)viewport[2]/(float)viewport[3], 0.5f, 100.0f);
		case SceneLayerId::GUI: {
			const auto aspect = (float)viewport[2]/(float)viewport[3];
			if (aspect >= 1.0f)
				return glm::ortho(-aspect, aspect, -1.0f, 1.0f);
			else
				return glm::ortho(-1.0f, 1.0f, -1.0f/aspect, 1.0f/aspect);
		}
		default: break;
	}
	return glm::mat4x4();
}

bool Scene::depthTestState(SceneLayerId layer) const
{
	switch (layer) {
		case SceneLayerId::Background : return false;
		case SceneLayerId::Objects: return true;
		case SceneLayerId::GUI: return false;
		default: break;
	}
	return false;
}

}
