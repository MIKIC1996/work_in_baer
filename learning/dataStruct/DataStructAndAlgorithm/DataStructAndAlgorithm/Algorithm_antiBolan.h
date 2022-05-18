#pragma once
#include "seq_stored_stack.h"




static int my_atoi(char const * data, std::size_t size) {
	char* sp = (char*)malloc(size + 1);
	memcpy(sp, data, size);
	sp[size] = '\0';
	int ret = atoi(sp);
	free(sp);
	return ret;
}


static bool isNum(char s) {
	return s >= 0x30 && s <= 0x39;
}

static bool isSignal(char s) {
	return s == '+' || s == '-' || s == '*' || s == '/';
}

static bool isParentheses(char s) {
	return s == '(' || s == ')';
}

static bool is_left_parenttheses(char s) {
	return s == '(';
}

static bool is_right_parenttheses(char s) {
	return s == ')';
}



struct anti_bolan_unit { //��Ԫ��������ʶһ���ַ�����������һ���������

	operator bool() {
		return _type == EMPTY;
	}

	enum  s_type{
		Num =1,
		Plus = 2,
		Minus = 3,
		Mult =4 ,
		Deri = 5,
		Lepa =6,
		Ripa = 7,
		EMPTY = 8
	};

	void print() {
		std::cout << "====unit====" << std::endl;
		for (int i = 0; i < _size; ++i) {
			std::cout << _ptr[i];
		}
		std::cout << std::endl;
		std::cout << (int)_type << "  " << _size << std::endl; ;
		
		std::cout << "------------" << std::endl;
	}

	char const * _ptr;
	int _size;
	s_type _type;
};

//���ַ����з����� ֵ �������
static anti_bolan_unit next_unit(char const *  _start, int size) {
	assert(_start && size > 0);
	char const* ptr = _start;
	bool last_is_num = false;
	for (int i = 0; i < size; ++i) {

		if (!isNum(*ptr) && last_is_num) { //֮ǰ�����֣����ڲ�����
			return anti_bolan_unit{ _start ,  i , anti_bolan_unit::Num };
		}

		if (is_left_parenttheses(*ptr)) {
			return anti_bolan_unit{ _start,1,anti_bolan_unit::Lepa };
		}
		else if (is_right_parenttheses(*ptr)) {
			return anti_bolan_unit{ _start,1,anti_bolan_unit::Ripa };
		}
		else if (isSignal(*ptr)) {
			switch (*ptr)
			{
			case '+':
				return anti_bolan_unit{ _start,1,anti_bolan_unit::Plus };
				break;
			case '-':
				return anti_bolan_unit{ _start,1,anti_bolan_unit::Minus };
				break;
			case '*':
				return anti_bolan_unit{ _start,1,anti_bolan_unit::Mult };
				break;
			case '/':
				return anti_bolan_unit{ _start,1,anti_bolan_unit::Deri };
				break;
			default:
				std::cout << *ptr << std::endl;
				assert(false);
				break;
			}
		}
		else if(isNum(*ptr)){
			last_is_num = true;
			++ptr;
		}
		else { //Υ������
			std::cout << *ptr << std::endl;
			assert(false);
		}
	}
	return anti_bolan_unit{ _start,size,anti_bolan_unit::Num };
}


//�������������˫ֵ����
static int caculate(int a, int b, anti_bolan_unit::s_type ope) {
	switch (ope)
	{
	case anti_bolan_unit::Plus:
		return a + b;
		break;
	case anti_bolan_unit::Minus:
		return a - b;
		break;
	case anti_bolan_unit::Mult:
		return a * b;
		break;
	case anti_bolan_unit::Deri:
		assert(b != 0);
		return a / b;
		break;
	default:
		assert(false);
	}
	return -1;
}


static int easy_antibolan(char const * & ptr,int& left_size) {
	
	sequence_stored_stack<int> num_stack;
	sequence_stored_stack<anti_bolan_unit::s_type> signal_stack;

	char const* start = ptr;
	int start_size = left_size;
	while (ptr != &start[start_size]) {
		anti_bolan_unit unit = next_unit(ptr, left_size);

		if (unit._type == anti_bolan_unit::Num) {
			num_stack.push(my_atoi(unit._ptr, unit._size));
			ptr += unit._size;
			left_size -= unit._size;
		}
		//�����������ֻ����ǰ����������ȣ��Ƿ����ȼ���Ȼ���ͣ�������ߣ��Ͱѷ���ѹ��ջ�������Ȼ���ͣ����������ֵ����һ���������ֵ��
		else if (unit._type == anti_bolan_unit::Plus || unit._type == anti_bolan_unit::Minus) {
			if (!signal_stack.isEmpty()) //����ջ��Ϊ�գ���ֱ��ִ�У���Ϊû�бȼӼ����ȼ����͵��������ǰ��ֻ�п����Ǹ߼�����ͬ���� ����ֻҪǰ������������Ϳ������������ֵ
			{
				int val2 = num_stack.top();
				num_stack.pop();
				int val1 = num_stack.top();
				num_stack.pop();
				num_stack.push(caculate(val1, val2, signal_stack.top()));//���������ֵ����һ��������� ֵ����ѹ��ջ
				signal_stack.pop();
			}
			signal_stack.push(unit._type);
			ptr += unit._size;
			left_size -= unit._size;
		}
		else if (unit._type == anti_bolan_unit::Mult || unit._type == anti_bolan_unit::Deri) {//�����˳���������������ȼ������������һ��ǰ����û��ͬ���ȼ����оͼ����������ֵ
			if (!signal_stack.isEmpty() && (signal_stack.top() == anti_bolan_unit::Mult || signal_stack.top() == anti_bolan_unit::Deri)) //����ջ��Ϊ�գ�����һ������Ϊͬ��
			{
				int val2 = num_stack.top();
				num_stack.pop();
				int val1 = num_stack.top();
				num_stack.pop();
				num_stack.push(caculate(val1, val2, signal_stack.top()));
				signal_stack.pop();
			}
			signal_stack.push(unit._type);
			ptr += unit._size;
			left_size -= unit._size;

		}
		else if (unit._type == anti_bolan_unit::Lepa) { //���������ţ��͵������� ���еݹ���ã������������ֵ
			ptr++;
			left_size--;
			int ret = easy_antibolan(ptr, left_size);
			num_stack.push(ret);
		}
		else if (unit._type == anti_bolan_unit::Ripa) { //���������ţ�˵��������һ�� �ӵݹ���ã��������������������Ľ������
			int ret = 0;
			assert(num_stack.size() == signal_stack.size() + 1);
			while (signal_stack.size()) {
				int val2 = num_stack.top();
				num_stack.pop();
				int val1 = num_stack.top();
				num_stack.pop();
				ret = caculate(val1, val2, signal_stack.top());
				signal_stack.pop();
				num_stack.push(ret);
			}
			ptr++;
			left_size--;
			return ret;
		}
	}
	
	int ret = 0;
	assert(num_stack.size() == signal_stack.size() + 1);
	while (signal_stack.size()) {
		int val2 = num_stack.top();
		num_stack.pop();
		int val1 = num_stack.top();
		num_stack.pop();
		ret = caculate(val1, val2, signal_stack.top());
		signal_stack.pop();
		num_stack.push(ret);
	}
	return ret;


}

























