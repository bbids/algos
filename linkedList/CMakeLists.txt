add_library(LinkedList STATIC SinglyLinkedList.cpp)

# Set include directories
target_include_directories(LinkedList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
