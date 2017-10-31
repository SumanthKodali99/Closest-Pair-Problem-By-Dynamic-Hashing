#ifndef POINTSLIST_H
#define POINTSLIST_H
#pragma once

#include <deque>

#include <fstream>

#include <string>

#include <exception>

#include <random>

#include "Point.h"

namespace CLOSEST_POINTS_ALGO {

	class PointsList {
	public:
		virtual Point * GetNextPoint() = 0;
		virtual size_t GetPointsCounter() const = 0;
		virtual double GetMinX() const = 0;
		virtual double GetMinY() const = 0;
		virtual double GetMaxX() const = 0;
		virtual double GetMaxY() const = 0;
	protected:
		virtual ~PointsList() {};
	};


	class FilePointsList : public PointsList {
	public:
		FilePointsList(std::string fileName) 
			:lastPoint(0, 0)
		{
			std::cout << "Loading points from " << fileName << "..";

			std::ifstream inputFile(fileName.c_str());
			if (!inputFile)
				throw std::runtime_error("Failed opening: " + fileName);

			minX = 0;
			minY = 0;
			maxX = 0;
			maxY = 0;

			double x;
			double y;

			while (inputFile >> x && inputFile >> y) {

				points.emplace_back(x, y);

				if (x < minX) minX = x;
				if (y < minY) minY = y;
				if (x > maxX) maxX = x;
				if (y > maxY) maxY = y;
			}

			newPointIt = points.begin();

			std::cout << " done" << std::endl;

			if (points.size() < 2)
				throw std::runtime_error("At least two points are expected");
		}

		virtual Point * GetNextPoint() override {
			
			newPointIt = points.begin();

			if (newPointIt != points.cend()) {

				lastPoint.SetValue(newPointIt->GetX(), newPointIt->GetY());
				
				points.pop_front();

				++pointsCounter;

				return &lastPoint;
			}
			else
				return nullptr;
		}

		virtual size_t GetPointsCounter() const override {
			return pointsCounter;
		}

		virtual double GetMinX() const override { return minX; }
		virtual double GetMinY() const override { return minY; }
		virtual double GetMaxX() const override { return maxX; }
		virtual double GetMaxY() const override { return maxY; }

	private:
		size_t pointsCounter = 0;

		std::deque<Point>::iterator newPointIt;
		std::deque<Point> points;
		Point lastPoint;

		double minX = 0;
		double minY = 0;
		double maxX = 0;
		double maxY = 0;
	};
	

	class StreamPointsList : public PointsList {
	public:
		StreamPointsList(size_t numberOfPoints, double nMinAllowedX, double nMinAllowedY, double nMaxAllowedX, double nMaxAllowedY)
			:maxPointsCounter(numberOfPoints)
			, minAllowedX(nMinAllowedX)
			, minAllowedY(nMinAllowedY)
			, maxAllowedX(nMaxAllowedX)
			, maxAllowedY(nMaxAllowedY)
			, pointsCounter(0)
			, lastPoint(0, 0)
		{			
			minX = 0;
			minY = 0;
			maxX = 0;
			maxY = 0;

			std::random_device rd;
			std::srand(rd());
		}

		virtual Point * GetNextPoint() override {

			if (pointsCounter < maxPointsCounter) {

				double x = std::rand() * (maxAllowedX - minAllowedX) / RAND_MAX + minAllowedX;
				double y = std::rand() * (maxAllowedY - minAllowedY) / RAND_MAX + minAllowedY;
				
				if (x < minX) minX = x;
				if (y < minY) minY = y;
				if (x > maxX) maxX = x;
				if (y > maxY) maxY = y;

				lastPoint.SetValue(x, y);

				++pointsCounter;

				return &lastPoint;
			} else
				return nullptr;
		}

		virtual size_t GetPointsCounter() const override {
			return pointsCounter;
		}

		virtual double GetMinX() const override { return minX; }
		virtual double GetMinY() const override { return minY; }
		virtual double GetMaxX() const override { return maxX; }
		virtual double GetMaxY() const override { return maxY; }

	private:
		Point lastPoint;

		size_t pointsCounter = 0;
		const size_t maxPointsCounter;
		double minX = 0;
		double minY = 0;
		double maxX = 0;
		double maxY = 0;
		const double minAllowedX;
		const double minAllowedY;
		const double maxAllowedX;
		const double maxAllowedY;
	};

} //namespace CLOSEST_POINTS_ALGO

#endif //POINTSLIST_H
