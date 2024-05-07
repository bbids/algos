#include "main.h"

#include <iostream>
#include <algorithm> // for std::copy

template <typename T>
DynamicArray<T>::DynamicArray(int initialCapacity)
: size(0)
, capacity(initialCapacity)
, data(new T[initialCapacity])
{}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
  delete[] data;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
  delete[] this->data;

  this->size = other.size;
  this->capacity = other.capacity;

  this->data = new T[this->capacity];
  
  if (other.data) {
    // std::memcpy(this->data, other.data, other.size * sizeof(T) );
    std::copy(other.begin(), other.end(), this->data);
  }

}

template <typename T>
void DynamicArray<T>::resizeAndCopy()
{
  int newCapacity{this->capacity << 1};
  T *newData = new T[newCapacity];
  T *q = newData;

  for (T *p = this->data; p < this->data + this->size; ++p)
  {
    *q = *p;
    ++q;
  }

  delete[] this->data;
  this->data = newData;
  this->capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::push_back(T value)
{
  if (this->size == this->capacity)
  {
    this->resizeAndCopy();
  }

  this->data[this->size] = value;

  ++this->size;
}

template <typename T>
void DynamicArray<T>::pop_back()
{
  if (!this->size)
    return;

  --this->size;
}

template <typename T>
void DynamicArray<T>::insert(int ind, T value)
{
  if (ind < 0 || ind > this->size)
    return;

  if (this->size == this->capacity)
  {
    this->resizeAndCopy();
  }

  T *newIndPos = this->data + ind;

  for (T *p = this->data + this->size; p != newIndPos; --p)
  {
    *p = *(p - 1);
  }

  *newIndPos = value;
  ++this->size;
}

template <typename T>
void DynamicArray<T>::insert(T *pos, T value)
{
  if (pos < this->data || pos > this->data + this->size)
    return;

  if (this->size == this->capacity)
  {
    this->resizeAndCopy();
  }

  for (T *p = this->data + this->size; p != pos; --p)
  {
    *p = *(p - 1);
  }

  *pos = value;
  ++this->size;
}

template <typename T>
const T& DynamicArray<T>::get(int ind) const
{
  if (ind < 0 || ind >= this->size)
    throw std::out_of_range("Index out of bounds");
  return *(this->data + ind);
}

template <typename T>
T* DynamicArray<T>::begin() const
{
  return this->data;
}

template <typename T>
T* DynamicArray<T>::end() const
{
  return this->data + this->size;
}

template <typename T>
void DynamicArray<T>::clear()
{
  delete[] this->data;
  this->capacity = 1;
  this->size = 0;
  this->data = new T[this->capacity];
}


template <typename T>
T& DynamicArray<T>::operator[](int ind)
{
  return *(this->data + ind);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
  if (this != &other)
  {
    delete[] this->data;

    this->capacity = other.capacity;
    this->size = other.size;
    this->data = new T(this->capacity);

    // std::memcpy(this->data, other.data, other.size * sizeof(T));
    std::copy(other.begin(), other.end(), this->data);

  }

  return *this;
}

template <typename T>
void printElements(DynamicArray<T> *arr);

int main()
{
  DynamicArray<int> arr {12};
  arr.push_back(12);
  arr.push_back(7);
  arr.push_back(8);
  printElements(&arr);

  DynamicArray<int> another { arr };
  printElements(&another);

  DynamicArray<int> wholeAnother = another;
  printElements(&wholeAnother);

  wholeAnother[0] = -1;

  printElements(&wholeAnother);
  printElements(&another);

  return 0;
}

template <typename T>
void printElements(DynamicArray<T> *arr)
{
  for (int *p = arr->data; p < arr->data + arr->size; ++p)
  {
    std::cout << *p << ' ';
  }
  std::cout << '\n';
}