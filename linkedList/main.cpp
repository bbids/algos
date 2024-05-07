#include <iostream>
#include "SinglyLinkedList.h"

int main()
{
    SinglyLinkedList* llist = new SinglyLinkedList();
    
    llist->insertNodeAtTail(8);
    llist->insertNodeAtHead(12);
    llist->insertNodeAtHead(12);
    llist->insertNodeAtHead(12);
    llist->insertNodeAtTail(4);
    llist->insertNodeAtHead(12);
    llist->insertNodeAtHead(12);
    llist->insertNodeAtPosition(85, 0);


    llist->printLinkedList();

    std::cout << "-------------\n";

    llist->removeDuplicates();

    llist->printLinkedList();



    delete llist;
}