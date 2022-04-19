#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
    bool empty() const {
	   if (first && last)
		  return false;
	   else
		  return true;
    };

  //EFFECTS: returns the number of elements in this List
    int size() const {
	   int count = 0;
	   for (Node *np = first; np; np = np->next) {
		  ++count;
	   }
	   return count;
    };

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T & front() {
	   assert(!empty());
	   return first->datum;
    };

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
    T & back() {
	   assert(!empty());
	   return last->datum;
    };

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
	 Node *p = new Node;
	 p->datum = datum;
	 p->next = first;
	 p->prev = nullptr;
	 if (empty()) { first = last = p; }
	 else {
		first->prev = p;
		first = p;
	 }
  };

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
	 Node *p = new Node;
	 p->datum = datum;
	 p->next = nullptr;
	 if (empty()) { 
		first = last = p;
		p->prev = nullptr;
	 }
	 else {
		p->prev = last;
		last->next = p;
		last = p;
	 }
  };

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
	 assert(!empty());
	 Node *victim = first;
	 if (first != last) {
		first = first->next;
		first->prev = nullptr;
	 }
	 else {
		first = nullptr;
		last = nullptr;
	 }
	 
	 delete victim;
  };

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
	 assert(!empty());
	 Node *victim = last;
	 if (last != first) {
		last = last->prev;
		last->next = nullptr;
	 }
	 else {
		first = nullptr;
		last = nullptr;
	 }
	 
	 delete victim;
  };

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
	 while (!empty()) {
		pop_front();
    }
  };

  List<T>() : first(nullptr), last(nullptr) {};		 // default ctor

  List<T>(const List<T> &other) : first(), last() {	 // copy ctor
	 copy_all(other);
  }; 

  List<T> & operator=(const List<T> &rhs) {			 // assignment op
	 if (this == &rhs) { return *this; }
	 clear();
	 copy_all(rhs);
	 return *this;
  }

  ~List<T>() { clear(); };

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
	 assert(empty());
	 for (Node *np = other.first; np; np = np->next) {
		push_back(np->datum);
	 }
  };

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

	 

	 // Iterator(Iterator & other) : node_ptr(other.node_ptr) {};

	 /* Iterator & operator=(Iterator & rhs) {
		node_ptr = rhs.node_ptr;
	 }*/

	 // ~Iterator() {};

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator & operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator & operator++() {
	   assert(node_ptr);
	   node_ptr = node_ptr->next;
	   return *this;
    }

    T & operator*() {
	   assert(node_ptr);
	   return node_ptr->datum;
    }

    bool operator==(const Iterator rhs) const {
	   return node_ptr == rhs.node_ptr;
    }

    bool operator!=(const Iterator rhs) const {
	   return node_ptr != rhs.node_ptr;
    }

    Iterator() : node_ptr(nullptr) {};

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {};

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
	 return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
	 return Iterator();
  }

  void check_association(Iterator i) {
	 bool in_list = false;
	 if (!empty()) {
		for (Iterator it = begin(); it != end(); ++it) {
		    if (it == i) { in_list = true; }
		}
	 }
	 else {
		if (begin() == i) { in_list = true; }
	 }

	 assert(in_list);
  };

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
	 assert(i.node_ptr);
	 check_association(i);
	 Iterator it = i;
	 if (it == begin()) {
		pop_front();
	 }
	 else if (++it == end()) {
		pop_back();
	 }
	 else {
		Node *victim = i.node_ptr;
		((--i).node_ptr)->next = victim->next;
		((++i).node_ptr)->prev = victim->prev;
		delete victim;
	 }
  };

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
	 check_association(i);
	 Iterator it = i;
	 if (empty() || it == begin()) {
		push_front(datum);
	 }
	 else {
		Node *p = new Node;
		p->datum = datum;
		p->next = i.node_ptr;
		p->prev = (i.node_ptr)->prev;
		((i.node_ptr)->prev)->next = p;
		(i.node_ptr)->prev = p;
		

	 }
  };

  

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.