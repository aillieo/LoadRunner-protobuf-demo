//ע��˴��ĺ궨����Ҫд��#include "pb.h"֮ǰ 

//�������dll��Ŀ�ڲ�ʹ��__declspec(dllexport)���� 

//��dll��Ŀ�ⲿʹ��ʱ����__declspec(dllimport)���� 

#define DLL_IMPLEMENT  

#pragma comment(lib, "ws2_32.lib")

#include "pb.h"  
#include <Windows.h>  
#include <intrin.h>  
#include <stdlib.h>  
#include <string.h>  
#include <stdio.h>

#include "MsgName.pb.h"


int constructMessage(char* des , short nType, int nIndex, const std::string &dataStr )
{

	//������Ч���� ������nSize����ռ���ֽ�
	short nSize = sizeof(short) + sizeof(int) +  dataStr.length()*sizeof(char) ;


	int pos = 0;

	nSize = htons(nSize);
	memcpy(des + pos,&nSize,sizeof(short));
	pos += sizeof(short);

	nType = htons(nType);
	memcpy(des + pos,&nType,sizeof(short));
	pos += sizeof(short);

	nIndex = htonl(nIndex);
	memcpy(des + pos,&nIndex,sizeof(int));
	pos += sizeof(int);

	memcpy(des + pos,dataStr.c_str(),dataStr.length()*sizeof(char));
	pos += dataStr.length()*sizeof(char);


	//���ع�����ɵ���Ϣ�ĳ���
	return pos;

}




DLL_API int getSerializedName(char* des, char* name)
{

	// ����һ��MsgName
	MsgName msgname; 

	// Ϊ�䴫��name�ֶ�
	msgname.set_name(name);

	std::string s_data;

	// ���л���s_data
	msgname.SerializeToString(&s_data);

	// ������Ϣ������des
	int len = constructMessage(des, 0, 0, s_data);

	// ���ع����ɵ���Ϣ�ĳ���
	return len;

}

DLL_API int getParsedName(char* name, char* src, int len)
{

	// ȥ����Ϣǰ���� nType �� nIndex ������
	int offset = sizeof(short) + sizeof(int);

	if(len<=offset) return -1;

	std::string data;
	data.assign(src + offset , len - offset);

	// ����һ��MsgName
	MsgName msgname; 

	// ��data�����л�
	if (!msgname.ParseFromString(data)) return -1;

	// �õ���Ϣ�е�name������name
	strcpy(name, msgname.name().c_str());

	return 0 ;

}

