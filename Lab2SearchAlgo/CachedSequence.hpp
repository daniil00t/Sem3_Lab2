#pragma once

#include <utility>
#include <stdexcept>

#include "ATD/Sequence.h"
#include "ATD/ArraySequence.h"
#include "ATD/LinkedList.h"

#include "IDictionary.hpp"
#include "HashMap.hpp"
#include "ATD/DoubleLinkedList.h"

using namespace sequences;
using namespace dictionary;

template<class K, class V>
class CachedSequence
{
public:
	typedef std::pair<K, V> KeyValuePair;
	typedef DoubleNode<KeyValuePair> CachePointer;
private:
	Sequence<KeyValuePair>* data;
	IDictionary<K, CachePointer*>* cacheTable;
	DoubleLinkedList<KeyValuePair>* cacheList = new DoubleLinkedList<KeyValuePair>();

	int cacheSize;
public:
	CachedSequence(std::function<int(K, int)> hashFunc, int cacheSize) :
		data(new ArraySequence<KeyValuePair>()),
		cacheTable(new HashMap<K, CachePointer*>(hashFunc, cacheSize)),
		cacheSize(cacheSize)
	{}

	void Add(K key, V value)
	{
		KeyValuePair pair = std::make_pair(key, value);
		data->Append(pair);
		PutInCache(pair);
	}
	V Get(K key)
	{
		V res;
		try
		{
			res = GetFromCache(key).second;
			RefreshCache(key);
		}
		catch (key_not_found e)
		{
			KeyValuePair fromArray = FindInArray(key);
			res = fromArray.second;
			PutInCache(fromArray);
		}
		return res;
	}
private:
	KeyValuePair GetFromCache(K key)
	{
		return cacheTable->Get(key)->GetContent();
	}
	KeyValuePair FindInArray(K key)
	{
		KeyValuePair tmp;

		for (int i = 0; i < data->GetLength(); i++)
		{
			tmp = data->Get(i);
			if (tmp.first == key)
				return tmp;
		}

		throw key_not_found("");
	}
	void PutInCache(KeyValuePair pair)
	{
		if (cacheList->GetLength() >= cacheSize)
		{
			//Remove last item from cache
			CachePointer* last = cacheList->Tail();

			cacheTable->Remove(last->GetContent().first);
			cacheList->Remove(last);
		}


		//Add to the start
		cacheList->Prepend(pair);
		cacheTable->Add(pair.first, cacheList->Head());
	}
	void RefreshCache(K key)
	{
		CachePointer* toStart = cacheTable->Get(key);

		cacheList->MoveToStart(toStart);
	}

};