#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#pragma once

namespace CLOSEST_POINTS_ALGO {

		class Configuration {
		public:
			Configuration(int argc, char * argv[]);

			void LoadFileConfiguration(int argc, char * argv[]);
			void LoadStreamConfiguration(int argc, char * argv[]);

			std::string GetInputFileName() const;
			std::string GetResultFileName() const;

			double GetMinAllowedXValue() const;
			double GetMinAllowedYValue() const;
			double GetMaxAllowedXValue() const;
			double GetMaxAllowedYValue() const;

			size_t Configuration::GetNumberOfPointToGenerate() const;

			static std::string GetRequirementsString();

			enum Type {
				bstType
				, hashType
			};

			enum Mode {
				fileMode
				, streamMode
			};

			Mode GetMode() const;
			Type GetType() const;

		private:
			std::string inputFileName;
			std::string resultFileName;

			double minAllowedXValue = 0;
			double minAllowedYValue = 0;
			double maxAllowedXValue = 0;
			double maxAllowedYValue = 0;

			size_t numberOfPointsToGenerate;

			Mode mode;
			Type type;

			static const std::string bstModeStr;
			static const std::string hashModeStr;
			static const std::string fileModeStr;
			static const std::string streamModeStr;
		};

} //namespace CLOSEST_POINTS_ALGO

#endif //CONFIGURATION_H