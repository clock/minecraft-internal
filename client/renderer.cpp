#include "renderer.hpp"

void renderer::gl::draw_outlined_box(BoundingBox box) {
	glBegin(3);
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.maxZ));
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.maxZ));
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.minZ));
	glEnd();

	glBegin(3);
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.maxZ));
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.maxZ));
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.minZ));
	glEnd();

	glBegin(1);
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.minZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.maxZ));
	glVertex3f(static_cast<GLfloat>(box.maxX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.maxZ));
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.minY), static_cast<GLfloat>(box.maxZ));
	glVertex3f(static_cast<GLfloat>(box.minX), static_cast<GLfloat>(box.maxY), static_cast<GLfloat>(box.maxZ));
	glEnd();
}