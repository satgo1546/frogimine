//=============================================================================
// ■ default-font.cpp
//-----------------------------------------------------------------------------
//   绘制文本时使用的默认字体数据，仅覆盖ASCII编码中32（空格）~126（~）。
//   字体来源于Linux终端自带的lat9u-12.psfu字体。
//=============================================================================

const uint8_t default_font[][12] = {
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00011000,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00110110,
		0b00110110,
		0b00010100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b01101100,
		0b11111110,
		0b01101100,
		0b01101100,
		0b01101100,
		0b11111110,
		0b01101100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00010000,
		0b01111100,
		0b11010110,
		0b01110000,
		0b00111000,
		0b00011100,
		0b11010110,
		0b01111100,
		0b00010000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b01100010,
		0b01100110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00111000,
		0b01101100,
		0b00111000,
		0b00111000,
		0b01110010,
		0b11111110,
		0b11001100,
		0b11001100,
		0b01110110,
		0b00000000,
		0b00000000,
	},
	{
		0b00011100,
		0b00011100,
		0b00001100,
		0b00011000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00001100,
		0b00011000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00011000,
		0b00001100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00110000,
		0b00011000,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00011000,
		0b00110000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b01101100,
		0b00111000,
		0b11111110,
		0b00111000,
		0b01101100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b01111110,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00011000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11111110,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b11000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11010110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00011000,
		0b01111000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b01111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b11000110,
		0b11111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b00000110,
		0b00000110,
		0b00111100,
		0b00000110,
		0b00000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00001100,
		0b00011100,
		0b00111100,
		0b01101100,
		0b11001100,
		0b11111110,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111110,
		0b11000000,
		0b11000000,
		0b11000000,
		0b11111100,
		0b00000110,
		0b00000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000000,
		0b11000000,
		0b11111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111110,
		0b11000110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111110,
		0b00000110,
		0b00000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00011000,
		0b00000000,
	},
	{
		0b00000000,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b11000000,
		0b01100000,
		0b00110000,
		0b00011000,
		0b00001100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11111110,
		0b00000000,
		0b11111110,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01100000,
		0b00110000,
		0b00011000,
		0b00001100,
		0b00000110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b00001100,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11011110,
		0b11011110,
		0b11011110,
		0b11011100,
		0b11000000,
		0b01111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00111000,
		0b01101100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11111110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b11111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00111100,
		0b01100110,
		0b11000000,
		0b11000000,
		0b11000000,
		0b11000000,
		0b11000000,
		0b01100110,
		0b00111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111000,
		0b01101100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01101100,
		0b11111000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111110,
		0b01100110,
		0b01100000,
		0b01100000,
		0b01111100,
		0b01100000,
		0b01100000,
		0b01100110,
		0b11111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111110,
		0b01100110,
		0b01100000,
		0b01100000,
		0b01111100,
		0b01100000,
		0b01100000,
		0b01100000,
		0b11110000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000000,
		0b11000000,
		0b11001110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11111110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b11011000,
		0b11011000,
		0b01110000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11001100,
		0b11011000,
		0b11110000,
		0b11110000,
		0b11011000,
		0b11001100,
		0b11000110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11110000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100010,
		0b01100110,
		0b11111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11000110,
		0b11101110,
		0b11111110,
		0b11010110,
		0b11010110,
		0b11010110,
		0b11000110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11000110,
		0b11100110,
		0b11100110,
		0b11110110,
		0b11011110,
		0b11001110,
		0b11001110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111100,
		0b01100000,
		0b01100000,
		0b01100000,
		0b11110000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11010110,
		0b01111100,
		0b00000110,
		0b00000000,
	},
	{
		0b00000000,
		0b11111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111100,
		0b01111000,
		0b01101100,
		0b01100110,
		0b11100110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000000,
		0b01100000,
		0b00111000,
		0b00001100,
		0b00000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111110,
		0b01011010,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01101100,
		0b00111000,
		0b00010000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11000110,
		0b11010110,
		0b11010110,
		0b11010110,
		0b11111110,
		0b11101110,
		0b11000110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11000110,
		0b11000110,
		0b01101100,
		0b00111000,
		0b00111000,
		0b00111000,
		0b01101100,
		0b11000110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11111110,
		0b11000110,
		0b10001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b11000010,
		0b11000110,
		0b11111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b11000000,
		0b01100000,
		0b00110000,
		0b00011000,
		0b00001100,
		0b00000110,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01111100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00011000,
		0b00111100,
		0b01100110,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11111111,
	},
	{
		0b00000000,
		0b00011100,
		0b00011000,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01111000,
		0b00001100,
		0b01111100,
		0b11001100,
		0b11011100,
		0b01110110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b11100000,
		0b01100000,
		0b01100000,
		0b01111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b11111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000000,
		0b11000000,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00011100,
		0b00001100,
		0b00001100,
		0b01111100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b01111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01111100,
		0b11000110,
		0b11111110,
		0b11000000,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00011100,
		0b00110110,
		0b00110000,
		0b00110000,
		0b11111100,
		0b00110000,
		0b00110000,
		0b00110000,
		0b01111000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01110110,
		0b11001110,
		0b11000110,
		0b11000110,
		0b01111110,
		0b00000110,
		0b11000110,
		0b01111100,
	},
	{
		0b00000000,
		0b11100000,
		0b01100000,
		0b01100000,
		0b01101100,
		0b01110110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b11100110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00111000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00011100,
		0b00001100,
		0b00001100,
		0b00001100,
		0b11001100,
		0b11001100,
		0b01111000,
	},
	{
		0b00000000,
		0b11100000,
		0b01100000,
		0b01100000,
		0b01100110,
		0b01101100,
		0b01111000,
		0b01101100,
		0b01100110,
		0b11100110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110100,
		0b00011000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01101100,
		0b11111110,
		0b11010110,
		0b11010110,
		0b11000110,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11011100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11011100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111100,
		0b01100000,
		0b01100000,
		0b11110000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01110110,
		0b11001100,
		0b11001100,
		0b11001100,
		0b01111100,
		0b00001100,
		0b00001100,
		0b00011110,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11011100,
		0b01100110,
		0b01100000,
		0b01100000,
		0b01100000,
		0b11110000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01111100,
		0b11000110,
		0b01110000,
		0b00011100,
		0b11000110,
		0b01111100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b11111100,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110110,
		0b00011100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b01110110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11000110,
		0b11000110,
		0b11000110,
		0b01101100,
		0b00111000,
		0b00010000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11000110,
		0b11000110,
		0b11010110,
		0b11010110,
		0b11111110,
		0b01101100,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11000110,
		0b01101100,
		0b00111000,
		0b00111000,
		0b01101100,
		0b11000110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11000110,
		0b11000110,
		0b11000110,
		0b11001110,
		0b01110110,
		0b00000110,
		0b11000110,
		0b01111100,
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b11111110,
		0b10001100,
		0b00011000,
		0b00110000,
		0b01100010,
		0b11111110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00001110,
		0b00011000,
		0b00011000,
		0b00011000,
		0b01110000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00001110,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01110000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00001110,
		0b00011000,
		0b00011000,
		0b00011000,
		0b01110000,
		0b00000000,
		0b00000000,
	},
	{
		0b00000000,
		0b01110110,
		0b11011100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	},
};
