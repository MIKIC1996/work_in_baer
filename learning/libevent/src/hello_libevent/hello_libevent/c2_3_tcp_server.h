#pragma once



#include "libevent_header.h"


//������Ҫ�Ļص�������ʽ
static void listener_cb(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int socklen, void* arg) {
	std::cout << "listen a new connection" << std::endl;
}


static void tcp_server_test() {

#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif // _WIN32


	//����libevent��������
	event_base* base = event_base_new();
	if (!base) {
		std::cout << "event base new fail" << std::endl;
		return;
	}

	//�����Ķ˿�
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));//���������ṹ�������
	sin.sin_family = AF_INET;//�趨����Э�� UDP TCP
	sin.sin_port = htons(3456);//�趨�����˿�

	//���ü��������ͻص�����
	evconnlistener* ev = evconnlistener_new_bind(
		base, //������
		listener_cb,//�ص�����
		base,//�ص�������ȡ�Ĳ���arg
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,//��ַ���ã�evconnlistener�ر�ͬʱ�ر�socket
		10,//���Ӷ��д�С
		(sockaddr*)&sin,//��ַ��˿�
		sizeof(sin)//C�����������ж�sin���͵ķ��������Ǵ�С
	);
	if (!ev) {
		std::cout << "listener bind error" << std::endl;
		return;
	}

	event_base_dispatch(base);
	evconnlistener_free(ev);
	event_base_free(base);

	return;
}