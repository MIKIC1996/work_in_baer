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



	//�̳�Line_table
	//��ĳ�ʼ��
	virtual void init() {
		for (int i = 0; i < max_length; ++i) {
			_buffer[i]._next = i + 1; //��һ���ڵ��nextָ�� ���Բ������ݵĽڵ�
		}
		_buffer[max_length - 1]._next = 0; //���һ���ڵ�ָ�� �����ݵĵ�һ���ڵ�,��ʼ����ʱ��,��ָ��գ�Ҳ����0
	}

	//�Ƿ�Ϊ��
	virtual bool isEmpty() {
		return this->size() == 0;
	}

	//��ǰ����
	virtual std::size_t size() {
		int count = 0;
		int start_index = _buffer[max_length - 1]._next;//��һ�����ݽڵ�

		while (start_index != 0) {
			++count;
			start_index = _buffer[start_index]._next;
		}
		return count;
	}

	//���
	virtual void clear() {
		int size = this->size();
		for (int i = 0; i < size; ++i) { 
			this->deleteElem(0); 
		}
	}

	//���ݲ���
	virtual void insert(int i, Elem data)
	{
		if (i < 0 || i > this->size()) {
			assert(false);
		}
		//����һ���¿ռ�
		int index_can_insert = this->malloc_ssl();
		_buffer[index_can_insert]._data = data;


		int start_index = max_length - 1; //������㣬�����һ���ڵ㿪ʼ��������Ϊ�� -1�±� �㣬��Ϊ��ָ�����0�±��

		//start �� start_index ���Ӧ�� start���߼��±꣬start_index ����ʵ�±꣬���ǰ� _buffer[max_lengtn-1]Ҳ�ɿ�����һ��Ԫ�أ���������������Ͳ�����Ϊ��
		for (int start = -1; start != i - 1; ++start) { //������Ҫ�ҵ�������Ҫ���Ǹ�Ԫ�ص�ǰһ��Ԫ��
			start_index = _buffer[start_index]._next;
		}

		int current_next = _buffer[start_index]._next;//��¼ǰһ��Ԫ�صĺ����
		_buffer[start_index]._next = index_can_insert; //�޸�ǰһ��Ԫ�صĺ����
		_buffer[index_can_insert]._next = current_next; //�޸Ĳ���Ԫ�صĺ����

	}

	//����ɾ��
	virtual void deleteElem(int i) {
		if (i < 0 || i >= this->size()) {
			assert(false);
		}

		int start_index = max_length - 1;
		for (int start = -1; start != i - 1; ++start) { //�ҵ�ǰһ��Ԫ��
			start_index = _buffer[start_index]._next;
		}
		//�ҵ���ǰԪ��
		int target_index = _buffer[start_index]._next;
		//�ҵ����Ԫ���±�
		int next_index = _buffer[target_index]._next;

		//��ǰһ��Ԫ�ص� _next�ĳɺ��Ԫ�ص�
		_buffer[start_index]._next = next_index;
		free_ssl(target_index);
	}

	//���ݲ�ѯ
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

	//���ݶ�λ
	virtual int locateElem(Elem data) {
		
		//�����������ݼ�
		int start_index = max_length - 1;
		for (int start = -1; start != this->size() - 1; ++start) {
			if (_buffer[start_index]._data == data && start_index != max_length-1) { //��������
				return start;
			}
			start_index = _buffer[start_index]._next;
		}
		assert(false);
		return 0;
	}

private:
	//����һ���¿ռ����
	int malloc_ssl() {
		int index_can_insert = _buffer[0]._next;
		int index_can_next_insert = _buffer[index_can_insert]._next;
		_buffer[0]._next = index_can_next_insert;
		return index_can_insert;
	}

	//���ռ䷵������ͷ�巨��������ռ���� ��������� ��λ
	void free_ssl(int i) {
		if (i < 0 || i >= max_length)return;
		int ord_first_free = _buffer[0]._next;
		_buffer[0]._next = i;
		_buffer[i]._next = ord_first_free;
	}

	Node _buffer[max_length];
};

