#include "Element.h"
#include "Function.h"
#include "EventDispatcher.h"
#include "Action.h"
#include "ParticleSystem.h"
#include "Scene.h"

USING_NS_F2D

Element::~Element()
{

}

void Element::Release()
{
	EventDispatcher::getInstance()->RemoveByEventObj(this);
	ClearAction();
	Clear();

	delete this;
}

void Element::Update(const float& delta)
{
	for (int i = 0; i < m_updateFunc_list.size(); ++i)
	{
		m_updateFunc_list.at(i)->Update(delta);
	}

	vector<Action*>::iterator actIte = m_action_list.begin();
	while (actIte != m_action_list.end())
	{
		if ((*actIte)->IsFinish())
		{
			(*actIte)->Release();
			actIte = m_action_list.erase(actIte);
		}
		else
		{
			++actIte;
		}
	}

	for (int i = 0; i < m_action_list.size(); ++i)
	{
		m_action_list.at(i)->Update(delta);
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

void Element::Render()
{

}

void Element::ParticleRender()
{
	for (int i = 0; i < m_particleSys_list.size(); ++i)
	{
		m_particleSys_list.at(i)->Render();
	}
}

int Element::GetOrder() const
{
	return _order;
}

void Element::SetOrder(const int& order)
{
	_order = order;
}

float Element::GetPositionX() const
{
	return _positionX;
}

float Element::GetPositionY() const
{
	return _positionY;
}

float Element::GetPositionZ() const
{
	return _positionZ;
}

void Element::SetPosition(
	const float& positionX,
	const float& positionY,
	const float& positionZ)
{
	_positionX = positionX;
	_positionY = positionY;
	_positionZ = positionZ;
}

void Element::SetPosition(
	const float& positionX,
	const float& positionY)
{
	_positionX = positionX;
	_positionY = positionY;
}

void Element::SetPositionX(const float& positionX)
{
	_positionX = positionX;
}

void Element::SetPositionY(const float& positionY)
{
	_positionY = positionY;
}

void Element::SetPositionZ(const float& positionZ)
{
	_positionZ = positionZ;
}

float Element::GetAngleX() const
{
	return _angleX;
}

float Element::GetAngleY() const
{
	return _angleY;
}

float Element::GetAngleZ() const
{
	return _angleZ;
}

void Element::SetAngle(
	const float& angleX,
	const float& angleY,
	const float& angleZ)
{
	_angleX = angleX;
	_angleY = angleY;
	_angleZ = angleZ;
}

void Element::SetAngleX(const float& angleX)
{
	_angleX = angleX;
}

void Element::SetAngleY(const float& angleY)
{
	_angleY = angleY;
}

void Element::SetAngleZ(const float& angleZ)
{
	_angleZ = angleZ;
}

float Element::GetAnchorX() const
{
	return _anchorX;
}

float Element::GetAnchorY() const
{
	return _anchorY;
}

void Element::SetAnchor(
	const float& anchorX,
	const float& anchorY)
{
	_anchorX = anchorX;
	_anchorY = anchorY;
}

void Element::SetAnchorX(const float& anchorX)
{
	_anchorX = anchorX;
}

void Element::SetAnchorY(const float& anchorY)
{
	_anchorY = anchorY;
}

float Element::GetScaleX() const
{
	return _scaleX;
}

float Element::GetScaleY() const
{
	return _scaleY;
}

void Element::SetScale(const float& scale)
{
	_scaleX = scale;
	_scaleY = scale;
}

void Element::SetScale(
	const float& scaleX,
	const float& scaleY)
{
	_scaleX = scaleX;
	_scaleY = scaleY;
}

void Element::SetScaleX(const float& scaleX)
{
	_scaleX = scaleX;
}

void Element::SetScaleY(const float& scaleY)
{
	_scaleY = scaleY;
}

int Element::GetWidth() const
{
	return _width;
}

int Element::GetHeight() const
{
	return _height;
}

bool Element::IsVisible()
{
	return _visible;
}

void Element::SetVisible(bool bVisible)
{
	_visible = bVisible;
}

void Element::SetWidth(const int& width)
{
	_width = width;
}

void Element::SetHeight(const int& height)
{
	_height = height;
}

void  Element::AddUpdateFunc(UpdateFunc* func)
{
	m_updateFunc_list.push_back(func);
}

void  Element::RemoveUpdateFunc(UpdateFunc* func)
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

void Element::ClearUpdateFunc()
{
	vector<UpdateFunc*>::iterator ite = m_updateFunc_list.begin();
	while (ite != m_updateFunc_list.end())
	{
		(*ite)->Release();
		ite = m_updateFunc_list.erase(ite);
	}
}

void Element::RunAction(Action* action)
{
	action->Register(this);
	m_action_list.push_back(action);
}

void Element::RemoveAction(Action* action)
{
	vector<Action*>::iterator ite = m_action_list.begin();
	while (ite != m_action_list.end())
	{
		if ((*ite) == action)
		{
			(*ite)->Release();
			m_action_list.erase(ite);
			break;
		}

		++ite;
	}
}

void Element::ClearAction()
{
	vector<Action*>::iterator ite = m_action_list.begin();
	while (ite != m_action_list.end())
	{
		(*ite)->Release();
		ite = m_action_list.erase(ite);
	}
}

bool Element::IsActionPlaying() const
{
	if (m_action_list.size() > 0)
	{
		return true;
	}

	return false;
}

void Element::Add(ParticleSystem* system)
{
	m_particleSys_list.push_back(system);
}

void Element::Remove(ParticleSystem* system)
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

void Element::Clear()
{
	vector<ParticleSystem*>::iterator sysIte = m_particleSys_list.begin();
	while (sysIte != m_particleSys_list.end())
	{
		(*sysIte)->Release();
		sysIte = m_particleSys_list.erase(sysIte);
	}
}

void Element::BindScene(Scene* scene)
{
	_scene = scene;
}

Scene* Element::GetScene() const
{
	return _scene;
}