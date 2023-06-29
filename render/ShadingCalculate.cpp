#include "ShadingCalculate.h"

// ����������ͷ�������֮��Ƕȵ�����  
// ����0��1֮���ֵ  
float ComputeNDotL(const point_t& vertex, const Vec4f& normal, const point_t& lightPosition)
{
	//TODO:���������򵥼���нǣ��� �ƹ�λ��-���嶥��λ�� ��ʸ��   
	//����� ���㷴�䣬��Ҫ�� ���嶥��λ��-�ƹ�λ�� ��ʸ��
	//vector_sub(&lightDirection, vertex , lightPosition);

	Vec4f lightDirection = lightPosition - vertex;
	lightDirection.normalize();

	float dot = normal * lightDirection;

	//float correctionDot = (dot + 1)*0.5f;
	return CMID(dot, 0.0f, 1.0f);
}

//���������ĵ������
float ComputeCameraToVertor(const point_t& vertex, const Vec4f& normal, const point_t& camera_pos)
{
	Vec4f  CameraToVertor=  camera_pos- vertex;
	CameraToVertor.normalize();

	float dot = normal * CameraToVertor;

	return dot; 
}

//���㶥�㵽�ƹ�ľ���,���ڲ�����Ӱ
//float DisVertexToLight(const point_t *Light, Vec4f* VertertPosInWorld)
//{
//
//	Vec4f dis;
//	vector_sub(&dis, Light, VertertPosInWorld);
//	return vector_length(&dis);
//}


//���㶥��ĵƹ�ǿ�Ⱥ���ɫ
float calculateVertexLight(const point_t *v1, Vec4f& normal)
{
	normal.normalize();
	//�ƹ���������ڳ˻�����ɫ     (0-1)֮�� ��������ɫ������
	float surfaceLight = ComputeNDotL(*v1, normal, dirLight.dir); //����ƹ�

	return surfaceLight;

}

//�����޳� �������Ϊ���
float CullCalcutate(const point_t *v1, const point_t *v2, const point_t *v3, const point_t *camera_pos)
{
	Vec4f cross21, cross31, surfaceNormal;

	cross21 = *v2 - *v3;
	cross31 = *v2 - *v1;
	surfaceNormal = cross(cross21, cross31);
	//��˷���  �������������жϲ�˽���ķ���ʹ�����ֶ��ɣ���������ϵ��ʹ�����֡����ǵ�mesh������˳ʱ��
	
	point_t center;
	center= *v1+ *v2 + *v3;
	center = center * 0.333f;

	surfaceNormal.normalize();

	//�޳����� 
	float cull = ComputeCameraToVertor(center, surfaceNormal, *camera_pos); 

	return cull;
}


//����ƽ����Ⱦ������淨�ߡ����սǶ�
float calculateGroudShader(const point_t *v1, const point_t *v2, const point_t *v3)
{
	Vec4f cross1, cross2, surfaceNormal;
	point_t center;

	//����ƽ����Ⱦ����ʹ���淨�ߣ������������ǹ�Դλ�õ�������ĵ㡣

	//���ڶ�����Ⱦ��û���淨�ߣ��������� ÿ�����أ��������������㷨ʸ����ֵ���ġ�

	// �������ϵ������Ǹ÷������ÿ�����㷨�������ĵ��ƽ��ֵ

	//�������Ч��  �ڶ���׶κ����ؽ׶μ��㶼���ԡ�
	//���Ǽ�����յ����ȣ� ��Ϊ �ƹ��������������꣬����������ת����������ϵ����׶μ���������

	cross1 = *v2 - *v3;
	cross2 = *v2 - *v1;
	surfaceNormal = cross(cross1, cross2);
	//��˷���  �������������жϲ�˽���ķ���ʹ�����ֶ��ɣ���������ϵ��ʹ�����֡����ǵ�mesh������˳ʱ��

	//��ķ������� === 3������ķ����������������ۼӺ����3��
	center = *v1 + *v2 + *v3;
	center = center * 0.333f;
	surfaceNormal.normalize();

	//�ƹ���������ڳ˻�����ɫ     (0-1)֮�� ��������ɫ������ 
	float surfaceLight = ComputeNDotL(center, surfaceNormal, dirLight.dir); //����ƹ�
	//printf("surfaceLight��ǰ%f", surfaceLight);
	return surfaceLight;

}


