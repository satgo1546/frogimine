//=============================================================================
// ■ global.cpp
//-----------------------------------------------------------------------------
//   全局包含脖子文件。系统已经去掉了头，可以安全食用了。
//=============================================================================

#ifndef INCLUDE_GLOBAL_H
#define INCLUDE_GLOBAL_H

//---------------------------------------------------------------------------
// ● 定义类型
//   因为没有头，所以只能这样定义uint*_t了。
//---------------------------------------------------------------------------
typedef __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;
typedef uint32_t type_address;
typedef uint16_t type_port;
struct pos {
	int x;
	int y;
};
struct rect {
	int x;
	int y;
	unsigned int width;
	unsigned int height;
};

#endif
