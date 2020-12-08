#pragma once
#include<iostream>
/**
* \brief Simple implementation of doubly-linked ring. Focuses mostly around insertion of the elements as well as iterators.
*/
template<typename Key, typename Info>
class Ring {
private:
	struct Node {
		Key key;
		Info info;
		Node* next;
		Node* prev;
		Node(const Key& kval, const Info& vinfo) : key(kval), info(vinfo), next(this), prev(this) {}
		Node(const Key& kval, const Info& vinfo, Node* vnext, Node* vprev) : key(kval), info(vinfo), next(vnext), prev(vprev) {}
	};
	Node* any;
	/**
	* Method iterates throught the Ring and executes method in every iteration, furthermore, if method returns true the loop is terminated.
	* @param[in] method : Bool method with a iterator& at the input.
	* @param[in] forwardDirection : If true direction is forward, otherwise the direction is backwards.
	* @return : True - method is satisfied atleast once, False - Ring is empty(), method is not satisfied.
	*/
	template<typename ToDo>
	bool iterate_through(ToDo method, bool forwardDirection = true) const;
public:
	Ring();
	Ring(const Ring<Key, Info>& copy);
	~Ring();
	/**
	* Iterators for the ring.
	*/
	class iterator {
		friend class Ring<Key, Info>;
		const Ring<Key, Info>* master;
		mutable Node* current;
		iterator(Node* curr, const Ring<Key, Info>* m) : master(m), current(curr) {}
	public:
		iterator() : master(nullptr), current(nullptr){}
		iterator(const iterator& x) : master(x.master), current(x.current) {}
		~iterator() = default;

		iterator& operator=(const iterator& x) {
			current = x.current;
			master = x.master;
			return *this;
		}

		const iterator& operator++() const {
			if (!current)
				throw "Iterator does not have a value!";
			current = current->next;
			return *this;
		}

		iterator operator++(int) const {
			if (!current)
				throw "Iterator does not have a value!";
			iterator cache(*this);
			current = current->next;
			return cache;
		}

		const iterator& operator--() const {
			if (!current)
				throw "Iterator does not have a value!";
			current = current->prev;
			return *this;
		}

		iterator operator--(int) const {
			if (!current)
				throw "Iterator does not have a value!";
			iterator cache(*this);
			current = current->prev;
			return cache;
		}

		bool operator==(const iterator& x) const {
			return current == x.current;
		}

		bool operator!=(const iterator& x) const {
			return !(*this == x);
		}

		bool operator==(const Ring<Key, Info>& x) const {
			return master == &x;
		}

		bool operator!=(const Ring<Key, Info>& x) const {
			return !(*this == x);
		}

		const Info& operator*() const {
			if (!current)
				throw "Iterator does not have a value!";
			return current->info;
		}

		Info& operator*() {
			if (!current)
				throw "Iterator does not have a value!";
			return current->info;
		}

		const Key& getKey() const {
			if (!current)
				throw "Iterator does not have a value!";
			return current->key;
		}

		const Info& getInfo() const {
			if (!current)
				throw "Iterator does not have a value!";
			return current->info;
		}

