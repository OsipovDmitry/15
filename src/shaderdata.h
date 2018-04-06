#ifndef SHADERDATA_H
#define SHADERDATA_H

#include <string>

const std::string rectangleVertexShader(
	"#version 330 core\n"

	"layout (location = 0) in vec3 a_position;\n"
	"layout (location = 1) in vec3 a_normal;\n"
	"layout (location = 2) in vec2 a_texcoord;\n"

	"uniform mat4x4 u_modelMatrix;\n"
	"uniform mat4x4 u_viewMatrix;\n"
	"uniform mat4x4 u_projMatrix;\n"
	"uniform mat3x3 u_normalMatrix;\n"

	"out vec2 v_texcoord;\n"

	"void main()\n"
	"{\n"
	"	gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(a_position, 1.0);\n"
	"	v_texcoord = a_texcoord;\n"
	"}\n"
);

const std::string rectangleFragmentShader(
	"#version 330 core\n"

	"uniform sampler2D u_texture;\n"

	"in vec2 v_texcoord;\n"

	"out vec4 o_color;\n"

	"void main()\n"
	"{\n"
	"	o_color = texture(u_texture, v_texcoord);\n"
	"}\n"
);

const std::string objectVertexShader(
	"#version 330 core\n"

	"layout (location = 0) in vec3 a_position;\n"
	"layout (location = 1) in vec3 a_normal;\n"
	"layout (location = 2) in vec2 a_texcoord;\n"

	"uniform mat4x4 u_modelMatrix;\n"
	"uniform mat4x4 u_viewMatrix;\n"
	"uniform mat4x4 u_projMatrix;\n"
	"uniform mat3x3 u_normalMatrix;\n"
	"uniform vec4 u_lightPos = vec4(0.0, 2.0, 0.0, 1.0);\n"

	"out vec3 v_normal;\n"
	"out vec3 v_light;\n"
	"out vec2 v_texcoord;\n"

	"void main()\n"
	"{\n"
	"   vec4 worldPos = u_modelMatrix * vec4(a_position, 1.0);\n"
	"	gl_Position = u_projMatrix * u_viewMatrix * worldPos;\n"
	"	v_normal = u_normalMatrix * a_normal;\n"
	"	v_texcoord = a_texcoord;\n"
	"   v_light = normalize(u_lightPos.xyz - worldPos.xyz);\n"
	"}\n"
);

const std::string objectFragmentShader(
	"#version 330 core\n"

	"uniform sampler2D u_texture;\n"

	"in vec3 v_normal;\n"
	"in vec3 v_light;\n"
	"in vec2 v_texcoord;\n"

	"out vec4 o_color;\n"

	"void main()\n"
	"{\n"
	"	vec3 normal = normalize(v_normal);\n"
	"	vec3 toLight = normalize(v_light);\n"
	"	o_color = max(0.4, dot(normal, toLight)) * texture(u_texture, v_texcoord);\n"
	"}\n"
);

const std::string selectVertexShader(
	"#version 330 core\n"

	"layout (location = 0) in vec3 a_position;\n"
	"layout (location = 1) in vec3 a_normal;\n"
	"layout (location = 2) in vec2 a_texcoord;\n"

	"uniform mat4x4 u_modelMatrix;\n"
	"uniform mat4x4 u_viewMatrix;\n"
	"uniform mat4x4 u_projMatrix;\n"

	"void main()\n"
	"{\n"
	"	gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(a_position, 1.0);\n"
	"}\n"
);

const std::string selectFragmentShader(
	"#version 330 core\n"

	"uniform vec4 u_color;\n"

	"out vec4 o_color;\n"

	"void main()\n"
	"{\n"
	"	o_color = u_color;\n"
	"}\n"
);

#endif // SHADERDATA_H
