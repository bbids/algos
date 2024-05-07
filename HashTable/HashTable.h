#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashEntry.h"

#include <cstddef>  // size_t
#include <list>
#include <vector>
#include <string>

using std::size_t;

template <typename T>
struct HashTable
{
  size_t size {};
  std::vector<std::list<HashEntry<T>>> table;
  int takenBuckets {};
  
  HashTable(size_t initialSize = 16);

  void rehash();
  double loadFactor() const;
  void clear();

  bool contains(std::string key) const;
  void insert(std::string key, T value);
  void erase(std::string key);
  const T& get(std::string key) const;

};

#include "./TemplateClassCode/HashTable.cpp"



#endif