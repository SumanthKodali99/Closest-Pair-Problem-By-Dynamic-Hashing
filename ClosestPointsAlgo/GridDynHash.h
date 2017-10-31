#ifndef GRIDDYNHASH_H
#define GRIDDYNHASH_H
#pragma once

#include <deque>
#include <list>
#include <memory>
#include <cassert>
#include <iostream>
#include <array>

#include "Point.h"
#include "Grid.h"


namespace CLOSEST_POINTS_ALGO {

	class GridDynHash : public Grid {
	public:
		typedef uint64_t GridXIndex;
		typedef uint64_t GridYIndex;

		GridDynHash(double newMeshSize, size_t nTableSize
			, double nMinX, double nMaxX, double nMinY, double nMaxY
			)
			:Grid(newMeshSize)
			, tableSize(nTableSize)
			, minX(nMinX)
			, maxX(nMaxX)
			, minY(nMinX)
			, maxY(nMaxX) 
		{
			meshSize = newMeshSize;
			minDistance = newMeshSize;

			if (boxes.size() < tableSize) {
				boxes.resize(tableSize);
			}
		}

		~GridDynHash() { }

		size_t GetXIndex(double xCoord) const override {
			return static_cast<size_t>(xCoord / meshSize); //to the lower integer
		}

		size_t GetYIndex(double yCoord) const override {
			return static_cast<size_t>(yCoord / meshSize); //to the lower integer
		}

		//build a new grid with points from a previous one
		std::shared_ptr<Grid> Build() override {
			
			double newMeshSize = minDistance;
			size_t newTableSize = (numberOfPoints+1) * loadFactor;

			std::cout << "InstanceNumber: " << (instanceNumber + 1) << " "
				<< "Mesh size: " << meshSize << " "
				<< "Load factor: " << currentLoadFactor << ",  " << "\n"
				<< "MinX:" << minX << " "
				<< "MaxX:" << maxX << " "
				<< "MinY:" << minY << " "
				<< "MaxY:" << maxY << "\n"
				<< "NumberOfPoints: " << numberOfPoints << "\n"
				<< "TableSize: " << tableSize << std::endl;

			std::shared_ptr<GridDynHash> newGrid = std::make_shared<GridDynHash>(
				newMeshSize
				, newTableSize
				, minX
				, maxX
				, minY
				, maxY
				);
			
			for (auto & bucket : boxes) {
				if (bucket) {
					for (const auto & boxTuple : *bucket) {
						const Box & box = std::get<1>(boxTuple);
						for (const auto & point : box) {
							newGrid->Insert(point);
						}
					}
				}
			}

			newGrid->minDistancePoints = minDistancePoints;

			return newGrid;
		}

