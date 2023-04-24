#include "realvector.h" 
#include <iostream>
#include <string>

void printVec(const RealVector<int>& vec){
	std::cout << "My vector: { ";
	for(auto it = vec.begin(); it != vec.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << "}" << std::endl;
}

// //play around with RealVector here!
int main(){
	//make an empty vector
	RealVector<int> myVec(2, 1);
	printVec(myVec);
	std::cout << "Last ELEM: " << myVec[myVec.size()-1];

	std::cout << "Enter [ELEM] [INDEX]:"; 
	int to_add;
	size_t index;
	while(std::cin >> to_add >> index){
		myVec.insert(index, to_add);
		//print vector
		printVec(myVec);

		//next prompt
		std::cout << "Enter [ELEM] [INDEX]:"; 
	}
	return 0;
}