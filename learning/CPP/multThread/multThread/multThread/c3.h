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
/*
C++14提供了shared_mutex来解决读者 - 写者问题，也就是读写锁，和普通锁不一样，读写锁同时只能有一个写者或多个读者，但不能同时既有读者又有写者，读写锁的性能一般比普通锁要好。
shared_mutex通过lock_shared，unlock_shared，shared_lock进行读者的锁定与解锁；通过lock，unlock，unique_lock进行写者的锁定与解锁。
*/



class ThreadSafeCounter {
public:
	ThreadSafeCounter() = default;

	// 多个线程/读者能同时读计数器的值。
	unsigned int get() const {
		std::shared_lock<std::shared_mutex> lock(mutex_);
		return value_;
	}

	// 只有一个线程/写者能增加/写线程的值。
	void increment() {
		std::unique_lock<std::shared_mutex> lock(mutex_);
		value_++;
	}

	// 只有一个线程/写者能重置/写线程的值。
	void reset() {
		std::unique_lock<std::shared_mutex> lock(mutex_);
		value_ = 0;
	}

private:
	mutable std::shared_mutex mutex_;
	unsigned int value_ = 0;
};



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



