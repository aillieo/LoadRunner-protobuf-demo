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

// 辅助函数 内部使用 将protobuf序列化后的字符串封装成消息发送给服务器
int constructMessage(char* des , short nType, int nIndex, const std::string &dataStr);

// 导出函数 给LoadRunner调用 输入字符串name 赋值给消息并序列化 传给des
extern "C" DLL_API int getSerializedName(char* des, char* name);

// 导出函数 给LoadRunner调用 输入接收到的消息src及长度len 反序列化 并得出name字段传给name
extern "C" DLL_API int getParsedName(char* name, char* src, int len);