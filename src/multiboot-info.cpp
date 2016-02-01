//=============================================================================
// ■ multiboot-info.cpp
//-----------------------------------------------------------------------------
//   处理与存储Multiboot启动信息结构，参照：
//   https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Boot-information-format
//=============================================================================

namespace MultibootInfo {
	uint32_t flags;
	uint32_t mem_lower, mem_upper;
	const char* cmdline;
	const char* boot_loader_name;
	void initialize(type_address address) {
		flags = Memory::read32_at(address);
		if (flags & 1 << 0) {
			mem_lower = Memory::read32_at(address + 4);
			mem_upper = Memory::read32_at(address + 8);
		}
		if (flags & 1 << 2) {
			cmdline = (const char*) Memory::read32_at(address + 16);
		} else {
			cmdline = nullptr;
		}
		if (flags & 1 << 9) {
			boot_loader_name = (const char*) Memory::read32_at(address + 64);
		} else {
			boot_loader_name = nullptr;
		}
	}
}
