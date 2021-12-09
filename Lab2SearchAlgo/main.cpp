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
	Interface::start();

	/*SparseMatrix<int> SM(10, 10, 0);
	SM.set(10, 0, 0);
	SM.print();*/

	//HashMap<int, int>HM(
	//	[](int p, int tableSize)->int
	//	{
	//		return p % tableSize;
	//	}, 100);
	//HM.Add({ 0, 1 });
	//HM.Add({ 100, 1100000 });
	//HM.Add({ 101, 1100000 });
	//HM.Add({ 102, 1100020 });

	//std::function<int(int, int)> func = [](int p, int tableSize)->int
	//{
	//	return p % tableSize;
	//};
	///*HM.Map(
	//	[](int p) -> int {
	//		cout << p;
	//		return p;
	//	}
	//);*/

	///*iterator iter = Iterator();*/

	///*HashMap<int, int>::iterator iter;

	//for (iter = HM.Iterator(); iter != HM.End(); ++iter)
	//	cout << (*iter).first << (*iter).second << "\n";*/

	//cout << HM;
	
	return 0;
}