		double Report(const Point & newPoint, Point & closestPoint) override {

			size_t xIndex = GetXIndex(newPoint.GetX());
			size_t yIndex = GetYIndex(newPoint.GetY());

			std::array<const Grid::Box *, 9> neighbourBoxes = { 0 };

			uint64_t bucketIndex0 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex, yIndex)) % tableSize;
			if (boxes[bucketIndex0]) {
				auto & bucket0 = *boxes[bucketIndex0];
				for (auto & box : bucket0) {
					if (std::get<0>(box) == CompositeIndex(xIndex, yIndex)) {
						neighbourBoxes[0] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex1 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex - 1, yIndex - 1)) % tableSize;
			if (boxes[bucketIndex1]) {
				auto & bucket1 = *boxes[bucketIndex1];
				for (auto & box : bucket1) {
					if (std::get<0>(box) == CompositeIndex(xIndex - 1, yIndex - 1)) {
						neighbourBoxes[1] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex2 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex - 1, yIndex)) % tableSize;
			if (boxes[bucketIndex2]) {
				auto & bucket2 = *boxes[bucketIndex2];
				for (auto & box : bucket2) {
					if (std::get<0>(box) == CompositeIndex(xIndex - 1, yIndex)) {
						neighbourBoxes[2] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex3 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex - 1, yIndex + 1)) % tableSize;
			if (boxes[bucketIndex3]) {
				auto & bucket3 = *boxes[bucketIndex3];
				for (auto & box : bucket3) {
					if (std::get<0>(box) == CompositeIndex(xIndex -1, yIndex + 1)) {
						neighbourBoxes[3] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex4 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex + 1, yIndex - 1)) % tableSize;
			if (boxes[bucketIndex4]) {
				auto & bucket4 = *boxes[bucketIndex4];
				for (auto & box : bucket4) {
					if (std::get<0>(box) == CompositeIndex(xIndex + 1, yIndex - 1)) {
						neighbourBoxes[4] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex5 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex + 1, yIndex)) % tableSize;
			if (boxes[bucketIndex5]) {
				auto & bucket5 = *boxes[bucketIndex5];
				for (auto & box : bucket5) {
					if (std::get<0>(box) == CompositeIndex(xIndex + 1, yIndex)) {
						neighbourBoxes[5] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex6 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex + 1, yIndex + 1)) % tableSize;
			if (boxes[bucketIndex6]) {
				auto & bucket6 = *boxes[bucketIndex6];
				for (auto & box : bucket6) {
					if (std::get<0>(box) == CompositeIndex(xIndex +1, yIndex+1)) {
						neighbourBoxes[6] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex7 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex, yIndex - 1)) % tableSize;
			if (boxes[bucketIndex7]) {
				auto & bucket7 = *boxes[bucketIndex7];
				for (auto & box : bucket7) {
					if (std::get<0>(box) == CompositeIndex(xIndex, yIndex-1)) {
						neighbourBoxes[7] = &std::get<1>(box); //the same
					}
				}
			}
			uint64_t bucketIndex8 = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(xIndex, yIndex + 1)) % tableSize;
			if (boxes[bucketIndex8]) {
				auto & bucket8 = boxes[bucketIndex8];
				for (auto & box : *bucket8) {
					if (std::get<0>(box) == CompositeIndex(xIndex, yIndex+1)) {
						neighbourBoxes[8] = &std::get<1>(box); //the same
					}
				}
			}

			double minDistanceToNeighbour = std::numeric_limits<long double>::max();

			for (const Grid::Box * boxPtr : neighbourBoxes) {
				if (boxPtr) {
					for (const Point & pointRef : *boxPtr) {
						long double distance = newPoint.Distance(pointRef);
						if (distance < minDistanceToNeighbour) {
							minDistanceToNeighbour = distance;
							closestPoint.SetValue(pointRef.GetX(), pointRef.GetY());
						}
					}
				}
			}

			return minDistanceToNeighbour;
		}


		std::shared_ptr<Grid> Add(const Point & p) override {

			bool toRebuild = false;

			Point closestPoint;
			double minDistanceToNeighbour = Report(p, closestPoint);

			if (minDistanceToNeighbour != 0) {
				if (minDistanceToNeighbour < minDistance) {
					minDistance = minDistanceToNeighbour;
					minDistancePoints[0].SetValue(p.GetX(), p.GetY());
					minDistancePoints[1].SetValue(closestPoint.GetX(), closestPoint.GetY());
					toRebuild = true;
				}
			}

			double x = p.GetX();
			double y = p.GetY();

			if (x < minX) {
				minX = x;
			} else if (x > maxX) {
				maxX = x;
			}
			if (y < minY) {
				minY = y;
			} else if (y > maxY) {
				maxY = y;
			}

			currentLoadFactor = static_cast<double>(numberOfPoints) / tableSize;

			if (currentLoadFactor > loadFactor) {
				toRebuild = true;
			}

			std::shared_ptr<Grid> grid = shared_from_this();
			if (toRebuild) {
				grid = Build();
			}

			grid->Insert(p);

			return grid;
		}



		void Insert(const Point & p) override {

			Point closestPoint;
			double minDistanceToNeighbour = Report(p, closestPoint);

			if (minDistanceToNeighbour != 0) {
				if (minDistanceToNeighbour < minDistance) {
					minDistance = minDistanceToNeighbour;
					minDistancePoints[0].SetValue(p.GetX(), p.GetY());
					minDistancePoints[1].SetValue(closestPoint.GetX(), closestPoint.GetY());
				}
			}

			GridXIndex gridXIndex = GetXIndex(p.GetX());
			GridYIndex gridYIndex = GetYIndex(p.GetY());

			uint64_t bucketIndex = std::hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex>()(CompositeIndex(gridXIndex, gridYIndex)) 
				% tableSize;

			if (! boxes[bucketIndex]) {
				boxes[bucketIndex] = std::make_unique<std::vector<std::tuple<CompositeIndex, Box>>>();
			}

			if (boxes.size() < tableSize)
				boxes.resize(tableSize);

			auto & bucket = *boxes[bucketIndex];
			if (bucket.size() > maxBucketLength)
				maxBucketLength = bucket.size();
			for (auto & box : bucket) {
				if (std::get<0>(box) == CompositeIndex(gridXIndex, gridYIndex)) {
					//insert the point into existing box
					std::get<1>(box).push_back(p);
					if (std::get<1>(box).size() > maxBoxSize) 
						maxBoxSize = std::get<1>(box).size();

					++numberOfPoints;
					return;
				}
			}
			//insert a new box
			bucket.emplace_back(std::make_tuple(CompositeIndex(gridXIndex, gridYIndex), Box()));
			if (bucket.size() > maxBucketLength) 
				maxBucketLength = bucket.size();
			std::get<1>(bucket.back()).push_back(p);
			if (std::get<1>(bucket.back()).size() > maxBoxSize) 
				maxBoxSize = std::get<1>(bucket.back()).size();

			++numberOfPoints;
			return;
		}

	private:
		std::vector<std::unique_ptr<std::vector<std::tuple<CompositeIndex, Box>>>> boxes;
		size_t tableSize;

		size_t maxBucketLength = 0;
		size_t maxBoxSize = 0;

		double minX = std::numeric_limits<double>::max();
		double maxX = - std::numeric_limits<double>::max();
		double minY = std::numeric_limits<double>::max();
		double maxY = - std::numeric_limits<double>::max();

		double currentLoadFactor = 0;
		static double loadFactor;
	};

}//namespace CLOSEST_POINTS_ALGO


#endif //GRIDDYNHASH_H