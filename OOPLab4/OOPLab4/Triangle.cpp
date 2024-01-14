#include "Triangle.h"
#include <sstream>
#include <iomanip>

double Triangle::GetArea() const
{
	return 0.5 * abs(m_vertex[0].x * (m_vertex[1].y - m_vertex[2].y)
		+ m_vertex[1].x * (m_vertex[2].y - m_vertex[0].y) + m_vertex[2].x * (m_vertex[0].y - m_vertex[1].y));
}

double Triangle::GetPerimeter() const
{
	return hypot(m_vertex[0].x - m_vertex[1].x, m_vertex[0].y - m_vertex[1].y)
		+ hypot(m_vertex[1].x - m_vertex[2].x, m_vertex[1].y - m_vertex[2].y)
		+ hypot(m_vertex[0].x - m_vertex[2].x, m_vertex[0].y - m_vertex[2].y);
}

std::string Triangle::ToString() const
{
	std::ostringstream oss;

	oss << std::setprecision(2) << std::fixed;

	oss << "type: triangle" << std::endl
		<< "vertex 1: (" << m_vertex[0].x << ", " << m_vertex[0].y << ")" << std::endl
		<< "vertex 2: (" << m_vertex[1].x << ", " << m_vertex[1].y << ")" << std::endl
		<< "vertex 3: (" << m_vertex[2].x << ", " << m_vertex[2].y << ")" << std::endl
		<< "area: " << GetArea() << std::endl
		<< "perimeter: " << GetPerimeter() << std::endl
		<< "outline color: " << std::hex << m_outlineColor << std::endl
		<< "fill color: " << std::hex << m_fillColor << std::endl;

	return oss.str();
}

uint32_t Triangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Triangle::GetFillColor() const
{
	return m_fillColor;
}

Point Triangle::GetVertex1() const
{
	return m_vertex[0];
}

Point Triangle::GetVertex2() const
{
	return m_vertex[1];
}

Point Triangle::GetVertex3() const
{
	return m_vertex[2];
}
