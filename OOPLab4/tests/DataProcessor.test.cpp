#include "../../catch2/catch.hpp"
#include "../OOPLab4/DataProcessor.h"
#include <sstream>
#include <float.h>
#include <math.h>

TEST_CASE("Testing shape classes")
{
	SECTION("Making line segment 5 6 9 1 00FF00")
	{
		LineSegment line = LineSegment(Point(5, 6), Point(9, 1), 16724991);
		REQUIRE(line.GetArea() == 0);
		REQUIRE(fabs(line.GetPerimeter() - 6.4031242374) < DBL_EPSILON);
		REQUIRE(line.GetStartPoint() == Point(5, 6));
		REQUIRE(line.GetEndPoint() == Point(9, 1));
		REQUIRE(line.GetOutlineColor() == 16724991);
		REQUIRE(line.ToString() == "type: line segment\nleft start point: (5.00, 6.00)\nend point: (9.00, 1.00)\nlength: 6.40\noutline color : ff33ff\n");
	}

	SECTION("Making circle 0 0 15 00FF33FF EEFFBBFF")
	{
		Circle circle = Circle(Point(0, 0), 15, 16724991, 4009737215);
		REQUIRE(circle.GetCenter() == Point(0, 0));
		REQUIRE(circle.GetRadius() == 15.00);
		REQUIRE(fabs(circle.GetArea() - 706.8583470577) < DBL_EPSILON);
		REQUIRE(circle.GetPerimeter() == 6.4031242374);
		REQUIRE(circle.GetOutlineColor() == 16724991);
		REQUIRE(circle.GetFillColor() == 4009737215);
		REQUIRE(circle.ToString() == "type: circle\ncenter: (0.00, 0.00)\nradius: 15.00\narea: 706.86\nperimeter: 94.25\noutline color: ff33ff\nfill color: eeffbbff\n");
	}

	SECTION("Making rectangle 5 -6 10 10 00FF33FF EEFFBBFF")
	{
		Rectangle rectangle = Rectangle(Point(5, -6), 10, 10, 16724991, 4009737215);
		REQUIRE(rectangle.GetArea() == 100.00);
		REQUIRE(rectangle.GetPerimeter() == 40.00);
		REQUIRE(rectangle.GetHeight() == 10);
		REQUIRE(rectangle.GetWidth() == 10);
		REQUIRE(rectangle.GetLeftTop() == Point(5, -6));
		REQUIRE(rectangle.GetRightBottom() == Point(rectangle.GetLeftTop().x + rectangle.GetWidth(), rectangle.GetLeftTop().y + rectangle.GetHeight()));
		REQUIRE(rectangle.GetOutlineColor() == 16724991);
		REQUIRE(rectangle.GetFillColor() == 4009737215);
		REQUIRE(rectangle.ToString() == "type: rectangle\nleft top: (5.00, -6.00)\nwidth: 10.00\nheight: 10.00\narea: 100.00\nperimeter: 40.00\noutline color: ff33ff\nfill color: eeffbbff\n");
	}

	SECTION("Making triangle 0 0 3 4 6 0 00FF33FF EEFFBBFF")
	{
		Triangle triangle = Triangle(Point(0, 0), Point(3, 4), Point(6, 0), 16724991, 4009737215);
		REQUIRE(triangle.GetArea() == 12.00);
		REQUIRE(triangle.GetPerimeter() == 16.00);
		REQUIRE(triangle.GetVertex1() == Point(0, 0));
		REQUIRE(triangle.GetVertex2() == Point(3, 4));
		REQUIRE(triangle.GetVertex3() == Point(6, 0));
		REQUIRE(triangle.GetOutlineColor() == 16724991);
		REQUIRE(triangle.GetFillColor() == 4009737215);
		REQUIRE(triangle.ToString() == "type: triangle\nvertex 1: (0.00, 0.00)\nvertex 2: (3.00, 4.00)\nvertex 3: (6.00, 0.00)\narea: 12.00\nperimeter: 16.00\noutline color: ff33ff\nfill color: eeffbbff\n");
	}
}

