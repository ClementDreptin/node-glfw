#include <napi.h>

#include "Core/App.h"

void Run(const Napi::CallbackInfo& info)
{
	std::string appName = "";
	if (info.Length() == 1 && info[0].IsString())
		appName = info[0].ToString();
	
	auto app = new App(appName);

	app->Run();

	delete app;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{	
	exports.Set(Napi::String::New(env, "run"),
				Napi::Function::New(env, Run));
	return exports;
}

NODE_API_MODULE(node_glfw, Init)
