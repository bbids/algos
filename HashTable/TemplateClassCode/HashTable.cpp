#include "../HashTable.h"

#include <iostream>
#include <cstddef>    // size_t
#include <functional> // hash
#include <utility>    // move
#include <optional>   // nullopt

using std::size_t;

template <typename T>
HashTable<T>::HashTable(size_t initialSize)
: size(initialSize)
, table(initialSize)
{}

template <typename T>
void HashTable<T>::rehash()
{
  this->size <<= 1;

  std::vector<std::list<HashEntry<T>>> newTable (this->size);
  for (size_t i = 0; i < this->table.size(); ++i)
  {
    // iterate through list    
    for (auto &entry : this->table[i])
    {
      // size changed so need new hashes
      size_t hashVal = std::hash<std::string>{}(entry.key);
      size_t newInd = hashVal % this->size;

      HashEntry<T> newEntry { entry.key, entry.value };
      // std::list is a double-linked list, so order doesn't matter
      newTable[newInd].push_front(newEntry);
    }
  }

  this->table.clear();
  this->table = newTable;
}

template <typename T>
void HashTable<T>::clear()
{
  this->size = 16;
  this->takenBuckets = 0;

  for (auto &llist : this->table)
  {
    llist.clear();
  }

  this->table.clear();
  this->table = std::vector<std::list<HashEntry<T>>> (this->size);
  
}

template <typename T>
double HashTable<T>::loadFactor() const
{
  return this->takenBuckets / this->size;
}

template <typename T>
bool HashTable<T>::contains(std::string key) const
{
  size_t hashVal = std::hash<std::string>{}(key);
  size_t ind = hashVal % this->size;

  for (auto &entry : this->table[ind])
  {
    if (entry.key == key)  return true;
  }

  return false;
}

template <typename T>
void HashTable<T>::erase(std::string key)
{
  size_t hashVal = std::hash<std::string>{}(key);
  size_t ind = hashVal % this->size;

  std::erase_if(this->table[ind], [key](HashEntry<T> x) {
    return x.key == key;
  });

  if (!this->table[ind].size())
    this->takenBuckets -= 1;
  
}

template <typename T>
void HashTable<T>::insert(std::string key, T value)
{
  if (this->loadFactor() > 0.75)
    this->rehash();


  size_t hashVal = std::hash<std::string>{}(key);
  size_t ind  = hashVal % this->size;

  HashEntry<T> en { key, value };

  if (this->table[ind].size())
  {
    // check if key already in the list, if so replace value
    for (auto &&entry : this->table[ind])
    {
      if (entry.key == key)
      {
        entry.value = value;
        return;
      }
    }
    // key not found, just add to list
    this->table[ind].push_front(en);
  }
  else
  {
    this->table[ind].push_front(en);
  }

  this->takenBuckets += 1;
}

template <typename T>
const T& HashTable<T>::get(std::string key) const
{
  size_t hashVal = std::hash<std::string>{}(key);
  size_t ind = hashVal % this->size;
  
  for (auto &entry : this->table[ind])
  {
    if (entry.key == key)
      return entry.value;
  }

  throw std::runtime_error("Key not found!");
}