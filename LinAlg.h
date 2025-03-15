#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include "IArray.h"
#include "Matrix.h"
#include "Vector.h"

namespace linAlg {
	
	template<typename T>
	Matrix<T> multiThreadMatrixMultiplication(Matrix<T>& arr1, Matrix<T>& arr2, size_t countThread = 1) {
		if (arr1.getRows() == arr2.getColumns()) {
			Matrix<T> result(arr2.getRows(), arr1.getColumns());
			
			if (countThread < 1) 
				countThread = 1;
			else if (countThread > arr2.getRows())
				countThread = arr2.getRows();

			std::vector<std::thread> threadMatrix;
			size_t blockSizeMatrix = arr2.getRows() / countThread;
			std::mutex mut;

			auto mutiplyBlockMatrix = 
			[&arr1, &arr2, &result, &mut](size_t startRow, size_t endRow) {
				size_t n = arr2.getRows();
				size_t m = arr1.getRows();

				for (size_t i = startRow; i < endRow; ++i) {
					for (size_t j = 0; j < n; ++j) {
						T value = 0;
						for (size_t k = 0; k < m; ++k) {
							value += arr1.getValue(k, i) * arr2.getValue(j, k);
						}
						std::lock_guard<std::mutex> guard(mut);
						result.setValue(value, j, i);
					}
				}
			};

			for (size_t threadNum = 0; threadNum < countThread; ++threadNum) {
				size_t startRow = threadNum * blockSizeMatrix;
				size_t endRow = (threadNum == countThread - 1) ? arr1.getColumns() : startRow + blockSizeMatrix;
				threadMatrix.emplace_back(mutiplyBlockMatrix, startRow, endRow);
			}

			for (size_t th = 0; th < threadMatrix.size(); ++th) {
				if (th == threadMatrix.size() - 1) {
					threadMatrix[th].join();
				}
				else {
					threadMatrix[th].detach();
				}
			}
			
			return result;
		}
		else {
			throw std::exception("EXCEPTION: invalid array size, Matrix::multiThreadMatrixMultiplicationn");
		}
	}

}
