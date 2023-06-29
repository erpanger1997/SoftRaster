#pragma once
#include "Scene.h"

//����ģ�ͽ���

//������ɫ��ʽ

//Phong shading
//blinn shading

//Groud Shader

//VertexLight


//���㷨������
float ComputeNDotL(const point_t& vertex, const Vec4f& normal, const point_t& lightPosition);

//���㶥�㵽�ƹ�ľ���,���ڲ�����Ӱ
//float DisVertexToLight(const point_t *Light, Vec4f* VertertPosInWorld);

//����
float calculateVertexLight(const point_t *v1,  Vec4f& normal);
//ƽ��
float calculateGroudShader(const point_t *v1, const point_t *v2, const point_t *v3);

float ComputeCameraToVertor(const point_t& vertex, const Vec4f& normal, const point_t& BBBCameraToVertor);

float CullCalcutate(const point_t *v1, const point_t *v2, const point_t *v3, const point_t *camera_pos);

//TODO:�����������ֹ���ģ�ͣ� BRDFģ���µ������� ��
//1.Lambertģ�ͣ�����������ģ�ͣ�����ͬ�ԣ� Idiffuse = Kd*Id*cos��

//1.����Shader
float calculateVertexLight(const point_t *v1, Vec4f& normal);
//2.ƽ��Shader
float calculateGroudShader(const point_t *v1, const point_t *v2, const point_t *v3);

//3.����������
color_t Lambert(transform_t* mainTrans, Vec4f *v_Obj, Vec4f* normal, Vec4f* lightPos, color_t diffuseColor, color_t ambientColor);

//4.������߹�������� Ҳ����Phong����ģ��
color_t Phong(transform_t* mainTrans, Vec4f *posInObj, Vec4f *normal, Vec4f* lightPos, Vec4f* cameraPos, color_t diffuseColor, color_t ambientColor, color_t specularColor);


//5. blinn shading