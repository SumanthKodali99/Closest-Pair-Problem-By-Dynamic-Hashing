#include "stdafx.h"

#include "Configuration.h"

namespace CLOSEST_POINTS_ALGO {

	const std::string Configuration::bstModeStr = "bst";
	const std::string Configuration::hashModeStr = "hash";
	const std::string Configuration::fileModeStr = "file";
	const std::string Configuration::streamModeStr = "stream";


	Configuration::Configuration(int argc, char * argv[]) {

		std::string typeStr;

		if (argc > 1) {
			typeStr = argv[1];
		} else
			throw std::runtime_error("Not enough agruments: type\n" + GetRequirementsString());

		if (typeStr == bstModeStr) {
			type = bstType;
		} else
			if (typeStr == hashModeStr) {
				type = hashType;

			} else
				throw std::runtime_error("Unsupported mode " + typeStr + " - must be '"+bstModeStr+"' or '"
				+hashModeStr+"'\n" + GetRequirementsString()
				);

		std::string modeStr;

		if (argc > 2) {
			modeStr = argv[2];
		} else
			throw std::runtime_error("Not enough agruments: mode\n" + GetRequirementsString());

		if (modeStr == fileModeStr) {
			LoadFileConfiguration(argc - 2, argv + 2);
			mode = fileMode;
		} else
			if (modeStr == streamModeStr) {
				LoadStreamConfiguration(argc - 2, argv + 2);
				mode = streamMode;

			} else
				throw std::runtime_error("Unsupported mode " + modeStr + " - must be '"+ fileModeStr 
				+"' or '"+streamModeStr+"'\n" + GetRequirementsString()
				);
	}


	void Configuration::LoadFileConfiguration(int argc, char * argv[]) {

		if (argc > 1) {
			inputFileName = argv[1];
		} else
			throw std::runtime_error("Not enough agruments: output file name\n" + GetRequirementsString());

		if (argc > 2) {
			resultFileName = argv[2];
		} else
			throw std::runtime_error("Not enough agruments: result file name\n" + GetRequirementsString());

		minAllowedXValue = 0;
		minAllowedYValue = 0;
		maxAllowedXValue = 0;
		maxAllowedYValue = 0;
	}

	void Configuration::LoadStreamConfiguration(int argc, char * argv[]) {

		if (argc > 1) {
			resultFileName = argv[1];
		} else
			throw std::runtime_error("Not enough agruments: result file name\n" + GetRequirementsString());

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


	std::string Configuration::GetInputFileName() const {
		return inputFileName;
	}

	std::string Configuration::GetResultFileName() const {
		return resultFileName;
	}

	std::string Configuration::GetRequirementsString() {
		return "Expected arguments list:"
			"\nVariant 1: file <input_data_file> <output file name>"
			"\nVariant 2: stream <output file name> <min X value> <min Y value> <max X value> <max Y value>";
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

	Configuration::Mode Configuration::GetMode() const {
		return mode;
	}

	Configuration::Type Configuration::GetType() const {
		return type;
	}

	size_t Configuration::GetNumberOfPointToGenerate() const {
		return numberOfPointsToGenerate;
	}

} //namespace CLOSEST_POINTS_ALGO
