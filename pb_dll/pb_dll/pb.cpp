//注意此处的宏定义需要写在#include "pb.h"之前 

//以完成在dll项目内部使用__declspec(dllexport)导出 

//在dll项目外部使用时，用__declspec(dllimport)导入 

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

	//数据有效长度 不包含nSize本身占的字节
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

	MsgName msgname; 
	msgname.set_name(name);

	std::string s_data;
	msgname.SerializeToString(&s_data);

	int len = constructMessage(des, 0, 0, s_data);

	return len;

}

DLL_API int getParsedName(char* name, char* src, int len)
{

	int offset = sizeof(short) + sizeof(int);

	if(len<=offset) return -1;

	std::string data;
	data.assign(src + offset , len - offset);


	MsgName msgname; 
	if (!msgname.ParseFromString(data)) return -1;


	strcpy(name, msgname.name().c_str());

	return 0 ;

}

