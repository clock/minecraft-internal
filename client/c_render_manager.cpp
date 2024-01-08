#include "c_render_manager.hpp"
#include "mappings.hpp"
#include <iostream>

c_render_manager::c_render_manager(jobject render_instance) {
	this->render_instance = render_instance;
}

jclass c_render_manager::get_class() {
	return java_instance->get_class(mappings["render_manager"].class_name);
}

void c_render_manager::cleanup() {
	java_instance->env->DeleteLocalRef(this->render_instance);
}

double c_render_manager::get_render_posx() {
	jclass render_manager_cls = this->get_class();
	jobject render_manager_obj = this->render_instance;
	jfieldID render_posx_field = java_instance->env->GetFieldID(render_manager_cls, mappings["render_manager"].fields["render_posx"].field_name, mappings["render_manager"].fields["render_posx"].field_sig);
	return java_instance->env->GetDoubleField(this->render_instance, render_posx_field);
}

double c_render_manager::get_render_posy() {
	jclass render_manager_cls = this->get_class();
	jfieldID render_posy_field = java_instance->env->GetFieldID(render_manager_cls, mappings["render_manager"].fields["render_posy"].field_name, mappings["render_manager"].fields["render_posy"].field_sig);
	return java_instance->env->GetDoubleField(this->render_instance, render_posy_field);
}

double c_render_manager::get_render_posz() {
	jclass render_manager_cls = this->get_class();
	jfieldID render_posz_field = java_instance->env->GetFieldID(render_manager_cls, mappings["render_manager"].fields["render_posz"].field_name, mappings["render_manager"].fields["render_posz"].field_sig);
	return java_instance->env->GetDoubleField(this->render_instance, render_posz_field);
}