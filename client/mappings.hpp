#pragma once
#include <string>
#include <unordered_map>

struct field {
	const char* field_name;
	const char* field_sig;
};

struct method {
	const char* method_name;
	const char* method_sig;
};

struct klass {
	const char* class_name = "";
	std::unordered_map<std::string, field> fields;
	std::unordered_map<std::string, method> methods;
};

inline std::unordered_map<std::string, klass> mappings;

void init_mappings();
