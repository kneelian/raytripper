#include <cmath>
#include <array>
#include <tuple>
#include <vector>

#include "types.hpp"

void canvas_demo()
{

	/**/
	vec4_t a = { 3, 5, 14, 0 };
	vec4_t b = a;
	//fmt::print("({},{},{}: {})\n", a.x, a.y, a.z, (-a-b).mag());/*

	/*vec4_t p = make_pnt(-4.5, 1.0, 0.0);
	vec4_t v = make_vec(0.7, 0.5, 0.0).norm();

	vec4_t g = make_vec(0.0,  -0.025, 0.0);
	vec4_t w = make_vec(-0.025, 0.0, 0.0);
*/
	int ticks = 0;

	std::vector<vec4_t> dots; dots.clear();

	for(FP a = -6.4; a < 6.4; a += 0.0005)
	{
		dots.push_back({a, sin(a), 0, 0});
		dots.push_back({a, sin(a+3.1415/4), 0, 0});
		dots.push_back({a, sin(a+3.1415/2), 0, 0});
		dots.push_back({a, sin(a+3*3.1415/4), 0, 0});
		dots.push_back({a, sin(a+3.1415), 0, 0});
		dots.push_back({a, sin(a+3.1415*(6/4)), 0, 0});
	}


//	dots.push_back(p);

/*	while(p.y > -5.0)
	{
		ticks++;
		p += v;
		v += (g + w);
		dots.push_back(p);

		//if(ticks > 49) { break; }
	}
*/
	FP min_x = INFTY,
	   min_y = INFTY,
	   max_x = -INFTY,
	   max_y = -INFTY;

	for(auto &d : dots)
	{
		if (d.x > max_x) { max_x = d.x; }
		if (d.x < min_x) { min_x = d.x; }
		if (d.y > max_y) { max_y = d.y; }
		if (d.y < min_y) { min_y = d.y; }
	}

	canvas_t canvas;
	canvas.clear();

	FP scaling_x = canvas.width / ((max_x+1.0) - (min_x-1.0));
	FP scaling_y = canvas.height/ ((max_y+.50) - (min_y-.50));

	for(auto &d : dots)
	{
		d.x += abs(min_x) + 1.0;
		d.y += abs(min_y) - 1.50;
	}

	FP scaled_zero_x = (abs(min_x) + 1.0) * scaling_x;
	FP scaled_zero_y = (abs(min_y) + 1.0) * scaling_y;

	//fmt::print("{}\n\n", min_x);
	for(int i = floor(min_x); i < ceil(max_x); i++)
	{
		//fmt::print("{}\n", float(i + 1) * scaling_x);
		for(int j = 0; j < canvas.width; j++)
		{
			canvas.write
			(
				float(i + 1) * scaling_x, 
				j, 
				{0, 0.2, 0.1, 0}
			);
		}
	}

	for(int i = floor(min_y); i < ceil(max_y); i++)
	{
		//fmt::print("{}\n", float(i + 1) * scaling_x);
		for(int j = 0; j < canvas.width; j++)
		{
			canvas.write
			(
				j,
				canvas.width -float(i + 1) * scaling_y,  
				{0, 0.2, 0.1, 0}
			);
		}
	}

	for(int i = 0; i < canvas.width; i++)
		canvas.write(i, canvas.width - scaled_zero_y, {0.5,0.0,0.0,0.0});
	for(int i = 0; i < canvas.width; i++)
		canvas.write(scaled_zero_x, i, {0.5,0.0,0.0,0.0});


	for(auto &d : dots)
		canvas.write(d.x * scaling_x, canvas.width - (d.y * scaling_y), {1.0, 1.0, 1.0, 1.0});

	canvas.as_ppm6();
}