#include "Director.h"
#include "Scene.h"
#include "EventDispatcher.h"
#include "..\Application.h"

USING_NS_F2D

bool IsMin(Scene* a, Scene* b)
{
	return a->GetOrder() < b->GetOrder();
}

static Director* pInstance = 0;

Director* Director::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new Director();
	}

	return pInstance;
}

void Director::Update(const float& delta)
{
	vector<Scene*>::iterator ite = m_scene_list.begin();
	while (ite != m_scene_list.end())
	{
		if ((*ite)->IsVisible() == false)
		{
			(*ite)->Release();
			ite = m_scene_list.erase(ite);
		}
		else
		{
			++ite;
		}
	}

	for (int i = 0; i < m_scene_list.size(); ++i)
	{
		m_scene_list.at(i)->Update(delta);
	}

	stable_sort(m_scene_list.begin(), m_scene_list.end(), IsMin);

	for (int i = 0; i < m_scene_list.size(); ++i)
	{
		if (m_scene_list.at(i)->IsVisible())
		{
			m_scene_list.at(i)->Render();
		}
	}
}

void Director::Release()
{
	ClearScene();

	delete this;
	pInstance = 0;
}

void Director::PushScene(Scene* scene)
{
	m_scene_list.push_back(scene);
}

void Director::ReplaceScene(Scene* scene)
{
	PopScene();
	PushScene(scene);
}

void Director::PopScene()
{
	for (int i = m_scene_list.size() -1; i >= 0; i--)
	{
		if (m_scene_list.at(i)->IsVisible() == true)
		{
			m_scene_list.at(i)->SetVisible(false);
			break;
		}
	}

	/*if (m_scene_list.size() <= 0)
	{
		return;
	}

	m_scene_list.at(m_scene_list.size() - 1)->SetVisible(false);*/
}

void Director::ClearScene()
{
	vector<Scene*>::iterator ite = m_scene_list.begin();
	while (ite != m_scene_list.end())
	{
		(*ite)->Release();
		ite = m_scene_list.erase(ite);
	}
}

bool Director::IsPause()
{
	return Application::getInstance()->IsPause();
}

void Director::SetPause(bool bPause)
{
	Application::getInstance()->SetPause(bPause);
}

RECT Director::GetViewRect() const
{
	return WindowManager::getInstance()->getViewRect();
}

EventDispatcher* Director::getEventDispatcher()
{
	return EventDispatcher::getInstance();
}
