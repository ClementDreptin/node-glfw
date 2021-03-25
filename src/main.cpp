#include "StdIncludes.h"
#include <napi.h>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Run(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	if (info.Length() > 0)
	{
		Napi::TypeError::New(env, "run does not take any argument").ThrowAsJavaScriptException();
		return;
	}

	GLFWwindow* window;

	if (!glfwInit())
		return;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "run"),
				Napi::Function::New(env, Run));
	return exports;
}

NODE_API_MODULE(node_glfw, Init)
