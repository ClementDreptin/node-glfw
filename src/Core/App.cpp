#include "Core/App.h"

#include "Core/Log.h"

App* App::s_Instance = nullptr;

App::App(Napi::Env env, const std::string& name)
	: m_Env(env)
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
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(App::OnMousePressed));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(App::OnMouseMoved));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(App::OnKeyPressed));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(App::OnWindowResized));
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClosed));
}

bool App::OnMousePressed(MouseButtonPressedEvent& event)
{
	Napi::Object object = Napi::Object::New(m_Env);
	object.Set("name", event.GetName());
	object.Set("button", event.GetMouseButton());
	
	m_MousePressedCallback.Call(m_Env.Global(), { object });
	return true;
}

bool App::OnMouseMoved(MouseMovedEvent& event)
{
	Napi::Object object = Napi::Object::New(m_Env);
	object.Set("name", event.GetName());
	object.Set("x", event.GetX());
	object.Set("y", event.GetY());

	m_MouseMovedCallback.Call(m_Env.Global(), { object });
	return true;
}

bool App::OnKeyPressed(KeyPressedEvent& event)
{
	Napi::Object object = Napi::Object::New(m_Env);
	object.Set("name", event.GetName());
	object.Set("keyCode", event.GetKeyCode());
	object.Set("repeatCount", event.GetRepeatCount());

	m_KeyPressedCallback.Call(m_Env.Global(), { object });
	return true;
}

bool App::OnWindowResized(WindowResizeEvent& event)
{
	if (event.GetWidth() == 0 || event.GetHeight() == 0)
		m_Minimized = true;

	m_Minimized = false;

	Napi::Object object = Napi::Object::New(m_Env);
	object.Set("name", event.GetName());
	object.Set("width", event.GetWidth());
	object.Set("height", event.GetHeight());

	m_WindowResizedCallback.Call(m_Env.Global(), { object });

	return true;
}

bool App::OnWindowClosed(WindowCloseEvent& event)
{
	Napi::Object object = Napi::Object::New(m_Env);
	object.Set("name", event.GetName());

	m_WindowClosedCallback.Call(m_Env.Global(), { object });

	Close();
	return true;
}
