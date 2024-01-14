#include "LineSegment.h"
#include <sstream>
#include <iomanip>

double LineSegment::GetArea() const
{
	return 0.0;
}

double LineSegment::GetPerimeter() const
{
	return hypot(m_endPoint.x - m_startPoint.x, m_endPoint.y - m_startPoint.y);
}

std::string LineSegment::ToString() const
{
	std::ostringstream oss;

	oss << std::setprecision(2) << std::fixed;

	oss << "type: line segment" << std::endl
		<< "start point: (" << m_startPoint.x << ", " << m_startPoint.y << ")" << std::endl
		<< "end point: (" << m_endPoint.x << ", " << m_endPoint.y << ")" << std::endl
		<< "length: " << GetPerimeter() << std::endl
		<< "outline color: " << std::hex << m_outlineColor << std::endl;

	return oss.str();
}

uint32_t LineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

Point LineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}