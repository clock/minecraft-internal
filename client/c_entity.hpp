#pragma once
#include <string>
#include "java.hpp"
#include <string>

class c_entity {
public:
	c_entity(jobject player_instance);
	double get_x();
	double get_y();
	double get_z();
	float get_yaw();
	float get_pitch();
	float get_prev_yaw();
	float get_prev_pitch();
	void set_yaw(float yaw);
	void set_pitch(float pitch);
	void set_prev_yaw(float yaw);
	void set_prev_pitch(float pitch);
	double get_prev_x();
	double get_prev_y();
	double get_prev_z();
	int get_id();
	bool is_valid();
	bool is_dead();
	bool is_sneaking();
	float get_health();
	float get_max_health();
	int get_hurt_time_resistant();
	bool is_invulnerable();
	bool is_velocity_changed();
	double get_motion_x();
	std::string get_name();

	void cleanup();

	jclass get_class();
private:
	jobject player_instance;
};