TEST_CASE("ReadShapeData reads data from istream and saves the object")
{
	DataProcessor processor;
	std::ostringstream oss;

	SECTION("Read data with invalid shape type")
	{
		std::istringstream iss("table 0 0 3 4 00FF00FF");
		REQUIRE(!processor.ReadShapeData(iss));
	}

	SECTION("Read line segment data")
	{
		std::istringstream iss("line 0 0 3 4 00FF00FF");
		REQUIRE(processor.ReadShapeData(iss));
	}

	SECTION("Read invalid line segment data")
	{
		std::istringstream iss("line 0 0 3");
		REQUIRE(!processor.ReadShapeData(iss));
	}

	SECTION("Read triangle data")
	{
		std::istringstream iss("triangle 0 0 3 4 6 0 00FF00FF EEFFAAFF");
		REQUIRE(processor.ReadShapeData(iss));
	}

	SECTION("Read rectangle data")
	{
		std::istringstream iss("rectangle 0 10 20 10 00FF33FF EEFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
	}

	SECTION("Read circle data")
	{
		std::istringstream iss("circle 10 10 20 22AA33FF CCFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
	}
}

TEST_CASE("FindMaxAreaShape finds the shape with max area")
{
	DataProcessor processor;
	std::ostringstream oss;

	SECTION("If there is no shapes")
	{
		processor.PrintMaxAreaShapeInfo(oss);
		REQUIRE(oss.str() == "Failed to print shape data.\n");
	}

	SECTION("If there is single shape")
	{
		std::istringstream iss("rectangle 0 10 20 10 00FF33FF EEFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
		processor.PrintMaxAreaShapeInfo(oss);
		REQUIRE(oss.str() == "type: rectangle\nleft top: (0.00, 10.00)\nwidth: 20.00\nheight: 10.00\narea: 200.00\nperimeter: 60.00\noutline color: ff33ff\nfill color: eeffbbff\n");
	}
	
	SECTION("Find max area rectangle: first rect area = 50, second = 100, third = 15")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33FF EEFFBBFF\nrectangle 5 -6 10 10 00FF33FF EEFFBBFF\nrectangle -7 4 1 15 00FF33FF EEFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
		processor.PrintMaxAreaShapeInfo(oss);
		REQUIRE(oss.str() == "type: rectangle\nleft top: (5.00, -6.00)\nwidth: 10.00\nheight: 10.00\narea: 100.00\nperimeter: 40.00\noutline color: ff33ff\nfill color: eeffbbff\n");
	}

	SECTION("Find max area circle among other shape types: first rect area = 50, second triangle = 12, third circle = 706.86")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33FF EEFFBBFF\ntriangle 0 0 3 4 6 0 00FF33FF EEFFBBFF\ncircle 0 0 15 00FF33FF EEFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
		processor.PrintMaxAreaShapeInfo(oss);
		REQUIRE(oss.str() == "type: circle\ncenter: (0.00, 0.00)\nradius: 15.00\narea: 706.86\nperimeter: 94.25\noutline color: ff33ff\nfill color: eeffbbff\n");
	}
}

TEST_CASE("FindMinPerimeterShape finds the shape with min perimeter")
{
	DataProcessor processor;
	std::ostringstream oss;

	SECTION("If there is no shapes")
	{
		processor.PrintMinPerimeterShapeInfo(oss);
		REQUIRE(oss.str() == "Failed to print shape data.\n");
	}

	SECTION("If there is single shape")
	{
		std::istringstream iss("rectangle 0 10 20 10 00FF33FF EEFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
		processor.PrintMinPerimeterShapeInfo(oss);
		REQUIRE(oss.str() == "type: rectangle\nleft top: (0.00, 10.00)\nwidth: 20.00\nheight: 10.00\narea: 200.00\nperimeter: 60.00\noutline color: ff33ff\nfill color: eeffbbff\n");
	}

	SECTION("Find min perimeter rectangle: first rect perim = 30, second = 40, third = 32")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33FF EEFFBBFF\nrectangle 5 -6 10 10 00FF33FF EEFFBBFF\nrectangle -7 4 1 15 00FF33FF EEFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
		processor.PrintMinPerimeterShapeInfo(oss);
		REQUIRE(oss.str() == "type: rectangle\nleft top: (1.00, 3.00)\nwidth: 10.00\nheight: 5.00\narea: 50.00\nperimeter: 30.00\noutline color: ff33ff\nfill color: eeffbbff\n");
	}
	
	SECTION("Find min perimeter triangle among other shape types: first rect perim = 30, second triangle = 16, third circle = 94.25")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33FF EEFFBBFF\ntriangle 0 0 3 4 6 0 00FF33FF EEFFBBFF\ncircle 0 0 15 00FF33FF EEFFBBFF");
		REQUIRE(processor.ReadShapeData(iss));
		processor.PrintMinPerimeterShapeInfo(oss);
		REQUIRE(oss.str() == "type: triangle\nvertex 1: (0.00, 0.00)\nvertex 2: (3.00, 4.00)\nvertex 3: (6.00, 0.00)\narea: 12.00\nperimeter: 16.00\noutline color: ff33ff\nfill color: eeffbbff\n");
	}
}