		bool isNull() const {
			return !current;
		}
	};
	/**
	* Assign operator.
	*/
	Ring<Key, Info>& operator=(const Ring<Key, Info>& copy);
	/**
	* Equality operator.
	* @return : True - iterator stores node of the Ring, False - otherwise.
	*/
	bool operator==(const iterator& it) const;
	/**
	* Inequality operator.
	* @return : True - iterator stores node of the Ring, False - otherwise.
	*/
	bool operator!=(const iterator& it) const;
	/**
	* Outputs the iterator to the first element of a Ring.
	* @return : Iterator(head);
	*/
	iterator begin() const;
	/**
	* Outputs the information about the ring being empty.
	* @return : True - Ring is empty. False - otherwise.
	*/
	bool empty() const;
	/**
	* Clears the ring.
	*/
	void clear();
	/**
	* Method pushes the element before any. If any exists.
	* @param[in] k : Key
	* @param[in] i : Info
	*/
	void push(const Key& k, const Info& i);
	/**
	* Method pushes the key and info of the iterator before any.
	* @param[in] it : Iterator to the Ring.
	*/
	void push(const iterator& it);
	/**
	* Itserts the given key and info after the key.
	* @param[in] k : Key which is going to be inserted.
	* @param[in] i : Info which is going to be inserted.
	* @param[in] key : Node is going to be inserted after this key.
	* @param[in] occurrence : Key is not unique so we do need to take a occurrence in a count.
	* @return : True - element was successfully inserted, False - otherwise.
	*/
	bool push_after(const Key& k, const Info& i, const Key& key, int occurrence = 1);
	/**
	* Itserts the given key and info of the iterator after the key.
	* @param[in] it : iterator to random Ring.
	* @param[in] key : Node is going to be inserted after this key.
	* @param[in] occurrence : Key is not unique so we do need to take a occurrence in a count.
	* @return : True - element was successfully inserted, False - otherwise.
	*/
	bool push_after(const iterator& it, const Key& key, int occurrence = 1);
	/**
	* Itserts the given key and info of the iterator after the iterator of a 'this' Ring.
	* @param[in] it : iterator to random Ring.
	* @param[in] ringElement : An element of the Ring.
	* @return : True - the element was successfully inserted, False - there was an error. it is null or ringElement is not a member of this.
	*/
	bool push_after(const iterator& it, const iterator& ringElement);
	/**
	* Itserts the given key and info before the key.
	* @param[in] k : Key which is going to be inserted.
	* @param[in] i : Info which is going to be inserted.
	* @param[in] key : Node is going to be inserted before this key.
	* @param[in] occurrence : Key is not unique so we do need to take a occurrence in a count.
	* @return : True - element was successfully inserted, False - otherwise.
	*/
	bool push_before(const Key& k, const Info& i, const Key& key, int occurrence = 1);
	/**
	* Itserts the given key and info of the iterator before the key.
	* @param[in] it : iterator to random Ring.
	* @param[in] key : Node is going to be inserted before this key.
	* @param[in] occurrence : Key is not unique so we do need to take a occurrence in a count.
	* @return : True - element was successfully inserted, False - otherwise.
	*/
	bool push_before(const iterator& it, const Key& key, int occurrence = 1);
	/**
	* Itserts the given key and info of the iterator before the iterator of a 'this' Ring.
	* @param[in] it : iterator to random Ring.
	* @param[in] ringElement : An element of the Ring.
	* @return : True - the element was successfully inserted, False - there was an error. it is null or ringElement is not a member of this.
	*/
	bool push_before(const iterator& it, const iterator& ringElement);
	/**
	* Removes a node to which iterator is pointing.
	* If: 
	* iterator is pointing to a node from the current Ring == Ring is nonempty
	* iterator is not null
	* @return : True - element was successfully deleted, False = otherwise.
	*/
	bool remove(const iterator& it);
	/**
	* Find a given occurrence of a key in a ring.
	* @param[in] key : A wanted key.
	* @param[in] occurrence : A occurrence of a wanted key.
	* @param[in] it : A iterator to which the node of the key is going to be assigned.
	* @param[in] forwardDirection : If true the direction is forward == node = node -> next, if false node = node -> prev
	* @return : True - the element was found. False - otherwise
	*/
	bool find(const Key& key, int occurrence, iterator& it, bool forwardDirection = true);
	/**
	* Simple output method.
	* @param[in] forwardDirection : True - direction set to forward. False - otherwise
	* @param[in] out : std::ostream type.
	*/
	void show(bool forwardDirection = true, std::ostream& out = std::cout);
};

template<typename Key, typename Info>
Ring<Key, Info>::Ring() : any(nullptr) 
{}

template<typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& copy) {
	//this iterates throught copy and pushes every element to this.
	copy.iterate_through([this](iterator& x)
		{
			push(x);
			return false;
		}
	);
}

template<typename Key, typename Info>
Ring<Key, Info>::~Ring() { 
	clear(); 
}

template<typename Key, typename Info>
template<typename ToDo>
bool Ring<Key, Info>::iterate_through(ToDo method, bool forwardDirection) const {
	if (empty())
		return false;
	iterator x = begin();
	if (forwardDirection) {
		do {
			if (method(x)) {
				return true;
			}
			x++;
		} while (x != begin());
	}
	else {
		do {
			if (method(x)) {
				return true;
			}
			x--;
		} while (x != begin());
	}
	return false;
}

