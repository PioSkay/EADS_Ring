#include"Lab2.h"

template<typename Key, typename Info>
void removeALLElements(Ring<Key, Info>& r) {
	auto it = r.begin();
	while (!r.empty()) {
		r.remove(it++);
	} 
}

template <typename Key, typename Info>
Ring <Key, Info> split(Ring <Key, Info>& r, const Key& startKey, int startOccurance, 
	const Key& endKey, int endOccurance,
	bool direction) 
{
	typename Ring<Key, Info>::iterator start;
	typename Ring<Key, Info>::iterator end;
	Ring<Key, Info> local;
	if (!r.find(startKey, startOccurance, start)) {
		throw "Start element not found!";
	}
	if (startKey == endKey and startOccurance == endOccurance) {
		end = start; 
	}
	else {
		if (!r.find(endKey, endOccurance, end)) {
			throw "End element not found!";
		}
	}
	//remark about the ++start and --start
	//i can do it because i know that: elements exists
	//if there are no elements in between the following condition (start == end) will be satisfied
	//what about end and start pointing to the same element?
	//I am outputting all of the elements except for the end-start element
	//I hope that I understood the concept properly
	if (direction) {
		++start;
		//the last element here is going to be end + 1 because we do not want to copy start or end.
		while (start != end) {
			local.push(start);
			r.remove(start++);
		}
	}
	else {
		--start;
		while (start != end) {
			local.push(start);
			r.remove(start--);
		}
	}
	return local;
}

