// ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <fstream>
#include "InstructionMixer.h"
#include <iostream>
using namespace std;

#define HARDNESS_LOW 3
#define HARDNESS_HIG 64
int main(int argc, char* argv[])
{
	char srcFilePath[ 260 ];
	char desFilePath[ 260 ];
	int hardness = HARDNESS_LOW;

	if( argc < 3 ) {
		//cout << "�����и�ʽ�� Դ����ļ�·�� ����ļ�·��" << endl;
		cout << "����Դ�ļ�·��:";
		cin.getline( srcFilePath,260 );
		cout << "����Ŀ���ļ�·��:";
		cin.getline( desFilePath , 260 );

		argv[ 1 ] = srcFilePath;
		argv[ 2 ] = desFilePath;
		cout << "�����������1~63:";
		cin >> hardness;
	}

	if (argc == 4)
	{
		hardness = atol(argv[3]);
		if (hardness <= 0)
			hardness = HARDNESS_LOW;
		if (hardness > 64)
			hardness = HARDNESS_HIG;
	}

	Instruction::initInstructionLibrary();

	// ��������1
	MixEngine_bit mix_bit;
	mix_bit.setHardness(hardness);
	
	MixEngine_tran mix_tran;
	mix_tran.setHardness(hardness);

	// ��������2
	MixEngine_jcc mix_jcc;
	mix_jcc.setHardness(hardness);

	// ������
	InstructionMixer mixer;
	

	// ������������ӽ���������
	mixer.addEngine( &mix_tran );
	mixer.addEngine( &mix_bit );
	mixer.addEngine( &mix_jcc );
	
	// �򿪺ʹ����ļ�
	ofstream oFile( argv[ 2 ]  );
	ifstream iFile( argv[1] , ios::in  );

	if( iFile.is_open( )==false) {
		cout << argv[ 1 ] << "�ļ��޷���" << endl;
		return 0;
	}
	if( oFile.is_open( ) == false) {
		cout << argv[ 2 ] << "�ļ��޷���" << endl;
		return 0;
	}


	char line[200];
	vector<Instruction> vecIns;
	
	// ��ȡÿһ�л��Դ�ļ��Ĵ���
	while( iFile.getline(line,200) ) {

		// ����
 		if( mixer.mix( line , &vecIns ) ) {
			// �����ɹ����򽫻����������������ļ�
			for( auto &i : vecIns ) {
				oFile << i << endl;
			}
		}
		else {
			// ����ʧ����ԭָ��������ļ���
			oFile << line << endl;
		}
	}


	oFile.close( );
	iFile.close( );
	return 0;
}

