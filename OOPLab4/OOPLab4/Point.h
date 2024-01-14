#pragma once

struct Point
{
public:
	Point(double x, double y)
		: x(x)
		, y(y)
	{
	}

	double x;
	double y;

	bool operator==(const Point& other) const;
};