#include "SpriteGroup.h"
#include "Sprite.h"

USING_NS_F2D

SpriteGroup* SpriteGroup::Create()
{
	SpriteGroup* group = new(nothrow) SpriteGroup();
	assert(group && "SrpiteGroup Create Failed!");

	return group;
}

SpriteGroup::~SpriteGroup()
{
	Clear();
}

void SpriteGroup::Add(Sprite* sprite)
{
	m_sprite_list.push_back(sprite);
}

void SpriteGroup::Remove(Sprite* sprite)
{
	vector<Sprite*>::iterator ite = m_sprite_list.begin();
	while (ite != m_sprite_list.end())
	{
		if ((*ite) == sprite)
		{
			(*ite)->Release();
			m_sprite_list.erase(ite);
			break;
		}

		++ite;
	}
}

void SpriteGroup::Update(const float& delta)
{
	Element::Update(delta);

	for (int i = 0; i < m_sprite_list.size(); ++i)
	{
		Sprite* sprite = m_sprite_list.at(i);
		sprite->SetPosition(
			sprite->GetPositionX() + GetPositionX(),
			sprite->GetPositionY() + GetPositionY(),
			sprite->GetPositionZ() + GetPositionZ());

		sprite->SetAngle(
			sprite->GetAngleX() + GetAngleX(),
			sprite->GetAngleY() + GetAngleY(),
			sprite->GetAngleZ() + GetAngleZ());

		sprite->SetAnchor(
			(sprite->GetAnchorX() + GetAnchorX()) / 2.0f,
			(sprite->GetAnchorY() + GetAnchorY()) / 2.0f);

		sprite->SetScale(
			sprite->GetScaleX() * GetScaleX(),
			sprite->GetScaleY() * GetScaleY());

		sprite->Update(delta);
	}
}

void SpriteGroup::Render()
{
	Element::Render();

	for (int i = 0; i < m_sprite_list.size(); ++i)
	{
		Sprite* sprite = m_sprite_list.at(i);
		sprite->Render();

		sprite->SetPosition(
			sprite->GetPositionX() - GetPositionX(),
			sprite->GetPositionY() - GetPositionY(),
			sprite->GetPositionZ() - GetPositionZ());

		sprite->SetAngle(
			sprite->GetAngleX() - GetAngleX(),
			sprite->GetAngleY() - GetAngleY(),
			sprite->GetAngleZ() - GetAngleZ());

		sprite->SetAnchor(
			sprite->GetAnchorX() * 2.0f - GetAnchorX(),
			sprite->GetAnchorY() * 2.0f - GetAnchorY());

		if (GetScaleX() != 0)
		{
			sprite->SetScaleX(sprite->GetScaleX() / GetScaleX());
		}
		if (GetScaleY() != 0)
		{
			sprite->SetScaleY(sprite->GetScaleY() / GetScaleY());
		}
	}
}

vector<Sprite*> SpriteGroup::GetSpriteList() const
{
	return m_sprite_list;
}

void SpriteGroup::Clear()
{
	vector<Sprite*>::iterator ite = m_sprite_list.begin();
	while (ite != m_sprite_list.end())
	{
		(*ite)->Release();
		ite = m_sprite_list.erase(ite);
	}
}