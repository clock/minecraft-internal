#include "c_minecraft.hpp"
#include "mappings.hpp"
#include "java.hpp"

jclass c_minecraft::get_class() {
	return java_instance->get_class(mappings["minecraft"].class_name);
}

jobject c_minecraft::get_instance() {
	jclass minecraft_class = this->get_class();
	jmethodID get_minecraft = java_instance->env->GetStaticMethodID(minecraft_class, mappings["minecraft"].methods["get_minecraft"].method_name, mappings["minecraft"].methods["get_minecraft"].method_sig);
	auto buf = java_instance->env->CallStaticObjectMethod(minecraft_class, get_minecraft);

	java_instance->env->DeleteLocalRef(minecraft_class);

	return buf;
}

c_entity c_minecraft::get_local_player() {
	jobject minecraft_instance = this->get_instance();
	jclass minecraft_class = this->get_class();

	jfieldID get_player = java_instance->env->GetFieldID(minecraft_class, mappings["minecraft"].fields["player"].field_name, mappings["minecraft"].fields["player"].field_sig);
	auto buf = java_instance->env->GetObjectField(minecraft_instance, get_player);

	java_instance->env->DeleteLocalRef(minecraft_instance);

	return c_entity(buf);
}