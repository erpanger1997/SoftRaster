
#include "geometry.h"

//ģ�嶨��󣬾͸����ͱ��һ��������ֱ����ʽʵ������
//�����㲻�˵�����£�����һЩ�������󣩲���Ҫģ��ר�Ż�

//ģ��ר�Ż� : Ҳ��ģ���ػ�������ʱ����ģ�����������ʵ����ģ�壬��Ϊȫ�ػ���ƫ�ػ� 

//�� template<typename T1, typename T2>����Ϊ��
//ȫ�ػ������޶���ģ��ʵ�ֵľ�������  ��template <>  
//ƫ�ػ�����������ģ���ж�����ͣ���ôֻ�޶����е�һ���֣� template <> 
//�����ں���ģ�壬ȴֻ��ȫ�ػ�������ƫ�ػ�����Ϊƫ�ػ��Ĺ��ܿ���ͨ��������������ɡ�

//��ʵƫ�ػ� ��û��ʵ����ģ�壬�������������ƣ���һ���µ�ģ��

//ȫ�ػ�����������ʵ������ģ�塣

//�������ǿ��� ȫ�ػ� Ҫд��CPP�ļ��� ƫ�ػ�����Ҫд��Hͷ�ļ�

// ��Ϊ ���캯����float ����ΪInt������ʹ������ģ�� ���ֱ�ָ������
template <> template <> 
vec<3, int>  ::vec(const vec<3, float>& v) : x(int(v.x + .5f)), y(int(v.y + .5f)), z(int(v.z + .5f)) {}

template <> template <> 
vec<3, float>::vec(const vec<3, int>& v) : x(v.x), y(v.y), z(v.z) {}

template <> template <>
vec<4, float>::vec(const vec<4, int>& v) : x(v.x), y(v.y), z(v.z),w(v.w) {}

//template <> template <> 
//vec<2, int>  ::vec(const vec<2, float>& v) : x(int(v.x + .5f)), y(int(v.y + .5f)) {}
//
//template <> template <> 
//vec<2, float>::vec(const vec<2, int>& v) : x(v.x), y(v.y) {}