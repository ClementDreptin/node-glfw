#pragma once

#include <napi.h>

#include "Core/Utils.h"
#include "Events/AppEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Core/Window.h"

class App
{
public:
	App(Napi::Env env, const std::string& name = "");
	virtual ~App();

	void Run();

	void OnEvent(Event& e);

	inline static App& Get() { return *s_Instance; }
	inline Window& GetWindow() { return *m_Window; }

	inline void SetMousePressedCallback(Napi::Function callback) { m_MousePressedCallback = callback; }
	inline void SetMouseMovedCallback(Napi::Function callback) { m_MouseMovedCallback = callback; }
	inline void SetKeyPressedCallback(Napi::Function callback) { m_KeyPressedCallback = callback; }
	inline void SetWindowResizedCallback(Napi::Function callback) { m_WindowResizedCallback = callback; }
	inline void SetWindowClosedCallback(Napi::Function callback) { m_WindowClosedCallback = callback; }

	void Close();
private:
	Scope<Window> m_Window;
	bool m_Running = true;
	bool m_Minimized = false;

	Napi::Env m_Env;
	Napi::Function m_MousePressedCallback;
	Napi::Function m_MouseMovedCallback;
	Napi::Function m_KeyPressedCallback;
	Napi::Function m_WindowResizedCallback;
	Napi::Function m_WindowClosedCallback;

	static App* s_Instance;

	bool OnMousePressed(MouseButtonPressedEvent& event);
	bool OnMouseMoved(MouseMovedEvent& event);
	bool OnKeyPressed(KeyPressedEvent& event);
	bool OnWindowResized(WindowResizeEvent& event);
	bool OnWindowClosed(WindowCloseEvent& event);
};
