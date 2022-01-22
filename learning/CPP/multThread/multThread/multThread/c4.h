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