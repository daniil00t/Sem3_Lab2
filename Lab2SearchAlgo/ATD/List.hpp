#pragma once

#include <stdexcept>
#include <string>
#include <cstddef>
#include <memory>


template <typename T>
class List {
private:
	struct Record {
		T* item = nullptr;
		Record* next = nullptr;

		Record(const T& item, Record* next = nullptr)
			: next(next), item(new T(item)) {}

		Record(Record* next = nullptr)
			: next(next) {}

		~Record() {
			if (item) {
				delete item;
				item = nullptr;
			}
		}
	};
	Record head;
	std::size_t size = 0;
public:
	static const std::string INDEX_OUT_OF_RANGE;
	static const std::string ZERO_SIZE;

	class ConstIterator;
	class Iterator;

	List();
	List(const T* items, std::size_t size);
	List(std::size_t size);
	List(const List<T>& list);
	virtual ~List();

	List<T>& operator=(const List<T>& other);

	T& getFirst();
	const T& getFirst() const;
	T& getLast();
	const T& getLast() const;
	T& get(std::size_t index);
	const T& get(std::size_t index) const;

	void set(const T& item, std::size_t index);
	std::unique_ptr<List<T>> getSublist(std::size_t start, std::size_t end) const;
	std::size_t getSize() const;
	void append(const T& item);
	void prepend(const T& item);
	void removeAt(std::size_t index);
	void insertAt(const T& item, std::size_t index);
	std::unique_ptr<List<T>> concat(const List<T>& list) const;

	bool operator==(const List<T>& other) const;

	List<T>::Iterator begin();
	List<T>::ConstIterator begin() const;
};
template <typename T>
const std::string List<T>::INDEX_OUT_OF_RANGE = "index out of range";
template <typename T>
const std::string List<T>::ZERO_SIZE = "size is 0";


template <typename T>
class List<T>::ConstIterator {
private:
	const Record* currentRec = nullptr;
	const Record* prevRec = nullptr;

	const List<T>* list;
public:
	static const std::string NO_NEXT_ELEM;
	static const std::string NO_CURRENT_ELEM;

	ConstIterator(const Record* currentRec, const List<T>* list);
	ConstIterator(const ConstIterator& it);
	virtual ~ConstIterator() = default;

	const T& next();
	virtual void go();
	const T& current();
	virtual bool hasNext();
};
template <typename T>
const std::string List<T>::ConstIterator::NO_NEXT_ELEM = "there is no next element";
template <typename T>
const std::string List<T>::ConstIterator::NO_CURRENT_ELEM = "there is no current element";

template <typename T>
class List<T>::Iterator {
private:
	Record* currentRec = nullptr;
	Record* prevRec = nullptr;

	List<T>* list;
public:
	static const std::string NO_NEXT_ELEM;
	static const std::string NO_CURRENT_ELEM;

	Iterator(Record* currentRec, List<T>* list);
	Iterator(const Iterator& it);
	virtual ~Iterator() = default;

	void go();
	T& next();
	T& current();
	void remove();
	void insert(const T& item);
	bool hasNext();
};
template <typename T>
const std::string List<T>::Iterator::NO_NEXT_ELEM = "there is no next element";
template <typename T>
const std::string List<T>::Iterator::NO_CURRENT_ELEM = "there is no current element";


template <typename T>
List<T>::List()
	: size(0) {}

template <typename T>
List<T>::List(const T* items, std::size_t size) : List() {
	Record* ptr = &(this->head);
	for (std::size_t i = 0; i < size; ++i) {
		ptr->next = new Record(items[i]);

		ptr = ptr->next;
	}

	this->size = size;
}

template <typename T>
List<T>::List(std::size_t size) : List() {
	Record* ptr = &(this->head);
	for (std::size_t i = 0; i < size; i++) {
		ptr->next = new Record(T());
		ptr = ptr->next;
	}

	this->size = size;
}

