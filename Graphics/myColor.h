#pragma once

class myColor
{
public:
	float r, g, b, a;
	myColor()
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	};
	myColor(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};
	myColor(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 1.0f;
	};

	void set(float r, float b, float g)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	};
	void set(float r, float b, float g, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};

	myColor operator+(myColor color)
	{
		myColor res;
		res.r = color.r + r;
		res.a = color.a + a;
		res.g = color.g + g;
		res.b = color.b + b;
		return res;
	};
	myColor operator+(float color)
	{
		myColor res;
		res.r = color + r;
		res.a = color + a;
		res.g = color + g;
		res.b = color + b;
		return res;
	};
	void operator+=(myColor color)
	{	
		r = color.r + r;
		a = color.a + a;
		g = color.g + g;
		b = color.b + b;
	};
	void operator+=(float color)
	{
		r = color + r;
		a = color + a;
		g = color + g;
		b = color + b;
	};
	myColor operator*(float factor)
	{
		myColor res;
		res.r = factor * r;
		res.a = factor * a;
		res.g = factor * g;
		res.b = factor * b;
		return res;
	};
	void operator*=(float factor)
	{
		r = factor * r;
		a = factor * a;
		g = factor * g;
		b = factor * b;
	};
	void operator=(myColor color)
	{
		r = color.r;
		a = color.a;
		g = color.g;
		b = color.b;
	};
	void operator=(float color)
	{
		r = color;
		a = color;
		g = color;
		b = color;
	};
	float operator[](unsigned i)
	{
		switch (i)
		{
		case 0:
			return r;
			break;
		case 1:
			return g;
			break;
		case 2:
			return b;
			break;
		case 3:
			return a;
			break;
		default:
			break;
		}
		assert(false); // Pas de valeur pour i > 3
		return 1.0f;
	};

	static myColor RED(float a)
	{
		return myColor(1.0f, 0.0f, 0.0f, a);
	};
	static myColor RED()
	{
		return RED(1.0f);
	};

	static myColor WHITE(float a)
	{
		return myColor(1.0f, 1.0f, 1.0f, a);
	};
	static myColor WHITE()
	{
		return WHITE(1.0f);
	};

	static myColor BLUE(float a)
	{
		return myColor(0.0f, 0.0f, 1.0f, a);
	};
	static myColor BLUE()
	{
		return BLUE(1.0f);
	};

	static myColor GREEN(float a)
	{
		return myColor(0.0f, 1.0f, 0.0f, a);
	};
	static myColor GREEN()
	{
		return GREEN(1.0f);
	};

	static myColor BLACK(float a)
	{
		return myColor(0.0f, 0.0f, 0.0f, a);
	};
	static myColor BLACK()
	{
		return BLACK(1.0f);
	};
};