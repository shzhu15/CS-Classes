#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

class LinkedList {
//    Link m_pHead begin;
  public:
    LinkedList() {
       m_pHead = NULL;
       }
    void initialize();
    bool insert(unsigned int uiData);
    bool remove(unsigned int &pData);
    void print();
    friend std::ostream & operator<<(std::ostream & out, LinkedList&);

  private:
    struct Link {
	unsigned int m_uiData;
	Link *m_pNext;
	void initialize(unsigned int uiData, Link *pNext);
    } *m_pHead;
};

#endif /* _LINKED_LIST_H_ */
