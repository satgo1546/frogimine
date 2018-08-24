//=============================================================================
// ■ fmlib_test.cxx
//-----------------------------------------------------------------------------
//   FMLib的测试用例。
//=============================================================================

#include "fmlib.cpp"
using namespace std;

int main() {
	FM::Test::initialize();
	{
		FM::Test::section("String");
		FM::Test::test(FM::String::strlen("abcde"), (size_t) 5);
	}
	{
		FM::Test::section("IUPAC");
		FM::Test::test(FM::IUPAC::systematic_element_name(902), "Ennilbium");
		FM::Test::test(FM::IUPAC::systematic_element_symbol(118), "Uuo");
	}
}
