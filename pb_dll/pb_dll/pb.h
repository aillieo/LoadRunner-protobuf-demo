#pragma once;  

//该宏完成在dll项目内部使用__declspec(dllexport)导出  

//在dll项目外部使用时，用__declspec(dllimport)导入  

//宏DLL_IMPLEMENT在pb.cpp中定义  

#ifdef DLL_IMPLEMENT  
#define DLL_API __declspec(dllexport)  
#else  
#define DLL_API __declspec(dllimport)  
#endif  

#include <string>

int constructMessage(char* des , short nType, int nIndex, const std::string &dataStr);


extern "C" DLL_API int getSerializedName(char* des, char* name);

extern "C" DLL_API int getParsedName(char* name, char* src, int len);
