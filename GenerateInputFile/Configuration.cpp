#include "stdafx.h"

#include "Configuration.h"

namespace CLOSEST_POINTS_ALGO {
	namespace GENERATE_INPUT_FILE {

		Configuration::Configuration(int argc, char * argv[]) {

			if (argc > 1) {
				outputFileName = argv[1];
			} else
				throw std::runtime_error("Not enough agruments: output file name\n" + GetRequirementsString());

			if (argc > 2) {
				try {
					numberOfPointsToGenerate = std::stoul(argv[2]);
				} catch (std::runtime_error & ex) {
					throw std::runtime_error(std::string("2nd command line argument convirsion error (an integer is expected): ")
						+ ex.what()
						+ "\n"
						+ GetRequirementsString()
						);
				}
			} else
				throw std::runtime_error("No enough agruments: number of points" + GetRequirementsString());

			if (argc > 3) {
				try {
					minAllowedXValue = std::stod(argv[3]);
				} catch (std::runtime_error & ex) {
					throw std::runtime_error(std::string("3rd command line argument convirsion error (a real number is expected): ")
						+ ex.what()
						+ "\n"
						+ GetRequirementsString()
						);
				}
			} else
				throw std::runtime_error("No enough agruments: minAllowedXValue" + GetRequirementsString());

			if (argc > 4) {
				try {
					minAllowedYValue = std::stod(argv[4]);
				} catch (std::runtime_error & ex) {
					throw std::runtime_error(std::string("4th command line argument convirsion error (a real number is expected): ")
						+ ex.what()
						+ "\n"
						+ GetRequirementsString()
						);
				}
			} else
				throw std::runtime_error("No enough agruments: minAllowedYValue" + GetRequirementsString());

			if (argc > 5) {
				try {
					maxAllowedXValue = std::stod(argv[5]);
				} catch (std::runtime_error & ex) {
					throw std::runtime_error(std::string("5th command line argument convirsion error (a real number is expected): ")
						+ ex.what()
						+ "\n"
						+ GetRequirementsString()
						);
				}
			} else
				throw std::runtime_error("No enough agruments: maxAllowedXValue" + GetRequirementsString());

			if (argc > 6) {
				try {
					maxAllowedYValue = std::stod(argv[6]);
				} catch (std::runtime_error & ex) {
					throw std::runtime_error(std::string("6th command line argument convirsion error (a real number is expected): ")
						+ ex.what()
						+ "\n"
						+ GetRequirementsString()
						);
				}
			} else
				throw std::runtime_error("No enough agruments: maxAllowedYValue" + GetRequirementsString());

		}


		std::string Configuration::GetOutpuFileName() const { 
			return outputFileName; 
		}
		
		size_t Configuration::GetNumberOfPointToGenerate() const { 
			return numberOfPointsToGenerate; 
		}
		
		double Configuration::GetMinAllowedXValue() const {
			return minAllowedXValue;
		}
		
		double Configuration::GetMinAllowedYValue() const {
			return minAllowedYValue;
		}
		
		double Configuration::GetMaxAllowedXValue() const {
			return maxAllowedXValue;
		}
		
		double Configuration::GetMaxAllowedYValue() const {
			return maxAllowedYValue;
		}

		std::string Configuration::GetRequirementsString() {
			return "Expected arguments list: <output file name> <number of points to generate> <min X value> <min Y value> <max X value> <max Y value>";
		}

	} //namespace GENERATEINPUTFILE
} //namespace CLOSEST_POINTS_ALGO
