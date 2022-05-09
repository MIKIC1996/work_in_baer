#pragma once
#include "libevent_header.h"

//���󣬳�ʱ �����ӶϿ�����룩
static void event_cb(bufferevent* be, short events, void* arg)
{
	std::cout << "[E]" << std::endl;
	
	if (events & BEV_EVENT_TIMEOUT && events & BEV_EVENT_READING)
	{
		std::cout << "BEV_EVENT_READING BEV_EVENT_TIMEOUT" << std::endl;
		//bufferevent_enable(be,EV_READ); //��ȡ��ʱʱ�䷢�������ݶ�ȡֹͣ
		bufferevent_free(be);
	}
	else if (events & BEV_EVENT_ERROR)
	{
		bufferevent_free(be);
	}
	else
	{
		std::cout << "OTHERS" << std::endl;
	}
}

static void write_cb(bufferevent* be, void* arg)
{
	std::cout << "[W]" << std::endl;
}

static void read_cb(bufferevent* be, void* arg)
{
	std::cout << "[R]" << std::endl;
	char data[1024] = { 0 };
	//��ȡ���뻺������
	int len = bufferevent_read(be, data, sizeof(data) - 1);
	std::cout << "[" << data << "]" << std::endl;
	if (len <= 0)return;
	if (strstr(data, "quit") != NULL)
	{
		std::cout << "quit";
		//�˳����ر�socket BEV_OPT_CLOSE_ON_FREE
		bufferevent_free(be);
	}
	//�������� д�뵽�������
	bufferevent_write(be, "OKKKKKKKKsss", 10); //ÿ���㷢�����ݣ��������ݻ��������������ŷ��ͣ����ٵ���ˮλʱ������д��ص�����

}


static void listen_cb(evconnlistener* ev, evutil_socket_t s, sockaddr* sin, int slen, void* arg)
{
	std::cout << "listen_cb" << std::endl;
	event_base* base = (event_base*)arg;
	bufferevent* be = bufferevent_socket_new(base, s, BEV_OPT_CLOSE_ON_FREE);
	
	//�����¼�ʹ�� ����д
	bufferevent_enable(be, EV_READ | EV_WRITE);

	// ����ˮλ,Ĭ��0��0
	bufferevent_setwatermark(be, EV_READ, 5, 10);
	bufferevent_setwatermark(be, EV_WRITE,
		50,	//��ˮλ 0���������� Ĭ����0 �������ݵ���5 д��ص������ã�
		0	//��ˮλ��Ч
	);

	//��ʱʱ�������
	timeval t1 = { 3,0 };
	bufferevent_set_timeouts(be, &t1, 0);

	//���ûص�����
	bufferevent_setcb(be, read_cb, write_cb, event_cb, base);
}


static void c4_3_buffer_server_test()
{
#ifdef _WIN32 
	//��ʼ��socket��
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#else
	//���Թܵ��źţ��������ݸ��ѹرյ�socket
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif

	event_base* base = event_base_new();
	//�������������

	//�趨�����Ķ˿ں͵�ַ
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5001);

	evconnlistener* ev = evconnlistener_new_bind(base,
		listen_cb,		//�ص�����
		base,			//�ص������Ĳ���arg
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
		10,				//listen back
		(sockaddr*)&sin,
		sizeof(sin)
	);

	//�����¼���ѭ��
	event_base_dispatch(base);
	evconnlistener_free(ev);
	event_base_free(base);

};

