#include "Camera.h"
Camera::Camera()
{
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 100.0f);

	pos = VGet(0, 0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	// �����Ȃ�.
}