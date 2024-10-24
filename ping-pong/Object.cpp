#include<math.h>

#include "Object.h"
VECTOR Object::VectorNorm(VECTOR& V1)
{
    float size = sqrtf(V1.x * V1.x + V1.y * V1.y + V1.z * V1.z);
    if (V1.x != 0 && V1.y != 0 && V1.z != 0)
    {
        V1 = VNorm(V1);
    }
    else if (V1.x != 0)
    {
        V1.x = V1.x / size;
    }
    else  if (V1.y != 0)
    {

        V1.y = V1.y / size;
    }
    else if (V1.z != 0)
    {

        V1.z = V1.z / size;
    }

    return V1;

}

VECTOR Object::Outer_Volume(const VECTOR& V1, const VECTOR& V2)
{
    VECTOR OuterVolume;
    OuterVolume.x = V1.y * V2.z - V1.z * V2.y;
    OuterVolume.y = V1.z * V2.x - V1.x * V2.z;
    OuterVolume.z = V1.x * V2.y - V1.y * V2.x;

    return OuterVolume;
}

VECTOR Object::VMultiplication(const VECTOR& V1, const VECTOR& V2)
{
    VECTOR ans;
    ans.x = V1.x * V2.x;
    ans.y = V1.y * V2.y;
    ans.z = V1.z * V2.z;

    return ans;
}

VECTOR Object::PositiveProjectionVector(const VECTOR& Ground, const VECTOR& V1)
{

    float GroundLength = VSize(Ground);



    return VScale(Ground, VDot(Ground, V1) / (GroundLength * GroundLength));
}

bool Object::isCollisonTriangle(const VECTOR& CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3)
{
    //checkから各頂点へのベクトル
    VECTOR Check_to_1 = VSub(Apex1, CheckPoint);
    VECTOR Check_to_2 = VSub(Apex2, CheckPoint);
    VECTOR Check_to_3 = VSub(Apex3, CheckPoint);
    //外積を出す
    VECTOR OuterVolume_1 = Outer_Volume(Check_to_1, Check_to_2);
    VECTOR OuterVolume_2 = Outer_Volume(Check_to_2, Check_to_3);
    VECTOR OuterVolume_3 = Outer_Volume(Check_to_3, Check_to_1);

    VECTOR OuterVolume_Multiplication = VMultiplication(VMultiplication(OuterVolume_1, OuterVolume_2), OuterVolume_3);
    ///3つの外積をかけたものと２つの外積の符号が同じか確かめる
    ///2つの外積を確かめることでどのパターンでも符号違いが検出できる

    ///符号違いを確かめるには3つの外積をかけたものと２つの外積をかけたものが＋－でわかる
    VECTOR Check1 = VMultiplication(OuterVolume_Multiplication, OuterVolume_1);
    VECTOR Check2 = VMultiplication(OuterVolume_Multiplication, OuterVolume_2);


    if (Check1.x >= 0 && Check1.y >= 0 && Check1.z >= 0 && Check2.x >= 0 && Check2.y >= 0 && Check2.z >= 0)
    {
        ///向きが同じなら3角形の内側にポイントがあるからTRUEを返す
        return true;
    }
    ///向きが違うとポイントが3角形外にあるのでFALSEを返す
    return false;
}

void Object::SetPos(const VECTOR& Pos)
{
    pos = Pos;
}
VECTOR Object::RotFreeAxis(VECTOR& V1, const VECTOR& Axis, const MATRIX& Power)
{
    V1 = VSub(V1, Axis);
    V1 = VTransform(V1, Power);
    V1 = VAdd(V1, Axis);
    return V1;
}
bool Object::isCollicon_Ball_to_Ball(const VECTOR& ball1_pos, const float& ball1_Rsdius, const VECTOR& ball2_pos, const float& ball2_Rsdius)
{
    float Sum_Rsdius = ball1_Rsdius + ball2_Rsdius;
    float PosDistance = VSize(VSub(ball1_pos,ball2_pos));
    if (Sum_Rsdius > PosDistance)
    {
        return true;
    }
    return false;
}

