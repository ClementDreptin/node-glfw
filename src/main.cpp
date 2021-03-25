#include "StdIncludes.h"
#include <napi.h>

void Print(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	if (info.Length() < 1)
	{
		Napi::TypeError::New(env, "No argument provided").ThrowAsJavaScriptException();
		return;
	}

	if (!info[0].IsString())
	{
		Napi::TypeError::New(env, "Argument is not a string").ThrowAsJavaScriptException();
		return;
	}

	std::string text = info[0].As<Napi::String>().Utf8Value();

	std::cout << text << std::endl;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "print"),
				Napi::Function::New(env, Print));
	return exports;
}

NODE_API_MODULE(node_glfw, Init)
