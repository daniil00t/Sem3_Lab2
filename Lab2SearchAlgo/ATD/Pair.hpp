template <typename K, typename V>
struct Pair {
	K key;
	V value;

	bool operator==(const Pair& other) {
		return this->key == other.key && this->value == other.value;
	}

	bool operator!=(const Pair& other) {
		return !operator==(other);
	}
};