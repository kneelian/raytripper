#define f32 float
#define f64 double

#define FP f64

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

	bool pnt() // is it a point or not
	{ return t == 1; }

	bool vec()// is it a vector or not
	{ return t == 0; }

	FP mag()
	{
		if(pnt()) { return 0.0; } else
		return sqrt((x * x) + (y * y) + (z * z));
	}
};

vec4_t make_pnt(FP x, FP y, FP z)
{ return {x, y, z, 1.0}; }

vec4_t make_vec(FP x, FP y, FP z)
{ return {x, y, z, 0.0}; }