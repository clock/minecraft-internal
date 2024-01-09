#include "renderer.hpp"

void renderer::gl::draw_outlined_box(BoundingBox box) {
	glBegin(3);
	glVertex3f(box.minX, box.minY, box.minZ);
	glVertex3f(box.maxX, box.minY, box.minZ);
	glVertex3f(box.maxX, box.minY, box.maxZ);
	glVertex3f(box.minX, box.minY, box.maxZ);
	glVertex3f(box.minX, box.minY, box.minZ);
	glEnd();

	glBegin(3);
	glVertex3f(box.minX, box.maxY, box.minZ);
	glVertex3f(box.maxX, box.maxY, box.minZ);
	glVertex3f(box.maxX, box.maxY, box.maxZ);
	glVertex3f(box.minX, box.maxY, box.maxZ);
	glVertex3f(box.minX, box.maxY, box.minZ);
	glEnd();

	glBegin(1);
	glVertex3f(box.minX, box.minY, box.minZ);
	glVertex3f(box.minX, box.maxY, box.minZ);
	glVertex3f(box.maxX, box.minY, box.minZ);
	glVertex3f(box.maxX, box.maxY, box.minZ);
	glVertex3f(box.maxX, box.minY, box.maxZ);
	glVertex3f(box.maxX, box.maxY, box.maxZ);
	glVertex3f(box.minX, box.minY, box.maxZ);
	glVertex3f(box.minX, box.maxY, box.maxZ);
	glEnd();
}