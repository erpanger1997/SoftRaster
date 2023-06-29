#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ShadingCalculate.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "geometry.h"
#include "Camera.h"
using namespace std;
//����Ⱦ�У�rhw ��������ռ�תCVV�ռ��ʱ��������ռ�����w�ĸ����ĵ�����
//����������ռ�תcvv��ʱ��һ���Ǵ�4ά���ŵ�3ά����һ����ͬʱǡ��ʵ���˽���ԶС��Ч����

//z - test  �� ��Z/w��ת����-1��1ȡֵ��Χ�ľ����壬Ȼ�� �� ��Z+1)/2 ת�� 0-1��Χ��   Ȼ�����õ� 1/Z�� �������Ե�����жϡ� ����ԽԶ��ԭ����ZԽ���õ������������ԽС��Խ�����

//����������������жϣ���Ϊ����ͬ�������� �ý������жϾ��ȸ���Զ���жϾ��ȸ�С�� ���⣬�� 0�ĵ����������壩����ʾ��Ұ������Զ��һ����

//��׶��(frustum, ��һ������)�任������۲���(Canonical View Volume ���¼��CVV)

//unity Ҳ����������ϵ

//��������ϵ, ��������
//Xx Yx Zx 0
//Xy Yy Zy 0
//Xz Yz Zz 0
//Dx Dy Dz 1

//X(x, y, z), Y(x, y, z), Z(x, y, z)�ֱ��ʾ����ϵ���������, ͨ��Ϊ��׼������, ���Ǳ�׼������, ��ʾ�ڸ���Ŵ������������׼���ı���, D(x, y, z)��ʾ�ڸ�����ϵ�е���ƫ�Ƶ�λ��

//��׼����
//1 0 0 0
//0 1 0 0
//0 0 1 0
//0 0 0 1
//��ʾ X(1, 0, 0), Y(0, 1, 0), Z(0, 0, 1) ƫ��(0, 0, 0), ��X�Ǳ�׼������ X(4, 0, 0)�����еĵ㽫�Ŵ�4��.


#define MAX_NUM_CAMERA 10

extern camera cameras[MAX_NUM_CAMERA];
extern camera camera_main;
extern camera shadowCamera;

typedef struct {

	int width;                  // ���ڿ��
	int height;                 // ���ڸ߶�
								//����������Ļ������  800*600*32
	IUINT32 **framebuffer;      // ���ػ��棺framebuffer[x] �����x��      framebuffer[x][y] �����x�е�y������

								//ÿ�����ص���� 800*600*4   32λϵͳ�char 1λ  short 2λ   float int long ����4λ ֻ��double��8λ
	float **zbuffer;            // ��Ȼ��棺zbuffer[y] Ϊ�� y��ָ��      zbuffer[x][y] �����x�е�y������
	float *shadowbuffer;        // ��Ӱ����  �Ժ�������ͬһ������
	int render_state;           // ��Ⱦ״̬

	//TODO:��Щ��ת�Ƶ� �����������
	IUINT32 background;         // ������ɫ
	IUINT32 foreground;         // �߿���ɫ
}
device_t;

int transform_check_cvv(const Vec4f *v);

void transform_homogenize_reverse(const transform_t *ts, point_t *x, const point_t *y);

void transform_homogenize(const transform_t *ts, point_t *y, const point_t &x);

//��ֵ  ����ÿ�����ص�Ĺ��ɵĲ�ֵ  ��������x,y,z,w ��ɫrpg
void vertex_interp(int render_state, vertex_t *y, const vertex_t *x1, const vertex_t *x2, float t);

////����ɨ���ߵ����ز�ֵ  ����ÿ�����ص�Ĺ��ɵĲ�ֵ  ��������x,y,z,w ��ɫrpg
//void vertex_division(int render_state, vertex_t *y, const vertex_t *x1, const vertex_t *x2, float width);

// ���������β��Ϊ 0-2 �������Σ����ҷ��غϷ������ε�����
int trapezoid_init_triangle(trapezoid_t *trap, const vertex_t *p1, const vertex_t *p2, const vertex_t *p3);
bool PointinTriangle(Vec3f& uv);
Vec3f barycentric(Vec2f A, Vec2f B, Vec2f C, Vec2f P);
//��ǰ���б�ʣ��Ż�
//����Y���������������������������Y�Ķ���
void trapezoid_edge_interp(device_t *device, trapezoid_t *trap, float y);

// �����������ߵĶ˵㣬��ʼ�������ɨ���ߵ����Ͳ���
void trapezoid_init_scan_line(int  renderState, const trapezoid_t *trap, scanline_t *scanline, int y);

// ���� 1.��դ��2D��
void device_pixel(device_t *device, int x, int y, IUINT32 color);

// x y������������������
// �����߶� 2.��դ��2Dֱ�ߣ�����ɭ�hķֱ�����㷨����С��ֱ���㷨�ȣ� ���-�յ㣬Ѱ���߶������άդ����������ص�
void device_draw_line(device_t *device, int x1, int y1, int x2, int y2, IUINT32 c);

//void device_draw_primitive_shadow(device_t *device, Shader *mShader, vertex_t *v1, vertex_t *v2, vertex_t *v3);

void device_render_trap_shadow(device_t *device, trapezoid_t *trap, float surfaceLight);

// ���������ȡ����
//IUINT32 device_texture_read(const Shader *mShader, float u, float v);

// ����ɨ����
void device_draw_scanline(device_t *device, Shader *mShader, scanline_t *scanline, float surfaceLight);

// ����Ⱦ����   ��Ⱦһ��������
void device_render_trap(device_t *device, Shader* mShader, trapezoid_t *trap, float surfaceLight);

// ���� render_state ����ͼԪ: ԭʼ������   
void device_draw_primitive(device_t *device, Shader *mShader,  vertex_t* v1, vertex_t* v2, vertex_t* v3);

// ���õ�ǰ����
void device_set_texture(Shader *mShader, void *bits, long pitch, int w, int h);


Vec4f TriangleMaxMinXY(Vec4f& A, Vec4f& B, Vec4f& C);
void PointinTriangleUV(Vec2f& A, Vec2f& B, Vec2f& C, const Vec2f& P, Vec3f& uv);
void vertex_interpUV(vertex_t& ret, const vertex_t& A, const vertex_t& B, const vertex_t& C, Vec3f uv);

//�����ȡX���step
void AllGetStep(int render_state, vertex_t* y, const vertex_t* x1, const vertex_t* x2, float t);

void device_init(device_t *device, int width, int height, void *fb);

void device_destroy(device_t *device);

void device_clear(device_t *device);

// ��� framebuffer �� zbuffer
void device_clear(device_t *device, int mode);
