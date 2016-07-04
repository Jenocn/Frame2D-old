#include "Camera.h"
#include "D3DManager.h"

static Camera* pInstance = 0;

Camera* Camera::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new Camera();
	}

	return pInstance;
}

void Camera::Release()
{
	delete this;
	pInstance = 0;
}

D3DXVECTOR3 Camera::GetCameraPosition() const
{
	return _cameraPosition;
}

void Camera::SetCameraPosition(const D3DXVECTOR3& position)
{
	SetCameraPosition(position.x, position.y, position.z);
}

void Camera::SetCameraPosition(
	const float& positionX,
	const float& positionY,
	const float& positionZ)
{
	_cameraPosition.x = positionX;
	_cameraPosition.y = positionY;
	_cameraPosition.z = positionZ;

	//定义一个矩阵
	D3DXMATRIX matView;
	//向上的向量,表示向前看
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
	//计算出取景变换矩阵
	D3DXMatrixLookAtLH(&matView, &_cameraPosition, &_viewPosition, &vUp);
	//应用取景变换矩阵
	D3DManager::getInstance()->getDevice()->SetTransform(D3DTS_VIEW, &matView);
}

D3DXVECTOR3 Camera::GetViewPosition() const
{
	return _viewPosition;
}

void Camera::SetViewPosition(const D3DXVECTOR3& position)
{
	_viewPosition = position;

	SetViewPosition(position.x, position.y, position.z);
}

void Camera::SetViewPosition(
	const float& positionX,
	const float& positionY,
	const float& positionZ)
{
	_viewPosition.x = positionX;
	_viewPosition.y = positionY;
	_viewPosition.z = positionZ;

	//定义一个矩阵
	D3DXMATRIX matView;
	//向上的向量,表示向前看
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
	//计算出取景变换矩阵
	D3DXMatrixLookAtLH(&matView, &_cameraPosition, &_viewPosition, &vUp);
	//应用取景变换矩阵
	D3DManager::getInstance()->getDevice()->SetTransform(D3DTS_VIEW, &matView);
}

float Camera::GetVisibleRange()
{
	return _visibleRange;
}

void Camera::SetVisibleRange(const float& range)
{
	_visibleRange = range;

	RECT rect = D3DManager::getInstance()->GetRenderWindow();

	// 投影矩阵
	D3DXMATRIX matProj;
	//计算投影变换矩阵
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f,
		(float)((double)(rect.right - rect.left) / (rect.bottom - rect.top)),
		1.0f,
		_visibleRange // 可视距离
		);

	//设置投影变换矩阵
	D3DManager::getInstance()->getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
}
