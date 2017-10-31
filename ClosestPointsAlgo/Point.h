#ifndef POINT_H
#define POINT_H
#pragma once

#include <cmath>

namespace CLOSEST_POINTS_ALGO {

	class Point {
	public:
		Point(double x, double y)
			:xCoord(x)
			, yCoord(y) {
		}

		Point()
			:xCoord(0)
			, yCoord(0)
		{
		}

		double GetX() const { return xCoord; }
		double GetY() const { return yCoord; }

		void SetValue(double x, double y) {
			xCoord = x;
			yCoord = y;
		}

		long double Distance(const Point & rhs) const {
			long double diffY = yCoord - rhs.yCoord;
			long double diffX = xCoord - rhs.xCoord;
			return std::sqrt(std::pow(yCoord - rhs.yCoord, 2) + std::pow(xCoord - rhs.xCoord, 2));
		}

	private:
		double xCoord;
		double yCoord;
	};

} //namespace CLOSEST_POINTS_ALGO

#endif //CONFIGURATION_H