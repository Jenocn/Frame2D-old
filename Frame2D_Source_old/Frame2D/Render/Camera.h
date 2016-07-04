#ifndef _CAMERA_H_H_
#define _CAMERA_H_H_

#include "DX9.h"

/*
	摄像机类
*/
class Camera
{
public:
	static Camera* getInstance();

	/*
		函数功能:释放内存,并delete自身
	*/
	void Release();

	/*
		函数功能:获得摄像机位置
		返回值:空间向量表示的位置
	*/
	D3DXVECTOR3 GetCameraPosition() const;

	/*
		函数功能:设置摄像机的位置
		参数1:空间向量表示的目标位置
	*/
	void SetCameraPosition(const D3DXVECTOR3& position);

	/*
		函数功能:设置摄像机的位置
		参数1~3:空间x,y,z的坐标
	*/
	void SetCameraPosition(
		const float& positionX,
		const float& positionY,
		const float& positionZ);

	/*
		函数功能:获得视点的位置
		返回值:空间向量表示的位置
	*/
	D3DXVECTOR3 GetViewPosition() const;

	/*
		函数功能:设置视点位置
		参数1:空间向量表示的目标位置
	*/
	void SetViewPosition(const D3DXVECTOR3& position);

	/*
		函数功能:设置视点的位置
		参数1~3:空间x,y,z的坐标
	*/
	void SetViewPosition(
		const float& positionX,
		const float& positionY,
		const float& positionZ);

	/*
		函数功能:获得可视距离
	*/
	float GetVisibleRange();

	/*
		函数功能:设置可视距离
		参数1:Z轴可视距离
	*/
	void SetVisibleRange(const float& range);

private:
	Camera()
	: _visibleRange(0)
	{}

	Camera(Camera&);
	Camera& operator=(Camera&);

private:
	// 摄像机位置
	D3DXVECTOR3 _cameraPosition;
	// 观察位置
	D3DXVECTOR3 _viewPosition;
	// 可视距离
	float _visibleRange;
};

#endif