#pragma once
#include <map>
#include <vector>
using std::map;

enum INSTRUCTION_CLASS 
{
	e_none,
	e_tran,// ���ݴ���ָ��,����mov��add��push��xchg��pop��
	e_bit, // λ����ָ��
	e_jcc, // ����������תָ��
	e_jmp, // ֱ����תָ��
	e_call,// ��������ָ�� ��call offset , call [address]
	e_str  // ������ָ��
};


#define MAX_OPERATORSTRING	64
#define MAX_INS				64
#define MAX_OPERAOTCOUNT	4


unsigned int hashCode( const char* pStr );

class TString;
class InstructionGroup;

class Instruction {

private:
	INSTRUCTION_CLASS	m_insClass;
	int			m_operatorCount;    // ָ�����������
	char		m_mnemonic[ MAX_INS ]; // ָ��
	char		m_operator[MAX_OPERAOTCOUNT][MAX_OPERATORSTRING]; // ������

public:
	friend InstructionGroup;
	Instruction( );
	explicit Instruction( const char* pIns);

	bool		setInstruction( const char* pIns );

	// ָ������
	
	INSTRUCTION_CLASS	type()const;
	TString		instruction( )const;
	const char* mnemonic( )const;
	const char* operator1()const;
	const char* operator2( )const;
	const char* operator3( )const;

	void		setMnemonic( const char* mnemonic );
	void		setOperator1(const char* pOperator );
	void		setOperator2( const char* pOperator );
	void		setOperator3( const char* pOperator );

	friend std::ostream& operator<<(std::ostream& o, const Instruction& ins);
	friend std::ofstream& operator<<(std::ofstream& o, const Instruction& ins);


	static bool addInstruct( const char* pIns , INSTRUCTION_CLASS type );
	static bool	initInstructionLibrary( );
	static INSTRUCTION_CLASS checkInstructClass(const char* mnemonic);
private:
protected:
	static bool m_bInit;
	static map<unsigned int, INSTRUCTION_CLASS> m_insList; // ָ��-����ӳ��
};

class InstructionGroup : public std::vector<Instruction>
{
public:
	void addInstruction(const Instruction& ins);
	
	TString toString()const;
	InstructionGroup() = default;
	InstructionGroup(const char* pIns);
	InstructionGroup(const TString& pIns);
};