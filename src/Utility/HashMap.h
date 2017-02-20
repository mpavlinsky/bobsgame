#pragma once
#include "bobtypes.h"
class Logger;
#include <unordered_map>


#include "Logger.h"
#include "ArrayList.h"




template <typename K, typename V> class HashMap
{
public:
	static Logger log;

	HashMap<K,V>();
	~HashMap<K, V>();


	void put(K k,V v);
	void removeAt(K k);
	void removeAllValues(V v);
	bool containsKey(K k);
	bool containsValue(V v);
	void clear();
	bool isEmpty();
	int size();
	V get(K k);
	K getFirstKey(V v);
	ArrayList<V>* getAllValues();



    //typedef unordered_map<K,V> hm;
    //hm* m = new hm();

    //unordered_map<K,V> *m = new unordered_map<K,V>();
    unordered_map<K,V> *m;

    //hm<K,V>* m = new hm<K,V>();






};

template <typename K, typename V>
Logger HashMap<K,V>::log = Logger("HashMap");

template <typename K, typename V>
HashMap<K, V>::HashMap()
{
    m = new unordered_map<K,V>();
}

template <typename K, typename V>
HashMap<K, V>::~HashMap()
{
    delete m;
}

template <typename K, typename V>
void HashMap<K, V>::put(K k, V v)
{
    if(containsKey(k))removeAt(k);
	//m->insert(k,v);//insert_or_assign(k, v);//this overwrites if key exists, regular insert doesnt
	(*m)[k] = v;

	//returns the previous value associated with key, or null if there was no mapping for key.
	//(A null return can also indicate that the map previously associated null with key.)

}

template <typename K, typename V>
void HashMap<K, V>::removeAt(K k)
{
	//V v = m->at(k);
	m->erase(k);
	//return v;
}


template <typename K, typename V>
void HashMap<K, V>::removeAllValues(V v)
{
	//remove all instances of value, can have multiple keys
    //typename HashMap<K, V>::iterator it;
	for (auto it = m->begin(); it != m->end(); )
	{
		if (it->second == v) { m->erase(it++); }
		else { ++it; }
	}
}
template <typename K, typename V>
bool HashMap<K, V>::containsKey(K k)
{
	return m->find(k) != m->end();
}
template <typename K, typename V>
bool HashMap<K, V>::containsValue(V v)
{
	if (m->end() != find_if(m->begin(),m->end(),[&v](const typename unordered_map<K, V>::value_type& vt){return vt.second == v; }))return true;
	return false;
}
template <typename K, typename V>
void HashMap<K, V>::clear()
{
	m->clear();
}
template <typename K, typename V>
bool HashMap<K, V>::isEmpty()
{
	if (m->size() > 0)return false;
	return true;
}
template <typename K, typename V>
int HashMap<K, V>::size()
{
	return (int)m->size();
}
template <typename K, typename V>
V HashMap<K, V>::get(K k)
{
	V v;
	try
	{
		v = m->at(k);

	}
	catch(const exception&)
	{
		log.error(string("get() out of range exception"));
	}
	return v;
}

//template <typename K, typename V>
//K HashMap<K, V>::getFirstKey(V v)
//{
//    //typename HashMap<K, V>::iterator it;
//	for (auto it = m->begin(); it != m->end(); )
//	{
//		if (it->second == v) { return (K)it->first; }
//		else { ++it; }
//	}
//	return nullptr;
//}

template <typename K, typename V>
ArrayList<V>* HashMap<K, V>::getAllValues()
{
	//typename HashMap<K, V>::iterator it;
	ArrayList<V> *v = new ArrayList<V>();
	for (auto it = m->begin(); it != m->end(); ++it)v->add(it->second);
	return v;
}





//Removes all of the mappings from this map.
//	void 	clear();

//Returns a shallow copy of this HashMap instance: the keys and values themselves are not cloned.
//Object 	clone()

//Attempts to compute a mapping for the specified key and its current mapped value (or null if there is no current mapping).
//V 	compute(K key, BiFunction<? super K,? super V,? extends V> remappingFunction)

//If the specified key is not already associated with a value (or is mapped to null), attempts to compute its value using the given mapping function and enters it into this map unless null.
//V 	computeIfAbsent(K key, Function<? super K,? extends V> mappingFunction)

//If the value for the specified key is present and non-null, attempts to compute a new mapping given the key and its current mapped value.
//V 	computeIfPresent(K key, BiFunction<? super K,? super V,? extends V> remappingFunction)

//Returns true if this map contains a mapping for the specified key.
//	boolean 	containsKey(Object key);

//Returns true if this map maps one or more keys to the specified value.
//	boolean 	containsValue(Object value);

//Returns a Set view of the mappings contained in this map.
//Set<Map.Entry<K,V>> 	entrySet()

//Performs the given action for each entry in this map until all entries have been processed or the action throws an exception.
//void 	forEach(BiConsumer<? super K,? super V> action)

//Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
///	V 	get(Object key);

//Returns the value to which the specified key is mapped, or defaultValue if this map contains no mapping for the key.
//V 	getOrDefault(Object key, V defaultValue)

//Returns true if this map contains no key-value mappings.
//	boolean 	isEmpty();

//Returns a Set view of the keys contained in this map.
//Set<K> 	keySet()

//If the specified key is not already associated with a value or is associated with null, associates it with the given non-null value.
//V 	merge(K key, V value, BiFunction<? super V,? super V,? extends V> remappingFunction)

//Associates the specified value with the specified key in this map.
//	V 	put(K key, V value);

//Copies all of the mappings from the specified map to this map.
//void 	putAll(Map<? extends K,? extends V> m)

//If the specified key is not already associated with a value (or is mapped to null) associates it with the given value and returns null, else returns the current value.
//	V 	putIfAbsent(K key, V value);

//Removes the mapping for the specified key from this map if present.
//	V 	remove(Object key);

//Removes the entry for the specified key only if it is currently mapped to the specified value.
//	boolean 	remove(Object key, Object value);

//Replaces the entry for the specified key only if it is currently mapped to some value.
//	V 	replace(K key, V value);

//Replaces the entry for the specified key only if currently mapped to the specified value.
//	boolean 	replace(K key, V oldValue, V newValue)

//Replaces each entry's value with the result of invoking the given function on that entry until all entries have been processed or the function throws an exception.
//		void 	replaceAll(BiFunction< ? super K, ? super V, ? extends V> function)

//Returns the number of key-value mappings in this map.
//		int 	size();

//Returns a Collection view of the values contained in this map.
//Collection<V> 	values()
