#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/compute.hpp>

namespace compute = boost::compute;
using namespace std;

//print out stl vectors
template <typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
	if (!v.empty()) {
		out << '[';
		copy(v.begin(), v.end(), ostream_iterator<T>(out, ", "));
		out << "\b\b]";
	}
	return out;
}

int main() {
	typedef int mytype;

	// create vectors on the host
	vector<mytype> A = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<mytype> B = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
	vector<mytype> C(A.size());

	// create vectors on the device
	compute::vector<mytype> devA(A.size());
	compute::vector<mytype> devB(B.size());
	compute::vector<mytype> devC(C.size());

	// copy input data to the device
	compute::copy(A.begin(), A.end(), devA.begin());
	compute::copy(B.begin(), B.end(), devB.begin());

	// perform C = A + B
	compute::transform(devA.begin(), devA.end(), devB.begin(), devC.begin(), compute::plus<mytype>());

	// copy data back to the host
	compute::copy(devC.begin(), devC.end(), C.begin());

	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "C = " << C << endl;

	return 0;
}