template<typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info>& copy) {
	if (this != &copy) {
		clear();
		copy.iterate_through([this](iterator& x)
			{
				push(x);
				return false;
			}
		);
	}
	return *this;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::operator==(const iterator& it) const {
	return it == *this;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::operator!=(const iterator& it) const {
	return it != *this;
}

template<typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin() const {
	return iterator(any, this);
}

template<typename Key, typename Info>
bool Ring<Key, Info>::empty() const {
	return any == nullptr;
}

template<typename Key, typename Info>
void Ring<Key, Info>::clear() {
	if (!empty()) {
		Node* curr = any;
		//classic ring loop
		do {
			Node* cache = curr;
			curr = curr->next;
			delete cache;
		} while (curr != any);
		//assagning any to nullptr
		any = nullptr;
	}
}

template<typename Key, typename Info>
void Ring<Key, Info>::push(const Key& k, const Info& i) {
	//in case of the first element
	if (any == nullptr) {
		Node* element = new Node(k, i);
		//creating a new any
		any = element;
		//node is by default linked to itself so i dont need to do anything
	}
	else {
		Node* element = new Node(k, i, any, any->prev);
		//link the element at the first spot
		any->prev->next = element;
		any->prev = element;
	}
}

template<typename Key, typename Info>
void Ring<Key, Info>::push(const iterator& it) {
	push(it.getKey(), it.getInfo());
}

template<typename Key, typename Info>
bool Ring<Key, Info>::push_after(const Key& k, const Info& i, const Key& key, int occurrence) {
	iterator x;
	if (find(key, occurrence, x)) {
		Node* element = new Node(k, i, x.current->next, x.current);
		x.current->next->prev = element;
		x.current->next = element;
        return true;
	}
	else {
		return false;
	}
}

template<typename Key, typename Info>
bool Ring<Key, Info>::push_after(const iterator& it, const Key& key, int occurrence) {
	if (!it.isNull())
		return push_after(it.getKey(), it.getInfo(), key, occurrence);
	return false;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::push_after(const iterator& it, const iterator& ringElement) {
	if (ringElement == *this and !it.isNull()) {
		Node* element = new Node(it.getKey(), it.getInfo(), ringElement.current->next, ringElement.current);
		ringElement.current->next->prev = element;
		ringElement.current->next = element;
		return true;
	}
	return false;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::push_before(const Key& k, const Info& i, const Key& key, int occurrence) {
	iterator x;
	if (find(key, occurrence, x)) {
		Node* element = new Node(k, i, x.current, x.current->prev);
		x.current->prev->next = element;
		x.current->prev = element;
		return true;
	}
	else {
		return false;
	}
}

template<typename Key, typename Info>
bool Ring<Key, Info>::push_before(const iterator& it, const Key& key, int occurrence) {
	if (!it.isNull())
		return push_before(it.getKey(), it.getInfo(), key, occurrence);
	return false;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::push_before(const iterator& it, const iterator& ringElement) {
	if (ringElement == *this and !it.isNull()) {
		Node* element = new Node(it.getKey(), it.getInfo(), ringElement.current, ringElement.current->prev);
		ringElement.current->prev->next = element;
		ringElement.current->prev = element;
		return true;
	}
	return false;
}
template<typename Key, typename Info>
bool Ring<Key, Info>::remove(const iterator& it) {
	//here we are checking few critical conditions
	//the third one is checking if iterator is a member of a given Ring
	if (empty() or it.isNull() or it != *this) {
		return false;
	}
	else {
		//we do need to take care of the any pointer in case we want to delete it
		if (it.current == any) {
			//if it is the only remaining element
			if (any->next == any) {
				delete any;
				any = nullptr;
				return true;
			}
			else {
				//otherwise we should just move it
				any = any->next;
			}
		}
		//changing the links
		it.current->prev->next = it.current->next;
		it.current->next->prev = it.current->prev;
		//deleting the node
		delete it.current;
		//in case someone would like to reuse the iterator
		it.current = nullptr;
        return true;
	}
}

template<typename Key, typename Info>
bool Ring<Key, Info>::find(const Key& key, int occurrence, iterator& it, bool forwardDirection) {
	if (occurrence <= 0) {
		return false;
	}
	int localOccurrence = 0;
	if (iterate_through([&localOccurrence, &occurrence, &key, &it](iterator& x)
		{
			if (x.getKey() == key) {
				if (--occurrence == 0) {
					it = x;
					return true;
				}
				localOccurrence++;
			}
			return false;
		},
		forwardDirection))
	{
		//we did find a key with a given occurrance
		return true;
	}
		//if occurrence and localOccurrence is not equal zero it means that we have found at least one key but not enought keys
		if (occurrence != 0 and localOccurrence != 0) {
			int cache = occurrence & localOccurrence;
			//if zero the occurrance is equal to local occurrance and in this case we want last element.
			//that is why we are not changing local occurrence in this case.
			if (cache != 0) {
				localOccurrence = cache;
			}
			if (iterate_through([&localOccurrence, &key, &it](iterator& x)
				{
					if (x.getKey() == key) {
						if (--localOccurrence == 0) {
							it = x;
							return true;
						}
					}
					return false;
				},
				forwardDirection))
			{
				return true;
			}
		}
		return false;
}

template<typename Key, typename Info>
void Ring<Key, Info>::show(bool forwardDirection, std::ostream& out) {
	iterate_through([&out](iterator& x)
		{
			out << "Key: " << x.getKey() << ", info: " << x.getInfo() << std::endl;
			return false;
		},
		forwardDirection
		);
}
