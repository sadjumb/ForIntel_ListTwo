#include <iostream>

template <class T> class list;

template <class T>
class Node 
{
private:
	Node(const T & x) : _value(x), _next(nullptr), _prev(nullptr) {}

	T			_value;
	Node<T>		*_next;
	Node<T>		*_prev;

	friend class	list<T>;
};

template <class T>
class list
{
public:
	list() : _head(nullptr), _tail(nullptr), _size(0) {}
	list(list &l)
	{
		*this = l;
	}
	
	~list()
	{
		while (this->_size)
		{
			this->pop_front();
		}
	}

	list			&operator =(const list &l)
	{
		Node<T>		*temp = l._head;

		if (this != &l)
		{
			this->~list();
			while (temp)
			{
				this->push_back(temp->_value);
				temp = temp->_next;
			}
		}
		return (*this);
	}

	void			push_front(T value)
	{
		Node<T>* node = new Node<T>(value);

		if(this->_head)
			this->_head->_prev = node;
		node->_next = this->_head;
		this->_head = node;
		if (!this->_tail)
			this->_tail = this->_head;
		++this->_size;
	}

	void			push_back(T value)
	{
		Node<T>		*node = new Node<T>(value);
		
		if (this->_tail)
			this->_tail->_next = node;
		node->_prev = this->_tail;
		this->_tail = node;
		if (!this->_head)
			this->_head = this->_tail;
		++this->_size;
	}

	void			pop_front()
	{
		Node<T>		*next = (this->_head) ? this->_head->_next : nullptr;

		if (this->_head)
		{
			delete this->_head;
			this->_head = next;
			if (!next)
				this->_tail = nullptr;
			else
				next->_prev = nullptr;
			--this->_size;
		}
	}

	void 			pop_back()
	{
		Node<T>		*prev = (this->_tail) ? this->_tail->_prev : nullptr;

		if (this->_tail)
		{
			delete this->_tail;
			this->_tail = prev;
			if (!prev)
				this->_head = nullptr;
			else
				prev->_next = nullptr;
			--this->_size;
		}
	}

	const T			&front() const
	{
		return (this->_head) ? this->_head->_value : nullptr;
	}

	const T			&back() const
	{
		return (this->_tail) ? this->_tail->_value : nullptr;
	}

	template <class Predicate>
	void			remove_if(Predicate pred)
	{
		Node<T>		*temp = this->_head;
		Node<T>		*copy = nullptr;

		while (temp)
		{
			if (pred(temp->_value))
			{
				copy = temp->_next;
				if (temp->_prev)
					temp->_prev->_next = temp->_next;
				if (temp->_next)
					temp->_next->_prev = temp->_prev;
				if (temp == this->_head)
					this->_head = copy;
				if (temp == this->_tail)
					this->_tail = temp->_prev;
				delete temp;
				temp = copy;
				--this->_size;
			}
			else
				temp = temp->_next;
		}
	}

	void			remove_if_equal(T k)
	{
		this->remove_if([&k](T n) { return (n == k); });
	}

	std::size_t		size()
	{
		return (this->_size);
	}

	template <class Predicate>
	void			foreach(Predicate pred)
	{
		Node<T>		*temp = this->_head;

		while (temp)
		{
			pred(temp->_value);
			temp = temp->_next;
		}
	}

private:
	Node<T>			*_head;
	Node<T>			*_tail;
	std::size_t		_size;

	template <class L>
	friend void		tricky_swap(list<L> l1, list<L> l2);
};


bool	print_pred(std::string n)
{
	std::cout << n << " ";
	return (true);
}

int 	main()
{
	//const std::size_t    size = 5;
	//list<int>            li;

	//for (size_t i(0); i < size; ++i)
	//{
	//	li.push_front(i);
	//}

	//li.foreach(print_pred);
	//std::cout << std::endl;

	//li.push_back(1);
	//li.foreach(print_pred);
	//std::cout << std::endl;

	//li.push_back(1921);
	//li.foreach(print_pred);
	//std::cout << std::endl;
	//
	//li.pop_front();
	//li.foreach(print_pred);
	//std::cout << std::endl;
	//
	//li.pop_back();
	//li.foreach(print_pred);
	//std::cout << std::endl;

	//li.push_back(333);
	//li.push_back(222);
	//li.remove_if_equal(1);
	//li.foreach(print_pred);
	//std::cout << std::endl;

	//list<int> list3 = li;
	//list3.foreach(print_pred);
	//std::cout << std::endl;
	//list3.pop_back();
	//list3.foreach(print_pred);
	//std::cout << std::endl << "lc(copy)";
	//li.foreach(print_pred);
	//list<int> lcopy(li);
	//lcopy.foreach(print_pred);
	//std::cout << std::endl;

	list<std::string> str1;
	list<std::string> str2;

	str1.push_back("Hell");
	str1.push_back("Hi");
	str1.push_back("Well");
	
	str2 = str1;

	
	return 0;
}
