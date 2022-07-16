#include <cstdlib>
#include <iostream>
#include "ll.h"
using namespace std;

void LinkedList::Link::initialize(unsigned int uiData, Link *pNext) {
    m_uiData = uiData;
    m_pNext = pNext;
}

void LinkedList::initialize() {
    m_pHead = nullptr;
}

bool LinkedList::insert(unsigned int uiData) {
    Link* new_link = new Link;

    new_link->initialize(uiData, m_pHead);
    m_pHead = new_link;

    return true;
}

bool LinkedList::remove(unsigned int &pData) {

    bool ret_val = false;

    if (m_pHead != nullptr) {
        Link *temp = m_pHead;
        m_pHead = m_pHead->m_pNext;
        pData = temp->m_uiData;

        ret_val = true;
    }

    return ret_val;
}

void LinkedList::print() {
  Link *current;
    current = m_pHead;
    while (current != nullptr) {
      cout << current->m_uiData << " ";
      current = current->m_pNext;
  }
}
std::ostream & operator <<(std::ostream &out, LinkedList &a) {
  for(auto p = a.m_pHead; p; p = p->m_pNext) {
      out << p->m_uiData << " ";
  }
  return out;
}
