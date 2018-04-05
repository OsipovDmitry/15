#include <iostream>

#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsmesh.h"
#include "graphicsmaterial.h"

#include "shaderdata.h"

namespace graphics {

Controller::Controller(QOpenGLContext* pGLContext) :
	m_pGLContext(pGLContext),
	m_pCurrentScene(),
	m_selectColorTexture(0),
	m_selectDepthRenderbuffer(0),
	m_selectFramebuffer(0)
{
	m_programs[static_cast<int32_t>(ProgramId::Rectangle)] = createProgram(rectangleVertexShader, rectangleFragmentShader);
	m_programs[static_cast<int32_t>(ProgramId::Object)] = createProgram(objectVertexShader, objectFragmentShader);
	m_programs[static_cast<int32_t>(ProgramId::Select)] = createProgram(selectVertexShader, selectFragmentShader);
}

Controller::~Controller()
{
	auto funcs = functions();

	for (auto programId: m_programs)
		funcs->glDeleteProgram(programId);
}

QOpenGLFunctions_3_3_Core*Controller::functions() const
{
	return m_pGLContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

const int32_t *Controller::viewport() const
{
	return static_cast<const int32_t*>(m_viewport);
}

GLuint Controller::program(ProgramId id) const
{
	return m_programs[static_cast<size_t>(id)];
}

GLuint Controller::selectFramebuffer() const
{
	return m_selectFramebuffer;
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
	auto funcs = functions();

	funcs->glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
	funcs->glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
	funcs->glClearDepth(1.0f);
	funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	auto funcs = functions();

	if (m_selectFramebuffer) {
		funcs->glBindFramebuffer(GL_FRAMEBUFFER, m_selectFramebuffer);
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
		funcs->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
		funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
		funcs->glDeleteFramebuffers(1, &m_selectFramebuffer);
	}

	if (m_selectColorTexture) {
		funcs->glBindTexture(GL_TEXTURE_2D, 0);
		funcs->glDeleteTextures(1, &m_selectColorTexture);
	}

	if (m_selectDepthRenderbuffer) {
		funcs->glBindRenderbuffer(GL_RENDERBUFFER, 0);
		funcs->glDeleteRenderbuffers(1, &m_selectDepthRenderbuffer);
	}

	funcs->glGenRenderbuffers(1, &m_selectDepthRenderbuffer);
	funcs->glBindRenderbuffer(GL_RENDERBUFFER, m_selectDepthRenderbuffer);
	funcs->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

	funcs->glGenTextures(1, &m_selectColorTexture);
	funcs->glBindTexture(GL_TEXTURE_2D, m_selectColorTexture);
	funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	funcs->glGenFramebuffers(1, &m_selectFramebuffer);
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, m_selectFramebuffer);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_selectColorTexture, 0);
	funcs->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_selectDepthRenderbuffer);
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Controller::createProgram(const std::string& vShaderData, const std::string& fShaderData)
{
	auto funcs = functions();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	auto pVertexText = &(vShaderData[0]);
	auto pFragmentText = &(fShaderData[0]);

	vertex = funcs->glCreateShader(GL_VERTEX_SHADER);
	funcs->glShaderSource(vertex, 1, &pVertexText, NULL);
	funcs->glCompileShader(vertex);
	funcs->glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		funcs->glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	fragment = funcs->glCreateShader(GL_FRAGMENT_SHADER);
	funcs->glShaderSource(fragment, 1, &pFragmentText, NULL);
	funcs->glCompileShader(fragment);
	funcs->glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		funcs->glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	auto programId = funcs->glCreateProgram();
	funcs->glAttachShader(programId, vertex);
	funcs->glAttachShader(programId, fragment);
	funcs->glLinkProgram(programId);
	funcs->glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if(!success)
	{
		funcs->glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	funcs->glDeleteShader(vertex);
	funcs->glDeleteShader(fragment);

	return programId;
}

}
