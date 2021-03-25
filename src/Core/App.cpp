#include "Core/App.h"

#include "Core/Log.h"

App* App::s_Instance = nullptr;

App::App(const std::string& name)
{
	if (s_Instance)
	{
		LOG_ERROR("App already exists!");
		return;
	}
	s_Instance = this;

	m_Window = Scope<Window>(Window::Create(WindowProps(name)));
	m_Window->SetEventCallback(BIND_EVENT_FN(App::OnEvent));
}

App::~App() {}

void App::Close()
{
	m_Running = false;
}

void App::Run()
{
	while (m_Running)
		m_Window->OnUpdate();
}

void App::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));
}

bool App::OnWindowClose(WindowCloseEvent& event)
{
	Close();
	return true;
}

bool App::OnWindowResize(WindowResizeEvent& event)
{
	if (event.GetWidth() == 0 || event.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;

	return false;
}
