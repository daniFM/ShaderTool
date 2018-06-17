/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#include <Canvas3D.hpp>
#include <GLTexture.hpp>

namespace st
{
	Canvas3D::Canvas3D(Widget *parent) : nanogui::GLCanvas(parent)
	{
		using namespace nanogui;

		setShader();

		MatrixXu indices(3, 12); /* Draw a cube */
		indices.col(0) << 0, 1, 3;
		indices.col(1) << 3, 2, 1;
		indices.col(2) << 3, 2, 6;
		indices.col(3) << 6, 7, 3;
		indices.col(4) << 7, 6, 5;
		indices.col(5) << 5, 4, 7;
		indices.col(6) << 4, 5, 1;
		indices.col(7) << 1, 0, 4;
		indices.col(8) << 4, 0, 3;
		indices.col(9) << 3, 7, 4;
		indices.col(10) << 5, 6, 2;
		indices.col(11) << 2, 1, 5;

		MatrixXf positions(3, 8);
		positions.col(0) << -1, 1, 1;
		positions.col(1) << -1, 1, -1;
		positions.col(2) << 1, 1, -1;
		positions.col(3) << 1, 1, 1;
		positions.col(4) << -1, -1, 1;
		positions.col(5) << -1, -1, -1;
		positions.col(6) << 1, -1, -1;
		positions.col(7) << 1, -1, 1;

		MatrixXf colors(3, 12);
		colors.col(0) << 1, 0, 0;
		colors.col(1) << 0, 1, 0;
		colors.col(2) << 1, 1, 0;
		colors.col(3) << 0, 0, 1;
		colors.col(4) << 1, 0, 1;
		colors.col(5) << 0, 1, 1;
		colors.col(6) << 1, 1, 1;
		colors.col(7) << 0.5, 0.5, 0.5;
		colors.col(8) << 1, 0, 0.5;
		colors.col(9) << 1, 0.5, 0;
		colors.col(10) << 0.5, 1, 0;
		colors.col(11) << 0.5, 1, 0.5;

		mShader.uploadIndices(indices);

		mShader.uploadAttrib("position", positions);
		mShader.uploadAttrib("color", colors);
	}

	void Canvas3D::drawGL()
	{
		using namespace nanogui;

		mShader.bind();

		Matrix4f mvp;
		mvp.setIdentity();
		float fTime = (float)glfwGetTime() / 1000000000;
		mvp.topLeftCorner<3, 3>() = Eigen::Matrix3f
		(
			Eigen::AngleAxisf(mRotation[0] * fTime, Vector3f::UnitX()) *
			Eigen::AngleAxisf(mRotation[1] * fTime, Vector3f::UnitY()) *
			Eigen::AngleAxisf(mRotation[2] * fTime, Vector3f::UnitZ())
		) * 0.25f;

		mShader.setUniform("modelViewProj", mvp);

		glEnable(GL_DEPTH_TEST);
		/* Draw 12 triangles starting at index 0 */
		mShader.drawIndexed(GL_TRIANGLES, 0, 12);
		glDisable(GL_DEPTH_TEST);

	}

	void Canvas3D::setShader()
	{
		mShader.init(
			/* An identifying name */
			"a_simple_shader",

			/* Vertex shader */
			"#version 330\n"
			"uniform mat4 modelViewProj;\n"
			"in vec3 position;\n"
			"in vec3 color;\n"
			"out vec4 frag_color;\n"
			"void main() {\n"
			"    frag_color = 3.0 * modelViewProj * vec4(color, 1.0);\n"
			"    gl_Position = modelViewProj * vec4(position, 1.0);\n"
			"}",

			/* Fragment shader */
			"#version 330\n"
			"out vec4 color;\n"
			"in vec4 frag_color;\n"
			"void main() {\n"
			"    color = frag_color;\n"
			"}"
		);

		mShader.bind();
	}

	void Canvas3D::setShader(shared_ptr<st::Shader> shader)
	{
		string code = *shader->getCode().get();
		string vertex_shader_code = code.substr(0, code.find_last_of("#"));
		string fragment_shader_code = code.substr(code.find_last_of("#"));

		mShader.init(shader->getTitle(), vertex_shader_code, fragment_shader_code);

		mShader.bind();
	}
}