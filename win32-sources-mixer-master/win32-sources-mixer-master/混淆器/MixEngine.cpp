#include "stdafx.h"
#include "MixEngine.h"
#include <ctime>



// �����ݴ���ָ����м򵥵Ļ���
bool MixEngine_tran::mix(const Instruction& pInsObj, vector<Instruction>* vecMixer)
{
	srand(time(nullptr));

	if (pInsObj.type() != e_tran)
	{
		return false;
	}

	if (vecMixer == nullptr)
		return false;

	vecMixer->clear();

	/**
	* ������ʽ��
	* ��Ԥ�����ָ����뵽ԭָ�����Χ.
	*/
	char* ins[10] =
	{
		"add esp,2;add esp,2;sub esp,4",
		"ADD EAX,ECX; NEG ECX; ADD ECX,EAX;SUB EAX,ECX;XCHG EAX,ECX",
	};


	int count = m_hardness > _countof(ins) ? _countof(ins) : m_hardness;

	int pos = rand() % count;
	for (int i = 0; i<count; ++i)
	{
		InstructionGroup insGrp(ins[i]);
		for (auto&item : insGrp)
		{
			if( i == pos)
			vecMixer->push_back(item);
		}
	}
	vecMixer->push_back(pInsObj);
	return true;
}

// ��λ����ָ����л���
bool MixEngine_bit::mix(const Instruction& pInsObj, vector<Instruction>* vecMixer)
{
	/*
	 * ��������:
	 * call _XXXXXX
	 * db ����
	 * _XXXXXX:
	 * ԭָ��
	 * ����:
	 * call _ABCDEF_00000001	   ;\
	 * db "asdjaksdjfaosdf"		   ;| ����ָ��.
	 * _ABCDEF_00000001:		   ;/
	 * mov eax , dword ptr [ebp+8] ; ԭָ��
	 */
	if (pInsObj.type() != e_bit)
		return false;

	static int times = 0;

	if (vecMixer == nullptr)
		return false;

	vecMixer->clear();

	char buff[128];
	sprintf_s(buff, 128, "ABCDEF_%08d", times++);

	Instruction ins0;
	Instruction ins1;
	Instruction ins2;
	Instruction ins3;


	ins0.setMnemonic("call");
	ins0.setOperator1(buff);

	strcat_s(buff, ":");
	ins2.setMnemonic(buff);

	ins1.setMnemonic("db");
	buff[0] = '\"';

	if (m_hardness >= 125)
		m_hardness = 125;

	for (int i = 1; i < m_hardness; ++i)
	{
		buff[i] = rand() % ('z' - 'a') + 'a';
	}
	buff[m_hardness] = '\"';
	buff[m_hardness+1] = 0;

	ins1.setOperator1(buff);


	ins3.setMnemonic("add");
	ins3.setOperator1("esp");
	ins3.setOperator2("4");

	vecMixer->push_back(ins0);
	vecMixer->push_back(ins1);
	vecMixer->push_back(ins2);
	vecMixer->push_back(ins3);
	vecMixer->push_back(pInsObj);

	times++;
	return true;
}

// ��������ת���л���
bool MixEngine_jcc::mix(const Instruction& pInsObj, vector<Instruction>* vecMixer)
{

	if (pInsObj.type() != e_jcc)
		return false;

	/*
	ԭָ� JCC  ԭʼƫ��

	��ָ�
	or eax,080000000h
	js J_H_Z_L_XXXXX	// 3
	db	"32�ֽ�����"		// 1
	J_H_Z_L_XXXXX:		// 2
	and eax,0x7FFFFFFF
	JCC  J_H_Z_L_XXXXX  // 0

	*/

	static int times = 0;

	if (vecMixer == nullptr)
		return false;

	vecMixer->clear();

	char buff[128];
	sprintf_s(buff, 128, "J_H_Z_L_X_%08d", times++);

	Instruction ins0("or eax,080000000h");
	Instruction ins1; // db "XXXXXXXXXXX"
	Instruction ins2; // J_H_Z_L_X_00000000X:
	Instruction ins3; // JS J_H_Z_L_X_00000000X
	Instruction ins4("and eax,0x7FFFFFFF");

	char* regs[] = 
	{
		"eax","ebx","ecx","edx","esi","edi","ebp","esp"
	};

	int reg = rand() % _countof(regs);
	ins0.setOperator1(regs[reg]);
	ins4.setOperator1(regs[reg]);


	ins3.setMnemonic("JS");
	ins3.setOperator1(buff);

	strcat_s(buff, ":");
	ins2.setMnemonic(buff);




	ins1.setMnemonic("db");
	buff[0] = '\"';
	for (int i = 1; i <= m_hardness; ++i)
	{
		buff[i] = rand() % ('z' - 'a') + 'a';
	}
	buff[m_hardness + 1] = '\"';
	buff[m_hardness + 2] = 0;

	ins1.setOperator1(buff);


	times++;

	vecMixer->push_back(ins0);
	vecMixer->push_back(ins3);
	vecMixer->push_back(ins1);
	vecMixer->push_back(ins2);
	vecMixer->push_back(ins4);
	vecMixer->push_back(pInsObj);


	return true;
}

void MixEngine::setHardness(int hardness)
{
	m_hardness = hardness;
}

bool MixEngine_call::mix(const Instruction& pInsObj, vector<Instruction>* vecMixer)
{
	if (pInsObj.type() != e_call)
		return false;

	if (vecMixer == nullptr)
		return false;

	// ��Ҫ�ж�
	return true;
}
