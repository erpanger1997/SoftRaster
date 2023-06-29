#ifndef objectManager_h
#define objectManager_h
#include <vector>
#include "Shader.h"
#include "Lights.h"
using namespace std;
//���ڼ��������ģ�͡����񡢶��������ʡ���ͼ


//����������Ⱦ����
extern vector<Object_t> Scene_render_Objs;


//=====================================================================
// ���μ��㣺���㡢ɨ���ߡ���Ե�����Ρ���������
//=====================================================================

//�ƹ�  ���Դ  ���ڼ�����Ǿ�̬��Դ
extern dirlight_t dirLight;

//�����⣬��ʱֻ��һ���������ǿ�Ⱥ���ɫ
extern Light_t AmbientLight;


//�Ժ���ĵ����������
//����
extern vertex_t ground_mesh[6];


//��β��� ��ɫ
extern vertex_t mesh[8];

//rhw  Ҳ����  reciprocal homogeneous w    ʵ������ͼ�ռ�������ĵ�-w�ĵ��������ڻ�ԭZ�ᣬ���������ͽ���ԶС



//��Ϊ��ɫ�ǵ㣬����w= 1��   normals������������w =0
extern vertex_t box_mesh[36];


#endif