#include <iostream>
#include "LinAlg.h"

template<typename T>
void printArr(linAlg::IArray<T>& arr, std::string textMessage = "") {
	
	std::cout << "============== " << textMessage << " ==============\n\n" << std::endl;

	for (size_t indexC = 0; indexC < arr.getColumns(); ++indexC){
		for (size_t indexR = 0; indexR < arr.getRows(); ++indexR){
			std::cout << arr.getValue(indexR, indexC) << "\t";
		}
		std::cout << "\n";
	}

	std::cout << std::endl;
}

int main() {
	//use linAlg::Vector
	std::cout << "Vector use: \n" << std::endl;

	linAlg::Vector<int> a({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});
	printArr(a, "Vector a");
	linAlg::Vector<int> b({14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
	printArr(b, "Vector b");
	linAlg::Vector<int> c;

	try {
		c = a + b;
		printArr(c, "Vector c = a + b");

		c = a - b;
		printArr(c, "Vector c = a - b");

		a.minusThis(c);
		printArr(a, "Vector a - c");

		a.sumThis(c);
		printArr(a, "Vector a + c");

		a.multiplicationThisByNymber(5);
		printArr(a, "Vector a * 5");

		c = a * 5;
		printArr(c, "Vector c = a * 5");

	}
	catch(std::exception& ex){
		std::cout << ex.what() << std::endl;
	}
	
	//use linAlg::Matrix
	std::cout << "Matrix use: \n" << std::endl;
	 
	linAlg::Matrix<int> aM({ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}});
	printArr(aM, "Matrix aM");

	linAlg::Matrix<int> bM({ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
							 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
							 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0} });
	printArr(bM, "Matrix bM");
	linAlg::Matrix<int> cM;

	try {
		cM = aM - bM;
		printArr(cM, "Matrix cM = aM - bM");

		cM = aM + bM;
		printArr(cM, "Matrix cM = aM + bM");

		cM = aM * bM;
		printArr(cM, "Matrix cM = aM * bM");
		
		cM = linAlg::multiThreadMatrixMultiplication(aM, bM, 5);
		printArr(cM, "Matrix cM = aM * bM (threads)");
		
		aM.sumThis(cM);
		printArr(aM, "Matrix aM + cM");

		aM.minusThis(cM);
		printArr(aM, "Matrix aM - cM");

		aM.transpose();
		printArr(aM, "Matrix aM transpose");

		aM.multiplicationThisByNymber(2);
		printArr(aM, "Matrix aM * 2");

		cM = aM * 2;
		printArr(cM, "Matrix cM = aM * 2");
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
	

	return 0;
}
