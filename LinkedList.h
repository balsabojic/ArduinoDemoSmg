#ifndef LINKEDLIST_H__
#define LINKEDLIST_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**
 * A simple (no delete operations) generic linked list.
 */
template<class T>
class LinkedList {
    struct ListElement {
      ListElement* next;
      T data;

      ListElement(T data): next(NULL), data(data) {
      }
    };

    ListElement* first;
    int count;

  public:

    class Iterator {
        ListElement* element;

      public:

        Iterator(ListElement* element): element(element) {
        }

        T operator*() {
          return element->data;
        }

        void operator++() {
          element = element->next;
        }

        void operator++(int) {
          element = element->next;
        }

        bool operator==(const Iterator& rhs) {
          return element == rhs.element;
        }

        bool operator!=(const Iterator& rhs) {
          return element != rhs.element;
        }
    };

    LinkedList(): first(NULL), count(0) {
    }

    /**
     * Insert at the beginning of the list.
     */
    void insert(T element) {
      count++;
      ListElement* newEle = new ListElement(element);
      if (first) {
        newEle->next = first;
      }
      first = newEle;
    }

    int size() const {
      return count;
    }

    Iterator begin() {
      return Iterator(first);
    }

    Iterator end() {
      return Iterator(NULL);
    }

};

#endif
