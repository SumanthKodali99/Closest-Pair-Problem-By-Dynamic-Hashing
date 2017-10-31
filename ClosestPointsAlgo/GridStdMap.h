#ifndef GRIDSTDMAP_H
#define GRIDSTDMAP_H
#pragma once

#include <map>
#include <array>
#include <vector>
#include <cassert>

#include "Point.h"

#include "Grid.h"

namespace CLOSEST_POINTS_ALGO {

	class GridStdMap : public Grid {
	public:
		GridStdMap(double meshSize, double nMinDistance)
			:Grid(meshSize)
		{
			minDistance = nMinDistance;
		}

		//build a grid with points from a previous one
		std::shared_ptr<Grid> Build() override {

			meshSize = minDistance;

			std::cout << "InstanceNumber: " << instanceNumber << "\n"
				<< " (grid size: " << boxes.size() << ") " << "\n"
				<< "NumberOfPoints: " << numberOfPoints << ",  " << "\n"
				<< "Mesh size: " << meshSize << ",  " << "\n"
				<< "Boxes: " << boxes.size() << std::endl;

			std::shared_ptr<Grid> newGrid = std::make_shared<GridStdMap>(meshSize, minDistance);
			for (const auto & box : boxes) {
				for (const auto & point : box.second) {
					newGrid->Insert(point);
				}
			}

			newGrid->minDistancePoints = minDistancePoints;

			return newGrid;
		}

		size_t GetXIndex(double xCoord) const override {
			return static_cast<size_t>(xCoord / meshSize); //to the lower integer
		}

		size_t GetYIndex(double yCoord) const override {
			return static_cast<size_t>(yCoord / meshSize); //to the lower integer
		}

		double Report(const Point & newPoint, Point & closestPoint) override {
			
			size_t xIndex = GetXIndex(newPoint.GetX());
			size_t yIndex = GetYIndex(newPoint.GetY());

			std::array<const Grid::Box *, 9> neighbourBoxes;

			neighbourBoxes[0] = &boxes[CompositeIndex(xIndex, yIndex)]; //the same
			neighbourBoxes[1] = &boxes[CompositeIndex(xIndex - 1, yIndex - 1)];  //left-up
			neighbourBoxes[2] = &boxes[CompositeIndex(xIndex - 1, yIndex)]; //left 
			neighbourBoxes[3] = &boxes[CompositeIndex(xIndex - 1, yIndex + 1)]; //left-botom
			neighbourBoxes[4] = &boxes[CompositeIndex(xIndex + 1, yIndex - 1)]; //right-up
			neighbourBoxes[5] = &boxes[CompositeIndex(xIndex + 1, yIndex)]; //right
			neighbourBoxes[6] = &boxes[CompositeIndex(xIndex + 1, yIndex + 1)]; //right-bottom
			neighbourBoxes[7] = &boxes[CompositeIndex(xIndex, yIndex - 1)]; //up
			neighbourBoxes[8] = &boxes[CompositeIndex(xIndex, yIndex + 1)]; //bottom

			assert(neighbourBoxes[0]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[1]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[2]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[3]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[4]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[5]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[6]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[7]->size() <= 4); //no more than 4 points in a box
			assert(neighbourBoxes[8]->size() <= 4); //no more than 4 points in a box
			
			double minDistanceToNeighbour = std::numeric_limits<long double>::max();

			for (const Grid::Box * boxPtr : neighbourBoxes) {
				for (const Point & pointRef : *boxPtr) {
					long double distance = newPoint.Distance(pointRef);
					if (distance < minDistanceToNeighbour) {
						minDistanceToNeighbour = distance;
						closestPoint.SetValue(pointRef.GetX(), pointRef.GetY());
					}
				}
			}

			return minDistanceToNeighbour;
		}


		std::shared_ptr<Grid> Add(const Point & p) override {
			
			Point closestPoint;
			double minDistanceToNeighbour = Report(p, closestPoint);

			std::shared_ptr<Grid> grid = shared_from_this();

			if (minDistanceToNeighbour != 0) {
				if (minDistanceToNeighbour < minDistance) {
					minDistance = minDistanceToNeighbour;

					minDistancePoints[0].SetValue(p.GetX(), p.GetY());
					minDistancePoints[1].SetValue(closestPoint.GetX(), closestPoint.GetY());

					grid = Build();
				}
			}

			++numberOfPoints;

			grid->Insert(p);

			return grid;
		}


		void Insert(const Point & p) override {

			auto & boxPoints = boxes[CompositeIndex(GetXIndex(p.GetX()), GetYIndex(p.GetY()))];
			boxPoints.emplace_back(p.GetX(), p.GetY());

			return;
		}

		std::map<CompositeIndex, Box> boxes;
	};

} //namespace CLOSEST_POINTS_ALGO

#endif //GRIDSTDMAP_H