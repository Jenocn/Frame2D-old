#include "BulletLauncherRealize.h"

#include "BulletRealize.h"

Bullet* BulletLauncherOnward::CreateBullet()
{
	return BulletOnward::Create(_bulletName);
}

Bullet* BulletLauncherCurveCosL::CreateBullet()
{
	return BulletCurveCosL::Create(_bulletName);
}

Bullet* BulletLauncherCurveCosR::CreateBullet()
{
	return BulletCurveCosR::Create(_bulletName);
}

Bullet* BulletLauncherMissile::CreateBullet()
{
	return BulletMissile::Create(_bulletName);
}

Bullet* BulletLauncherDisperse::CreateBullet()
{
	return BulletDisperse::Create(_bulletName);
}

Bullet* BulletLauncherFollow::CreateBullet()
{
	return BulletFollow::Create(_bulletName);
}

Bullet* BulletLauncherRebound::CreateBullet()
{
	return BulletRebound::Create(_bulletName);
}

Bullet* BulletLauncherReboundOnward::CreateBullet()
{
	return BulletReboundOnward::Create(_bulletName);
}

Bullet* BulletLauncherLockBeginPosition::CreateBullet()
{
	return BulletLockBeginPosition::Create(_bulletName);
}
