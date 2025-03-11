#pragma once
#include <vector>
#include "IArray.h"


namespace linAlg {

	template<typename T>
	class Vector : public IArray<T> 
	{
	public:
		Vector();
		Vector(const size_t countRow);
		Vector(const std::vector<T>& data);

		//получить количесвто строк
		size_t getRows() const override;
		T getValue(const size_t rowIndex);
		void setValue(const T value, const size_t rowIndex);

		void sumThis(const IArray<T>& arr); //Прибавляем к текущему вектору 

		void minusThis(const IArray<T>& arr);
		void multiplicationThisByNymber(T number);

		Vector<T> operator+ (IArray<T>& arr) const; //Cложить два объекта можно на вход предоставить матриц такого же размера как вектор
		Vector<T> operator- (IArray<T>& arr) const;
		Vector<T> operator* (T number) const;

	private:

		//Установить значение по индексу
		void setValue(const T value, const size_t rowIndex, const size_t columnIndex) override;

		//Получить данные из массива
		const std::vector<T>& getData() const override;

		//Получит значение по индексу
		T getValue(const size_t rowIndex, const size_t columnIndex) const override;

		//получить количество столбцов
		size_t getColumns() const override;

		//Основной контейнер данных
		std::vector<T> m_data; 
		size_t m_rows; //размер строки
		size_t m_columns; //размер столбца (по умолчанию = 1)
	};

	template<typename T>
	inline Vector<T>::Vector(){
		m_data.clear();
		m_rows = 0;
		m_columns = 0;
	}

	template<typename T>
	inline Vector<T>::Vector(const size_t countRow){
		m_rows = countRow;
		m_columns = 1;
		m_data.resize(m_rows);
	}

	template<typename T>
	inline Vector<T>::Vector(const std::vector<T>& data){
		m_rows = data.size();
		m_columns = 1;
		m_data = data;
	}

	template<typename T>
	inline size_t Vector<T>::getRows() const{
		return  m_rows;
	}

	template<typename T>
	inline T Vector<T>::getValue(const size_t rowIndex){
		try{
			return getValue(rowIndex, 1);
		}
		catch (std::exception& ex) {
			throw ex;
		}
	}

	template<typename T>
	inline void Vector<T>::setValue(const T value, const size_t rowIndex){
		try {
			setValue(value, rowIndex, 1);
		}
		catch (std::exception& ex) {
			throw ex;
		}
	}

	template<typename T>
	void Vector<T>::sumThis(const IArray<T>& arr){
		if (arr.getRows() == m_rows && arr.getColumns() == m_columns) {
			for (size_t index = 0; index < m_rows; ++index) {
				m_data[index] += arr.getValue(index, 1);
			}
		}
		else {
			throw std::exception("EXCEPTION: invalid array size, Vector::sumThis\n");
		}
	}

	template<typename T>
	inline void Vector<T>::minusThis(const IArray<T>& arr){
		if (arr.getRows() == m_rows && arr.getColumns() == m_columns) {
			for (size_t index = 0; index < m_rows; ++index) {
				m_data[index] -= arr.getValue(index, 1);
			}
		}
		else {
			throw std::exception("EXCEPTION: invalid array size, Vector::minusThis\n");
		}
	}

	template<typename T>
	inline void Vector<T>::multiplicationThisByNymber(T number){
		for (size_t i = 0; i < m_data.size(); ++i) {
			m_data[i] *= number;
		}
	}

	template<typename T>
	Vector<T> Vector<T>::operator+(IArray<T>& arr) const{
		Vector<T> result(m_rows);
		if (arr.getRows() == m_rows && arr.getColumns() == m_columns){
			for (size_t index = 0; index < m_rows; ++index){
				T value = arr.getValue(index, 1) + m_data[index];
				result.setValue(value, index);
			}
		}
		else {
			throw std::exception("EXCEPTION: invalid array size, Vector::operator+\n");
		}

		return result;
	}

	template<typename T>
	inline Vector<T> Vector<T>::operator-(IArray<T>& arr) const{
		Vector<T> result(m_rows);
		if (arr.getRows() == m_rows && arr.getColumns() == m_columns) {
			for (size_t index = 0; index < m_rows; ++index) {
				T value = arr.getValue(index, 1) - m_data[index];
				result.setValue(value, index);
			}
		}
		else {
			throw std::exception("EXCEPTION: invalid array size, Vector::operator-\n");
		}

		return result;
	}

	template<typename T>
	inline Vector<T> Vector<T>::operator*(T number) const{
		Vector<T> result = *this;
		for (size_t i = 0; i < result.m_data.size(); ++i) {
			result.m_data[i] *= number;
		}
		return result;
	}

	template<typename T>
	inline size_t Vector<T>::getColumns() const{
		return m_columns;
	}

	template<typename T>
	inline const std::vector<T>& Vector<T>::getData() const {
		return m_data;
	}

	template<typename T>
	inline T Vector<T>::getValue(const size_t rowIndex, const size_t columnIndex) const{
		if (rowIndex > m_data.size()) {
			throw std::exception("EXCEPTION: Vector::getValue, out of range\n");
		}
		return m_data[rowIndex];
	}

	template<typename T>
	inline void Vector<T>::setValue(const T value, const size_t rowIndex, const size_t columnIndex){
		if (rowIndex > m_data.size()) {
			throw std::exception("EXCEPTION: Vector::getValue, out of range\n");
		}
		m_data[rowIndex] = value;
	}

}