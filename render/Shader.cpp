#include "Shader.h"
#include "ShadingCalculate.h"
#include "Pipline.h"

Shader::Shader()
{
	v1 = new vertex_t();
	v2 = new vertex_t();
	v3 = new vertex_t();
}

Shader::~Shader()
{
	delete(v1);
	delete(v2);
	delete(v3);
}


//IShader::~IShader() {}

//Ϊ��ʹ��GPU�Ĳ�������

//�Զ���ִ�� 
//1.����任��͸��ͶӰ��  
//2.�𶥵���ռ��㡢���㶯����ɫ����Ƥ��������㡢����
//1.��������ϵ����������ϵ��ת��
//2.CVV�ռ�ü�(��׶�ü�)
//2.��ʼ���� uv�ĸ�ֵ


//�������ɱ任�Լ����յĶ��㣬��λ�úͷ����������������ռ��ʾ��

//���� Vec4f ���������
Vec3f Shader::vertex(Vec3f iface, int nthvert) {
	Vec3f gl_Vertex = iface;

	return gl_Vertex;
}

void Shader::vertex_shader(vertex_t* v1,int nfaces_index,int vertex_index)
{
	Vec3f v11 = mModel->vert(nfaces_index,vertex_index); //��ʵ����

	v1->pos = point_t(v11.x, v11.y, v11.z, 1);

	v1->tc = mModel->uv(nfaces_index, vertex_index); //��ʵUV

	Vec3f vNormal = mModel->normal(nfaces_index, vertex_index);

	v1->normal = Vec4f(vNormal.x, vNormal.y, vNormal.z,0);

	cross(v1->worldPos ,v1->pos , transform.model);
	//ͶӰ���� cvv�ռ�
	cross(v1->project_pos, v1->pos, transform.mvp);
	//����ת��������ռ�
	cross(v1->world_normal, v1->normal, transform.model);
}

void Shader::frag_shader(vertex_t& frag_Vertex_t, IUINT32& color)
{

	float surfaceLight = ComputeNDotL(frag_Vertex_t.worldPos, frag_Vertex_t.world_normal, dirLight.dir);


	//ǰ����������ת�����������ڴ洢���
	float rhw = frag_Vertex_t.pos.w; 


	if (render_state & RENDER_STATE_COLOR)
	{
		//תΪ255

		TGAColor m_d = mModel->diffuse(frag_Vertex_t.tc);
		TGAColor m_s = mModel->specular(frag_Vertex_t.tc);
		//TGAColor m_g = mModel->

		int R = m_d.bgra[2] + m_s.bgra[2];
		int G = m_d.bgra[1] + m_s.bgra[1];
		int B = m_d.bgra[0] + m_s.bgra[0];


		//��֤��0-255֮��
		R = CMID(R, 0, 255);
		G = CMID(G, 0, 255);
		B = CMID(B, 0, 255);

		////�����ؽ׶� �������ͼ��������ȣ��Ƿ�Ҫ������Ӱ
		//if (device->shadowbuffer != NULL)
		//{
		//	float z = scanline->v.shadowPos_z;

		//	//	if (pcfDepth >0 && z > pcfDepth && pcfDepth !=0)
		//		//{
		//		//	//printf("nowZ========%f------oldZ==========%f\n", z, device->shadowbuffer[scanlineY*width + scanlineX]);
		//		//	R = R * 0.7;
		//		//	G = G * 0.7 ;
		//		//	B = B * 0.7 ;
		//		//}
		//}

		color = (R << 16) | (G << 8) | (B);  //�ϲ�RGBΪһ��int

	}

	else if (render_state & RENDER_STATE_TEXTURE)
	{
		//if (mShader->mModel != nullptr)
		//{
			TGAColor mTgacolor = mModel->diffuse(frag_Vertex_t.tc);
			int R = mTgacolor.bgra[2] - '0' + 48;
			int G = mTgacolor.bgra[1] - '0' + 48;
			int B = mTgacolor.bgra[0] - '0' + 48;
			//R *= surfaceLight;
			//G *= surfaceLight;
			//B *= surfaceLight;
			color = (R << 16) | (G << 8) | (B);
		//}

		//�����ؽ׶� �������ͼ��������ȣ��Ƿ�Ҫ������Ӱ
		//if (device->shadowbuffer != NULL)
		//{
		//	float z = scanline->v.shadowPos_z;

		//	/*if (pcfDepth > 0 && z > pcfDepth && pcfDepth != 0)
		//	{
		//		int R = (cc & (0xff0000)) >> 16;
		//		int G = (cc & (0x00ff00)) >> 8;
		//		int B = (cc & (0x0000ff));
		//		R *= 0.7;
		//		G *= 0.7;
		//		B *= 0.7;
		//		cc = (R << 16) | (G << 8) | (B);
		//	}*/
		//	//color = cc;
		//}
	}

	//�����ֵ
	else if (render_state & (RENDER_STATE_verterNormal_color))
	{
		//asset(v.color.r<0.2f);
		//��ȡ��ɫ 0-1
		float r = frag_Vertex_t.color.x + AmbientLight.r; //* pixRhw; 
		float g = frag_Vertex_t.color.y + AmbientLight.g;//* pixRhw;
		float b = frag_Vertex_t.color.z + AmbientLight.b;//* pixRhw;


		float verterLight = frag_Vertex_t.vertexLight;
		//+ scanline->step.vertexLight;

	//תΪ255
		int R = (int)(r * 255.0f * verterLight);
		int G = (int)(g * 255.0f * verterLight);
		int B = (int)(b * 255.0f * verterLight);

		//��֤��0-255֮��
		R = CMID(R, 0, 255);
		G = CMID(G, 0, 255);
		B = CMID(B, 0, 255);

		//λ���� 
		color = (R << 16) | (G << 8) | (B);  //�ϲ�RGBΪһ��int

	}

	else if (render_state & (RENDER_STATE_surfaceNormal_color))
	{
		//��ȡ��ɫ 0-1
		float r = frag_Vertex_t.color.x;// *pixRhw; 
		float g = frag_Vertex_t.color.y;// *pixRhw;
		float b = frag_Vertex_t.color.z;// *pixRhw;

		//תΪ255
		//int R = (int)(r * 255.0f * surfaceLight);
		//int G = (int)(g * 255.0f * surfaceLight);
		//int B = (int)(b * 255.0f * surfaceLight);

		int R = (int)(r * 255.0f);
		int G = (int)(g * 255.0f);
		int B = (int)(b * 255.0f);

		//��֤��0-255֮��
		R = CMID(R, 0, 255);
		G = CMID(G, 0, 255);
		B = CMID(B, 0, 255);

		//λ���� 
		color = (R << 16) | (G << 8) | (B);  //�ϲ�RGBΪһ��int

	}
}
