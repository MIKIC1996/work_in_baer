#pragma once
#include "stack_interface.h"


template<typename Elem>
class sequence_stored_stack :public stack_interface<Elem> {
public:
	static constexpr int __size = 1024;


	sequence_stored_stack() {
		init();
	}

	virtual void init() {
		memset(_data, 0, __size);
		_top_index = 0;
	}
	virtual void destory() {
		//如果使用堆存放数组，需要在这里释放空间
	}

	void print() {
		for (int i = 0; i < this->size(); ++i) {
			std::cout << _data[i] << "  ";
		}
		std::cout << std::endl;
	}

	virtual void clear() {
		if (std::is_trivially_destructible<Elem>::value) { //无关仅要的析构函数
			init();
		}
		else {
			while (this->size()) {
				this->pop();
			}
		}
	}

	virtual std::size_t size() {
		return _top_index;
	}


	virtual bool isEmpty() {
		return _top_index == 0;
	}

	virtual Elem& top() {
		assert(!this->isEmpty());
		return _data[_top_index-1];
	}

	virtual void push(const Elem& e) {
		assert(this->size() < __size);
		_data[_top_index] = e;
		++_top_index;
	}

	virtual void pop() {
		assert(!this->isEmpty());
		pop_trivally_dctor(std::bool_constant<std::is_trivially_destructible<Elem>::value>());
	}

private:
	void pop_trivally_dctor(std::true_type) {
		_data[_top_index - 1].~Elem();
		pop_trivally_dctor(std::false_type());
	}

	void pop_trivally_dctor(std::false_type) {
		memset(&_data[_top_index - 1], 0, sizeof(Elem));
		--_top_index;
	}

private:
	Elem _data[__size];
	int _top_index;
};