//1.����������:���ظö������ɫ

color_t Lambert(transform_t* mainTrans, Vec4f *v_Obj, Vec4f* normal, Vec4f* lightPos, color_t diffuseColor, color_t ambientColor)
{
	//������任����ͼ�ռ�  
	Vec4f  ObjInView;
	cross(ObjInView,(*v_Obj) , mainTrans->mv);

	//������任�����͸�ӿռ�  
	Vec4f  ObjInCVV;
		//= (*v_Obj) * mainTrans->mvp;
	cross(ObjInCVV, (*v_Obj), mainTrans->mvp);
	//Vec4f* normalInView = NULL;
	//�����߱任����ͼ�ռ�
	//matrix_apply(normalInView, normal, &mainTrans->mv);

	Vec4f normalInView;
		//= (*normal) * mainTrans->mv;

	cross(normalInView, (*normal), mainTrans->mv);
	//TODO:����ѵƹ�ת����ͼ�ռ�

	// ������ͼ�ռ�ĵƹⷽ��
	Vec4f lightDirInView = *lightPos - ObjInView;

	//-----------------���ؽ׶�------------

	//	// ��һ��
	//	In.normalInView = normalize(In.normalInView);
	//	In.lightDirInView = normalize(In.lightDirInView);
	//
	//	// ����Lambertģ�ͣ����ߵ������ⷽ�����������
	//	float4 diffuse = max(0, dot(In.normalInView, In.lightDirInView));
	//	diffuse = diffuse * diffuseColor;
	//
	//	Out.color = ambientColor + diffuse;


	//����Lambertģ�ͣ����ߵ������ⷽ�����������
	float diffuse = max(0, (normalInView* lightDirInView));

	return ambientColor + diffuseColor * diffuse;
}


//2.������߹�������� Ҳ����Phong����ģ��
color_t Phong(transform_t* mainTrans, Vec4f *posInObj, Vec4f *normal, Vec4f* lightPos, Vec4f* cameraPos, color_t diffuseColor, color_t ambientColor, color_t specularColor)
{

	//	Output.position = mul(Input.position, matWorldViewProjection);
	//	Output.normalInView = normalize(mul(Input.normal, matWorldView));
	//	Output.lightDirInView = normalize(lightPos - mul(Input.position, matWorldView));
	//	float3 position = mul(Input.position, matWorldView);
	//	Output.viewDirInView = normalize(matView[3].xyz - position);
	//	return Output;

	//������任����ͼ�ռ�  
	Vec4f  posInView;
		//= (*posInObj) * mainTrans->mv;

	cross(posInView, (*posInObj), mainTrans->mv);
	//������任�����͸�ӿռ�  
	Vec4f  posInCvv;
		//= (*posInObj) * mainTrans->mvp;
	cross(posInCvv, (*posInObj), mainTrans->mvp);

	//�����߱任����ͼ�ռ�
	//matrix_apply(normalInView, normal, &mainTrans->mv);
	Vec4f normalInView;
		//=  (*normal)  * mainTrans->mv;
	cross(normalInView, (*normal), mainTrans->mv);

	// ������ͼ�ռ�ĵƹⷽ��
	Vec4f lightDirInView =  *lightPos- posInView;

	//������ͼ�ؼ��������������ķ���
	Vec4f cameraDirInView =  *cameraPos - posInView;
	cameraDirInView.normalize();

	//----------------pix shader-----------------------------------//
	//	float4 diffuse = max(0, dot(In.normalInView, In.lightDirInView));
	//	diffuse = diffuse * diffuseColor;
	//
	//	float3 vReflect = normalize(2 * dot(In.normalInView, In.lightDirInView) * In.normalInView - In.lightDirInView);
	//
	//	float4 specular = specularColor * pow(max(0, dot(vReflect, In.viewDirInView)), 2);
	//
	//	Out.color = ambientColor + diffuse + specular;

	float diffuse = max(0, (normalInView* lightDirInView));
	diffuseColor = diffuseColor* diffuse;

	//��������
	Vec4f  vReflect = (normalInView) * (2 * (normalInView*lightDirInView)) - lightDirInView;
	vReflect.normalize();

	//��ͨ���������߹�

	return  ambientColor + diffuseColor + specularColor * pow(max(0, (vReflect* cameraDirInView)), 2);
}

