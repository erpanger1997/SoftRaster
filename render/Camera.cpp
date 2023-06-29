#include "Camera.h"



//���������
void matrix_set_lookat_r(Matrix44f*m, const Vec4f *eye, const Vec4f *eyeTarget, const Vec4f *up)
{
	//��ȡ���������ϵ��3�������� ��Ϊ��ǰ��Ŀ���ΪUnity����������ϵ�����в��Ҳ��ѭ���ַ���
	Vec4f zaxis = (*eyeTarget - *eye).normalize(); //zaxis �����Z�� ����Ļ��
	Vec4f xaxis = cross(*up, zaxis).normalize();
	Vec4f yaxis = cross(zaxis, xaxis);

	//���� ������������������ϵ����ת 
	Matrix44f rotationM;
	rotationM[0][0] = xaxis.x;
	rotationM[1][0] = xaxis.y;
	rotationM[2][0] = xaxis.z;

	rotationM[0][1] = yaxis.x;
	rotationM[1][1] = yaxis.y;
	rotationM[2][1] = yaxis.z;

	rotationM[0][2] = zaxis.x;
	rotationM[1][2] = zaxis.y;
	rotationM[2][2] = zaxis.z;

	rotationM[0][3] = rotationM[1][3] = rotationM[2][3] = 0.0f;
	rotationM[3][0] = rotationM[3][1] = rotationM[3][2] = 0.0f;
	rotationM[3][3] = 1.0f;

	//���� ������������������ϵ��λ��
	Matrix44f transM = Matrix44f().identity();

	transM[3][0] = -eye->x;
	transM[3][1] = -eye->y;
	transM[3][2] = -eye->z;

	//*m = transM * rotationM;
	matrix_mul(*m, transM, rotationM); //����-��������� ��ƽ�ƣ�����ת
}



//��Ϊ�ʼ��������ϵ����������ϵ�غϣ�������˶����Ǵ���������ϵ ת����������ϵ��������ʵ��״̬�ǣ������š�����ת����ƽ�ƣ�
//������������ϵת����������ϵ  �����෴  ��Ϊ (T*R)������� = ��R�������*��T������� ��ƽ�ơ�����ת�������ţ�
// ���������  eye�������� front��ǰ��  up��Y��
void matrix_set_lookat(Matrix44f*m, const Vec4f *eye, const Vec4f *eyeTarget, const Vec4f *up)
{
	//��ȡ���������ϵ��3�������� ��Ϊ��ǰ��Ŀ���ΪUnity����������ϵ�����в��Ҳ��ѭ���ַ���
	Vec4f zaxis = (*eyeTarget - *eye).normalize(); //zaxis �����Z�� ����Ļ��
	Vec4f xaxis = cross(*up, zaxis).normalize();
	Vec4f yaxis = cross(zaxis, xaxis);

	//���� ������������������ϵ����ת 
	Matrix44f rotationM;
	rotationM[0][0] = xaxis.x;
	rotationM[1][0] = xaxis.y;
	rotationM[2][0] = xaxis.z;

	rotationM[0][1] = yaxis.x;
	rotationM[1][1] = yaxis.y;
	rotationM[2][1] = yaxis.z;

	rotationM[0][2] = zaxis.x;
	rotationM[1][2] = zaxis.y;
	rotationM[2][2] = zaxis.z;

	rotationM[0][3] = rotationM[1][3] = rotationM[2][3] = 0.0f;
	rotationM[3][0] = rotationM[3][1] = rotationM[3][2] = 0.0f;
	rotationM[3][3] = 1.0f;

	//���� ������������������ϵ��λ��
	Matrix44f transM = Matrix44f();
	transM.identity();
	transM[3][0] = -eye->x;
	transM[3][1] = -eye->y;
	transM[3][2] = -eye->z;

	//*m = transM * rotationM;
	matrix_mul(*m, transM, rotationM); //����-��������� ��ƽ�ƣ�����ת
}


//�����������ϵ�е�һ�� P_V, ����͸�ӱ任��ΪP_H(�����ֱ�ΪP_Hx, P_Hy, P_Hz, 1)
//P_Hz = -P_Vz  *  (far + near) / (far - near) - 2far*near / (far - near)
//P_Hw = -P_Vz��

//��Ϊ����͸�ӳ����󶥵��w������1  ��ô��Χ�� -1 ��1 ��x ӳ�䵽 0zl �� 1 �� ���� x�� = x/2 + 0.5 

//͸�Ӿ���  �����������ϵ������ת��Ϊ�������õ���Ļ����
//zn ��ƽ��Z
//zf Զƽ��Z
//	float aspect = (float)width / ((float)height); �ֱ��ʵĿ���
///fovy = view frustum ��Z��нǻ�����
void matrix_set_perspective(Matrix44f* m, float fovy, float aspect, float zn, float zf)
{
	float fax = 1.0f / (float)tan(fovy * 0.5f);  //cot@
	(*m).set_zero();
	(*m)[0][0] = fax / aspect;
	(*m)[1][1] = fax;
	(*m)[2][2] = zf / (zf - zn);
	(*m)[3][2] = -zn * zf / (zf - zn);
	(*m)[2][3] = 1; //��W=1
}


void CameraInit()
{
}

//�����λ��ˢ�º�,�豸�ľ���ı�
void camera_update(camera* caneraMain)
{

	matrix_set_perspective(&caneraMain->projection_trans, caneraMain->fov, caneraMain->aspect, caneraMain->zn, caneraMain->zf); //�趨��ƽ��Ϊ1������WȡֵΪ1�ͺ��ˡ����ŵ�ͶӰ��ȽϷ���

	//���� view���� ���Ǽ����matrix_Obj2World,������ǰ�camera����obj�� World2view ������������� TOdo:�Ժ����Ӱ�������������
	
	//matrix_World2Obj(&device->transform.view, caneraMain->rotation,caneraMain->pos, 1);

	//Vec4f right, eyeTarget, up, front;
	//vector_add(&eyeTarget, &caneraMain->eye, &caneraMain->front);
	//��������� �������λ��
	matrix_set_lookat(&caneraMain->view, &(caneraMain->eye), &caneraMain->eyeTarget, &caneraMain->worldup);

}

//ƽ�й�=�������� ���Դ=͸�Ӿ���
//����Ƕ�̬�ƹ⣬��Ҫˢ��

//TODO����ʱʹ�����������fov
void camera_updateShadow(camera * caneraShadow, camera *  camera_main)
{
	matrix_set_perspective(&caneraShadow->projection_trans, camera_main->fov, camera_main->aspect, camera_main->zn, camera_main->zf);
	//��������� �������λ��
	matrix_set_lookat(&caneraShadow->view, &(caneraShadow->eye), &caneraShadow->eyeTarget, &caneraShadow->worldup);



}

