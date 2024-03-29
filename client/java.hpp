#pragma once
#include <jni.h>
#include <jvmti.h>
#include <unordered_map>
#include <string>
#include <memory>

class JavaInstance {
private:
	std::unordered_map<std::string, jclass> classes;
public:
	// dont need to be smart pointers because they are managed by the jvm
	JNIEnv* env = nullptr;
	JavaVM* vm = nullptr;

	void get_loaded_classes() {
		jvmtiEnv* jvmti;

		if (vm->GetEnv((void**)&jvmti, JVMTI_VERSION_1_2) != JNI_OK)
			return;

		jclass lang_class = env->FindClass("java/lang/Class");
		jmethodID getName = env->GetMethodID(lang_class, "getName", "()Ljava/lang/String;");

		jint class_count;
		jclass* classes_ptr;

		jvmti->GetLoadedClasses(&class_count, &classes_ptr);

		for (int i = 0; i < class_count; i++) {
			jstring name = (jstring)env->CallObjectMethod(classes_ptr[i], getName);
			const char* name_chars = env->GetStringUTFChars(name, 0);

			printf("class: %s\n", name_chars);
			classes.emplace(std::make_pair(name_chars, classes_ptr[i]));

			env->ReleaseStringUTFChars(name, name_chars);
		}
	}

	jclass get_class(std::string class_name) {
		if (classes.contains(class_name))
			return classes[class_name];

		return nullptr;
	}
};

inline auto java_instance = std::make_unique<JavaInstance>();