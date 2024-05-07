#include "../HashEntry.h"

template <typename T>
HashEntry<T>::HashEntry(std::string initKey, const T &initValue)
: key(initKey)
, value(initValue)
{}