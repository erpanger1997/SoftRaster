#pragma once
#include "geometry.h"
#include "Camera.h"
#include "Model.h"
#include <stdbool.h>
#include "CMaterail.h"

//class IShader {
//	virtual ~IShader();
//	virtual Vec4f vertex(int iface, int nthvert) = 0;
//	virtual bool fragment(Vec3f bar, TGAColor& color) = 0;
//};

// ǰ����ģʽ��û����ɫ���̣�Ҳ����Ҫ��ɫ��


#define RENDER_STATE_WIREFRAME_TEXT     "��Ⱦ�߿�"
#define RENDER_STATE_TEXTURE_TEXT        "��Ⱦ����"
#define RENDER_STATE_COLOR_TEXT          "������ɫ" //�����Ǹ��ݶ������(��Z������)����   ʹ�õ��Ǹ��ݶ�����������ż�������ɫ��Ȼ�󶥵�������ֵ��

#define RENDER_STATE_surfaceNormal_color_TEXT   "�淨�ߵ���ɫ��ʾ"   //Ҳ������ν��ƽ����ɫ��ÿ��ͼԪ�����ض���һ�µĸ����ͼԪ�ĵ�һ���������ɫ�� flat shading
#define RENDER_STATE_verterNormal_color_TEXT     "���㷨�ߵ���ɫ��ʾ"   //Ҳ������ν�Ķ�����ɫ��������ɫ��������Gouraud��ɫ��ͼԪ�еĸ����ص���ɫֵ�ɶ������ɫ�����Բ�ֵ�õ���

enum Render_State
{
	RENDER_STATE_WIREFRAME = 1,
	RENDER_STATE_TEXTURE = 2,
	RENDER_STATE_COLOR = 4,
	RENDER_STATE_surfaceNormal_color = 8,
	RENDER_STATE_verterNormal_color = 16
};

typedef struct {
	Vec4f pos; //λ��
	color_t color; //��ɫ
	Vec4f normal; //����
	Vec4f tangent; //����
	Vec4f binormal; //������
	Vec2f texcoord; //uv����
} a2v;

typedef struct {
	Vec4f pos;
	Vec2f texcoord;
	color_t color;
	Vec4f normal;
	Vec4f storage0;
	Vec4f storage1;
	Vec4f storage2;
} v2f;

//���ǵĽṹģ�ͣ�UObject = Model +Tramsform +materal +shader
//��Ⱦʱ�Ľṹ  vertex_t edge_t +���� 
//�����ص�˵�� pos��Wֵ�� ��color_t��Wֵ������
//pos������ϵת����Ϊ��ͳһת������չ������ά�� pos��Wֵ�����������4ά��3ά�Ļ�ԭ��Ҳ����CVV����դ���Ľ׶�
//color_t��Wֵ�������ڼ�¼�ö���/���ص����ȣ���������޳�

typedef class {
public:
	point_t pos;//λ�� �����

	Vec2f tc; //��������
	color_t color; //��ɫ       
	Vec4f normal; //���Ĵ������ӷ���    ������ϲ� float rhw �ϲ���;  //�ö����֮ǰ��w�ĵ����� Ҳ�������Ŵ�С
	point_t worldPos;  //֮ǰ�����������λ�� �����shader�в���Ҫ
	float vertexLight; //����ƹ��ǿ��
	float shadowPos_z; //ͶӰ������Ĺ�դ��λ�� �����shader�в���Ҫ
	Vec4f world_normal; 
	point_t project_pos;
	Vec4f raster_pos;
} vertex_t; //����

			//���������εı�Ե
typedef struct {
	vertex_t v,  //ɨ���� �� б�ߵĽ���
		v1, //������б�ߵ�ԭʼ���
		v2; //������б�ߵ�ԭʼ�յ�
} edge_t; //��Ե

		  //������
typedef struct {
	float top, bottom; //�����ε�����
	edge_t left, right;  //�����ε�����б��  ��ʵ �����εĸ߶ȣ��Ѿ�ȷ����

} trapezoid_t; //����

			   //��Ⱦ���ε�ʱ���ɨ����
typedef struct {
	vertex_t v, step; //���
	int x,
		y,
		width;  //���͵�ɨ���߿��
} scanline_t; //ɨ����


void vertex_add(vertex_t* y, const vertex_t* x);


//����
typedef class
{
public:
	unsigned long mesh_num;//..

	point_t pos;
	Vec4f axis;
	Vec4f scale;
	//mesh[0]��mesh[]��ռ�ÿռ䣬�ҵ�ַ�����ڽṹ���棬��vertex_t *data��Ϊָ�룬ռ��4���ֽڣ���ַ���ڽṹ֮��
	//vertex_t mesh[0]; //��ʼ��ַ �ɱ�����   vertex_t data[0]��vertex_t *data, vertex_t data[]������ 
	vertex_t* mesh;

	//IUINT32 texture[256][256]; //����
	Matrix44f model;         // �������  ���������ȼ������


	//materal m_materal; //����

	//TODO���Ժ�����

	//int* material_ids; //ֻ�洢ID����

	//int texture_id;
	//bool shadow;  //�Ƿ���������Ӱ  TODO���Ժ�����Ƿ������Ӱ
}
Object_t;

//����ͨ��Cpu�׶εı�ǩ ������shader��ʼ��ʱ Ҫ������Щlist ����shader�׶ε�ͨ��������ȡ
//Ϊ�˲���������Ҫ����Ϊ�����ͼԪ���������ֱ𲢷�
class Shader//:public IShader
{
public:
	//��ǰ�ĸ��������Ⱦ��
	camera curCamera;

	vertex_t* v1;
	vertex_t* v2;
	vertex_t* v3;
	Shader();
	~Shader();

	Model *mModel; //��ʱ����һ������

	transform_t transform;

	//Vec3f varying_tri;
	matrix_t<3, 3, float> varying_tri; //ͼԪ(������)���� triangle coordinates (clip coordinates), written by VS, read by FS

	int render_state;

	//��Ļ�ֱ���

	//int tex_width;              // ������
	//int tex_height;             // ����߶�
	//IUINT32** texture; //[256][256]; //����

	Vec2f _uv;  //UV  // ��������ȣ�tex_width - 1  // �������߶ȣ�tex_height - 1

		//ÿ����������ߵ�������Ⱦ���ߣ��������ڻ��������Ӱ����Ⱦ���ߵĲ���
	int cull;   // 0:���ü�;1:�ü�����;2:�ü�����

	virtual Vec3f vertex(Vec3f iface, int nthvert);

	//���㴦��������ö����ÿ�����һ��ͼԪ(�����õ������Σ���󲿷��������������)���򴫵ݵ�ͼԪ��Ⱦ����Ⱦ
	//virtual bool fragment(Vec3f bar, TGAColor& color);

	void vertex_shader(vertex_t* v1,  int nfaces_index, int vertex_index);
	void frag_shader(vertex_t& frag_Vertex_t, IUINT32& color);
};
//��.obj�ļ��У����Ǿ����ԡ� vt u v����ͷ���У����Ǹ�����������������
//�����ߡ� fx / x / xx / x / xx / x / x�����м䣨б��֮�䣩�������Ǵ������ζ������������
//��������������ڣ���������ͼ��Ŀ�� - �߶ȣ��������Ҫ������Ⱦ�е���ɫ

//��ÿ������ʹ��ÿ��shader��Ⱦ ��д��buffer�����ã��У����ﴦ����Ļ�ֱ��ʣ�
//����devece �����bufferд����Ļ�����ﴦ��