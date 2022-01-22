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
	//模式一，再某些基础操作进行时上锁
	std::unique_lock<easyLock>  operation1(){
		lock1.lock(); //上锁
		unsafeOperation();
		return std::unique_lock<easyLock>(lock1, std::adopt_lock);//将锁的作用域扩展出去，如果调用者不接受，随着uniquelock的析构，自动解锁。
	}
	
	

	//模式二 
	//锁传递
	std::unique_lock<easyLock>  operation2(std::unique_lock<easyLock> lock_ref) {
		

	}


private:
	void unsafeOperation() {
		std::cout << "do unsafe operation" << std::endl;
	}

	easyLock lock1;
};


//std::unique_lock，转移锁的所有权，将锁的作用范围扩大到函数外。
void unique_lock_test() {
	
	AA a1;
	 //a1.operation1();
	std::unique_lock<easyLock> lock(a1.operation1());

	std::cout << "end" << std::endl;
	
}


//读写锁

void readWriteLockTest() {

	std::shared_mutex lk;

	std::thread t([&lk] {  std::shared_lock<std::shared_mutex>sl(lk); std::cout << "lock1" << std::endl; getchar();     });
	std::shared_lock<std::shared_mutex>sl(lk);
	std::cout << "lock1" << std::endl;
	

	std::unique_lock<std::shared_mutex>sl2(lk);
	std::cout << "lock2" << std::endl; 
	getchar();

}




//std::recursive_mutex 递归锁
class Recursive_Test { //递归锁
public:

	bool isEmpty() {
		std::lock_guard<std::recursive_mutex> guard(_lock);
		return _vec.empty();
	}

	
	int* getFirst() {
		std::lock_guard<std::recursive_mutex> guard(_lock);
		if (isEmpty()) { //允许多次上锁，但是上了几次锁,就要你解几次锁
			return nullptr;
		}
		return _vec.front();
	}

private:
	std::recursive_mutex _lock;
	std::vector<int*> _vec; //数组组成的vector
};




void recursive_lock_test() {
	Recursive_Test t;
	t.getFirst();

}



