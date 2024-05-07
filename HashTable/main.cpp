#include "HashTable.h"

#include <iostream>
#include <cstddef>    // size_t
#include <functional> // hash

#include <typeinfo>   // typeid
#include <cxxabi.h>
/*
  Collision resolution via separate chaining:
    linked list with HashEntry values (key + value pair).

*/

using std::size_t;

int main()
{
  size_t a = 1;
  int b = 5;
  int status;
  std::cout << abi::__cxa_demangle(typeid(a % b).name(), NULL, NULL, &status) << '\n';

  size_t initSize { 1 };
  HashTable<int> map ( initSize );

  map.insert("somekey", 141);
  map.insert("somekey1", 521);
  map.insert("somekey2", 321);
  map.insert("somekey", 41);

  
  std::cout << map.get("somekey") << '\n';
  std::cout << map.get("somekey1") << '\n';

  std::cout << std::boolalpha;
  std::cout << map.contains("somekey") << '\n';
  map.erase("somekey");
  std::cout << map.contains("somekey") << '\n';
  map.insert("somekey", 2414);
  std::cout << map.get("somekey") << '\n';


  std::cout << "let's some resizing" << '\n';
  std::cout << "1: " << map.get("somekey") << '\n';
  std::cout << "2: " << map.get("somekey1") << '\n';
  std::cout << "3: " << map.get("somekey2") << '\n';

  map.rehash();

  std::cout << "1 after: " << map.get("somekey") << '\n';
  std::cout << "2 after: " << map.get("somekey1") << '\n';
  std::cout << "3 after: " << map.get("somekey2") << '\n';



  return 0;
}