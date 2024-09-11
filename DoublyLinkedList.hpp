#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP
/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add or remove methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * Although, it may be more difficult to do so. Your choice!
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */
//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
/**
 * Namespace for our classroom !
 */
namespace CPSC131
{
	/**
	 * Namespace to hold all things related to our DLL
	 */
	namespace DoublyLinkedList
	{
		/**
		 * Implement our DoublyLinkedList class !
		 */
		template <class T>
		class DoublyLinkedList
		{
			public:
				
				/**
				 * Node class, representing a single item in our linked list
				 */
				// TODO: Complete all class methods
				class Node
				{
					public:
						
						/// CTORS
						Node() : prev_(nullptr), next_(nullptr) {}
						Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}
						Node(T element, Node* prev, Node* next) {}
						
						/// Set the pointer to the previous element
						void setPrevious(Node* prev) {
							prev_ = prev;
						}
						
						/// Set the pointer to the previous element
						void setPrev(Node* prev) {
							prev_ = prev;
						}
						
						/// Get a pointer to the previous element
						Node* getPrevious() { return prev_; }
						
						/// Get a pointer to the previous element
						Node* getPrev() { return prev_; }
						
						/// Set the pointer to the next node
						void setNext(Node* next) {
							next_ = next;
						}
						
						/// Get a pointer to the next node
						Node* getNext() { return next_; }
						
						/// Set the element this node holds
						void setElement(T element) {
							element_ = element;
						}
						
						/// Get the element this node holds
						///	YOUR WELCOME
						T& getElement() { return this->element_; }
						
						/// Return a reference to the element
						///	YOUR WELCOME
						T& operator*() { return this->element_; }
						
					private:
						T element_;
						Node* prev_;
						Node* next_;
				};
				
				/**
				 * Nested Iterator class.
				 * This allows user code to refer to the Iterator's type as:
				 * 
				 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
				 * 
				 * (as opposed to specifying the template argument two times)
				 */
				class Iterator
				{
					public:
						
						///	Constructor that does nothing; YOUR WELCOME
						Iterator()
						{
							/// yw
						}
						
						///	Constructor taking a head and tail pointer; YOUR WELCOME
						Iterator(Node* head, Node* tail) : head_(head), tail_(tail)
						{
							 this->cursor_ = this->end();
						}
						
