#pragma once
#include "libevent_header.h"

static void client_cb(evutil_socket_t sock, short which, void* arg) {

	event* ev = (event*)(arg);
	if (which & EV_TIMEOUT) {
		std::cout << "time out" << std::endl;
		event_free(ev);
		evutil_closesocket(sock);
		return;
	}

	char buf[1024] = { 0 };
	int len = recv(sock, buf, sizeof(buf) - 1, 0);

	if (len > 0)
	{
		std::cout << buf << std::endl;
		send(sock, "ok", 2, 0);
	}
	else
	{
		//��Ҫ����event
		std::cout << "event_free" <<  std::endl;
		event_free(ev);
		evutil_closesocket(sock);
	}
}




static void listen_cb(evutil_socket_t sock, short which, void* arg) {
	std::cout << "listen_cb" << std::endl;
	sockaddr_in sin;
	socklen_t size = sizeof(sin);
	//��ȡ������Ϣ
	evutil_socket_t client = accept(sock, (sockaddr*)&sin, &size);
	char ip[16] = { 0 };
	evutil_inet_ntop(AF_INET, &sin.sin_addr, ip, sizeof(ip) - 1);
	std::cout << "client ip is" << ip << std::endl;

	//�µĿͻ������ݶ�ȡ�¼�
	event_base* base = (event_base*)(arg);
	//����¼��޸�Ϊ��Ե����
	event* client_read_ev = event_new(base, client,EV_READ | EV_PERSIST |EV_ET, client_cb, event_self_cbarg());
	timeval t = { 10,0 };
	//Ϊ�¼������˳�ʱ��Ҳ����10sû���յ����ݣ����Զ��Ͽ�����
	event_add(client_read_ev,&t);
}


static void c3_8_tcp_event_server() {
	
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
	
	//����windows �� socket����evutil_socket_t �������ӣ���ʵ���Ǹ�����linux fd�Ķ���
	evutil_socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock <= 0) {
		std::cerr << "socker error" << std::endl;
	}

	//�������͵�ַ����

	/*
	һ����������������
		���������ǵ����ң����������ң�������û�н��������ݻ���û�еõ����֮ǰ���Ҳ��᷵�ء�
		�����������ǵ����ң����������ң��������������أ�ͨ��select֪ͨ�����ߡ�
		ͬ���������ҵ���һ�����ܣ��ù���û�н���ǰ�������Ƚ����
		�첽�������ҵ���һ�����ܣ�����Ҫ֪���ù��ܽ�����ù����н����֪ͨ�ң��ص�֪ͨ����
	*/	

	evutil_make_socket_nonblocking(sock); //����socket������
	evutil_make_listen_socket_reuseable(sock);

	//�˿ں͵�ַ��
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(3456);
	if (0 != bind(sock, (sockaddr*)&sin, sizeof(sin)))
	{
		std::cerr << "bind error" << std::flush << std::endl;
		return;
	}
	//��ʼ����
	listen(sock, 10);

	//�����¼�������Ĭ��ˮƽ����
	event* ev = event_new(base, sock, EV_READ | EV_PERSIST, listen_cb, base);
	event_add(ev, 0);//��Ҳ�������ó�ʱ��������ʱ���ã����״̬��

	//�¼���ѭ��
	event_base_dispatch(base);
	evutil_closesocket(sock);
	event_base_free(base);

	return;


}

