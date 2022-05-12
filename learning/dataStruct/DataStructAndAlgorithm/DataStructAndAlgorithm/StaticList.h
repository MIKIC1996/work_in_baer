#pragma once


#include "line_table_interface.h"


template<typename Elem>
class StaticList :public Line_table<Elem>
{
public:

	struct Node {
		Elem _data;
		int _next;
	};

	static constexpr int max_length = 1024;

	//ctor
	StaticList() {}
	//detor
	virtual ~StaticList() {}

	void print() {
		int size = this->size();
		for (int i = 0; i < size; ++i) {
			std::cout << this->getElem(i) << std::endl;
		}
		
	}

	void push_front(const Elem& data) {
		this->insert(0, data);
	}

	void push_back(const Elem& data) {
		this->insert(this->size(), data);
	}

	void pop_front() {
		this->deleteElem(0);
	}

	void pop_back() {
		this->deleteElem(this->size() - 1);
	}

	Elem& operator[](int i) {
		return this->getElem(i);
	}

	void operator<<(const Elem& data) {
		this->push_back(data);
	}

	void operator>>(const Elem& data) {
		int i = this->locateElem(data);
		this->deleteElem(i);
	}



	//继承Line_table
	//表的初始化
	virtual void init() {
		for (int i = 0; i < max_length; ++i) {
			_buffer[i]._next = i + 1; //第一个节点的next指向 可以插入数据的节点
		}
		_buffer[max_length - 1]._next = 0; //最后一个节点指向 有数据的第一个节点,初始化的时候,他指向空，也就是0
	}

	//是否为空
	virtual bool isEmpty() {
		return this->size() == 0;
	}

	//当前长度
	virtual std::size_t size() {
		int count = 0;
		int start_index = _buffer[max_length - 1]._next;//第一个数据节点

		while (start_index != 0) {
			++count;
			start_index = _buffer[start_index]._next;
		}
		return count;
	}

	//清空
	virtual void clear() {
		int size = this->size();
		for (int i = 0; i < size; ++i) { 
			this->deleteElem(0); 
		}
	}

	//数据插入
	virtual void insert(int i, Elem data)
	{
		if (i < 0 || i > this->size()) {
			assert(false);
		}
		//申请一块新空间
		int index_can_insert = this->malloc_ssl();
		_buffer[index_can_insert]._data = data;


		int start_index = max_length - 1; //遍历起点，从最后一个节点开始，可以认为是 -1下标 点，因为他指向的是0下标点

		//start 和 start_index 相呼应， start是逻辑下标，start_index 是真实下标，我们吧 _buffer[max_lengtn-1]也可看做是一个元素，这样，这个容器就不可能为空
		for (int start = -1; start != i - 1; ++start) { //我们需要找到我们需要的那个元素的前一个元素
			start_index = _buffer[start_index]._next;
		}

		int current_next = _buffer[start_index]._next;//记录前一个元素的后继者
		_buffer[start_index]._next = index_can_insert; //修改前一个元素的后继者
		_buffer[index_can_insert]._next = current_next; //修改插入元素的后继者

	}

	//数据删除
	virtual void deleteElem(int i) {
		if (i < 0 || i >= this->size()) {
			assert(false);
		}

		int start_index = max_length - 1;
		for (int start = -1; start != i - 1; ++start) { //找到前一个元素
			start_index = _buffer[start_index]._next;
		}
		//找到当前元素
		int target_index = _buffer[start_index]._next;
		//找到后继元素下标
		int next_index = _buffer[target_index]._next;

		//将前一个元素的 _next改成后继元素的
		_buffer[start_index]._next = next_index;
		free_ssl(target_index);
	}

	//数据查询
	virtual Elem& getElem(int i) {
		if (i < 0 || i >= this->size() ) {
			assert(false);
		}
		int start_index = max_length - 1;
		for (int start = -1; start != i; ++start) {
			start_index = _buffer[start_index]._next;
		}
		return _buffer[start_index]._data;
	}

	//数据定位
	virtual int locateElem(Elem data) {
		
		//遍历现有数据集
		int start_index = max_length - 1;
		for (int start = -1; start != this->size() - 1; ++start) {
			if (_buffer[start_index]._data == data && start_index != max_length-1) { //符合条件
				return start;
			}
			start_index = _buffer[start_index]._next;
		}
		assert(false);
		return 0;
	}

private:
	//申请一个新空间出来
	int malloc_ssl() {
		int index_can_insert = _buffer[0]._next;
		int index_can_next_insert = _buffer[index_can_insert]._next;
		_buffer[0]._next = index_can_next_insert;
		return index_can_insert;
	}

	//将空间返还，用头插法，将这个空间插入 空闲链表的 首位
	void free_ssl(int i) {
		if (i < 0 || i >= max_length)return;
		int ord_first_free = _buffer[0]._next;
		_buffer[0]._next = i;
		_buffer[i]._next = ord_first_free;
	}

	Node _buffer[max_length];
};

