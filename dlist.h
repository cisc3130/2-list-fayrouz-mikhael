#ifndef DLIST_H
#define DLIST_H

#include <iterator>

template <class T>
class DList {
	struct Node {
		T data;
		Node* next ;
		Node* prev;
		Node(const T& x, Node* y = NULL , Node* p = NULL) : data(x), next(y) , prev(p) {}		// TODO
	};

	Node* head;

	public:

	class iterator {
		Node* nd;

		public:
		// typedefs
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;

		friend class DList;		// List objects have access to private members of List::iterator.

		// constructors
		inline iterator(Node* x=NULL) : nd(x) {}	// construct from node pointer
		inline iterator(const iterator& x) : nd(x.nd) {}	// construct from another iterator

		// operator overloads
		inline iterator& operator=(const iterator& x) {
			nd = x.nd;
			return *this;
		}	// assignment
		
		inline iterator& operator++() {
			nd = nd->next;
			return *this;
		}	// prefix increment

		inline iterator operator++(int) {
			iterator tmp(*this);	// make copy of current iterator for return
			nd = nd->next;				// advance current iterator
			return tmp;
		}	// postfix increment

		inline T& operator*() const { return nd->data; }	// dereference

		inline bool operator==(const iterator& x) const {
			return nd == x.nd;
		}	// equal

		inline bool operator !=(const iterator& x) const {
			return nd != x.nd;
		}	// not equal
	};		// end iterator


// TODO: header node should be allocated and linked to itself
 DList() : head(new Node(T())){ 	// make the next and the prevous of the head equal to head
	 head->next = head;
	 head->prev = head; 
}

	~DList() { clear(); }
	void clear() { while (!empty()) pop_front(); }

	// TODO: with sentinel node, head is never null
	bool empty() { 
	return head->next  == head; // it is empty if head's next is equal to head
	 }

	// TODO: with sentinel node, head always stays the same. Links: link head to new first node, new first node to head, new first node to former first node, former first node to new first node.
	void push_front(const T& x) {
		Node* nd = new Node(x);
		
		nd->next = head ->next; // link the new node's next to the former first node
		nd -> prev = head;	// link the pervous of the new node to head
		nd-> next -> prev = nd; // link the former first node pervous to the new node
		nd-> prev -> next = nd;	 // link head to the new node
		
		}

	// TODO: with sentinel node, head always exists. Links: link head to *second* node, and link second node to head.
	void pop_front() {
			Node* nd = head->next; 
			nd-> next-> prev = nd ->prev ; // link the second node to the head
			nd-> prev -> next = nd->next ; // link head to the second node
			delete nd; // delete the node
			
	}

	// TODO: with sentinel node, head never changes. With prev links, don't need to search list for node before position. Four links.
	void insert(const iterator position, const T& val) {
		Node* nd = new Node(val, position.nd);	// new node's next will be position's node

		if (head->next == position.nd){
		head->next = nd;
		nd->prev = head;	
		}
		 
		 
	else {
			Node* pnd = position.nd->prev;
				nd -> prev = pnd; // link the newnode's prev to the prevous node 
	            nd-> next = pnd-> next; // link the newnode 's next to  the position.nd
	            pnd->next = nd;// link  the prevous's node next to the the new node
	         	nd -> next -> prev = nd; // link the position.nd's prevous to the node	
			
		}
	}

// TODO: fill	
	void erase(const iterator position) {
    Node *ndd = position.nd;
    ndd-> prev -> next = ndd -> next; // link the position.nd 's prevous 's next to position.nd's next
    ndd-> next-> prev = ndd ->prev;// link the position.nd 's next 's prevous to position.nd's prevous

			delete ndd;
	}

// TODO: with sentinel node, head is not the first vaild node and null is not one past the last valid node
	iterator begin() { 
	return iterator(head->next); // return the first node after the head
	}
	iterator end() {	
	 return iterator(head); // return head
	 }
};


#endif
