#include <cmath>

#include "fmt/format.h"
#include "fmt/color.h"

// #include "speed-test.hpp" // test_speed();

#include "types.hpp"

int main()
{
	vec4_t a = { 3, 5, 14, 0 };
	vec4_t b = a;
	fmt::print("({},{},{}: {})\n", a.x, a.y, a.z, (a+b).mag());

	return 0;
}