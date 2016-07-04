//===================
// 子弹发射器基类的实现类集合
// 用于创建各种类型的发射器
//===================

#ifndef _BULLET_LAUNCHER_REALIZE_H_H_
#define _BULLET_LAUNCHER_REALIZE_H_H_

#include "BulletLauncher.h"

class Bullet;

class BulletLauncherOnward : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherOnward);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherOnward() {}
private:
	BulletLauncherOnward(BulletLauncherOnward&);
	BulletLauncherOnward& operator=(BulletLauncherOnward&);
};

class BulletLauncherCurveCosL : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherCurveCosL);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherCurveCosL() {}
private:
	BulletLauncherCurveCosL(BulletLauncherCurveCosL&);
	BulletLauncherCurveCosL& operator=(BulletLauncherCurveCosL&);
};

class BulletLauncherCurveCosR : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherCurveCosR);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherCurveCosR() {}
private:
	BulletLauncherCurveCosR(BulletLauncherCurveCosR&);
	BulletLauncherCurveCosR& operator=(BulletLauncherCurveCosR&);
};

class BulletLauncherMissile : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherMissile);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherMissile() {}
private:
	BulletLauncherMissile(BulletLauncherMissile&);
	BulletLauncherMissile& operator=(BulletLauncherMissile&);
};

class BulletLauncherDisperse : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherDisperse);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherDisperse() {}
private:
	BulletLauncherDisperse(BulletLauncherDisperse&);
	BulletLauncherDisperse& operator=(BulletLauncherDisperse&);
};

class BulletLauncherFollow : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherFollow);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherFollow() {}
private:
	BulletLauncherFollow(BulletLauncherFollow&);
	BulletLauncherFollow& operator=(BulletLauncherFollow&);
};

class BulletLauncherRebound : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherRebound);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherRebound() {}
private:
	BulletLauncherRebound(BulletLauncherRebound&);
	BulletLauncherRebound& operator=(BulletLauncherRebound&);
};

class BulletLauncherReboundOnward : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherReboundOnward);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherReboundOnward() {}
private:
	BulletLauncherReboundOnward(BulletLauncherReboundOnward&);
	BulletLauncherReboundOnward& operator=(BulletLauncherReboundOnward&);
};

class BulletLauncherLockBeginPosition : public BulletLauncher
{
public:
	BULLETLAUNCHER_CREATEFUNC(BulletLauncherLockBeginPosition);
	virtual Bullet* CreateBullet();
protected:
	BulletLauncherLockBeginPosition() {}
private:
	BulletLauncherLockBeginPosition(BulletLauncherLockBeginPosition&);
	BulletLauncherLockBeginPosition& operator=(BulletLauncherLockBeginPosition&);
};

#endif