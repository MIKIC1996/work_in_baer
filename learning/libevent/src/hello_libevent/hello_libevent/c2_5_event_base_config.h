#pragma once
#include "libevent_header.h"


//������Ҫ�Ļص�������ʽ
static void listener2_cb(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int socklen, void* arg) {
	std::cout << "listen a new connection" << std::endl;
}



static void c2_5_event_base_config_test()
{
#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

	//��ӡ��ǰ��֧�ֵ�����ģ��
	char const** sptMethod = event_get_supported_methods();
	for (int i = 0; sptMethod[i] != NULL; ++i) {
		std::cout << "spt method " << sptMethod[i] << std::endl;
	}


	//����һ���µ�����������
	event_config* conf = event_config_new();
	//���������ñ�־

	//��������������
	/*
	if (0 != event_config_require_features(conf, EV_FEATURE_ET)) {
		std::cout << "event_config_require_features failed" << std::endl;
	}
	*/
	//���������ò���Ҫ������ģ��
	event_config_avoid_method(conf, "epoll");

	//���������ñ�־

#ifdef _WIN32
	event_config_set_flag(conf, EVENT_BASE_FLAG_STARTUP_IOCP);//ʹ��IOCPģ��
	evthread_use_windows_threads();
	SYSTEM_INFO sinfo;
	GetSystemInfo(&sinfo);
	event_config_set_num_cpus_hint(conf, sinfo.dwNumberOfProcessors);
#endif


	//ʹ�ø��������������Ķ���
	event_base* base = event_base_new_with_config(conf);

	if (!base) {
		std::cout << "event_base_new_with_config failed" << std::endl;
		base = event_base_new();
	}
	else {
		//��ȡ��ǰģ��
		std::cout << "current method is " << event_base_get_method(base) << std::endl;

		std::cout << "event_base_new_with_config success" << std::endl;
		//��ȡ��ǰ�������Ķ��������
		int f = event_base_get_features(base);
		if (f & EV_FEATURE_ET)
			std::cout << "support EV_FEATURE_ET"<<std::endl;
		if (f & EV_FEATURE_O1) 
			std::cout << "support EV_FEATURE_O1" << std::endl;
		if (f & EV_FEATURE_FDS)
			std::cout << "support EV_FEATURE_O1" << std::endl;
		if (f & EV_FEATURE_EARLY_CLOSE)
			std::cout << "support EV_FEATURE_O1" << std::endl;
	}


	//�����Ķ˿�
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));//���������ṹ�������
	sin.sin_family = AF_INET;//�趨����Э�� UDP TCP
	sin.sin_port = htons(3456);//�趨�����˿�

	//���ü��������ͻص�����
	evconnlistener* ev = evconnlistener_new_bind(
		base, //������
		listener2_cb,//�ص�����
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


	//�����Ķ��������
	if (base) {
		event_base_free(base);
	}
	//���������õ�����
	event_config_free(conf);

};