						///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
						Iterator(Node* head, Node* tail, Node* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
						
						///	Get a pointer to the head node, or end() if this list is empty
						Node* begin()
						{	
							return head_;
						}
						
						///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
						Node* end()
						{
							return nullptr;
						}
						
						///	Get the node to which this iterator is currently pointing
						Node* getCursor()
						{
							if(cursor_ == nullptr) {
								throw std::range_error("out of bound");
							}
							
							return cursor_;
						}
						
						/**
						 * Assignment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator=(const Iterator& other)
						{
							if (this != &other) {
								head_ = this->head_;
								tail_ = this->tail_;
								cursor_ = this->cursor_;
							}
							
							return *this;
						}
						
						///	Comparison operator
						bool operator==(const Iterator& other)
						{
	
							return cursor_ == this->cursor_;
						}
						
						///	Inequality comparison operator
						bool operator!=(const Iterator& other)
						{
							return !(*this == other);
						}
						
						/**
						 * Prefix increment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator++()
						{
							//	TODO: Your code here
							if (cursor_ != nullptr) {
								cursor_ = cursor_->getNext();
							}
							
							return *this;
						}
						
						/**
						 * Postfix increment
						 * Return a copy of this Iterator, BEFORE it was modified
						 */
						Iterator operator++(int)
						{
							Iterator before = *this;
							++(*this);

							return before;
						}
						
						/**
						 * Prefix decrement operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator--()
						{
							// check is current node is pointing to a nullptr 
							// else we can make it point to the previous one
							// current->previous

							if (cursor_ == nullptr) {
								cursor_ = tail_;
							} else {
							cursor_ = cursor_->getPrev();
							}
							
							return *this;
						}
						
						/**
						 * Postfix decrement operator
						 * Return a copy of this Iterator BEFORE it was modified
						 */
						Iterator operator--(int)
						{
							Iterator copy = *this;
							--(*this);
							//	TODO: Your code here
							// same with this return (maybe copy)
							
							return copy;
						}
						
						/**
						 * AdditionAssignment operator
						 * Return a copy of the current iterator, after modification
						*/
						Iterator operator +=(size_t add)
						{
							for (size_t i = 0; i < add; ++i) {
								if (cursor_ != nullptr) {
									cursor_ = cursor_->getNext();
								}
							}
							
							return *this;
						}
						/**
						 * SubtractionAssignment operator
						 * Return a copy of the current iterator, after modification
						 */
						Iterator operator -=(size_t add)
						{
							for (size_t i = 0; i < add; ++i) {
								if (cursor_->getPrev() != nullptr) {
									break;
							}
							cursor_ = cursor_->getPrev();
							return *cursor_;
						}
						}
						
						/**
						 * AdditionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator +=(int add)
						{
							if (add > 0) {
								for (int i = 0; i < add; ++i) {
									cursor_ = cursor_->getNext();
								}
							}
							if (add < 0) {
								for (int i = 0; i < -add; ++i ) {
									if (cursor_->getPrev() == nullptr) {
										break;
									}
									cursor_= cursor_->getPrev();
								}
							}
							return *this;
						}
						
						/**
						 * SubtractionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator -=(int subtract)
						{
							if (subtract > 0) {
							for (int i = 0; i < subtract; ++i) {
								if (cursor_ != nullptr) {
									cursor_ = cursor_->getPrev();
								} else {
									cursor_ = head_;
									break;
								}
							}
							cursor_ = cursor_->getNext();
							}
							
							//	TODO: Your code here
							
							return *this;
						}
						
						/**
						 * Dereference operator returns a reference to the ELEMENT contained with the current node
						 */
						T& operator*()
						{
							if (cursor_ == nullptr) {
								throw std::range_error("out of range");
							}							
							return cursor_->getElement();
						}
					private:
						
						/// Pointer to the head node
						Node* head_ = nullptr;
						
						/// Pointer to the tail node
						Node* tail_ = nullptr;
						
						/**
						 * Pointer to the cursor node.
						 * This is only one way of letting the iterator traverse the linked list.
						 * You can change to a different method if you wish (and can still pass unit tests)
						 */
						Node* cursor_ = nullptr;
					
					friend class DoublyLinkedList;
				};
				
				/// Your welcome
				DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0)
				{
					// TODO: Your code here
				}
				
				///	Copy Constructor
				DoublyLinkedList(DoublyLinkedList& other): head_(nullptr), tail_(nullptr), size_(0)
				{
					for (Iterator copy = other.begin(); copy != other.end(); ++copy) {
						push_back(*copy);
					}
					//	TODO: Your code here
				}
				
				/// DTOR
				~DoublyLinkedList()
				{
					clear();
				}
				
				/**
				 * Clear the list and assign the same value, count times.
				 * If count was 5, T was int, and value was 3,
				 * 	we'd end up with a list like {3, 3, 3, 3, 3}
				 */
				void assign(size_t count, const T& value)
				{
					clear();
					for (size_t i = 0; i < count; ++i) {
						push_back(value);
					}
				}
				
				/**
				 * Clear the list and assign values from another list.
				 * The 'first' iterator points to the first item copied from the other list.
				 * The 'last' iterator points to the last item copied from the other list.
				 * 
				 * Example:
				 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
				 * 	Suppose first points to the 4
				 *	Suppose last points to the 7
				 * 	We should end up with our list becoming: {4, 3, 2, 7}
				 *
				 * If the user code sends out-of-order iterators,
				 * 	just copy from 'first' to the end of the source list
				 * Example: first=7, last=4 from the list above would give us:
				 * 	{7, 1}
				 */
				void assign(Iterator first, Iterator last)
				{
					clear();
					while (first != last) {
						push_back(*first);
						++first;
					}					
				}
				
