#pragma once
#include "DxLib.h"
class Object
{
public :
	virtual void Update()abstract;			// �X�V.
	virtual void Draw()abstract;			// �`��.
	//�Q�b�^�[
	int GetModelHandle() const { return modelHandle; }
	const  VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }
	const VECTOR& GetVelocity() const { return velocity; }
	const VECTOR& GetSlope()const { return slope; }
	const float& GetWidth()const { return width; }
	const float& GetHeight()const { return height; }
	const float& GetDepth()const { return Depth; }
	float GetScale()const { return Scale; }
	//�Z�b�^�[
	void SetPos(const VECTOR& Pos);
	void SetDir(const VECTOR& Dir);
	void SetSlope(const VECTOR& Slope);

	///�g������
	static VECTOR VectorNorm(VECTOR& V1);
	static VECTOR Outer_Volume(const VECTOR& V1, const VECTOR& V2);
	static VECTOR VMultiplication(const VECTOR& V1, const VECTOR& V2);
	static VECTOR PositiveProjectionVector(const VECTOR& Ground, const VECTOR& V1);
	static bool isCollisonTriangle(const VECTOR& CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
	static VECTOR Push_Back_Vector_Triangle(VECTOR& ChekPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
	/// <summary>
	/// �w��̎��ŉ�]������
	/// </summary>
	/// <param name="V1">�ω�������VECTOR</param>
	/// <param name="Axis">���ƂȂ�VERCTOR</param>
	/// <param name="Power">��]�����߂�s��</param>
	/// <returns></returns>
	static VECTOR RotFreeAxis(VECTOR& V1, const  VECTOR& Axis, const MATRIX& Power);
	static bool isCollicon_Ball_to_Ball(const VECTOR &ball1_pos,const float &ball1_Rsdius, const VECTOR& ball2_pos, const float& ball2_Rsdius);
	
protected:
	int		modelHandle;	// ���f���n���h��.
	VECTOR	pos;			// �|�W�V����.
	VECTOR	velocity;		// �ړ���.
	VECTOR	dir;			// �ړ�����.
	VECTOR  slope;          //object�̌X��
	float width;
	float height;
	float Depth;
	static const float Scale;
};