template <typename T>
List<T>::List(const List<T>& list) {
	const Record* other = &(list.head);
	Record* ptr = &(this->head);

	while (other->next != nullptr) {
		ptr->next = new Record(*(other->next->item));

		other = other->next;
		ptr = ptr->next;
	}

	this->size = list.size;
}

template <typename T>
List<T>::~List() {
	Record* ptr = this->head.next;
	Record* next;
	while (ptr != nullptr) {
		next = ptr->next;
		delete ptr;
		ptr = next;
	}

	this->size = 0;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (this == &other) return *this;

	List<T> temp(other);

	std::swap(this->head, temp.head);
	std::swap(this->size, temp.size);

	return *this;
}

template <typename T>
T& List<T>::getFirst() {
	return const_cast<T&>(const_cast<const List<T>*>(this)->getFirst());
}

template <typename T>
const T& List<T>::getFirst() const {
	if (this->size == 0) throw std::length_error(ZERO_SIZE);

	return *(this->head.next->item);
}

template <typename T>
T& List<T>::getLast() {
	return const_cast<T&>(const_cast<const List<T>*>(this)->getLast());
}

template <typename T>
const T& List<T>::getLast() const {
	if (this->size == 0) throw std::length_error(ZERO_SIZE);

	Record* ptr = &(this->head);
	while (ptr->next != nullptr) ptr = ptr->next;
	return *(ptr->item);
}

template <typename T>
T& List<T>::get(std::size_t index) {
	return const_cast<T&>(const_cast<const List<T>*>(this)->get(index));
}

template <typename T>
const T& List<T>::get(std::size_t index) const {
	if (index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);


	const Record* ptr = &(this->head);
	for (std::size_t i = 0; i < index + 1; i++) {
		ptr = ptr->next;
	}

	return *(ptr->item);
}


template <typename T>
void List<T>::set(const T& item, std::size_t index) {
	if (index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);


	Record* ptr = &(this->head);
	for (std::size_t i = 0; i < index + 1; i++) {
		ptr = ptr->next;
	}

	ptr->item = item;
}

template <typename T>
std::unique_ptr<List<T>> List<T>::getSublist(std::size_t start, std::size_t end) const { //end excluding
	if (!(0 <= start && start <= end && end <= this->size)) {
		if (start >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);
		if (end > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);
		if (start > end) throw std::logic_error("end must be not less than start");
	}

	List<T>* newList = new List<T>();


	Record* ptr = &(this->head);
	Record* newPtr = &(newList->head);

	for (std::size_t i = 0; i < start; i++) ptr = ptr->next;

	for (std::size_t i = 0; i < end - start; i++) {
		newPtr->next = new Record(ptr->next->item);

		ptr = ptr->next;
		newPtr = newPtr->next;
	}

	newList->size = end - start;

	return std::unique_ptr<List<T>>(newList);
}

template <typename T>
std::size_t List<T>::getSize() const { return this->size; }

template <typename T>
void List<T>::append(const T& item) {
	Record* ptr = &(this->head);
	while (ptr->next != nullptr) ptr = ptr->next;

	ptr->next = new Record(item);



	this->size++;
}

template <typename T>
void List<T>::prepend(const T& item) {
	Record* newRec = new Record(item, this->head.next);
	this->head.next = newRec;

	this->size++;
}

template <typename T>
void List<T>::removeAt(std::size_t index) {
	if (index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);

	Record* ptr = &(this->head);
	for (std::size_t i = 0; i < index; i++) ptr = ptr->next;

	Record* rem = ptr->next;
	ptr->next = rem->next;

	delete rem;

	this->size--;
}

template <typename T>
void List<T>::insertAt(const T& item, std::size_t index) {
	if (index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);


	Record* ptr = &(this->head);
	for (std::size_t i = 0; i < index; i++) ptr = ptr->next;

	Record* newRec = new Record(item = item, ptr->next);


	ptr->next = newRec;

	this->size++;
}

