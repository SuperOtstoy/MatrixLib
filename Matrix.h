#pragma once
#include <vector>
#include "IArray.h"

namespace linAlg {

	template<typename T>
	class Matrix : public IArray<T> {
	public:
		Matrix();
		Matrix(const size_t countRow, const size_t countColumn);
		Matrix(const std::vector<std::vector<T>>& data);

		//получить количесвто строк
		size_t getRows() const override;
		//получить количество столбцов
		size_t getColumns() const override;
		//Получит значение по индексу
		T getValue(const size_t rowIndex, const size_t columnIndex) const override;
		//Установить значение
		void setValue(const T value, const size_t rowIndex, const size_t columnIndex) override;

		void transpose();

		//прибавить матрицу к текущей матрице
		void sumThis(const IArray<T>& arr);

		void multiplicationThisByNymber(T number);

		void minusThis(const IArray<T>& arr);

		Matrix<T> operator- (IArray<T>& arr) const;

		Matrix<T> operator+ (IArray<T>& arr) const;

		Matrix<T> operator* (IArray<T>& arr) const;

		Matrix<T> operator* (T number) const;
		
	private:

		//Получить данные из массива
		const std::vector<T>& getData() const override;

		void MatrixMultiplyVectorRow(IArray<T>& arr, Matrix<T>& matrix) const;
		void MatrixMultiplyVectorColumn(IArray<T>& arr, Matrix<T>& matrix) const;
		void MatrixMultiplyMatrix(IArray<T>& arr, Matrix<T>& matrix) const;

		std::vector<T> m_data;
		size_t m_rows;
		size_t m_columns;
	};


	template<typename T>
	inline Matrix<T>::Matrix(){
		m_data.clear();
		m_rows = 0;
		m_columns = 0;
	}

	template<typename T>
	inline Matrix<T>::Matrix(const size_t countRow, const size_t countColumn){
		m_data.resize(countRow * countColumn);
		m_rows = countRow;
		m_columns = countColumn;
	}

	template<typename T>
	Matrix<T>::Matrix(const std::vector<std::vector<T>>& data){
		m_rows = data[0].size();
		m_columns =  data.size();
		m_data.resize(m_rows * m_columns);

		for (size_t indexC = 0; indexC < m_columns; ++indexC) {
			for (size_t indexR = 0; indexR < m_rows; ++indexR) {
				m_data[indexR + indexC * m_rows] = data[indexC][indexR];
			}
		}
	}
	
	template<typename T>
	inline size_t Matrix<T>::getRows() const{
		return m_rows;
	}
	
	template<typename T>
	inline size_t Matrix<T>::getColumns() const{
		return m_columns;
	}
	
	template<typename T>
	inline T Matrix<T>::getValue(const size_t rowIndex, const size_t columnIndex) const{
		size_t index = rowIndex + columnIndex * m_rows;
		if (index > m_data.size()) {
			throw linAlgException("EXCEPTION: Matrix::getValue, out of range\n");
		}
		return m_data[index];
	}
	
	template<typename T>
	inline void Matrix<T>::setValue(const T value, const size_t rowIndex, const size_t columnIndex){
		size_t index = rowIndex + columnIndex * m_rows;
		if (index > m_data.size()) {
			throw linAlgException("EXCEPTION: Matrix::getValue, out of range\n");
		}
		m_data[index] = value;
	}

	template<typename T>
	inline void Matrix<T>::transpose(){
		Matrix<T> transposeMatrix(m_columns, m_rows);
		for (size_t indexR = 0; indexR < m_rows; ++indexR) {
			for (size_t indexC = 0; indexC < m_columns; ++indexC) {
				T value = this->getValue(indexR, indexC);
				transposeMatrix.setValue(value, indexC, indexR);
			}
		}
		*this = transposeMatrix;
	}

	template<typename T>
	inline const std::vector<T>& Matrix<T>::getData() const{
		return m_data;
	}

	template<typename T>
	void Matrix<T>::sumThis(const IArray<T>& arr){
		if (m_rows == arr.getRows() && m_columns == arr.getColumns()) {
			std::vector<T> temp = arr.getData();
			for (size_t index = 0; index < m_data.size(); ++index) {
				m_data[index] += temp[index];
			}
		}
		else {
			throw linAlgException("EXCEPTION: invalid array size, Matrix::sumThis\n");
		}
	}

