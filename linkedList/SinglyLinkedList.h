#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <cstddef>

// Assume the programmer knows what he's doing

class SinglyLinkedListNode
{
    public:
        int data;
        SinglyLinkedListNode* next;
        SinglyLinkedListNode(int data, SinglyLinkedListNode* next = nullptr);
        SinglyLinkedListNode();
};

class SinglyLinkedList
{
    public:
        SinglyLinkedListNode* head;
        SinglyLinkedList();
        ~SinglyLinkedList();
        void deleteLinkedList();
        // ----
        void printLinkedList();
        void printReverse(); // TODO: iterative?
        void printReverse(SinglyLinkedListNode* current); // current onwards
        // ----
        void insertNodeAtTail(int data);
        void insertNodeAtHead(int data);
        void insertNodeAtPosition(int data, size_t position);
        void deleteNode(size_t position);
        // ----
        void reverse(); // TODO: iterative?
        void reverse(SinglyLinkedListNode* current); // from that node onwards
        bool compare(SinglyLinkedList* list2);
        bool compare(SinglyLinkedListNode* firstHead, SinglyLinkedListNode* secondHead); // from this node onwards
        void removeDuplicates(); // only works on sorted linked lists
        bool has_cycle();

};



#endif // SINGLYLINKEDLIST