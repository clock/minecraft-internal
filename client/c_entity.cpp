#include "c_entity.hpp"
#include "mappings.hpp"

c_entity::c_entity(jobject player_instance) {
	this->player_instance = player_instance;
}

void c_entity::cleanup() {
	java_instance->env->DeleteLocalRef(this->player_instance);
}

jclass c_entity::get_class() {
	return java_instance->get_class(mappings["entity"].class_name);
}

double c_entity::get_x() {

	jclass entity_class = get_class();
	jfieldID x = java_instance->env->GetFieldID(entity_class, mappings["entity"].fields["x"].field_name, mappings["entity"].fields["x"].field_sig);
	auto buf = java_instance->env->GetDoubleField(this->player_instance, x);

	return buf;
}

double c_entity::get_y() {
	jclass entity_class = get_class();
	jfieldID y = java_instance->env->GetFieldID(entity_class, mappings["entity"].fields["y"].field_name, mappings["entity"].fields["y"].field_sig);
	auto buf = java_instance->env->GetDoubleField(this->player_instance, y);

	return buf;
}

double c_entity::get_z() {
	jclass entity_class = get_class();
	jfieldID z = java_instance->env->GetFieldID(entity_class, mappings["entity"].fields["z"].field_name, mappings["entity"].fields["z"].field_sig);
	auto buf = java_instance->env->GetDoubleField(this->player_instance, z);

	return buf;
}

c_entity::~c_entity() {
	java_instance->env->DeleteLocalRef(this->player_instance);
}