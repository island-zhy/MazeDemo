#include "Transform.h"



Transform::Transform()
{
	XMStoreFloat3(&m_position,XMVectorSet(0.0f,0.0f,0.0f,1.0f));
	XMStoreFloat4x4(&m_rotation,XMMatrixRotationQuaternion(XMVectorSet(0.0f, 0.0f, 0.0f,0.0f)));
}


Transform::~Transform()
{
}