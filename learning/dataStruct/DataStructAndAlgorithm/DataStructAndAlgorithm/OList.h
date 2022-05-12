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

	//�̳�Line_table
	//��ĳ�ʼ��
	virtual void init() {
		_root = new Node{ Elem(),nullptr };
	}

	//�Ƿ�Ϊ��
	virtual bool isEmpty()
	{
		return this->size() == 0;
	}

	//��ǰ����
	virtual std::size_t size() {
		Node* start = _root;
		std::size_t count = 0;
		while (start->_next) {
			++count;
			start = start->_next;
		}
		return count;
	}

	//���
	virtual void clear() {
		int size = this->size();
		for (int i = 0; i < size; ++i) {
			deleteElem(0);
		}
	}

	//���ݲ���
	virtual void insert(int i, Elem data) {
		if (i < 0 || i > this->size()) {
			assert(false);
		}
		Node* newOne = new Node{ data,nullptr };

		Node* start = _root;
		for (int index = -1; index != i -1; ++index) { // �ҵ�ǰһ��Node
			start = _root->_next;
		}
		Node* origin_next_node = start->_next;
		start->_next = newOne;
		newOne->_next = origin_next_node;
	}

	//����ɾ��
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

	//���ݲ�ѯ
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
	
	//���ݶ�λ
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

