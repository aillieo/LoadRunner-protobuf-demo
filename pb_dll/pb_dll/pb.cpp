//ע��˴��ĺ궨����Ҫд��#include "TestDLL.h"֮ǰ 

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


	return pos;

}




DLL_API int getSerializedName(char* des, char* name)
{

	int len;


	return len ;

}

DLL_API int getParsedName(char* name, char* src)
{

	int len;


	return len ;

}