//TODO: ��ֵ�Ժ����
float PixShader_Phong()
{
	return 0;
}

//Lambertģ���ܺܺõı�ʾ�ֲڱ���Ĺ��գ������ܱ��ֳ����淴��߹⡣1975��Phong Bui Tong������Phongģ�ͣ�����˼��㾵��߹�ľ���ģ�ͣ����淴���ǿ�뷴����ߺ����ߵļн�a��أ�
//
//Ispecular = Ks * Is*(cos a) n
//
//����KsΪ�������ĸ߹�ϵ����IsΪ��ǿ��a�Ƿ���������ߵļнǣ�nΪ�߹�ָ����nԽ�������Խ�⻬�������Խ���У��߹ⷶΧԽС�����V��ʾ���㵽�ӵ�ĵ�λ������R��ʾ����ⷴ����cos a�ɱ�ʾΪV��R�ĵ����ģ�Ϳɱ�ʾΪ��
//
//Ispecular = Ks * Is*(V��R)n
//
//��������R������������L������ָ���Դ�������巨����N�����
//
//R = (2N��L)N �C L
//
//1) VertexShader
//float4x4 matWorldViewProjection;
//float4x4 matWorldView;
//float4x4 matView;
//float3 lightPos;
//
//struct VS_INPUT
//{
//	float4 position : POSITION0;
//	float3 normal : NORMAL;
//};
//
//struct VS_OUTPUT
//{
//	float4 position : POSITION0;
//	float3 normalInView : TEXCOORD0;
//	float3 lightDirInView : TEXCOORD1;
//	float3 viewDirInView : TEXCOORD2;
//};
//
//VS_OUTPUT vs_main(VS_INPUT Input)
//{
//	VS_OUTPUT Output;
//
//	Output.position = mul(Input.position, matWorldViewProjection);
//	Output.normalInView = normalize(mul(Input.normal, matWorldView));
//	Output.lightDirInView = normalize(lightPos - mul(Input.position, matWorldView));
//	float3 position = mul(Input.position, matWorldView);
//	Output.viewDirInView = normalize(matView[3].xyz - position);
//	return Output;
//}
//
//
//
//2)	PixelShader
//
//float4 ambientColor;
//float4 diffuseColor;
//float4 specularColor;
//
//struct PS_INPUT
//{
//	float3 normalInView : TEXCOORD0;
//	float3 lightDirInView : TEXCOORD1;
//	float3 viewDirInView : TEXCOORD2;
//};
//
//struct PS_OUTPUT
//{
//	float4 color : COLOR0;
//};
//
//
//PS_OUTPUT ps_main(PS_INPUT In)
//{
//	PS_OUTPUT Out;
//
//	float4 diffuse = max(0, dot(In.normalInView, In.lightDirInView));
//	diffuse = diffuse * diffuseColor;
//
//	float3 vReflect = normalize(2 * dot(In.normalInView, In.lightDirInView) * In.normalInView - In.lightDirInView);
//
//	float4 specular = specularColor * pow(max(0, dot(vReflect, In.viewDirInView)), 2);
//
//	Out.color = ambientColor + diffuse + specular;
//
//	return Out;
//}

