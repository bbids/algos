#include "SinglyLinkedList.h"

#include <unordered_set>
#include <iostream>

SinglyLinkedListNode::SinglyLinkedListNode(int val, SinglyLinkedListNode* ptr) 
: data(val), next(ptr)
{}

SinglyLinkedListNode::SinglyLinkedListNode()
: data(0), next(nullptr)
{}

SinglyLinkedList::SinglyLinkedList() : head(nullptr) {}

SinglyLinkedList::~SinglyLinkedList() {
    deleteLinkedList();
}

void SinglyLinkedList::deleteLinkedList() {
    while (head != nullptr) {
        SinglyLinkedListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void SinglyLinkedList::printLinkedList()
{
    SinglyLinkedListNode* current = head;
    if (head != nullptr) {
        while (current != nullptr)
        {
            std::cout << current->data << '\n';
            current = current->next;
        }
    }
}

void SinglyLinkedList::printReverse()
{
    printReverse(head);
}

void SinglyLinkedList::printReverse(SinglyLinkedListNode* current)
{
    if (current->next == nullptr) {
        std::cout << current->data << '\n';
    } else {
        printReverse(current->next);
        std::cout << current->data << '\n';
    }
}

void SinglyLinkedList::insertNodeAtTail(int data)
{
    SinglyLinkedListNode* newNode = new SinglyLinkedListNode(data);

    if (head != nullptr) { // we traverse the LL until next is nullptr
        SinglyLinkedListNode* temp = head;
        while (temp->next != nullptr) 
        {
            temp = temp->next;
        }
        temp->next = newNode;
    } else {
        head = newNode;
    }
}

void SinglyLinkedList::insertNodeAtHead(int data)
{
    SinglyLinkedListNode* newHead = new SinglyLinkedListNode(data);

    if (head == nullptr) {
        newHead->next = nullptr;
    } else {
        newHead->next = head;
    }
    head = newHead;
}

void SinglyLinkedList::insertNodeAtPosition(int data, size_t position)
{
    SinglyLinkedListNode* newNode = new SinglyLinkedListNode(data);

    if (head == nullptr) {
        head = newNode;
        head->next = nullptr;
    } else {
        size_t i = 0;
        SinglyLinkedListNode* current = head;

        while (i + 1 < position && current->next != nullptr) {
            current = current->next;
            i++;
        }

        if (position == 0) { // newNode becomes the new head
            newNode->next = current;
            head = newNode;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

void SinglyLinkedList::deleteNode(size_t position)
{
    if (head != nullptr) {
        SinglyLinkedListNode* current = head;
        size_t i = 0;

        while (i + 1 < position && current->next != nullptr) {
            current = current->next;
            ++i;
        }

        if (position == 0) {
            head = current->next;
            delete current;
        } else if (current->next != nullptr) {
            SinglyLinkedListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
}

void SinglyLinkedList::reverse()
{
    reverse(head);
}

void SinglyLinkedList::reverse(SinglyLinkedListNode* current)
{
    if (current == nullptr) {
        current = head;
    }

    if (current->next != nullptr) {
        reverse(current->next);
        current->next->next = current;
        current->next = nullptr;
    } else {
        head = current;
    }
}

bool SinglyLinkedList::compare(SinglyLinkedList* list2)
{
    return compare(head, list2->head);
}

bool SinglyLinkedList::compare(SinglyLinkedListNode* firstHead, SinglyLinkedListNode* secondHead)
{
    if (firstHead == nullptr && secondHead == nullptr) {
        return true;
    } else if (firstHead == nullptr || secondHead == nullptr) {
        return false;
    }

    int data1 = firstHead->data;
    int data2 = secondHead->data;
    if (data1 != data2) {
        return false;
    } else {

        return compare(firstHead->next, secondHead->next);
    }
}

void SinglyLinkedList::removeDuplicates()
{
    if (head != nullptr) {
        SinglyLinkedListNode* prev = head;
        SinglyLinkedListNode* current = head;
        SinglyLinkedListNode* temp;

        current = current->next;
        while (current != nullptr) {
            if (prev->data == current->data) {
                temp = current;
                prev->next = current->next;
                current = current->next;
                delete temp; // only current pointer ever deletes
            } else {
                current = current->next;
                prev = prev->next;
            }
        }
    }
}

bool SinglyLinkedList::has_cycle()
{
    std::unordered_set<SinglyLinkedListNode*> st;
    SinglyLinkedListNode* current = head;

    while (current != nullptr) {
        if (st.find(current) != st.end()) {
            st.insert(current);
        } else {
            return true;
        }
        current = current->next;
    }

    return false;
}