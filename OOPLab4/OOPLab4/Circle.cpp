#include "Circle.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <iomanip>


double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string Circle::ToString() const
{
	std::ostringstream oss;

	oss << std::setprecision(2) << std::fixed;

	oss << "type: circle" << std::endl
		<< "center: (" << m_center.x << ", " << m_center.y << ")" << std::endl
		<< "radius: " << m_radius << std::endl
		<< "area: " << GetArea() << std::endl
		<< "perimeter: " << GetPerimeter() << std::endl
		<< "outline color: " << std::hex << GetOutlineColor() << std::endl
		<< "fill color: " << std::hex << GetFillColor() << std::endl;

	return oss.str();
}

uint32_t Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Circle::GetFillColor() const
{
	return m_fillColor;
}

Point Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}
