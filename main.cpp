#include <cmath>

#include "fmt/format.h"
#include "fmt/color.h"

// #include "speed-test.hpp" // test_speed();

#include "types.hpp"



int main()
{
	vec4_t a = { 3, 5, 14, 0 };
	vec4_t b = a;
	fmt::print("({},{},{}: {})\n", a.x, a.y, a.z, (-a-b).mag());

	vec4_t p = make_pnt(0.0, 1.0, 0.0);
	vec4_t v = make_vec(1.0, 1.0, 0.0).norm();

	vec4_t g = make_vec(0.0,  -0.1, 0.0);
	vec4_t w = make_vec(-0.01, 0.0, 0.0);

	int ticks = 0;

	while(p.y > 0)
	{
		fmt::print("tick #{}:\t({:03.5f},{:03.5f},{:03.5f})\n", ticks, p.x, p.y, p.z);
		ticks++;
		p += v;
		v += (g + w);
	}

	fmt::print("final pos. @ tick #{}:\t({:03.5f},{:03.5f},{:03.5f})\n", ticks, p.x, p.y, p.z);

	return 0;
}