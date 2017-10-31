#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#pragma once

#include <istream>

namespace CLOSEST_POINTS_ALGO {
	namespace GENERATE_INPUT_FILE {

		class Configuration {
		public:
			Configuration(int argc, char * argv[]);

			std::string GetOutpuFileName() const;
			size_t GetNumberOfPointToGenerate() const;
			double GetMinAllowedXValue() const;
			double GetMinAllowedYValue() const;
			double GetMaxAllowedXValue() const;
			double GetMaxAllowedYValue() const;

			static std::string GetRequirementsString();

		private:
			std::string outputFileName;
			size_t numberOfPointsToGenerate;
			double minAllowedXValue;
			double minAllowedYValue;
			double maxAllowedXValue;
			double maxAllowedYValue;
		};

	} //namespace GENERATEINPUTFILE
} //namespace CLOSEST_POINTS_ALGO

#endif //CONFIGURATION_H