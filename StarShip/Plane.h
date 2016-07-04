#ifndef _PLANE_H_H_
#define _PLANE_H_H_

#include <Frame2D.h>

//======================
// 声明
//======================
class Bomb; // 炸弹基类
class BulletLauncher; // 子弹发射器基类
//======================

//======================
// 飞机类
//======================
class Plane : public Frame2D::Sprite
{
public:
	//======================
	// 创建自身对象
	//======================
	static Plane* Create();

	//======================
	// 创建自身对象
	// 参数1:生命值上限
	// 参数2:移动速度
	// 参数3:方向角度
	// 参数4:是否是移动状态
	// 参数5:是否是无敌状态
	//======================
	static Plane* Create(
		const float& hpMax,
		const float& moveSpeed,
		const float& directionAngle,
		bool bMove, bool bGod);

	//======================
	// 虚析构函数
	// 这里会自动清空子弹发射器容器并释放它们
	//======================
	virtual ~Plane();

	//======================
	// 攻击
	// (当需要攻击的时候调用)
	// 返回值:只要有一颗子弹发射成功那么就返回真
	//======================
	virtual bool Attack();
	
	virtual bool MissileShoot();

	//======================
	// 移动
	// (当飞机状态不为停止的时候,每帧调用)
	//======================
	virtual void Move();

	//======================
	// 死亡
	// (死亡的时候调用一次)
	//======================
	virtual void Die();

	//======================
	// update函数
	//======================
	virtual void Update(const float& delta);

	//=======================
	// 使用炸弹
	//=======================
	virtual bool UseBomb();

	//=======================
	// 添加炸弹
	//=======================
	void AddBomb(Bomb* bomb);

	//=======================
	// 删除炸弹
	//=======================
	void RemoveBomb(Bomb* bomb);

	//=======================
	// 获得炸弹数组
	//=======================
	vector<Bomb*> GetBombList() const;

	//=======================
	// 清空炸弹
	//=======================
	void ClearBomb();

	//======================
	// 添加一个子弹发射器
	//======================
	void AddBulletLauncher(BulletLauncher* launcher);

	//======================
	// 删除一个子弹发射器
	//======================
	void RemoveBulletLauncher(BulletLauncher* launcher);

	//======================
	// 清空所有子弹发射器
	//======================
	void ClearBulletLauncher();

	//======================
	// 获得发射器
	// 参数:索引,从0开始
	//======================
	vector<BulletLauncher*> GetBulletLauncherList() const;

	//======================
	// 添加一个导弹发射器
	//======================
	void AddMissileLauncher(BulletLauncher* launcher);

	//======================
	// 删除一个导弹发射器
	//======================
	void RemoveMissileLauncher(BulletLauncher* launcher);

	//======================
	// 清空所有导弹发射器
	//======================
	void ClearMissileLauncher();

	//======================
	// 获得导弹发射器
	// 参数:索引,从0开始
	//======================
	vector<BulletLauncher*> GetMissileLauncherList() const;

	//======================
	// setter
	//======================
	void SetHp(const float& hp);
	void SetHpMax(const float& hpMax);
	void SetMoveSpeed(const float& moveSpeed);
	void SetDirectionAngle(const float& angle);
	void SetMoveEnable(bool enable);
	void SetGodEnable(bool enable);
	void SetBruiseEnable(bool enable);

	//======================
	// getter
	//======================
	float GetHp() const;
	float GetHpMax() const;
	float GetMoveSpeed() const;
	float GetDirectionAngle() const;
	bool IsMove() const;
	bool IsGod() const;
	bool IsBruiseEnable() const;

protected:
	//======================
	// 默认构造函数
	//======================
	Plane()
	: _hp(0)
	, _hpMax(0)
	, _moveSpeed(0)
	, _directionAngle(0)
	, _bMove(false)
	, _bGod(false)
	{}

	//======================
	// 带参构造函数
	//======================
	Plane(
		const float& hp,
		const float& hpMax,
		const float& moveSpeed,
		const float& directionAngle,
		bool bMove,
		bool bGod)
	: _hp(hp)
	, _hpMax(hpMax)
	, _moveSpeed(moveSpeed)
	, _directionAngle(directionAngle)
	, _bMove(bMove)
	, _bGod(bGod)
	, _bBruise(false)
	, _bBruiseTemp(false)
	{}

private:
	Plane(Plane&);
	Plane& operator=(Plane&);

protected:
	// 炸弹数组
	vector<Bomb*> m_bomb_list;
	// 子弹发射器数组
	vector<BulletLauncher*> m_bulletLaunch_list;
	// 导弹发射器数组
	vector<BulletLauncher*> m_missileLaunch_list;

private:
	float _hp; // 当前生命值
	float _hpMax; // 生命值上限
	float _moveSpeed; // 移动速度
	float _directionAngle; // 方向,角度(0度表示方向朝上,逆时针旋转)
	bool _bMove; // 是否移动
	bool _bGod; // 是否无敌
	bool _bBruise; // 是否受伤(被攻击)
	bool _bBruiseTemp; // 辅助用
};

#endif