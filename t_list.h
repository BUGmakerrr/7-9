#pragma once

namespace bit
{
	template<class T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;

		__list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		Node* _node;

		__list_iterator(Node* node)
			:_node(node)
		{}

		// *it
		T& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &_node->_data;
		}

		// ++it;
		__list_iterator<T>& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		// it++
		__list_iterator<T> operator++(int)
		{
			__list_iterator<T> tmp(*this);
			//_node = _node->_next;
			++(*this);

			return tmp;
		}

		__list_iterator<T>& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		__list_iterator<T> operator--(int)
		{
			__list_iterator<T> tmp(*this);
			//_node = _node->_prev;
			--(*this);

			return tmp;
		}

		// it != end()
		bool operator!=(const __list_iterator<T>& it)
		{
			return _node != it._node;
		}

		bool operator==(const __list_iterator<T>& it)
		{
			return _node == it._node;
		}
	};

	template<class T>
	class list
	{
		typedef __list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		// 思考const_iterator是如何实现，提示：可以去分析一下原代码
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		// 带头双向循环链表
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		//list(const list<T>& lt);
		//list<T>& operator=(const list<T>& lt);
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		void push_back(const T& x)
		{
			Node* tail = _head->_prev;
			Node* newnode = new Node(x);
			
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}

		void pop_back();
		void push_front(const T& x);
		void pop_front();

		void insert(iterator pos, const T& x);
		void erase(iterator pos);
	private:
		Node* _head;
	};

	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++ it;
		}
		cout << endl;
	}

	struct Date
	{
		int _year = 0;
		int _month = 1;
		int _day = 1;
	};

	void test_list2()
	{
		int* p1 = new int;
		*p1;
		Date* p2 = new Date;
		*p2;
		p2->_year;

		list<Date> lt;
		lt.push_back(Date());
		lt.push_back(Date());

		list<Date>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//cout << *it << " ";
			cout << it->_year << "-" << it->_month << "-" << it->_day << endl; // 更喜欢这么用
			cout << (*it)._year << "-" << (*it)._month << "-" << (*it)._day << endl;

			++it;
		}
		cout << endl;
	}
}