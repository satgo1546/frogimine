//=============================================================================
// ■ default-font.cpp
//-----------------------------------------------------------------------------
//   绘制文本时使用的默认字体数据，仅覆盖ASCII编码中32（空格）~126（~）。
//   字体来源于Linux终端自带的lat9u-12.psfu字体。
//=============================================================================

// 我们默认这个字体要是8像素宽的，所以可以用一个字节存储一行。
const unsigned int default_font_width = 8;
const unsigned int default_font_height = 12;
const uint8_t default_font[][default_font_height] = {
	#include "generated/default-font-data.txt"
};
