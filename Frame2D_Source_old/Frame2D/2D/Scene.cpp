#include "Scene.h"
#include "Element.h"
#include "ParticleSystem.h"
#include "Function.h"
#include "EventDispatcher.h"

USING_NS_F2D

bool IsMin(const Element* a, const Element* b)
{
	return a->GetOrder() < b->GetOrder();
}

Scene* Scene::Create()
{
	Scene* scene = new(std::nothrow) Scene();
	assert(scene && scene->Init() && "Scene Create Failed!");

	return scene;
}

void Scene::Add(Element* element)
{
	m_temp_list.push_back(element);
	element->BindScene(this);
}

void Scene::Add(Element* element, const int& order)
{
	Add(element);
	element->SetOrder(order);
}

void Scene::Remove(Element* element)
{
	vector<Element*>::iterator ite = m_element_list.begin();
	while (ite != m_element_list.end())
	{
		if (element == (*ite))
		{
			(*ite)->Release();
			m_element_list.erase(ite);
			break;
		}

		++ite;
	}
}

void Scene::Release()
{
	ClearTempList();
	Clear();
	ClearUpdateFunc();

	// 如果绑定了消息监听,将监听器解除
	EventDispatcher::getInstance()->RemoveByEventObj(this);

	delete this;
}

void Scene::Clear()
{
	vector<Element*>::iterator ite = m_element_list.begin();
	while (ite != m_element_list.end())
	{
		(*ite)->Release();
		ite = m_element_list.erase(ite);
	}

	vector<ParticleSystem*>::iterator sysIte = m_particleSys_list.begin();
	while (sysIte != m_particleSys_list.end())
	{
		(*sysIte)->Release();
		sysIte = m_particleSys_list.erase(sysIte);
	}
}

void Scene::ClearTempList()
{
	vector<Element*>::iterator ite = m_temp_list.begin();
	while (ite != m_temp_list.end())
	{
		(*ite)->Release();
		ite = m_temp_list.erase(ite);
	}
}

vector<Element*> Scene::GetElementList() const
{
	return m_element_list;
}

void Scene::Add(ParticleSystem* system)
{
	m_particleSys_list.push_back(system);
}

void Scene::Remove(ParticleSystem* system)
{
	vector<ParticleSystem*>::iterator sysIte = m_particleSys_list.begin();
	while (sysIte != m_particleSys_list.end())
	{
		if ((*sysIte) == system)
		{
			(*sysIte)->Release();
			m_particleSys_list.erase(sysIte);
			break;
		}
	}
}

void Scene::Update(const float& delta)
{
	for (int i = 0; i < m_updateFunc_list.size(); ++i)
	{
		m_updateFunc_list.at(i)->Update(delta);
	}

	if (m_temp_list.size() > 0)
	{
		for (int i = 0; i < m_temp_list.size(); i++)
		{
			m_element_list.push_back(m_temp_list.at(i));
		}

		m_temp_list.clear();
	}

	vector<Element*>::iterator ite = m_element_list.begin();
	while (ite != m_element_list.end())
	{
		if ((*ite)->IsVisible() == false)
		{
			(*ite)->Release();
			ite = m_element_list.erase(ite);
		}
		else
		{
			++ite;
		}
	}

	for (int i = 0; i < m_element_list.size(); ++i)
	{
		m_element_list.at(i)->Update(delta);
	}

	vector<ParticleSystem*>::iterator sysIte = m_particleSys_list.begin();
	while (sysIte != m_particleSys_list.end())
	{
		if ((*sysIte)->IsVisible() == false)
		{
			(*sysIte)->Release();
			sysIte = m_particleSys_list.erase(sysIte);
		}
		else
		{
			++sysIte;
		}
	}

	for (int i = 0; i < m_particleSys_list.size(); ++i)
	{
		m_particleSys_list.at(i)->Update(delta);
	}
}

void Scene::Render()
{
	stable_sort(m_element_list.begin(), m_element_list.end(), IsMin);

	for (int i = 0; i < m_element_list.size(); ++i)
	{
		m_element_list.at(i)->Render();
		m_element_list.at(i)->ParticleRender();
	}

	for (int i = 0; i < m_particleSys_list.size(); ++i)
	{
		m_particleSys_list.at(i)->Render();
	}
}

int Scene::GetOrder() const
{
	return _sceneOrder;
}

void Scene::SetOrder(const int& order)
{
	_sceneOrder = order;
}

void  Scene::AddUpdateFunc(UpdateFunc* func)
{
	m_updateFunc_list.push_back(func);
}

void  Scene::RemoveUpdateFunc(UpdateFunc* func)
{
	vector<UpdateFunc*>::iterator ite = m_updateFunc_list.begin();
	while (ite != m_updateFunc_list.end())
	{
		if ((*ite) == func)
		{
			(*ite)->Release();
			m_updateFunc_list.erase(ite);
			break;
		}

		++ite;
	}
}

void Scene::ClearUpdateFunc()
{
	vector<UpdateFunc*>::iterator ite = m_updateFunc_list.begin();
	while (ite != m_updateFunc_list.end())
	{
		(*ite)->Release();
		ite = m_updateFunc_list.erase(ite);
	}
}

bool Scene::IsVisible() const
{
	return _visible;
}

void Scene::SetVisible(bool visible)
{
	_visible = visible;
}
