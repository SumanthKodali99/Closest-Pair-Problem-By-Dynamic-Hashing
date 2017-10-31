#include "stdafx.h"

#include "Configuration.h"
#include "Point.h"
#include "PointsList.h"

#include "GridStdMap.h"
#include "GridDynHash.h"


inline std::string GetNowString();


int main(int argc, char * argv[]) {

	try {
		using namespace CLOSEST_POINTS_ALGO;

		Configuration configuration(argc, argv);

		std::cout
			<< "\nInput file name: " << configuration.GetInputFileName()
			<< "\nResult file name: " << configuration.GetResultFileName()
			<< "\n" << std::endl;

		std::shared_ptr<PointsList> pointsList;
		if (configuration.GetMode() == Configuration::fileMode) {
			pointsList = std::make_shared<FilePointsList>(configuration.GetInputFileName());
			std::cout << "\nMode: file";
		}
		if (configuration.GetMode() == Configuration::streamMode) {
			pointsList = std::make_shared<StreamPointsList>(
				configuration.GetNumberOfPointToGenerate()
				, configuration.GetMinAllowedXValue()
				, configuration.GetMinAllowedYValue()
				, configuration.GetMaxAllowedXValue()
				, configuration.GetMaxAllowedYValue()
				);
			std::cout << "\nMode: stream";
		}
		if (!pointsList)
			throw std::runtime_error("Undefined mode");

		std::cout << "\n" << std::endl;

		std::ofstream resultFile(configuration.GetResultFileName(), std::fstream::app);
		if (!resultFile)
			throw std::runtime_error("Failed openning file: " + configuration.GetInputFileName());


		std::string nowTimeStr = GetNowString();

		resultFile
			<< nowTimeStr
			<< "  " << configuration.GetInputFileName()
			<< std::endl;

		auto startTimeStamp = std::chrono::steady_clock::now();
		auto portionStartTimeStamp = std::chrono::steady_clock::now();

		long double minDistance = std::numeric_limits<long double>::max();

		std::shared_ptr<Grid> grid;

		switch (configuration.GetType()) {
		case Configuration::bstType:
			grid = std::make_shared<GridStdMap>(minDistance, std::numeric_limits<double>::max());
			break;
		case Configuration::hashType:
			grid = std::make_shared<GridDynHash>(
				minDistance
				, 1
				, configuration.GetMinAllowedXValue()
				, configuration.GetMaxAllowedXValue()
				, configuration.GetMinAllowedYValue()
				, configuration.GetMaxAllowedYValue()
				);
			break;
		default:
			throw std::runtime_error("Unknown mode");
		}

		//over all points
		Point * newPointIt = nullptr;
		
		while ((newPointIt = pointsList->GetNextPoint()) != nullptr) {

			grid = grid->Add(*newPointIt);

			/*
			if ((pointsList->GetPointsCounter() % 100000) == 0) {
				std::cout << "Count: " << pointsList->GetPointsCounter();
				resultFile << "Count: " << pointsList->GetPointsCounter();
				auto portionElelapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - portionStartTimeStamp);
				std::cout << "; Portion time elapsed: " << (portionElelapsedTimeMs.count() / 1000.0) << "s" << std::endl;
				resultFile << "; Portion time elapsed: " << (portionElelapsedTimeMs.count() / 1000.0) << "s" << std::endl;
				portionStartTimeStamp = std::chrono::steady_clock::now();
			}
			*/
		}


		auto elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTimeStamp);

		size_t pointsCounter = pointsList->GetPointsCounter();

		resultFile
			<< " Time elapsed: " << (elapsedTimeMs.count() / 1000.0) << "s"
			<< " | Points:" << pointsCounter
			<< " | MinDist:" << grid->GetDistance() << "\n"
			<< grid->minDistancePoints[0].GetX() << ":" << grid->minDistancePoints[0].GetY() << "\n"
			<< grid->minDistancePoints[1].GetX() << ":" << grid->minDistancePoints[1].GetY() << "\n"
			<< " | MinX:" << pointsList->GetMinX()
			<< " | MinY:" << pointsList->GetMinY()
			<< " | MaxX:" << pointsList->GetMaxX()
			<< " | MaxY:" << pointsList->GetMaxY()
			<< "\n-----------------------------------------------------\n" << std::endl;

		std::cout << "Done" << std::endl
			<< "\nTime: " << (elapsedTimeMs.count() / 1000.0) << "s\n"
			<< "\nNumber of points: " << pointsCounter
			<< "\nDistance: " << grid->GetDistance() << "\n"
			<< grid->minDistancePoints[0].GetX() << ":" << grid->minDistancePoints[0].GetY() << "\n"
			<< grid->minDistancePoints[1].GetX() << ":" << grid->minDistancePoints[1].GetY() << "\n"
			<< "\nMin X: " << pointsList->GetMinX()
			<< "\nMin Y: " << pointsList->GetMinY()
			<< "\nMax X: " << pointsList->GetMaxX()
			<< "\nMax Y: " << pointsList->GetMaxY()
			<< std::endl;

	} catch (std::exception &ex) {
		std::cerr << "ERROR: " << ex.what() << std::endl;		
	} catch (...) {
		std::cerr << "UNKNOWN ERROR" << std::endl;		
	}

	return 0;
}

inline std::string GetNowString() {
	std::time_t now = time(nullptr);
	std::tm * nowTimeInfo = localtime(&now);

	std::stringstream timeMessage;
	timeMessage
		<< (nowTimeInfo->tm_year + 1900)
		<< '-'
		<< (nowTimeInfo->tm_mon + 1)
		<< '-'
		<< nowTimeInfo->tm_mday
		<< " "
		<< nowTimeInfo->tm_hour
		<< "-"
		<< nowTimeInfo->tm_min
		<< "-"
		<< nowTimeInfo->tm_sec;
	return timeMessage.str();
}