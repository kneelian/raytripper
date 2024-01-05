#include <array>
#include <tuple>
#include "fmt/core.h"
#include "fmt/ranges.h"

#define f32 float
#define f64 double
#define f80 long double

#define FP f64

#define INFTY std::numeric_limits<FP>::infinity()

struct col4_t
{
	FP r = 0.0;
	FP g = 0.0;
	FP b = 0.0;
	FP a = 0.0;

	col4_t& operator=(const col4_t& o)
	{
		r = o.r;
		g = o.g;
		b = o.b;
		a = o.a;
		return *this;
	}

	std::tuple<int,int,int> as_inttuple()
	{
		return
		{
			int(r * 255.999) % 255,
			int(g * 255.999) % 255,
			int(b * 255.999) % 255
		};
	}

	std::tuple<uint8_t, uint8_t, uint8_t> as_bytetuple()
	{
		return
		{
			uint8_t(r * 255.999),
			uint8_t(g * 255.999),
			uint8_t(b * 255.999)
		};
	}

	bool operator==(const col4_t& other)
	{
		if 
		(
			abs(r - other.r) < 0.0001 and
			abs(g - other.g) < 0.0001 and
			abs(b - other.b) < 0.0001 and
			abs(a - other.a) < 0.0001
		) { return true; }
		else return false;
	}

	col4_t operator+(const col4_t& other)
	{
		return
		{ 
			r + other.r,
			g + other.g,
			b + other.b,
			a + other.a
		};
	}

	col4_t operator-(const col4_t& other)
	{
		return
		{ 
			r - other.r,
			g - other.g,
			b - other.b,
			a - other.a
		};
	}

	col4_t operator*(const col4_t& o)
	{
		return
		{
			r * o.r,
			g * o.g,
			b * o.b,
			a * o.a
		};
	}

	col4_t operator*(const FP& o)
	{
		return
		{
			r * o,
			g * o,
			b * o,
			a * o
		};
	}

	col4_t operator/(const col4_t& o)
	{
		return
		{
			r / o.r,
			g / o.g,
			b / o.b,
			a / o.a
		};
	}

	col4_t operator/(const FP& o)
	{
		return *this * (1.0 / o);
	}
};

struct canvas_t
{
	static const int width  = 256;
	static const int height = 256;
	std::array<col4_t, width * height> pixels;

	void write(int x, int y, col4_t col)
	{ 
		x %= (width - 1);
		y %= (height- 1);
		pixels[x + width * y] = col; 
	}

	void w_rect(int x, int y, int w, int h, col4_t col)
	{
		for(int i = x; i < (x + w); i++)
		{
			for(int j = y; j < (y + h); j++)
			{
				pixels[i + width * j] = col;
			}
		}
	}

	void clear()
	{ for(auto &p : pixels) { p = {0,0,0,0}; }}

	void as_ppm6()
	{
		fmt::print("P6\n{} {}\n255\n", width, height);
		for(auto p : pixels)
		{
			auto t = p.as_bytetuple();
			fmt::print("{:c}{:c}{:c}", std::get<0>(t), std::get<1>(t), std::get<2>(t));
		}
	}
		void as_ppm3()
	{
		fmt::print("P3\n{} {}\n255\n", width, height);
		for(auto p : pixels)
		{
			fmt::print("{} ", fmt::join(p.as_inttuple(), " "));
		}
	}
};

struct vec4_t
{
	FP x = 0.0;
	FP y = 0.0;
	FP z = 0.0;
	FP t = 0.0;

	vec4_t& operator=(const vec4_t& other)
	{
		if(this ==&other) return *this;

		x = other.x;
		y = other.y;
		z = other.z;
		t = other.t;

		return *this;
	}

	bool operator==(const vec4_t& other)
	{
		if 
		(
			abs(x - other.x) < 0.0001 and
			abs(y - other.y) < 0.0001 and
			abs(z - other.z) < 0.0001 and
			abs(t - other.t) < 0.0001
		) { return true; }
		else return false;
	}
	bool operator!=(const vec4_t& other)
	{ return !(*this == other); }

	vec4_t operator+(const vec4_t& other)
	{
		return
		{ 
			x + other.x,
			y + other.y,
			z + other.z,
			t + other.t
		};
	}

	vec4_t& operator+=(const vec4_t& other)
	{
		*this = *this + other;
		return *this;
	}

	vec4_t operator-(const vec4_t& other)
	{
		return
		{ 
			x - other.x,
			y - other.y,
			z - other.z,
			t - other.t
		};
	}

	vec4_t operator-()
	{
		return
		{ 
			0 - x,
			0 - y,
			0 - z,
			0 - t
		};
	}
	/* mul with scalar */
	vec4_t operator*(const FP& other)
	{
		return
		{
			x * other,
			y * other,
			z * other,
			t * other
		};
	}
	vec4_t operator/(const FP& other)
	{
		return (*this * (1.0/other));
	}

	/* dot and cross product */
	FP     operator%(const vec4_t& o) // DOT PRODUCT
	{ 
		return (x * o.x) + (y * o.y) + (z * o.z) + (t * o.t); 
	}
	vec4_t operator*(const vec4_t& o) // cross product
	{ 
		return
		{
			y * o.z - z * o.y,
			z * o.x - x * o.z,
			x * o.y - y * o.x,
			t * o.t
		};
	}

	bool pnt() // is it a point or not
	{ return t == 1; }

	bool vec()// is it a vector or not
	{ return t == 0; }

	FP mag()
	{
		if(pnt()) { return 0.0; } else
		return sqrt((x * x) + (y * y) + (z * z) + (t * t));
	}

	void norm_me()
	{
		FP temp = mag();
		x /= temp;
		y /= temp;
		z /= temp;
		t /= temp;
	}

	vec4_t norm()
	{
		FP temp = mag();
		return
		{
			x /= temp,
			y /= temp,
			z /= temp,
			t /= temp
		};
	}
};

vec4_t make_pnt(FP x, FP y, FP z)
{ return {x, y, z, 1.0}; }

vec4_t make_vec(FP x, FP y, FP z)
{ return {x, y, z, 0.0}; }