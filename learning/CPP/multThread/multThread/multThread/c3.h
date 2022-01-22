#pragma once


#include "stdafx.h"


class easyLock{
public:
	void lock() {
		std::cout << "lock" << std::endl;
	}

	void unlock() {
		std::cout << "unlock" << std::endl;
	}

	bool tryLock() {
		std::cout << "tryLock" << std::endl;
	}
};


class AA {

public:
	//ģʽһ����ĳЩ������������ʱ����
	std::unique_lock<easyLock>  operation1(){
		lock1.lock(); //����
		unsafeOperation();
		return std::unique_lock<easyLock>(lock1, std::adopt_lock);//��������������չ��ȥ����������߲����ܣ�����uniquelock���������Զ�������
	}
	
	

	//ģʽ�� 
	//������
	std::unique_lock<easyLock>  operation2(std::unique_lock<easyLock> lock_ref) {
		

	}


private:
	void unsafeOperation() {
		std::cout << "do unsafe operation" << std::endl;
	}

	easyLock lock1;
};


//std::unique_lock��ת����������Ȩ�����������÷�Χ���󵽺����⡣
void unique_lock_test() {
	
	AA a1;
	 //a1.operation1();
	std::unique_lock<easyLock> lock(a1.operation1());

	std::cout << "end" << std::endl;
	
}


//��д��

void readWriteLockTest() {

	std::shared_mutex lk;

	std::thread t([&lk] {  std::shared_lock<std::shared_mutex>sl(lk); std::cout << "lock1" << std::endl; getchar();     });
	std::shared_lock<std::shared_mutex>sl(lk);
	std::cout << "lock1" << std::endl;
	

	std::unique_lock<std::shared_mutex>sl2(lk);
	std::cout << "lock2" << std::endl; 
	getchar();

}




//std::recursive_mutex �ݹ���
class Recursive_Test { //�ݹ���
public:

	bool isEmpty() {
		std::lock_guard<std::recursive_mutex> guard(_lock);
		return _vec.empty();
	}

	
	int* getFirst() {
		std::lock_guard<std::recursive_mutex> guard(_lock);
		if (isEmpty()) { //�������������������˼�����,��Ҫ��⼸����
			return nullptr;
		}
		return _vec.front();
	}

private:
	std::recursive_mutex _lock;
	std::vector<int*> _vec; //������ɵ�vector
};




void recursive_lock_test() {
	Recursive_Test t;
	t.getFirst();

}



