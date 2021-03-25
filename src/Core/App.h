#pragma once

#include "Core/Utils.h"
#include "Events/AppEvent.h"
#include "Core/Window.h"

class App
{
public:
	App(const std::string& name = "");
	virtual ~App();

	void Run();

	void OnEvent(Event& e);

	inline static App& Get() { return *s_Instance; }
	inline Window& GetWindow() { return *m_Window; }

	void Close();
private:
	Scope<Window> m_Window;
	bool m_Running = true;
	bool m_Minimized = false;

	static App* s_Instance;

	bool OnWindowClose(WindowCloseEvent& event);
	bool OnWindowResize(WindowResizeEvent& event);
};
