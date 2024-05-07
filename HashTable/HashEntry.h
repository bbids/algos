#ifndef HASHENTRY_H
#define HASHENTRY_H

#include <string>

template <typename T>
struct HashEntry
{
  std::string key {};
  T value {};

  HashEntry(std::string initKey, const T& initVal);
};

#include "./TemplateClassCode/HashEntry.cpp"

#endif