template <typename T>
std::unique_ptr<List<T>> List<T>::concat(const List<T>& list) const {
	Record* ptr1 = &(this->head);
	const Record* ptr2 = &(list.head);

	List<T>* newList = new List<T>();
	Record* ptr = &(newList->head);
	while (ptr1->next != nullptr) {
		ptr->next = new Record(ptr1->next->item);

		ptr1 = ptr1->next;
		ptr = ptr->next;
	}
	while (ptr2->next != nullptr) {
		ptr->next = new Record(ptr2->next->item);

		ptr2 = ptr2->next;
		ptr = ptr->next;
	}

	newList->size = this->size + list.size;
	return std::unique_ptr<List<T>>(newList);
}

template <typename T>
bool List<T>::operator==(const List<T>& other) const {
	if (this->getSize() != other.getSize()) return false;

	for (int i = 0; i < this->getSize(); i++) {
		if (this->get(i) != other.get(i)) return false;
	}
	return true;
}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
	return List<T>::Iterator(&(this->head), this);
}

template <typename T>
typename List<T>::ConstIterator List<T>::begin() const {
	return List<T>::ConstIterator(&(this->head), this);
}
template <typename T>
List<T>::ConstIterator::ConstIterator(const Record* currentRec, const List<T>* list)
	: currentRec(currentRec), prevRec(currentRec), list(list) {}

template <typename T>
List<T>::ConstIterator::ConstIterator(const List<T>::ConstIterator& it)
	: currentRec(it.currentRec), prevRec(it.prevRec), list(it.list) {}


template <typename T>
const T& List<T>::ConstIterator::next() {
	this->go();

	return this->current();
}

template <typename T>
void List<T>::ConstIterator::go() {
	if (this->currentRec->next == nullptr)
		throw std::runtime_error(this->NO_NEXT_ELEM);

	if (this->prevRec != this->currentRec)
		this->prevRec = this->currentRec;
	this->currentRec = this->currentRec->next;
}

template <typename T>
const T& List<T>::ConstIterator::current() {
	if (this->prevRec == this->currentRec) throw std::runtime_error(this->NO_CURRENT_ELEM);

	return *(this->currentRec->item);
}

template <typename T>
bool List<T>::ConstIterator::hasNext() {
	return this->currentRec->next != nullptr;
}




template <typename T>
List<T>::Iterator::Iterator(Record* currentRec, List<T>* list)
	: currentRec(currentRec), prevRec(currentRec), list(list) {}

template <typename T>
List<T>::Iterator::Iterator(const List<T>::Iterator& it)
	: currentRec(it.currentRec), prevRec(it.prevRec), list(it.list) {}


template <typename T>
T& List<T>::Iterator::next() {
	this->go();

	return this->current();
}

template <typename T>
T& List<T>::Iterator::current() {
	if (this->prevRec == this->currentRec) throw std::runtime_error(this->NO_CURRENT_ELEM);

	return *(this->currentRec->item);
}

template <typename T>
void List<T>::Iterator::remove() {
	if (this->prevRec == this->currentRec) throw std::runtime_error(this->NO_CURRENT_ELEM);

	Record* rem = this->currentRec;
	this->prevRec->next = this->currentRec->next;
	this->currentRec = this->prevRec;
	delete rem;

	this->list->size--;
}

template <typename T>
void List<T>::Iterator::insert(const T& item) {
	Record* newRec = new Record(item, currentRec->next);
	this->currentRec->next = newRec;

	this->list->size++;

	this->next();
}

template <typename T>
void List<T>::Iterator::go() {
	if (this->currentRec->next == nullptr)
		throw std::runtime_error(this->NO_NEXT_ELEM);

	if (this->prevRec != this->currentRec)
		this->prevRec = this->currentRec;
	this->currentRec = this->currentRec->next;
}

template <typename T>
bool List<T>::Iterator::hasNext() {
	return this->currentRec->next != nullptr;
}
