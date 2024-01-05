#include "c_active_render_info.hpp"
#include "mappings.hpp"
#include <iostream>

c_active_render_info::c_active_render_info() {
}

jclass c_active_render_info::get_class() {
	return java_instance->get_class(mappings["active_render_info"].class_name);
}

void c_active_render_info::cleanup() {
}

std::unique_ptr<GLfloat[]> c_active_render_info::get_modelview_matrix() {
	auto modelview = std::make_unique<GLfloat[]>(16);
	jclass active_render_info_cls = this->get_class();
	jfieldID modelview_field = java_instance->env->GetStaticFieldID(active_render_info_cls, mappings["active_render_info"].fields["modelview"].field_name, mappings["active_render_info"].fields["modelview"].field_sig);
	jobject modelview_obj = java_instance->env->GetStaticObjectField(active_render_info_cls, modelview_field);
	jclass float_buffer = java_instance->get_class("java.nio.FloatBuffer");
	jmethodID get_md = java_instance->env->GetMethodID(float_buffer, "get", "(I)F");
	for (int i = 0; i < 16; ++i) {
		modelview[i] = java_instance->env->CallFloatMethod(modelview_obj, get_md, i);
	}
	//java_instance->env->DeleteLocalRef(float_buffer); might have to delete this not sure, i doubt it since its a class but we'll see
	java_instance->env->DeleteLocalRef(modelview_obj);

	return modelview;
}

std::unique_ptr<GLfloat[]> c_active_render_info::get_projection_matrix() {
	auto projection = std::make_unique<GLfloat[]>(16);
	jclass active_render_info_cls = this->get_class();
	jfieldID projection_field = java_instance->env->GetStaticFieldID(active_render_info_cls, mappings["active_render_info"].fields["projection"].field_name, mappings["active_render_info"].fields["projection"].field_sig);
	jobject projection_obj = java_instance->env->GetStaticObjectField(active_render_info_cls, projection_field);
	jclass float_buffer = java_instance->get_class("java.nio.FloatBuffer");
	jmethodID get_md = java_instance->env->GetMethodID(float_buffer, "get", "(I)F");
	for (int i = 0; i < 16; ++i) {
		projection[i] = java_instance->env->CallFloatMethod(projection_obj, get_md, i);
	}
	//java_instance->env->DeleteLocalRef(float_buffer); might have to delete this not sure, i doubt it since its a class but we'll see
	java_instance->env->DeleteLocalRef(projection_obj);

	return projection;
}

std::unique_ptr<GLint[]> c_active_render_info::get_viewport() {
	auto viewport = std::make_unique<GLint[]>(16);
	jclass active_render_info_cls = this->get_class();
	jfieldID viewport_field = java_instance->env->GetStaticFieldID(active_render_info_cls, mappings["active_render_info"].fields["viewport"].field_name, mappings["active_render_info"].fields["viewport"].field_sig);
	jobject viewport_obj = java_instance->env->GetStaticObjectField(active_render_info_cls, viewport_field);
	jclass int_buffer = java_instance->get_class("java.nio.IntBuffer");
	jmethodID get_md = java_instance->env->GetMethodID(int_buffer, "get", "(I)I");
	for (int i = 0; i < 16; ++i) {
		viewport[i] = java_instance->env->CallIntMethod(viewport_obj, get_md, i);
	}
	//java_instance->env->DeleteLocalRef(int_buffer); might have to delete this not sure, i doubt it since its a class but we'll see
	java_instance->env->DeleteLocalRef(viewport_obj);

	return viewport;
}