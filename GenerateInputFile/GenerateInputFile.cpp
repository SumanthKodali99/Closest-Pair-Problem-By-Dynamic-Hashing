#include "stdafx.h"

#include "Configuration.h"

int main(int argc, char * argv[]) {

	try {
		
		using namespace CLOSEST_POINTS_ALGO::GENERATE_INPUT_FILE;

		Configuration configuration(argc, argv);
		
		std::cout
			<< "\nOutput file name: " << configuration.GetOutpuFileName() 
			<< "\nNumber Of points: " << configuration.GetNumberOfPointToGenerate()
			<< "\nMin X value: " << configuration.GetMinAllowedXValue()
			<< "\nMin Y value: " << configuration.GetMinAllowedYValue()
			<< "\nMax X value: " << configuration.GetMaxAllowedXValue()
			<< "\nMax Y value: " << configuration.GetMaxAllowedYValue()
			<< std::endl;

		std::ofstream outputFile(configuration.GetOutpuFileName());
		if (!outputFile)
			throw std::runtime_error("Failed creating/rewriting file: " + configuration.GetOutpuFileName());

		size_t N = configuration.GetNumberOfPointToGenerate();
		double minX = configuration.GetMinAllowedXValue();
		double minY = configuration.GetMinAllowedYValue();
		double maxX = configuration.GetMaxAllowedXValue();
		double maxY = configuration.GetMaxAllowedYValue();
		
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		for (size_t n = 0; n < N; ++n) {
			double x = std::rand() * (maxX - minX) / RAND_MAX + minX;
			double y = std::rand() * (maxY - minY) / RAND_MAX + minY;
			outputFile << x << " " << y << "\n";
		}

		std::cout << "Done";

	} catch (std::exception &ex) {
		std::cerr << "ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "UNKNOWN ERROR" << std::endl;
	}

	return 0;
}

