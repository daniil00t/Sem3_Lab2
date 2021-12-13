#pragma once
#include <memory>
#include <cstddef>

#include "HashMap.hpp"
#include "HashMapIterator.hpp"
#include "IMatrix.hpp"
using namespace dictionary;

struct Point {
	std::size_t x;
	std::size_t y;

	bool operator==(const Point& other) const {
		return this->x == other.x && this->y == other.y;
	}
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
	// Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
	out << "Point(" << point.x << ", " << point.y << ")";

	return out;
}



template <class T>
class SparseMatrix : IMatrix<T> {
private:
	HashMap<Point, T>* data;

	std::size_t width, height;

	const T zero;
public:

	SparseMatrix(Matrix<T>, T zero = T()); //convert Matrix to SparseMatrix
	SparseMatrix(T zero);
	SparseMatrix(std::size_t width, std::size_t height, T zero);
	virtual ~SparseMatrix();

	virtual T& get(std::size_t x, std::size_t y) override;
	virtual const T& get(std::size_t x, std::size_t y) const override;

	virtual void set(const T&, std::size_t x, std::size_t y) override;

	virtual std::size_t getWidth() const override;
	virtual std::size_t getHeight() const override;

	bool isZero(std::size_t x, std::size_t y) const;

	//HashMap<Point, T>& getData();
	std::unique_ptr<HashMap<Point, T>> getData();
	void print();
	void map(std::function<T(T)>);
};

template <typename T>
SparseMatrix<T>::SparseMatrix(Matrix<T> matrix, T zero) : zero(zero) {
	this->data = new HashMap<Point, T>(
		[](Point p, int tableSize)->int
		{
			return (p.x + p.y) % tableSize;
		});

	this->width = matrix.getWidth();
	this->height = matrix.getHeight();

	for (std::size_t i = 0; i < this->width; ++i) for (std::size_t j = 0; j < this->height; ++j) {
		T& item = matrix.get(i, j);
		if (item != zero)
			this->data->Add({ i, j }, item);
	}
}

template <typename T>
SparseMatrix<T>::SparseMatrix(T zero)
	: zero(zero) {}

template <typename T>
SparseMatrix<T>::SparseMatrix(std::size_t width, std::size_t height, T zero)
	: zero(zero), width(width), height(height) {
	this->data = new HashMap<Point, T>(
		[](Point p, int tableSize)->int
		{
			return (p.x + p.y) % tableSize;
		});
}

template <typename T>
SparseMatrix<T>::~SparseMatrix() {
	delete this->data;
}


template <typename T>
void SparseMatrix<T>::set(const T& item, std::size_t x, std::size_t y) {
	if (item != this->zero)
		this->data->Add(Point{ .x = x, .y = y }, item);
}

template <typename T>
T& SparseMatrix<T>::get(std::size_t x, std::size_t y) {
	return const_cast<T&>(const_cast<const SparseMatrix<T>*>(this)->get(x, y));
}

template <typename T>
const T& SparseMatrix<T>::get(std::size_t x, std::size_t y) const {
	return this->data->Get(Point{ .x = x, .y = y }); //throws error if element is zero
}

template <typename T>
std::size_t SparseMatrix<T>::getWidth() const {
	return this->width;
}

template <typename T>
std::size_t SparseMatrix<T>::getHeight() const {
	return this->height;
}

template <typename T>
bool SparseMatrix<T>::isZero(std::size_t x, std::size_t y) const {
	return !this->data->Contains({ x,y });
}

//template <typename T>
//HashMap<Point, T>& SparseMatrix<T>::getData() {
//	return *this->data;
//}
template <typename T>
std::unique_ptr<HashMap<Point, T>> SparseMatrix<T>::getData() {
	return std::make_unique<HashMap<Point, T>>(*this->data);
}

template <typename T>
void SparseMatrix<T>::print() {

	std::cout << "{ ";

	HashMapIterator<Point, T> iter = this->data->Iterator();

	for (; iter != this->data->End(); ++iter)
	{
		std::cout << *iter << " ";
	}

	std::cout << "}";
}

template <typename T>
void SparseMatrix<T>::map(std::function<T(T)> func) {
	HashMapIterator<Point, T> iter = this->data->Iterator();
	for (; iter != this->data->End(); ++iter)
	{
		this->data->Add((*iter).first, func((*iter).second));
	}
}
