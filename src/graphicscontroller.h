#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>
#include <vector>
#include <string>

#include <QGL>

class QOpenGLContext;
class QOpenGLFunctions_3_3_Core;
class QImage;

namespace game {
class GameWidget;
}

namespace graphics {

class Scene;
using ScenePtr = std::shared_ptr<Scene>;
using SceneWPtr = std::weak_ptr<Scene>;

class Material;
using MaterialPtr = std::shared_ptr<Material>;

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

enum class ProgramId : int32_t {
	Rectangle,
	Object,
	Select,
	Count
};

class Controller : public std::enable_shared_from_this<Controller>
{
public:
	Controller(QOpenGLContext* pGLContext);
	~Controller();

	QOpenGLFunctions_3_3_Core *functions() const;
	const int32_t* viewport() const;
	GLuint program(ProgramId id) const;
	GLuint selectFramebuffer() const;

	ScenePtr createScene();
	MaterialPtr createMaterial(const std::string& filename);
	MaterialPtr createMaterial(const QImage& image);
	MeshPtr createMesh(const std::vector<float>& vertices, const std::vector<uint32_t> indices);

	void setCurrentScene(ScenePtr pScene);

private:
	QOpenGLContext *m_pGLContext;
	std::array<GLuint, static_cast<size_t>(ProgramId::Count)> m_programs;
	GLuint m_selectFramebuffer, m_selectDepthRenderbuffer, m_selectColorTexture;
	SceneWPtr m_pCurrentScene;
	int32_t m_viewport[4];

	void render();
	void resize(int32_t width, int32_t height);

	GLuint createProgram(const std::string& vShaderData, const std::string& fShaderData);

	friend class game::GameWidget;
};

}

#endif // GRAPHICSCONTROLLER_H
