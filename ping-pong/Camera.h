#pragma once
#include"Dxlib.h"
class Camera
{
public :
    Camera(); ///コンストラクタ
    ~Camera();///デストラクタ

    // ポジションのgetter/setter.
    const VECTOR& GetPos() const { return pos; }

private:
    VECTOR	pos;			// ポジション.

};

