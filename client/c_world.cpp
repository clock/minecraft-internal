#include "c_world.hpp"
#include "mappings.hpp"
#include <iostream>

c_world::c_world(jobject world_instance) {
	this->world_instance = world_instance;
}

void c_world::cleanup() {
	java_instance->env->DeleteLocalRef(this->world_instance);
}

jclass c_world::get_class() {
	return java_instance->get_class(mappings["world"].class_name);
}

std::vector<std::shared_ptr<c_entity>> c_world::get_players() {

	static jfieldID player_entities = java_instance->env->GetFieldID(this->get_class(), mappings["world"].fields["player_list"].field_name, mappings["world"].fields["player_list"].field_sig);

	jclass list_cls = java_instance->env->FindClass("java/util/List");
	static jmethodID to_array_md = java_instance->env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");

	java_instance->env->DeleteLocalRef(list_cls);

	std::vector<std::shared_ptr<c_entity>> res;

	jobject obj_player_entities = java_instance->env->GetObjectField(this->world_instance, player_entities);

	if (!obj_player_entities)
		return res;

	jobjectArray array_player_list = reinterpret_cast<jobjectArray>(java_instance->env->CallObjectMethod(obj_player_entities, to_array_md));

	if (!array_player_list)
		return res;

	size_t len = java_instance->env->GetArrayLength(array_player_list);

	for (int i = 0; i < len; ++i)
	{
		jobject player = java_instance->env->GetObjectArrayElement(array_player_list, i);
		res.push_back(std::make_shared<c_entity>(player));
	}

	java_instance->env->DeleteLocalRef(obj_player_entities);
	java_instance->env->DeleteLocalRef(array_player_list);

	return res;
}

c_world::~c_world() {
	java_instance->env->DeleteLocalRef(this->world_instance);
}