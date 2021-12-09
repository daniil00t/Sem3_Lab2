#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>

#include "Pair.hpp"
#include "Array.hpp"
#include "List.hpp"

class KeyNotFoundError : std::runtime_error {
public:
	KeyNotFoundError() : std::runtime_error("key not found") {}
};

template <typename K, typename V>
class IDictionary {
public:
	class Iterator {
	public:
		virtual ~Iterator() = default;

		virtual K next() = 0;
		virtual void go() = 0;
		virtual K current() = 0;
		virtual bool hasNext() = 0;
	};

	virtual ~IDictionary() = default;

	virtual V& get(const K&) = 0;
	virtual const V& get(const K&) const = 0;

	virtual void set(const K&, const V&) = 0;
	virtual bool contains(const K&) const = 0;
	virtual void remove(const K&) = 0;

	virtual std::unique_ptr<Iterator> iterator() = 0;
};

template <typename K, typename V>
class HashTableBase : public IDictionary<K, V> {
protected:
	std::size_t size = 3;
	DynamicArray<List<Pair<K, V>>> data;

	virtual unsigned hash(K) const = 0;
public:

	class Iterator;

	HashTableBase();
	virtual ~HashTableBase() = default;

	virtual V& get(const K&) override;
	virtual const V& get(const K&) const override;

	virtual void set(const K&, const V&) override;
	virtual bool contains(const K&) const override;
	virtual void remove(const K&) override;

	virtual std::unique_ptr<typename IDictionary<K, V>::Iterator> iterator();
};

template <typename K, typename V>
class HashTableBase<K, V>::Iterator : public IDictionary<K, V>::Iterator {
protected:
	bool initFlag = true;
	std::size_t i = 0; //number of current bucket
	std::unique_ptr< typename List<Pair<K, V>>::Iterator > it; //iterator inside current list

	HashTableBase<K, V>* table = nullptr;

	virtual bool findNext();
public:
	static const std::string NO_NEXT_ELEM;
	static const std::string NO_CURRENT_ELEM;

	Iterator(HashTableBase<K, V>* table);
	virtual ~Iterator();

	K next();
	void go();
	K current();
	bool hasNext();
};
template <typename K, typename V>
const std::string HashTableBase<K, V>::Iterator::NO_NEXT_ELEM = "there is no next element";
template <typename K, typename V>
const std::string HashTableBase<K, V>::Iterator::NO_CURRENT_ELEM = "there is no current element";


template <typename K, typename V>
class HashTable : public HashTableBase<K, V> {};


template <typename K, typename V>
HashTableBase<K, V>::HashTableBase() :
	data(DynamicArray<List<Pair<K, V>>>(size)) {}

template <typename K, typename V>
V& HashTableBase<K, V>::get(const K& key) {
	return const_cast<V&>(const_cast<const HashTableBase<K, V>*>(this)->get(key));
}

template <typename K, typename V>
const V& HashTableBase<K, V>::get(const K& key) const {
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while (it.hasNext()) {
		auto& pair = it.next();
		if (pair.key == key)
			return pair.value;
	}

	throw KeyNotFoundError();
}

template <typename K, typename V>
void HashTableBase<K, V>::set(const K& key, const V& value) {
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();
	while (it.hasNext()) {
		auto& pair = it.next();
		if (pair.key == key) {
			pair.value = value;
			return;
		}
	}

	this->data.get(num).prepend(Pair<K, V>{.key = key, .value = value});
}

template <typename K, typename V>
bool HashTableBase<K, V>::contains(const K& key) const {
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while (it.hasNext()) {
		auto& pair = it.next();
		if (pair.key == key)
			return true;
	}

	return false;
}

template <typename K, typename V>
void HashTableBase<K, V>::remove(const K& key) {
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while (it.hasNext()) {
		auto& pair = it.next();
		if (pair.key == key) {
			it.remove();
			return;
		}
	}

	throw KeyNotFoundError();
}


template <typename K, typename V>
std::unique_ptr< typename IDictionary<K, V>::Iterator > HashTableBase<K, V>::iterator() {
	return std::make_unique< HashTableBase<K, V>::Iterator >(this);
}



template <typename K, typename V>
HashTableBase<K, V>::Iterator::Iterator(HashTableBase<K, V>* table) : table(table) {}

template <typename K, typename V>
HashTableBase<K, V>::Iterator::~Iterator() {}


template <typename K, typename V>
K HashTableBase<K, V>::Iterator::next() {
	this->go();

	return this->current();
}

template <typename K, typename V>
bool HashTableBase<K, V>::Iterator::findNext() {
	if (this->initFlag) {
		if (this->table->size == 0) return false;
		this->it = std::make_unique< typename List<Pair<K, V>>::Iterator >(this->table->data.get(0).begin());

		this->initFlag = false;
	}

	while (!this->it->hasNext()) {
		if (this->i + 1 >= this->table->size) return false;
		this->i++;

		this->it = std::make_unique< typename List<Pair<K, V>>::Iterator>(this->table->data.get(this->i).begin());
	}

	return true;
}

template <typename K, typename V>
K HashTableBase<K, V>::Iterator::current() {
	if (this->initFlag) throw std::runtime_error(this->NO_CURRENT_ELEM);

	return this->it->current().key;
}


template <typename K, typename V>
void HashTableBase<K, V>::Iterator::go() {
	if (!this->findNext())
		throw std::runtime_error(this->NO_NEXT_ELEM);

	this->it->go();
}

template <typename K, typename V>
bool HashTableBase<K, V>::Iterator::hasNext() {
	return this->findNext();
}

template <typename V>
class HashTable<int, V> : public HashTableBase<int, V> {
private:
	virtual unsigned hash(int key) const {
		return key % this->size;
	}
};

template <typename V>
class HashTable<std::string, V> : public HashTableBase<std::string, V> {
private:
	virtual unsigned hash(std::string key) const {
		return key.size() % this->size;
	}
};