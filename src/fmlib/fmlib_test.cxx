//=============================================================================
// ■ fmlib_test.cxx
//-----------------------------------------------------------------------------
//   FMLib的测试用例。
//=============================================================================

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cstdint>
#include <cinttypes>
#include "fmlib.cpp"
using namespace std;

int main() {
	FM::Test::initialize();
	FM::Test::section("IUPAC");
	FM::Test::test(FM::IUPAC::systematic_element_name(902));
}
