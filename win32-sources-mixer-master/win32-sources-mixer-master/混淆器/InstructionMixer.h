#pragma once
#include "Instruction.h"
#include <vector>
#include "MixEngine.h"
using std::vector;

class InstructionMixer {

	vector<MixEngine*> m_engine;  // �������
public:

	//��ʼ����
	/*!
	 * \brief mix
	 * �������������ָ��, �����ɵĻ���ָ�������vector��.
	 * �ڻ���ʱ,�������MACRO ��,��������,����false
	 * ������������ָ����һ��δ�������ָ��(e_none),��������,����ֱ�ӷ���false
	 * ���ָ���Ǳ������. ��ѭ���������л������濪ʼ���л���.
	 * �ڵ��û�������Ĺ�����,���һ������ɹ������˻���,������Ļ������潫û�д���Ļ���.
	 * ����ֱ�ӷ���true.
	 * \ret bool ����false��ʾ����ʧ��.trueΪ�����ɹ�
	 * \param const char * pIns ��������ԭָ��
	 * \param vector<Instruction> * vecMixer �������ָ��,����ԭָ��
	 */
	bool mix( const char* pIns , vector<Instruction>* vecMixer );

	
	/*!
	 * \brief addEngine
	 * ��ӻ�������
	 * \param MixEngine * pEngine
	 */
	void addEngine( MixEngine* pEngine );
};

