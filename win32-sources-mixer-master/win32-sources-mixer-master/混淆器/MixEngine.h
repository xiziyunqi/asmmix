#pragma once
#include "Instruction.h"
#include <vector>
using std::vector;

class MixEngine {

protected:
	int		m_hardness;
public:
	virtual bool mix( const Instruction& pInsObj , vector<Instruction>* vecMixer ) = 0;
	void setHardness(int hardness);
};

// ���ݴ���ָ�������
class MixEngine_tran : public MixEngine {

public:
	virtual bool mix( const Instruction& pInsObj , vector<Instruction>* vecMixer ) override;
};

// λ����ָ�������
class MixEngine_bit : public MixEngine {

public:
	virtual bool mix( const Instruction& pInsObj , vector<Instruction>* vecMixer ) override;
};


// ������תָ�������
class MixEngine_jcc : public MixEngine {

public:
	virtual bool mix( const Instruction& pInsObj , vector<Instruction>* vecMixer ) override;
};

class MixEngine_call : public MixEngine
{
public:
	virtual bool mix(const Instruction& pInsObj, vector<Instruction>* vecMixer) override;
};

