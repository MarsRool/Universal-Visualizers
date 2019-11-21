#include "stdafx.h"
#include "MR_Matrix.h"
#include "Tests.h"


//Test Matrix

bool Test_MR_Matrix()
{
	bool isOk = true;
	MR::Helpers::Matrix test(3, 3);
	double ** Ptr = new double*[3];
	Ptr[0] = new double[3]{ 1,3,4 };
	Ptr[1] = new double[3]{ 0,2,1 };
	Ptr[2] = new double[3]{ 1,5,-1 };
	test.setMatrix(3, 3, Ptr);
	test = test + test;
	double det = test.getDeterminant();
	double a23 = test[2][3];
	double a55 = test[5][5];
	return isOk;
}

/*using namespace std;
void vector_test()
{
	vector<string> myvector;  // a vector of stings.


	// push some strings in the vector.
	myvector.push_back("a");
	myvector.push_back("b");
	myvector.push_back("c");
	myvector.push_back("d");


	vector<string>::iterator it;  // declare an iterator to a vector of strings
	int n = 3;  // nth element to be found.
	int i = 0;  // counter.

	// now start at from the beginning
	// and keep iterating over the element till you find
	// nth element...or reach the end of vector.
	for (it = myvector.begin(); it != myvector.end(); it++, i++) {
		// found nth element..print and break.
		if (i == n) {
			cout << *it << endl;  // prints d.
			break;
		}
	}

	// other easier ways of doing the same.
	// using operator[]
	cout << myvector[n] << endl;  // prints d.

	// using the at method
	cout << myvector.at(n) << endl;  // prints d.
}*/