#pragma once
#include"Dxlib.h"
class Camera
{
public :
    Camera(); ///�R���X�g���N�^
    ~Camera();///�f�X�g���N�^

    // �|�W�V������getter/setter.
    const VECTOR& GetPos() const { return pos; }

private:
    VECTOR	pos;			// �|�W�V����.

};

