#ifndef DYNAMICARRAYH
#define DYNAMICARRAYH

/*
There are quite a few inconsistencies, such as using
raw for loops, not using begin and end, DRY violating deep copy, ...
Point is to practice C++ and DSA that's why ...
*/

template <typename T>
struct DynamicArray
{
  T *data {};
  int size{};
  int capacity{};

  DynamicArray(int initialCapacity = 1);
  ~DynamicArray();
  DynamicArray(const DynamicArray& other);

  /* Double the capacity and copy elements to new memory block.
  (1 + 2 + 4 + ... + N) / N ~ 2,
  meaning amortized time complexity is constant */
  void resizeAndCopy();

  void push_back(T value);
  void pop_back();
  void clear();
  void insert(int ind, T value);
  void insert(T* pos, T value);
  const T& get(int ind) const;

  T* begin() const;
  T* end() const;

  T& operator[](int ind);
  DynamicArray& operator=(const DynamicArray& other);
};

#endif