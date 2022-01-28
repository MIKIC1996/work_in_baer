#pragma once


//�߳�ͬ������������
#include "stdafx.h"

struct Task {
	int _val;
	std::string _str;
};


std::mutex mut;
std::queue<Task> taskQueue;
std::condition_variable cond;
bool threadSwitch = true;



void insertDataThread() {

	Task t{ 100,"hello world!" };
	
	{
		std::lock_guard<std::mutex> guard(mut);
		taskQueue.push(t);
	}//�����Զ���mut����

	cond.notify_one();
	
}



void processThread() {

	while (threadSwitch) {
		std::unique_lock<std::mutex> lk(mut); //����ס
		cond.wait(lk, []()->bool {return !taskQueue.empty(); }); //���������㣬��lk������unlock��,�ȴ�����������ʱ�����ֻ�ȡ��,���ж����������㣬��������ȡ״̬�������أ�
		
		Task tmp = taskQueue.front();
		taskQueue.pop();
		lk.unlock();

		std::cout << tmp._val << " : " << tmp._str.c_str() << std::endl;

	}
}


void condition_vari_test() {


	std::thread t1(processThread);

	while ('q' != getchar()) {
		insertDataThread();
	}
	threadSwitch = false;//�رտ���
	insertDataThread();//���̻߳��ѣ���Ȼһֱ��������״̬
	t1.join(); //�����̣߳��ȴ��˳�

}


//����
//ʹ��������ȡ�첽����ķ���ֵ

int getAnswer() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 100;
}


void async_task() {

	std::future<int> ret = std::async(getAnswer); //�ύ��һ���첽����
	std::cout << ret.get() <<std::endl;

}







//std::promise ��C++11��������г��õ�һ���࣬�����std::futureʹ�á�����������һ���߳�t1�б���һ��
//����typename T��ֵ���ɹ���󶨵�std::future��������һ�߳�t2�л�ȡ��

std::promise<int>  promise1;

void set_promise_val() {

	try {

		//throw std::logic_error("logic");
		std::this_thread::sleep_for(std::chrono::seconds(5));
		promise1.set_value(100);
		
	}
	catch (...) {
		promise1.set_exception(std::current_exception()); //���Խ����쳣
	}
}


void promise_test() {

	std::thread t1(set_promise_val);

	std::future<int> fu = promise1.get_future();//Ҳ���Եõ��쳣

	int ret = fu.get();//�����ȴ�
	std::cout << ret << std::endl;

	t1.join();
}


//����߳�ͬʱ�ȴ�һ��future
void mult_promise_test() {

	std::shared_future<int> sf = promise1.get_future().share();
	std::shared_future <int> sf2 = sf;


	std::thread t1(set_promise_val);

	std::thread t2([&sf] { std::cout << sf.get()<< std::endl;  });
	std::thread t3([&sf2]{ std::cout << sf2.get()<< std::endl;  });
	t1.join();
	t2.join();
	t3.join();
}