#pragma once



#include "line_table_interface.h"

template<typename Elem>
class OList : public Line_table<Elem>
{
public:
	
	struct Node {
		Elem _data;
		Node* _next;
	};

	OList() {
		this->init();
	}

	virtual ~OList() {}


	void print() {   
		for (int i = 0; i < this->size(); ++i) {   
			std::cout << this->getElem(i) << std::endl;   
		}   
	}   

	//继承Line_table
	//表的初始化
	virtual void init() {
		_root = new Node{ Elem(),nullptr };
	}

	//是否为空
	virtual bool isEmpty()
	{
		return this->size() == 0;
	}

	//当前长度
	virtual std::size_t size() {
		Node* start = _root;
		std::size_t count = 0;
		while (start->_next) {
			++count;
			start = start->_next;
		}
		return count;
	}

	//清空
	virtual void clear() {
		int size = this->size();
		for (int i = 0; i < size; ++i) {
			deleteElem(0);
		}
	}

	//数据插入
	virtual void insert(int i, Elem data) {
		if (i < 0 || i > this->size()) {
			assert(false);
		}
		Node* newOne = new Node{ data,nullptr };

		Node* start = _root;
		for (int index = -1; index != i -1; ++index) { // 找到前一个Node
			start = _root->_next;
		}
		Node* origin_next_node = start->_next;
		start->_next = newOne;
		newOne->_next = origin_next_node;
	}

	//数据删除
	virtual void deleteElem(int i) {
		if (i < 0 || i >= this->size()) {
			assert(false);
		}
		Node* start = _root;
		for (int index = -1; index != i - 1; ++index) {
			start = start->_next;
		}
		Node* target = start->_next;
		start->_next = target->_next;
		delete target;
	}

	//数据查询
	virtual Elem& getElem(int i) {
		if (i < 0 || i >= this->size()) {
			assert(false);
		}

		Node* start = _root;
		for (int index = -1; index != i ; ++index) {
			start = start->_next;
		}
		return start->_data;

	}
	
	//数据定位
	virtual int locateElem(Elem data) {
		
		Node* start = _root;
		for (int index = -1; index != this->size() - 1; ++index) {
			if (start->_data == data && start != _root) {
				return index;
			}
			start = start->_next;
		}
		assert(false);
	}

private:
	Node* _root;

};

