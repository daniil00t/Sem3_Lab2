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

	//SparseMatrix<int> SM(10, 10, 0);
	//SM.set(10, 0, 0);
	//SM.map(
	//	[](int p) -> int {
	//		cout << p * 2;
	//		return p * 2;
	//	}
	//);
	//SM.print();

	//HashMap<int, int>HM(
	//	[](int p, int tableSize)->int
	//	{
	//		return p % tableSize;
	//	}, 100);
	//HM.Add({ 0, 1 });
	//HM.Add({ 100, 2 });
	//HM.Add({ 101, 3 });
	//HM.Add({ 102, 4 });

	//HashMapIterator<int, int> iter = HM.Iterator();
	//for (; iter != HM.End(); ++iter)
	//{
	//	HM.Add((*iter).first, (*iter).second * 2);
	//}

	//HM.Map(
	//	[](int p) -> int {
	//		cout << p;
	//		return p;
	//	}
	//);

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
	
	//system("pause");
	return 0;
}