				/// Return a pointer to the head node, if any
				Node* head() const
				{
					return head_;
				}
				
				/// Return a pointer to the tail node, if any
				Node* tail() const
				{
					return tail_;
				}
				
				/**
				 * Return an iterator that points to the head of our list
				 */
				Iterator begin() const
				{
					return Iterator(head_, tail_, head_);
				}
				
				/**
				 * Return an iterator that points to the last element (tail) of our list
				 */
				Iterator last() const
				{
					return Iterator(tail_, head_, tail_);
				}
				
				/**
				 * Should return an iterator that represents being past the end of our nodes,
				 * or just that we are finished.
				 * You can make this a nullptr or use some other scheme of your choosing,
				 * 	as long as it works with the logic of the rest of your implementations.
				 */
				Iterator end() const
				{
					return Iterator(nullptr, nullptr, nullptr);
				}
				
				/**
				 * Returns true if our list is empty
				 */
				bool empty() const
				{
					return (size_ == 0);
				}
				
				/**
				 * Returns the current size of the list
				 * Should finish in constant time!
				 * (keep track of the size elsewhere)
				 */
				size_t size() const
				{
					return size_;
				}
				
				/**
				 * Clears our entire list, making it empty
				 * Remember: All removal operations should be memory-leak free.
				 */
				void clear()
				{
					while (head_ != nullptr) {
						Node* clear = head_->getNext();
						delete head_;
						head_ = clear;
					}
					head_ = nullptr;
					tail_ = nullptr;
					size_ = 0;
				}
				
				/**
				 * Insert an element after the node pointed to by the pos Iterator
				 * 
				 * If the list is currently empty,
				 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
				 * 
				 * If the incoming iterator is this->end(), insert the element at the tail
				 * 
				 * Should return an iterator that points to the newly added node
				 * 
				 * To avoid repeated code, it might be a good idea to have other methods
				 * 	rely on this one.
				 */
				Iterator insert_after(Iterator pos, const T& value)
				{
					Node* newNode = new Node(value);

					if (empty()) {
						head_ = newNode;
						tail_ = newNode;
						size_ = 1;
						return Iterator(head_, tail_, newNode);
					}

					if (pos == end()) {
						newNode->setPrev(tail_);
						tail_->setNext(newNode);
						tail_ = newNode;
						size_++;
						return Iterator(head_, tail_, newNode);
					}

					Node* pointing = pos.getCursor();
					Node* next = pointing->getNext();
					
					newNode->setPrev(pointing);
					newNode->setNext(next);
					pointing->setNext(newNode);

					if (next) {
						next->setPrev(newNode);
					} else{
						tail_ = newNode;
					}
					size_++;					
					// still in progress
					return Iterator(head_, tail_,newNode);
				}
				
				/**
				 * Insert a new element after the index pos.
				 * Should work with an empty list.
				 * 
				 * Should return an iterator pointing to the newly created node
				 * 
				 * To reduce repeated code, you may want to simply find
				 * 	an iterator to the node at the pos index, then
				 * 	send it to the other overload of this method.
				*/
				Iterator insert_after(size_t pos, const T& value)
				{

					Node* newNode = new Node(value);
					if (head_ == nullptr || pos == 0) {
						newNode->setNext(head_);
						if (head_ != nullptr) {
							head_->setPrev(newNode);
						}
						head_ = newNode;
						if (tail_ == nullptr) {
							tail_ = newNode;
						}
						size_++;
						return Iterator(head_, tail_, newNode);
					}
					if (pos >= size_) {
						return this->end();
					}
					Node* current = head_;
					for (size_t i = 0; i < pos; ++i) {
						current = current->getNext();
					}
					Node* next = current->getNext();

					newNode->setPrev(current);
					newNode->setNext(next);
					current->setNext(newNode);
					if (next) {
						next->setPrev(newNode);
					} else {
						tail_ = newNode;
					}
					size_++;
					
					return Iterator(head_, tail_, newNode);
				}
				
