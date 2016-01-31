//=============================================================================
// ■ kernel.cpp
//-----------------------------------------------------------------------------
//   这个文件是干什么的？www
//=============================================================================

//---------------------------------------------------------------------------
// ● 处理Multiboot启动信息结构，参照：
//   https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Boot-information-format
//---------------------------------------------------------------------------
void initialize_multiboot(type_address address) {
	uint32_t flags = Memory::read32_at(address);
	uint32_t mem_lower, mem_upper;
	if (flags & 1 << 0) {
		mem_lower = Memory::read32_at(address + 4);
		mem_upper = Memory::read32_at(address + 8);
	}
}

//---------------------------------------------------------------------------
// ● 主程序
//---------------------------------------------------------------------------
void initialize_main() {
	Terminal::width = 80;
	Terminal::height = 25;
	Terminal::write_char((struct pos) {4, 4}, '%', (struct Terminal::char_color) {
		.fg = Terminal::AQUA,
		.bg = Terminal::NAVY,
	});
	Graphics::width = 320;
	Graphics::height = 200;
	Graphics::fill_rect(16, 16, Graphics::width - 16 * 2,
		Graphics::height - 16 * 2, Graphics::GREEN);
	Graphics::draw_text((struct pos) {32, 32}, "Frogimine", Graphics::LIME);
	Graphics::set_pixel((struct pos) {64, 64}, Graphics::YELLOW);
	return;
}

//---------------------------------------------------------------------------
// ● 内核主程序
//---------------------------------------------------------------------------
extern "C" void kernel_main(type_address multiboot_info_address) {
	initialize_multiboot(multiboot_info_address);
	IDT::initialize();
	Interrupt::initialize();
	initialize_main();
}
