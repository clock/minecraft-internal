#include "c_timer.hpp"
#include "mappings.hpp"

c_timer::c_timer(jobject timer_instance) {
	this->timer_instance = timer_instance;
}

jclass c_timer::get_class() {
	return java_instance->get_class(mappings["timer"].class_name);
}

float c_timer::get_render_partial_ticks() {
	jclass timer_cls = this->get_class();
	jfieldID render_partial_ticks_field = java_instance->env->GetFieldID(timer_cls, mappings["timer"].fields["render_partial_ticks"].field_name, mappings["timer"].fields["render_partial_ticks"].field_sig);
	return java_instance->env->GetFloatField(this->timer_instance, render_partial_ticks_field);
}

float c_timer::get_timer_speed() {
	jclass timer_cls = this->get_class();
	jfieldID timer_speed_field = java_instance->env->GetFieldID(timer_cls, mappings["timer"].fields["timer_speed"].field_name, mappings["timer"].fields["timer_speed"].field_sig);
	return java_instance->env->GetFloatField(this->timer_instance, timer_speed_field);
}

void c_timer::set_timer_speed(float speed) {
	jclass timer_cls = this->get_class();
	jfieldID timer_speed_field = java_instance->env->GetFieldID(timer_cls, mappings["timer"].fields["timer_speed"].field_name, mappings["timer"].fields["timer_speed"].field_sig);
	java_instance->env->SetFloatField(this->timer_instance, timer_speed_field, speed);
}