				/**
				 * Erase the node pointed to by the Iterator's cursor.
				 * 
				 * If the 'pos' iterator does not point to a valid node,
				 * 	throw an std::range_error
				 * 
				 * Return an iterator to the node AFTER the one we erased,
				 * 	or this->end() if we just erased the tail
				 */
				Iterator erase(Iterator pos)
				{
					if(pos == end()) {
						throw std::range_error("Out of range");
					}
					
					Node* remove = pos.getCursor();
					Node* next = remove->getNext();
					Node* prev = remove->getPrev();

					if (remove == head_) {
						head_ = next;
						if (head_) {
							head_->setPrev(nullptr);
						}
					}
					if (remove == tail_) {
						tail_ = prev;
						if (tail_) {
							tail_->setNext(nullptr);
						}
					}

					if (prev != nullptr) {
						prev->setNext(next);
					}
					if (next != nullptr) {
						next->setPrev(prev);
					}
					delete remove;
					size_--;

					if (next == nullptr) {
						return Iterator(head_, tail_, nullptr);
					}
					return Iterator(head_, tail_, next);
				}
				
				/**
				 * Add an element just after the one pointed to by the 'pos' iterator
				 * 
				 * Should return an iterator pointing to the newly created node
				 */
				Iterator push_after(Iterator pos, const T& value)
				{
					Node* newNode = new Node(value);
					if (pos == end()) {
						push_back(value);
						delete newNode;
						return Iterator(head_,tail_, newNode );
					} 
					Node* current = pos.getCursor();
					Node* next = current->getNext();

					newNode->setPrev(current);
					newNode->setNext(next);
					current->setNext(newNode);
					if (next) {
						next->setPrev(newNode);
					} else {
						tail_ = newNode;
					}
					size_++;
					return Iterator(head_, tail_, newNode);
				}
				
				/**
				 * Add a new element to the front of our list.
				 */
				void push_front(const T& value)
				{
					Node* newNode = new Node(value);

					if (head_ == nullptr) {
						head_ = newNode;
						tail_ = newNode;
					} 
					else {
						 newNode->setNext(head_);
						 head_->setPrev(newNode);
						 head_ = newNode;
					}
					size_++;
				}
				
				/**
				 * Add an element to the end of this list.
				 * 
				 * Should return an iterator pointing to the newly created node.
				 */
				Iterator push_back(const T& value)
				{
					Node* newNode = new Node(value);

					if (tail_ == nullptr) {
						head_ = newNode;
						tail_ = newNode;
					} else {
						newNode->setPrev(tail_);
						tail_->setNext(newNode);
						tail_ = newNode;
					}
					size_++;
					
					return Iterator(head_, tail_, newNode);
				}
				
				/**
				 * Remove the node at the front of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_front()
				{
					// forgot about throwing
					if (empty()) {
						throw std::range_error("list is empty");
					}
					if (head_ == tail_) {
						delete head_;
						head_ = nullptr;
						tail_ = nullptr;
					}
					
					Node* move = head_;
					head_ = move->getNext();

					if (head_) {
						head_->setPrev(nullptr);
					}
					delete move;
					size_--;
				}
				
				/**
				 * Remove the node at the end of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_back()
				{
					// use notes + slides for pop back
					if (empty()) {
						throw std::range_error("list is empty");
					}
					if (head_ == tail_) {
						delete tail_;
						head_ = nullptr;
						tail_ = nullptr;
					}
					Node* remove = tail_;
					tail_ = remove->getPrev();

					if (tail_) {
						tail_->setNext(nullptr);
					}
					delete remove;
					size_--;
				}
				
				/**
				 * Return a reference to the element at the front.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& front()
				{
					//	TODO: Your code here
					if (head_ == nullptr) {
						throw std::range_error("list is empty");
					}
					return head_->getElement();
				}
				
				/**
				 * Return a reference to the element at the back.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& back()
				{
					//	TODO: Your code here
					if (tail_ == nullptr) {
						throw std::range_error("list is empty");
					}
					return tail_->getElement();
				}
				
				/**
				 * Return the element at an index
				 * 
				 * Should throw a range_error is out of bounds
				 */
				T& at(size_t index)
				{
					Node* current = head_;

					if (index >= size_) {
						throw std::range_error("out of bounds");
					}
					
						for (size_t i = 0; i < index; ++i) {
						current = current->getNext();
					}

					if (current == nullptr) {
						throw std::range_error("out of bounds");
					}

					return current->getElement();

				}
				
