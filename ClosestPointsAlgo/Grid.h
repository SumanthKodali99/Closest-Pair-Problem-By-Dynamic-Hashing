#ifndef GRID_H
#define GRID_H
#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Point.h"

namespace CLOSEST_POINTS_ALGO {

	class Grid : public std::enable_shared_from_this<Grid> {
	public:
		typedef std::vector<Point> Box;
		
		//build a new grid with points from a previous one
		virtual std::shared_ptr<Grid> Build() = 0;

		virtual double Report(const Point &, Point & closestPoint) = 0;

		virtual std::shared_ptr<Grid> Add(const Point & p) = 0;
		virtual void Insert(const Point & p) = 0;
		
		virtual size_t GetXIndex(double xCoord) const = 0;
		virtual size_t GetYIndex(double yCoord) const = 0;


		class CompositeIndex {
		public:
			CompositeIndex(size_t xIndex, size_t yIndex) {
				x.value = xIndex;
				y.value = yIndex;
			}

			CompositeIndex() {
				x.value = 0;
				y.value = 0;
			}

			bool CompositeIndex::operator == (const CompositeIndex & rhs) const {
				if (x.value == rhs.x.value && y.value == rhs.y.value)
					return true;
				else
					return false;
			}

			bool CompositeIndex::operator < (const CompositeIndex & rhs) const {
				if (x.value < rhs.x.value) {
					return true;
				}
				if (x.value > rhs.x.value) {
					return false;
				}
				if (y.value < rhs.y.value) {
					return true;
				}
				return false;
			}

			uint64_t CompositeIndex::GetX() const {
				return x.value;
			}

			uint64_t CompositeIndex::GetY() const {
				return y.value;
			}

			uint8_t CompositeIndex::GetXOctet(size_t index) const {
				assert(index < (sizeof(x.octets) / sizeof(x.octets[0])));
				return x.octets[index];
			}

			uint8_t CompositeIndex::GetYOctet(size_t index) const {
				assert(index < (sizeof(x.octets) / sizeof(x.octets[0])));
				return x.octets[index];
			}

		private:
			union {
				uint64_t value;
				uint8_t octets[8];
			} x;
			union {
				uint64_t value;
				uint8_t octets[8];
			} y;
		};
	
		double GetDistance() {
			return minDistance;
		}

		std::array<Point, 2> minDistancePoints;

	protected:
		Grid(double meshSize);
		virtual ~Grid();

		double meshSize;

		static std::size_t instanceNumber;
		size_t numberOfPoints = 0;

		double minDistance = std::numeric_limits<double>::max();
	};

	extern uint64_t randomConstants[256][16];

} //namespace CLOSEST_POINTS_ALGO

namespace std {

	template<>
	struct hash<CLOSEST_POINTS_ALGO::Grid::CompositeIndex> {

		typedef CLOSEST_POINTS_ALGO::Grid::CompositeIndex argument_type;
		typedef uint64_t result_type;

		/*
		result_type operator()(const argument_type & a) const {
			size_t lhs = std::hash<size_t>()(a.GetX());
			size_t rhs = std::hash<size_t>()(a.GetY());
			size_t res = lhs ^ (rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2));
			return res;
		}
		*/
		
		result_type operator()(const argument_type & a) const {
			
			uint64_t b00 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(0)][0];
			uint64_t b01 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(1)][1];
			uint64_t b02 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(2)][2];
			uint64_t b03 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(3)][3];
			uint64_t b04 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(4)][4];
			uint64_t b05 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(5)][5];
			uint64_t b06 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(6)][6];
			uint64_t b07 = CLOSEST_POINTS_ALGO::randomConstants[a.GetXOctet(7)][7];
			uint64_t b08 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(0)][8];
			uint64_t b09 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(1)][9];
			uint64_t b10 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(2)][10];
			uint64_t b11 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(3)][11];
			uint64_t b12 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(4)][12];
			uint64_t b13 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(5)][13];
			uint64_t b14 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(6)][14];
			uint64_t b15 = CLOSEST_POINTS_ALGO::randomConstants[a.GetYOctet(7)][15];

			uint64_t res = b00 ^ b01 ^ b02 ^ b03 ^ b04 ^ b05 ^ b06 ^ b07 ^ b08 ^ b09 ^ b10 ^ b11 ^ b12 ^ b13 ^ b14 ^ b15;

			return res;
		}
		
	};

} //namespace std

#endif //GRID_H