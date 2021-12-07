#include "Interface.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "HashMap.hpp"
#include "IDictionary.hpp"
#include "HashMapIterator.hpp"
#include "CachedSequence.hpp"

#include "IMatrix.hpp"
#include "SparseMatrix.hpp"


using namespace std;


int main()
{
	//Interface::start();

	Matrix<int> M(20, 20);
	M.set(10, 10, 10);
	M.set(10, 11, 10);
	M.set(10, 12, 10);
	SparseMatrix<int> SM(M, 0);
	//SM.set(10, 0, 0);
	cout << SM.getData();
	
	return 0;
}