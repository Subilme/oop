#include "DataProcessor.h"
#include <optional>
#include <sstream>
#include <iomanip>
#include <algorithm>

const std::map<std::string, DataProcessor::ShapeType> mapStringToShapeType = {
	{ "line", DataProcessor::ShapeType::LineSegment },
	{ "triangle", DataProcessor::ShapeType::Triangle },
	{ "rectangle", DataProcessor::ShapeType::Rectangle },
	{ "circle", DataProcessor::ShapeType::Circle }
};

bool DataProcessor::ReadShapeData(std::istream& input)
{
	std::string inputStr, shapeTypeStr;
	std::stringstream iss;
	std::optional<ShapeType> shapeType;

	while (std::getline(input, inputStr))
	{
		iss.clear();
		iss << inputStr;
		iss >> shapeTypeStr;
		shapeType.reset();

		// TODO: ����� �� �����
		auto it = mapStringToShapeType.find(shapeTypeStr);
		if (it != mapStringToShapeType.end())
		{
			shapeType = it->second;
		}

		if (!shapeType.has_value())
		{
			return false;
		}

		switch (*shapeType)
		{
		case ShapeType::LineSegment:
			if (!ReadLineSegmentData(iss))
			{
				return false;
			}
			break;

		case ShapeType::Triangle:
			if (!ReadTriangleData(iss))
			{
				return false;
			}
			break;

		case ShapeType::Rectangle:
			if (!ReadRectangleData(iss))
			{
				return false;
			}
			break;

		case ShapeType::Circle:
			if (!ReadCircleData(iss))
			{
				return false;
			}
			break;

		default:
			return false;
		}
	}

	return true;
}

void DataProcessor::PrintMaxAreaShapeInfo(std::ostream& output) const
{
	if (auto maxAreaShapePtr = FindMaxAreaShape())
	{
		output << maxAreaShapePtr->ToString();
	}
	else
	{
		output << "Failed to print shape data." << std::endl;
	}
}

void DataProcessor::PrintMinPerimeterShapeInfo(std::ostream& output) const
{
	if (auto minPerimeterShapePtr = FindMinPerimeterShape())
	{
		output << minPerimeterShapePtr->ToString();
	}
	else
	{
		output << "Failed to print shape data." << std::endl;
	}
}

std::shared_ptr<IShape> DataProcessor::FindMaxAreaShape() const
{
	if (m_shapes.empty())
	{
		return {};
	}

	std::shared_ptr<IShape> maxAreaShape = m_shapes[0];

	double maxArea = m_shapes[0]->GetArea();
	double area;
	for (size_t i = 1; i < m_shapes.size(); ++i)
	{
		if ((area = m_shapes[i]->GetArea()) > maxArea)
		{
			maxArea = area;
			maxAreaShape = m_shapes[i];
		}
	}
	return maxAreaShape;
}

std::shared_ptr<IShape> DataProcessor::FindMinPerimeterShape() const
{
	if (m_shapes.empty())
	{
		return {};
	}

	std::shared_ptr<IShape> minPerimeterShape = m_shapes[0];

	double minPerimeter = m_shapes[0]->GetPerimeter();
	double perimeter;
	for (size_t i = 1; i < m_shapes.size(); ++i)
	{
		if ((perimeter = m_shapes[i]->GetPerimeter()) < minPerimeter)
		{
			minPerimeter = perimeter;
			minPerimeterShape = m_shapes[i];
		}
	}

	return minPerimeterShape;
}

bool DataProcessor::ReadLineSegmentData(std::istream& input)
{
	double startX, startY, endX, endY;
	uint32_t outlineColor;

	if (input >> startX >> startY >> endX >> endY >> std::hex >> outlineColor)
	{
		m_shapes.push_back(std::make_shared<LineSegment>(Point(startX, startY), Point(endX, endY), outlineColor));
		return true;
	}

	return false;
}

bool DataProcessor::ReadTriangleData(std::istream& input)
{
	double vertex1X, vertex1Y, vertex2X, vertex2Y, vertex3X, vertex3Y;
	uint32_t outlineColor, fillColor;

	if (input >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.push_back(std::make_shared<Triangle>(Point(vertex1X, vertex1Y), Point(vertex2X, vertex2Y), Point(vertex3X, vertex3Y), outlineColor, fillColor));
		return true;
	}

	return false;
}

bool DataProcessor::ReadRectangleData(std::istream& input)
{
	double leftTopX, leftTopY, width, height;
	uint32_t outlineColor, fillColor;

	if (input >> leftTopX >> leftTopY >> width >> height >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.push_back(std::make_shared<Rectangle>(Point(leftTopX, leftTopY), width, height, outlineColor, fillColor));
		return true;
	}

	return false;
}

bool DataProcessor::ReadCircleData(std::istream& input)
{
	double centerX, centerY, radius;
	uint32_t outlineColor, fillColor;

	if (input >> centerX >> centerY >> radius >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.push_back(std::make_shared<Circle>(Point(centerX, centerY), radius, outlineColor, fillColor));
		return true;
	}

	return false;
}