int testing() {
	std::cout << "---Testing find:" << std::endl;
	{
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		std::cout << "\nTEST 1: Finding an element." << std::endl;
		std::cout << "Ring content: " << std::endl;
		a.show();
		std::cout << "We are looking for key 11 and occ 2." << std::endl;
		Ring<int, int>::iterator x;
		if (!a.find(11, 2, x)) {
			return false;
		}
		else {
			std::cout << "Element found! Info: " << *x << std::endl;
		}
	}
	{
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		std::cout << "\nTEST 2: Finding an element different direction." << std::endl;
		std::cout << "Ring content: " << std::endl;
		a.show();
		std::cout << "We are looking for key 11, occ 2 and direction backwards." << std::endl;
		Ring<int, int>::iterator x;
		if (!a.find(11, 2, x, false)) {
			return false;
		}
		else {
			std::cout << "Element found! Info: " << *x << std::endl;
		}
	}
	{
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		std::cout << "\nTEST 3: Finding an element different direction." << std::endl;
		std::cout << "Ring content: " << std::endl;
		a.show();
		std::cout << "We are looking for key 11, occ INT_MAX and direction backwards." << std::endl;
		Ring<int, int>::iterator x;
		if (!a.find(11, INT_MAX, x, false)) {
			return false;
		}
		else {
			std::cout << "Element found! Info: " << *x << std::endl;
		}
	}
	std::cout << "\n\n---Testing remove:" << std::endl;
	{
		std::cout << "\nTEST 1: Trying to remove iterator from from Ring b in Ring a." << std::endl;
		std::cout << "Ring a content: " << std::endl;
		Ring<int, int> a; a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		a.show();
		std::cout << "Ring b content: " << std::endl;
		Ring<int, int> b; b.push(33, 0);
		b.show();
		Ring<int, int>::iterator x = b.begin();
		if (a.remove(x)) {
			return false;
		}
	}
	{
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		std::cout << "\nTEST 2: Removing an iterator." << std::endl;
		std::cout << "Ring content before: " << std::endl;
		a.show();
		Ring<int, int>::iterator x = a.begin();
		if (!a.remove(x)) {
			return false;
		}
		std::cout << "Ring content after: " << std::endl;
		a.show();
	}
	{
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		std::cout << "\nTEST 3 & Task todo: Removing all elements using removeAllElements() == iterators and build in methods" << std::endl;
		std::cout << "Ring content before: " << std::endl;
		a.show();
		removeALLElements(a);
		std::cout << "Ring content after: " << std::endl;
		a.show();
	}
	std::cout << "\n\n---Assign operator:" << std::endl;
	{
		std::cout << "\nTEST 1: Simple b = a" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		std::cout << "a content: " << std::endl;
		a.show();
		Ring<int, int> b;
		b = a;
		std::cout << "b content: " << std::endl;
		b.show();
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 2: Simple a = a" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		std::cout << "a content: " << std::endl;
		a.show();
		std::cout << std::endl;
	}
	std::cout << "\n\n---push_after:" << std::endl;
	{
		std::cout << "\nTEST 1: Adding element after the head." << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		a.push_after(12, 12, 33);
		std::cout << "a content: " << std::endl;
		a.show();
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 2: Adding iterator value after iterator of a Ring" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		Ring<int, int> b;
		b.push(42, 12);
		if (!a.push_after(b.begin(), ++a.begin())) {
			return false;
		}
		std::cout << "a content: " << std::endl;
		a.show();
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 3: Adding iterator value after iterator of a incorrect Ring" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		Ring<int, int> b;
		b.push(42, 12);
		if (a.push_after(b.begin(), ++b.begin())) {
			return false;
		}
		else {
			std::cout << "push_after returned false!" << std::endl;
		}
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 4: Adding nullptr iterator after iterator of a Ring" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		if (a.push_after(Ring<int, int>::iterator(), ++a.begin())) {
			return false;
		}
		else {
			std::cout << "push_after returned false!" << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n---push_before:" << std::endl;
	{
		std::cout << "\nTEST 1: Adding element before the head." << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		a.push_before(15, 15, 33);
		std::cout << "a content: " << std::endl;
		a.show();
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 2: Adding iterator value before iterator of a Ring" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		Ring<int, int> b;
		b.push(53, 12);
		if (!a.push_before(b.begin(), ++a.begin())) {
			return false;
		}
		std::cout << "a content: " << std::endl;
		a.show();
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 3: Adding iterator value before iterator of a incorrect Ring" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		Ring<int, int> b;
		b.push(42, 12);
		if (a.push_before(b.begin(), ++b.begin())) {
			return false;
		}
		else {
			std::cout << "push_befor returned false!" << std::endl;
		}
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 4: Adding nullptr iterator before iterator of a Ring" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		if (a.push_after(Ring<int, int>::iterator(), ++a.begin())) {
			return false;
		}
		else {
			std::cout << "push_before returned false!" << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n---iterators:" << std::endl;
	{
		std::cout << "\nTEST 1: Accessing every element info with do-while" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		Ring<int, int>::iterator x = a.begin();
		do {
			std::cout << *x << std::endl;
			x++;
		} while (x != a.begin());
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 2: Accessing every element info of a const Ring with do-while" << std::endl;
		Ring<int, int> a;
		a.push(33, 0);  a.push(11, 1); a.push(12, 2); a.push(11, 3); a.push(12, 4); a.push(13, 5); a.push(14, 6); a.push(15, 7);
		const Ring<int, int> b = a;
		const Ring<int, int>::iterator x = b.begin();
		do {
			std::cout << *x << std::endl;
			x++;
		} while (x != b.begin());
		std::cout << std::endl;
	}
	{
		std::cout << "\nTEST 3: Quality operators with Ring and Iterators." << std::endl;
		Ring<int, int> a;
		a.push(33, 0);
		Ring<int, int>::iterator b = a.begin();
		if (a != b) {
			return false;
		}
		else {
			std::cout << "Expresion a != b returned false\nIterator belong to the Ring." << std::endl;
		}
		if (b != a) {
			return false;
		}
		else {
			std::cout << "Expresion b != a returned false\nIterator belong to the Ring." << std::endl;
		}
	}
	{
		std::cout << "\nTEST 4: Trying to move an empty iterator." << std::endl;
		Ring<int, int>::iterator x;
		bool isExc = false;
		try {
			x++;
		}
		catch (const char* x) {
			std::cout << "A following exception was generated:\n" << x << std::endl;
			isExc = true;
		}
		if (!isExc) {
			return false;
		}
	}
	std::cout << "\n\n---split method:" << std::endl;
	{
		std::cout << "\nTEST 1: Example from the lecture." << std::endl;
		Ring<int, int> a;
		a.push(1, 1);  a.push(2, 2); a.push(3, 3); a.push(2, 2); a.push(2, 2);
		try {
			Ring<int, int> b = split(a, 2, 1, 2, 3, true);
			std::cout << "a content: " << std::endl;
			a.show();
			std::cout << "b content: " << std::endl;
			b.show();
		}
		catch (const char* er) {
			std::cout << er;
			return false;
		}
	}
	{
		std::cout << "\nTEST 2: Example from the lecture with a differen direction." << std::endl;
		Ring<int, int> a;
		a.push(1, 1);  a.push(2, 2); a.push(3, 3); a.push(2, 2); a.push(2, 2);
		try {
			Ring<int, int> b = split(a, 2, 1, 2, 3, false);
			std::cout << "a content: " << std::endl;
			a.show();
			std::cout << "b content: " << std::endl;
			b.show();
		}
		catch (const char* er) {
			std::cout << er;
			return false;
		}
	}
	{
		std::cout << "\nTEST 3: Elements points to the same node." << std::endl;
		Ring<int, int> a;
		a.push(1, 1);  a.push(2, 2); a.push(3, 3); a.push(2, 2); a.push(2, 2);
		std::cout << "direction true:" << std::endl;
		try {
			Ring<int, int> b = split(a, 2, 1, 2, 1, true);
			std::cout << "a content: " << std::endl;
			a.show();
			std::cout << "b content: " << std::endl;
			b.show();
		}
		catch (const char* er) {
			std::cout << er;
			return false;
		}
	}
	{
		Ring<int, int> a;
		a.push(1, 1);  a.push(2, 2); a.push(3, 3); a.push(2, 2); a.push(2, 2);
		std::cout << "direction false:" << std::endl;
		try {
			Ring<int, int> b = split(a, 2, 1, 2, 1, false);
			std::cout << "a content: " << std::endl;
			a.show();
			std::cout << "b content: " << std::endl;
			b.show();
		}
		catch (const char* er) {
			std::cout << er;
			return false;
		}
	}
	{
		std::cout << "\nTEST 4: Element does not exist." << std::endl;
		Ring<int, int> a;
		a.push(1, 1);  a.push(2, 2); a.push(3, 3); a.push(2, 2); a.push(2, 2);
		try {
			Ring<int, int> b = split(a, 10, 1, 2, 1, true);
		}
		catch (const char* er) {
			std::cout << "Following exception was generated:" << std::endl;
			std::cout << er << std::endl;
		}

	}
	return true;
}
int main()
{
	if (testing()) {
		std::cout << "All test are correct." << std::endl;
	}
}