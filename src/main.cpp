#include <napi.h>

#include "Core/App.h"
#include "Core/Log.h"

void Run(const Napi::CallbackInfo& info)
{
	std::string appName = "";
	if (info.Length() != 1 && !info[0].IsObject())
	{
		Napi::TypeError::New(info.Env(), "run needs a config object");
		return;
	}
	
	Napi::Object config  = info[0].As<Napi::Object>();
	appName = config.Get("name").ToString();
	
	auto app = new App(info.Env(), appName);
	app->SetMousePressedCallback(config.Get("onMousePressed").As<Napi::Function>());
	app->SetMouseMovedCallback(config.Get("onMouseMoved").As<Napi::Function>());
	app->SetKeyPressedCallback(config.Get("onKeyPressed").As<Napi::Function>());
	app->SetWindowResizedCallback(config.Get("onWindowResized").As<Napi::Function>());
	app->SetWindowClosedCallback(config.Get("onWindowClosed").As<Napi::Function>());

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