bool Object::isCollicon_Ball_to_Triangle(const VECTOR& ball1_pos, const float& ball1_Rsdius, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3)
{
    ///三角形とposの最短距離を出す
    VECTOR Check_to_1 = VSub(Apex1, ball1_pos);
    VECTOR Check_to_2 = VSub(Apex2, ball1_pos);
    VECTOR Check_to_3 = VSub(Apex3, ball1_pos);
    ///２つの水平な線の外積は垂直
    VECTOR Outer1 = Outer_Volume(Check_to_1, Check_to_2);
    VECTOR Outer2 = Outer_Volume(Check_to_1, Check_to_3);

    VECTOR VertivalLine = Outer_Volume(Outer1, Outer2);
    
    ////最短距離をボールの半径の長さに変える
    VertivalLine = VScale(VectorNorm(VertivalLine), ball1_Rsdius);

   
    ////変形したながさの＋－をposに足す　円周上の最短距離をと最長を求める
    VECTOR AddVertivalLine = VAdd(ball1_pos, VertivalLine);
    VECTOR SubVertivalLine = VSub(ball1_pos, VertivalLine);

    ///その2つそれぞれで頂点たちをの外積を求める
    VECTOR AddVertivalLine_Apex1= VSub(Apex1, AddVertivalLine);
    VECTOR AddVertivalLine_Apex2 = VSub(Apex2, AddVertivalLine);

    VECTOR Add_Outer = Outer_Volume(AddVertivalLine_Apex1, AddVertivalLine_Apex2);

    VECTOR SubVertivalLine_Apex1 = VSub(Apex1, AddVertivalLine);
    VECTOR SubVertivalLine_Apex2 = VSub(Apex2, AddVertivalLine);

    VECTOR Sub_Outer = Outer_Volume(AddVertivalLine_Apex1, AddVertivalLine_Apex2);

    //2てんの方向が同じか確かめる　違うならtrueを返す
    VECTOR Jag = VMultiplication(Add_Outer, Sub_Outer);
    if (Jag.x > 0 && Jag.y > 0 && Jag.z > 0)
    {
        return false;
    }
    return true;
}

VECTOR Object::Push_Back_Vector_Triangle(VECTOR& ChekPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3)
{
    //posから各頂点へのベクトル
    VECTOR Check_to_1 = VSub(Apex1, ChekPoint);
    VECTOR Check_to_2 = VSub(Apex2, ChekPoint);
    VECTOR Check_to_3 = VSub(Apex3, ChekPoint);


     //辺のベクトルを求める
    VECTOR Around_1_2 = VSub(Apex2, Apex1);
    VECTOR Around_1_3 = VSub(Apex3, Apex1);
    VECTOR Around_3_2 = VSub(Apex2, Apex3);

    //辺からposへの垂線が交わる位置を求める
    VECTOR Pos_Intersect_Around1_2 = PositiveProjectionVector(Around_1_2, Check_to_1);
    VECTOR Pos_Intersect_Around1_3 = PositiveProjectionVector(Around_1_3, Check_to_1);
    VECTOR Pos_Intersect_Around3_2 = PositiveProjectionVector(Around_3_2, Check_to_3);

    ///相対的なPos_Intersect_Aroundと絶対的なPosの位置を比較するためPosを加算する
    Pos_Intersect_Around1_2 = VAdd(Pos_Intersect_Around1_2, ChekPoint);
    Pos_Intersect_Around1_3 = VAdd(Pos_Intersect_Around1_3, ChekPoint);
    Pos_Intersect_Around3_2 = VAdd(Pos_Intersect_Around3_2, ChekPoint);
    //辺からposへの垂線の交点へのベクトルを求める
    VECTOR  Pos_to_Around1_2 = VSub(Pos_Intersect_Around1_2, ChekPoint);
    VECTOR  Pos_to_Around1_3 = VSub(Pos_Intersect_Around1_3, ChekPoint);
    VECTOR  Pos_to_Around3_2 = VSub(Pos_Intersect_Around3_2, ChekPoint);


    ///最小値のベクトルを返す
    if (VSize(Pos_to_Around1_2) <= VSize(Pos_to_Around1_3))
    {
        if (VSize(Pos_to_Around1_2) <= VSize(Pos_to_Around3_2))
        {
            if (VSize(Pos_to_Around1_2) == 0)
            {
                VAdd(Pos_to_Around1_2, VGet(0, 1, 0));
            }
            return Pos_to_Around1_2;

        }
        else
        {
            if (VSize(Pos_to_Around3_2) == 0)
            {
                VAdd(Pos_to_Around3_2, VGet(0, 1, 0));
            }
            return  Pos_to_Around3_2;
        }
    }
    else
    {
        if (VSize(Pos_to_Around1_3) <= VSize(Pos_to_Around3_2))
        {
            if (VSize(Pos_to_Around1_3) == 0)
            {
                VAdd(Pos_to_Around1_3, VGet(0, 1, 0));
            }
            return Pos_to_Around1_3;
        }
        else
        {
            if (VSize(Pos_to_Around3_2) == 0)
            {
                VAdd(Pos_to_Around3_2, VGet(0, 1, 0));
            }
            return  Pos_to_Around3_2;
        }
    }
}