				/**
				 * Reverse the current list
				 * 
				 * It might be easy to consider the following:
				 * - Create a temp empty list
				 * - Iterate through the current list
				 * - For each item in the current list, push to the FRONT (not back)
				 * - Assign the current list to the temp list
				 * - Discard the temp list
				 */
				void reverse()
				{
					Node* temH = nullptr;
					Node* temT = nullptr;
					Node* current = head_;
					while (current != nullptr) {
						Node* newNode = new Node(current->getElement());
						if (temH == nullptr){
							temH = newNode;
							temT = newNode;
						} else {
							newNode->setPrev(temT);
							temT->setNext(newNode);
							temT = newNode;
						}
						current = current->getNext();
					}
					clear();
					head_ = temH;
					tail_ = temT;
				}
				
				/**
				 * I bet you're happy I'm not making you do this.
				 * No tests will be run against this function,
				 * 	but feel free to try it out, as a challenge!
				 * 
				 * If I were doing this and didn't care too much for efficiency,
				 * 	I would probably create an extra helper function to swap two
				 * 	positions in the current list.
				 * Then I would simply sweep through the list and perform
				 *  the bubble-sort algorithm. Perhaps selection sort.
				 * 
				 * If you want a huge challenge, try implementing quicksort.
				 * 
				 * (but again, don't worry about this method; it will not be tested)
				 */
				void sort()
				{
					//	:,D (i'll try after turn in)
				}
				
				/**
				 * Assignment operator
				 * 
				 * Clear this list and fill it with the others' values
				 * (by value, not by reference)
				 * 
				 * Return a reference to this list
				 */
				DoublyLinkedList<T>& operator =(const DoublyLinkedList<T>& other)
				{
					if (this == &other) {
						return *this;
					}

					clear();

					/*bool copyItem = true;

					for (Iterator it = other.begin(); it != other.end(); ++it) {
						if (copyItem) {
							push_back(*it);
						}
						copyItem = !copyItem;
					}*/
					for (Iterator it = other.begin(); it != other.end(); ++it) {
						push_back(*it);
					}
					
					return *this;
				}
				
				/**
				 * Return true if the lists are "equal"
				 * 
				 * "Equal" here is defined as:
				 * - Same size
				 * - Elements at the same indexes would return true for their own comparison operators
				 * 
				 * In other words: "They contain all the same values"
				 * (no need to be references to each othe r)
				 */
				bool operator ==(DoublyLinkedList<T>& other)
				{
					if (size_ != other.size()) {
						return false;
					}
					Node* current = head_;
					Node* comps = other.head_;

					while(current != nullptr) {
						if (current->getElement() != comps->getElement()) {
							return false;
						}
						current = current->getNext();
						comps = comps->getNext();
					}
					
					return true;
				}
				
				/**
				 * Return true if the lists are "not equal"
				 * 
				 * See the operator== stub for definition of "equal"
				 * 
				 * Probably want to avoid repeated code by relying on the other operator
				 */
				bool operator !=(DoublyLinkedList<T>& other)
				{
					return !(*this == other);
				}
				
			private:
		
				Node* head_ = nullptr;
				Node* tail_ = nullptr;
				size_t size_ = 0;
		};
	}
}
#endif