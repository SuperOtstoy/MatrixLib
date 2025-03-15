#pragma once
#include <type_traits>
#include <vector>
#include <string>

namespace linAlg {
	
	template<typename T>
	struct AllowedType : std::false_type {};

	template<>
	struct AllowedType<signed char> : std::true_type {};

	template<>
	struct AllowedType<short> : std::true_type {};

	template<>
	struct AllowedType<int> : std::true_type {};

	template<>
	struct AllowedType<long long> : std::true_type {};

	template<>
	struct AllowedType<float> : std::true_type {};

	template<>
	struct AllowedType<double> : std::true_type {};

	template<typename T>
	class IArray {
		static_assert(AllowedType<T>::value, "Invalid type, use int, float and double");

	public:

		virtual size_t getRows() const = 0;

		virtual size_t getColumns() const = 0;

		virtual T getValue(const size_t rowIndex, const size_t columnIndex) const = 0;

		virtual void setValue(const T value, const size_t rowIndex, const size_t columnIndex) = 0;

		virtual const std::vector<T>& getData() const = 0;	
	};


	class linAlgException : public std::exception {
	public:
		linAlgException(std::string message = "linAlgException exception") : m_message(message) {}

		char const* what() const override {
			return m_message.c_str();
		}

	private:
		std::string m_message;
	};

}
