#include <iostream>
#include <fstream>
#include <cstdlib>
#include "HashMap.hpp"
#include "IDictionary.hpp"
#include "HashMapIterator.hpp"
#include "CachedSequence.hpp"

#include "IMatrix.hpp"
#include "SparseMatrix.hpp"

int main()
{
	Matrix<int> M(2, 2);
	M.set(13, 0, 0);
	M.set(13, 0, 1);
	M.set(13, 1, 0);
	M.set(13, 1, 1);

	SparseMatrix<int> SM(M, 0);

	std::cout << SM.getData();
	


	return 0;
}
