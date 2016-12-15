#pragma once;  

//�ú������dll��Ŀ�ڲ�ʹ��__declspec(dllexport)����  

//��dll��Ŀ�ⲿʹ��ʱ����__declspec(dllimport)����  

//��DLL_IMPLEMENT��pb.cpp�ж���  

#ifdef DLL_IMPLEMENT  
#define DLL_API __declspec(dllexport)  
#else  
#define DLL_API __declspec(dllimport)  
#endif  

#include <string>

int constructMessage(char* des , short nType, int nIndex, const std::string &dataStr);


extern "C" DLL_API int getSerializedName(char* des, char* name);

extern "C" DLL_API int getParsedName(char* name, char* src, int len);
