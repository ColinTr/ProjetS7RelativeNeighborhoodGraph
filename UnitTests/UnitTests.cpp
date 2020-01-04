#include "CppUnitTest.h"

#include "../ConstructionRNG/Exception.cpp"
#include "../ConstructionRNG/Exception.hpp"

#include "../ConstructionRNG/MatrixOfBoolean.hpp"
#include "../ConstructionRNG/MatrixOfBoolean.cpp"

#include "../ConstructionRNG/MatrixOfFloat.cpp"
#include "../ConstructionRNG/MatrixOfFloat.hpp"

#include "../ConstructionRNG/FileData.cpp"
#include "../ConstructionRNG/FileData.hpp"

#include "../ConstructionRNG/GraphData.cpp"
#include "../ConstructionRNG/GraphData.hpp"

#include "../ConstructionRNG/DistancesBetweenNodes.cpp"
#include "../ConstructionRNG/DistancesBetweenNodes.hpp"

#include "../ConstructionRNG/DataExporter.cpp"
#include "../ConstructionRNG/DataExporter.hpp"

#include "../ConstructionRNG/RNGraph.cpp"
#include "../ConstructionRNG/RNGraph.hpp"

#include "../ConstructionRNG/TravelAlgorithmResult.cpp"
#include "../ConstructionRNG/TravelAlgorithmResult.hpp"

