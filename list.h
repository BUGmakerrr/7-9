#pragma once

namespace Frish{
	template<class T> struct __list_node{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;
	};
	template<class T> struct __list_iterator{
		typedef __list_node<T> Node;
		Node* _node;
		__list_iterator(Node node)
			:_node(node)
		{}
		T& operator*(){
			return _node->_data;
		}
		T& operator++(){
			_node = _node->_next;
		}
		__list_node<T> operator++(){
			_node = _node->next;
			return *this;
		}
		bool operator!=(__list_iterator<T>& it){
			return _node != it->_node;
		}
	};
	template<class T> class list{
		typedef __list_node<T> Node;
	public:
		list(){
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		void push_back(const T& x){
			Node* _tail = _head->_prev;
			Node* newnode = new Node(x);
			_tail->_next = newnode;
			newnode->_prev = _tail;
			newnode->_next = _head;
			_head->_prev = _tail;


		}
	private:
		Node* _head;
	};
}
