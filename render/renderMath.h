#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <windows.h>
#include <tchar.h>
#include <stdbool.h>
#include "geometry.h"
#include"geometry.h"
#define PI 3.141592653
#define angle_to_radian(X) ((X)/180*PI)  //�Ƕ�ת����
#define radian_to_angle(X) ((X)/PI*180)  //����ת�Ƕ�

typedef unsigned int IUINT32;

//=====================================================================
// ����任
//=====================================================================
typedef struct {

	float screen_width, screen_height;             // ��Ļ��С

	Vec4f worldPos;
	Vec4f worldRot;
	Vec4f worldScale;
	//ò��û��ģ�;���

	Matrix44f model;         // ����-�������ÿ�����嶼���Լ����������TODO: �Ժ���뵽ÿ���������
	Matrix44f view;          // ��Ӱ������任 ���絽���������任����  TODO:�Ժ���뵽ÿ�����������
	Matrix44f projection;    // ͶӰ�任 �����Ǳ任���������Զƽ��-��ƽ��ռ���  TODO:�Ժ���뵽ÿ�����������
	//����������ľ��루z��Ҳ����ˣ����ھ�������x��y������������㣬�������z����Ķ��㽫����Ļ�����ĸ����λ����Ļ�����ġ�     
	// ���⣬�����͸����ͼ

	Matrix44f mvp;     // transform = world * view * projection
	Matrix44f vp;           // view * projection
	Matrix44f mv;           // model * view
}
transform_t;

// �������
void transform_update(transform_t* ts);

void Init_Model_matrix(Matrix44f& srt, const point_t& pos, const Vec4f& axis, const Vec4f& scale);

void matrix_Obj2World(matrix_t<4,4,float> &m, Vec4f rot, Vec4f pos);

void matrix_World2Obj(matrix_t<4, 4, float> &m, Vec4f rot, Vec4f pos, float scale);

//����ϵ�ı仯 = �������λ��+����ϵ����ת   ����ϵ����ת �� ��������ϵ�ڲ���������ת��һ����
//��������ǻ���ָ��������ת����ת���� ��ָ������Ϊ (x,y,z)
void matrix_set_rotate(matrix_t<4, 4, float>*m, Vec4f vec, float theta, Vec3f offset);






 