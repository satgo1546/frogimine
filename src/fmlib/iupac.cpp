//=============================================================================
// ■ FM::IUPAC
//-----------------------------------------------------------------------------
//   参照：https://zh.wikipedia.org/wiki/IUPAC元素系统命名法
//=============================================================================

namespace IUPAC {
	const char* const numerical_root[10] = {
		"nil", "un", "bi", "tri", "quad",
		"pent", "hex", "sept", "oct", "enn"
	};

	const char* systematic_element_name_or_symbol(int n, bool symbol) {
		static char s[16];
		static char sym[4];

		if (n < 101 || n > 999) return NULL;
		int a = n / 100;
		n %= 100;
		int b = n / 10;
		int c = n % 10;
		if (symbol) {
			sym[0] = numerical_root[a][0] + ('A' - 'a');
			sym[1] = numerical_root[b][0];
			sym[2] = numerical_root[c][0];
			sym[3] = 0;
			return sym;
		} else {
			strcpy(s, a == 9 && b == 0 ? "en" : numerical_root[a]);
			s[0] += 'A' - 'a';
			strcat(s, b == 9 && c == 0 ? "en" : numerical_root[b]);
			strcat(s, c == 2 ? "b" : c == 3 ? "tr" : numerical_root[c]);
			strcat(s, "ium");
			return s;
		}
	}

	const char* systematic_element_name(int n) {
		return systematic_element_name_or_symbol(n, false);
	}

	const char* systematic_element_symbol(int n) {
		return systematic_element_name_or_symbol(n, true);
	}
}