	template<typename T>
	inline void Matrix<T>::multiplicationThisByNymber(T number) {
		for (size_t i = 0; i < this->m_data.size(); ++i) {
			m_data[i] *= number;
		}
	}

	template<typename T>
	inline void Matrix<T>::minusThis(const IArray<T>& arr){
		if (m_rows == arr.getRows() && m_columns == arr.getColumns()) {
			std::vector<T> temp = arr.getData();
			for (size_t index = 0; index < m_data.size(); ++index) {
				m_data[index] -= temp[index];
			}
		}
		else {
			throw linAlgException("EXCEPTION: invalid array size, Matrix::minusThis\n");
		}
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator-(IArray<T>& arr) const{
		Matrix<T> result(m_rows, m_columns);
		if (m_rows == arr.getRows() && m_columns == arr.getColumns()) {
			for (size_t indexR = 0; indexR < m_rows; ++indexR) {
				for (size_t indexC = 0; indexC < m_columns; ++indexC) {
					T value = this->getValue(indexR, indexC) - arr.getValue(indexR, indexC);
					result.setValue(value, indexR, indexC);
				}
			}
		}
		else {
			throw linAlgException("EXCEPTION: invalid array size, Matrix::operator-\n");
		}
		return result;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator+(IArray<T>& arr) const {
		Matrix<T> result(m_rows, m_columns);
		if (m_rows == arr.getRows() && m_columns == arr.getColumns()) {
			for (size_t indexR = 0; indexR < m_rows; ++indexR) {
				for (size_t indexC = 0; indexC < m_columns; ++indexC) {
					T value = this->getValue(indexR, indexC) + arr.getValue(indexR, indexC);
					result.setValue(value, indexR, indexC);
				}
			}
		}
		else {
			throw linAlgException("EXCEPTION: invalid array size, Matrix::operator-\n");
		}
		return result;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator*(IArray<T>& arr) const {
		//Умножение вектор-столбца (Матрицы из одного столбца) на вектор
		if (m_columns == arr.getRows() && m_rows == 1 && arr.getColumns() == 1) {
			Matrix<T> result(arr.getRows(), m_columns);
			MatrixMultiplyVectorRow(arr, result);
			return result;
		}
		//Умножаем матрицу на вектор столбец
		else if (m_rows == arr.getColumns() && arr.getRows() == 1) {
			Matrix<T> result(m_rows, m_columns);
			MatrixMultiplyVectorColumn(arr, result);
			return result;
		}
		//Умножаем матрицы базовым способом
		else if (m_rows == arr.getColumns()) {
			Matrix<T> result(arr.getRows(), m_columns);
			MatrixMultiplyMatrix(arr, result);
			return result;
			
		}
		else{
			throw linAlgException("EXCEPTION: invalid array size, Matrix::operator\n");
		}
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator*(T number) const{
		Matrix<T> result = *this;
		for (size_t i = 0; i < result.m_data.size(); ++i) {
			result.m_data[i] *= number;
		}
		return result;
	}

	template<typename T>
	void Matrix<T>::MatrixMultiplyVectorRow(IArray<T>& arr, Matrix<T>& matrix) const {
		for (size_t indexC = 0; indexC < matrix.getColumns(); ++indexC){
			for (size_t indexR = 0; indexR < matrix.getRows(); ++indexR) {
				T value = m_data[indexC] * arr.getValue(indexR, 0);
				matrix.setValue(value, indexR, indexC);
			}
		}
	}

	template<typename T>
	void Matrix<T>::MatrixMultiplyVectorColumn(IArray<T>& arr, Matrix<T>& matrix) const {
		for (size_t indexC = 0; indexC < matrix.getColumns(); ++indexC) {
			for (size_t indexR = 0; indexR < matrix.getRows(); ++indexR) {
				T value = m_data[indexR + indexC * m_rows] * arr.getValue(0, indexR);
				matrix.setValue(value, indexR, indexC);
			}
		}
	}

	template<typename T>
	inline void Matrix<T>::MatrixMultiplyMatrix(IArray<T>& arr, Matrix<T>& matrix) const{
		for (size_t indexR = 0; indexR < matrix.getRows(); ++indexR) {
			for (size_t indexC = 0; indexC < matrix.getColumns(); ++indexC) {
				T value = 0;
				for (int thisRow = 0; thisRow < this->getRows(); ++thisRow) {
					value += this->getValue(thisRow, indexC) * arr.getValue(indexR, thisRow);
				}
				matrix.setValue(value, indexR, indexC);
			}
		}
	}

}
