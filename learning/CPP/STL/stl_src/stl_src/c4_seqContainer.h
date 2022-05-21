#pragma once


#include "stdafx.h"
#include "c3_iterator.h"


namespace jmq_std {


	template<class T>
	struct __list_node {

		typedef void* void_pointer;

		void_pointer prev;
		void_pointer next;
		T data;
	};

	template <class T,class Ref,class Ptr>
	struct __list_iterator {

		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, Ref, Ptr> self;

		typedef BidirectionalIterator iterator_categoty;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef __list_node<T>* link_type;


		link_type node;

		__list_iterator(link_type n) :node(n) {}

		bool operator==(const self& x)const { return node == x.node; }
		bool operator!=(const self& x)const { return node != x.node; }
		reference operator*()const { return (*node).data; }
		pointer operator->() { return &operator*(); }
		self& operator++() {
			node = (link_type)((*node).next);
			return *this;
		}
		
		self& operator++(int) {
			self tmp = *this;
			++ *this;
			return tmp;
		}

		self& operator--() {
			node = (link_type)((*node).prev);
			return *this;
		}

		self& operator()(int) {
			self tmp = *this;
			-- *this;
			return tmp;
		}


		//list
		template<class T ,class alloc>
		class list { //��״˫������
		public:
			typedef __list_node<T> list_node;
			typedef list_node* link_type;
			typedef __list_iterator<T, T&, T*> iterator;

			typedef size_t size_type;
			typedef T& reference;

			iterator begin() { return (link_type)(node->next); }
			iterator end() { return node; }

			bool empty()const {
				return node->next == node;
			}

			size_type size()const {
				size_type res;
				std::distance(begin(), end(), res);	
				return res;
			}

			reference front() {
				return *begin();
			}

			reference back() {
				return *(--end());
			}
			
		protected:
			link_type node;
		};




	};



}