#include "../ConstructionRNG/ProgressBar.cpp"
#include "../ConstructionRNG/ProgressBar.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {

	//Change the path to the test files here :
	std::string dataFile = "C:/Users/Colin/Google Drive/DI/S7/Projet S7 - Nouvelle Version/UnitTestsData/unitTestsData.data";
	std::string classesFile = "C:/Users/Colin/Google Drive/DI/S7/Projet S7 - Nouvelle Version/UnitTestsData/temp.txt";

	//The files used in the tests :
	//unitTestsData.data
	/* 1, 1, 1, ligne1
	   2, 2, 2, ligne2
	   3, 3, 3, ligne3
	   4, 4, 4, ligne4
	   5, 5, 5, ligne5 */

	//temp.txt :
	/* 0, 0, 2, 1 */

	TEST_CLASS(testMatrixOfBoolean) {

	public:

		TEST_METHOD(TestIsSquare) {
			MatrixOfBoolean m1(2, 2);
			Assert::IsTrue(m1.isSquare());
			MatrixOfBoolean m2(2, 3);
			Assert::IsFalse(m2.isSquare());
		}

		TEST_METHOD(TestIsSizeNotValid) {
			MatrixOfBoolean m1(2, 2);
			Assert::IsFalse(m1.isSizeNotValid());
			MatrixOfBoolean m2(0, 0);
			Assert::IsTrue(m2.isSizeNotValid());
		}
		
	};

	TEST_CLASS(testMatrixOfFloat) {

	public:

		TEST_METHOD(TestIsSquare) {
			MatrixOfFloat m1(2, 2);
			Assert::IsTrue(m1.isSquare());
			MatrixOfFloat m2(2, 3);
			Assert::IsFalse(m2.isSquare());

		}

		TEST_METHOD(TestIsSizeNotValid) {
			MatrixOfFloat m1(2, 2);
			Assert::IsFalse(m1.isSizeNotValid());
			MatrixOfFloat m2(0, 0);
			Assert::IsTrue(m2.isSizeNotValid());
		}

		TEST_METHOD(TestResizeMatrix) {
			MatrixOfFloat m(2, 2);
			Assert::AreEqual((int) m.getNumberOfRows(), 2);
			Assert::AreEqual((int) m.getNumberOfColumns(), 2);
			m.resizeMatrix(3, 5);
			Assert::AreEqual((int) m.getNumberOfRows(), 3);
			Assert::AreEqual((int) m.getNumberOfColumns(), 5);
		}

	};

	TEST_CLASS(testFileData) {

	public:

		TEST_METHOD(TestConstructorAndGetters) {
			FileData fileData(dataFile, classesFile, ',');

			Assert::AreEqual(fileData.getSeparationCharacter(), ',');
			Assert::AreEqual(fileData.getNumberOfColumns(), (unsigned int) 4);
			Assert::AreEqual(fileData.getNumberOfColumnsNonClass(), (unsigned int) 3);
			Assert::AreEqual(fileData.getNumberOfRows(), (unsigned int) 5);
			Assert::IsFalse(fileData.isColumnAClassAttribute(0));
			Assert::IsTrue(fileData.isColumnAClassAttribute(2));
			Assert::IsTrue(fileData.isColumnAClassAttribute(3));
			Assert::IsTrue(fileData.isColumnUsedToGenerateTheGraph(2));
			Assert::IsFalse(fileData.isColumnUsedToGenerateTheGraph(3));
			Assert::IsTrue(fileData.isColumnUsedToGenerateTheGraph(1));
			std::string tmp = "2";
			Assert::AreEqual(fileData.getString(1, 2), tmp);
		}

	};

	TEST_CLASS(testGraphData) {

	public:

		TEST_METHOD(TestConstructor) {
			FileData fileData(dataFile, classesFile, ',');
			GraphData graphData(fileData);

			Assert::AreEqual(graphData.getNumberOfColumns(), (unsigned int) 3);
			Assert::AreEqual(graphData.getNumberOfRows(), (unsigned int) 5);
		}

	};

	TEST_CLASS(testDistancesBetweenNodes) {

	public:

		TEST_METHOD(TestConstructorAndGetter) {
			DistancesBetweenNodes distances(GraphData(FileData(dataFile, classesFile, ',')));

			Assert::AreEqual(distances.getNumberOfColumns(), (unsigned int) 5);
			Assert::AreEqual(distances.getNumberOfRows(), (unsigned int) 5);
			
			Assert::AreEqual((double) distances.getDistance(0, 1), 0.433013, 0.000001); //0.000001 is the tolerance
			Assert::AreEqual((double) distances.getDistance(1, 2), 0.433013, 0.000001);
			Assert::AreEqual((double) distances.getDistance(2, 3), 0.433013, 0.000001);
			Assert::AreEqual((double) distances.getDistance(3, 4), 0.433013, 0.000001);
		}

	};

	TEST_CLASS(testRNGraph) {

	public:

		TEST_METHOD(TestConstructor) {
			RNGraph rngraph(DistancesBetweenNodes(GraphData(FileData(dataFile, classesFile, ','))));

			Assert::AreEqual(rngraph.getNumberOfColumns(), (unsigned int) 5);
			Assert::AreEqual(rngraph.getNumberOfRows(), (unsigned int) 5);

			//We test the 3 first lines of the file
			Assert::IsFalse(rngraph.getElement(0, 0));
			Assert::IsTrue(rngraph.getElement(0, 1)); //Edge between node 0 and 1
			Assert::IsFalse(rngraph.getElement(0, 2));
			Assert::IsFalse(rngraph.getElement(0, 3));
			Assert::IsFalse(rngraph.getElement(0, 4));
			Assert::IsFalse(rngraph.getElement(1, 0));
			Assert::IsFalse(rngraph.getElement(1, 1));
			Assert::IsTrue(rngraph.getElement(1, 2)); //Edge between node 1 and 2
			Assert::IsFalse(rngraph.getElement(1, 3));
			Assert::IsFalse(rngraph.getElement(1, 4));
			Assert::IsFalse(rngraph.getElement(2, 0));
			Assert::IsFalse(rngraph.getElement(2, 1));
			Assert::IsFalse(rngraph.getElement(2, 2));
			Assert::IsTrue(rngraph.getElement(2, 3)); //Edge between node 2 and 3
			Assert::IsFalse(rngraph.getElement(2, 4));
		}

	};

	TEST_CLASS(testTravelAlgorithmResult) {

	public:

		TEST_METHOD(TestGeneratedStats) {
			FileData fileData(dataFile, classesFile, ',');
			GraphData graphdata(fileData);
			DistancesBetweenNodes distances(graphdata);
			RNGraph rngraph(distances);
			TravelAlgorithmResult result(rngraph.getNumberOfColumns());

			result.generateNeighbors(rngraph, 1);

			result.generateResultsWithNeighborAlgorithm(distances, 1, -1);

			Assert::AreEqual(result.getElementFromFoundAgainWhenInserted(0), (unsigned int) 5);
			Assert::AreEqual(result.getElementFromFoundAgainWhenInserted(1), (unsigned int) 5);
			Assert::AreEqual(result.getElementFromFoundAgainWhenInserted(2), (unsigned int) 5);
			Assert::AreEqual(result.getElementFromFoundAgainWhenInserted(3), (unsigned int) 5);
			Assert::AreEqual(result.getElementFromFoundAgainWhenInserted(4), (unsigned int) 5);

			Assert::AreEqual(result.getElementFromFoundRightNodeWhenInsertedOn(0), (unsigned int)5);
			Assert::AreEqual(result.getElementFromFoundRightNodeWhenInsertedOn(1), (unsigned int)5);
			Assert::AreEqual(result.getElementFromFoundRightNodeWhenInsertedOn(2), (unsigned int)5);
			Assert::AreEqual(result.getElementFromFoundRightNodeWhenInsertedOn(3), (unsigned int)5);
			Assert::AreEqual(result.getElementFromFoundRightNodeWhenInsertedOn(4), (unsigned int)5);

			Assert::AreEqual(result.getElementFromUsedNodeToTravel(0), (unsigned int) 4);
			Assert::AreEqual(result.getElementFromUsedNodeToTravel(1), (unsigned int) 10);
			Assert::AreEqual(result.getElementFromUsedNodeToTravel(2), (unsigned int) 12);
			Assert::AreEqual(result.getElementFromUsedNodeToTravel(3), (unsigned int) 10);
			Assert::AreEqual(result.getElementFromUsedNodeToTravel(4), (unsigned int) 4);
		}

	};

}