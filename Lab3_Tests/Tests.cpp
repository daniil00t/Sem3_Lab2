#include "pch.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include "CppUnitTest.h"
#include "../CachedSequence.hpp"
#include "../IMatrix.hpp"
#include "../SparseMatrix.hpp"
#include "../ATD/Person.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TEST_SAMPLE_SIZE 30000
#define TEST_CACHE_SIZE 50

#define TEST_FREQUENT_COUNT 5
#define TEST_FREQUENT_PERCENT 80

#define TEST_QUERIES_COUNT 5000

using SparseTestParam =
std::vector<std::vector<int>>;

namespace Lab3Tests
{
	TEST_CLASS(CachedSequenceTESTS)
	{
	public:
		
		TEST_METHOD(AppendAndGet)
		{
			CachedSequence<int, Person*>* seq = new CachedSequence<int, Person*>(
				[](int id, int tableSize)->int
				{
					return id % tableSize;
				},
				TEST_CACHE_SIZE);

			Person* p;
			std::ifstream inFirst("/data/firstnames.txt", /*std::ios::binary|*/std::ios::in);
			std::ifstream inLast("/data/us.txt", /*std::ios::binary|*/std::ios::in);

			string firstname;
			string lastname;
			for (int i = 0; i < TEST_SAMPLE_SIZE; i++){
				inFirst >> firstname;
				inLast >> lastname;
				try {
					seq->Add(i, new Person(firstname, lastname, rand() % 100, i));
					Assert::IsTrue(1);
				}
				catch (const std::exception&){ Assert::IsTrue(0); }
				
			}

			inFirst.close();
			inLast.close();

			Person* gotten;

			ArraySequence<int>* FAQ = new ArraySequence<int>();

			for (int i = 0; i < TEST_FREQUENT_COUNT; i++){
				try {
					FAQ->Append(rand() % TEST_SAMPLE_SIZE);
					Assert::IsTrue(1);
				}
				catch (const std::exception&) { Assert::IsTrue(0); }
			}

			for (int i = 0; i < TEST_QUERIES_COUNT; i++){
				if (rand() % 100 < TEST_FREQUENT_PERCENT){
					//From FAQ
					
					try {
						gotten = seq->Get(FAQ->Get(rand() % TEST_FREQUENT_COUNT));
						Assert::IsTrue(1);
					}
					catch (const std::exception&) { Assert::IsTrue(0); }
				}
				else{
					try {
						//Random - because exception -> unknown_key
						gotten = seq->Get(rand() % TEST_SAMPLE_SIZE);
						Assert::IsTrue(1);
					}
					catch (const std::exception&) { Assert::IsTrue(0); }
				}
			}
		}

	};

	TEST_CLASS(SparseMatrixTESTS){
	public :
		TEST_METHOD(Append) {
			const SparseTestParam sparseTestData[] = { {}, {{1,2,0},{0,3,4}}, {{1,2,0},{0,3,4},{0,0,0}}, {{0,0,0},{0,0,0},{0,0,0}}, {{0}}, {{1}} };
			

			Matrix<int>* matrix = new Matrix<int>(sparseTestData->size() == 0 ? 0 : sparseTestData->at(0).size(), sparseTestData->size());
			for (std::size_t y = 0; y < sparseTestData->size(); y++) for (std::size_t x = 0; x < sparseTestData->at(0).size(); x++) {
				matrix->set(sparseTestData->at(y).at(x), x, y);
			}
			std::unique_ptr<HashMap<Point, int>> sparseData = SparseMatrix<int>(*matrix).getData();

			for (std::size_t y = 0; y < sparseTestData->size(); y++) for (std::size_t x = 0; x < sparseTestData->at(0).size(); x++) {
				int value = sparseTestData->at(y).at(x);
				if (value != 0)
					Assert::IsFalse(sparseData->Contains({ x,y }));
				else
					Assert::IsTrue(sparseData->Contains({ x,y }));
			}

			delete matrix;
		}

	};

}
