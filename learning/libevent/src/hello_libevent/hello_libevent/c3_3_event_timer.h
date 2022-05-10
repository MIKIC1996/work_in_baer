#pragma once


#include "libevent_header.h"

static timeval tv1_tvl{ 2,0 };
static void timer_cb1(evutil_socket_t, short which, void* arg) {
	std::cout << "timer_cb1" << std::endl;
}

static timeval tv2_tvl{ 2,0 };
static void timer_cb2(evutil_socket_t, short which, void* arg) {
	std::cout << "timer_cb2" << std::endl;

	
	event* ev = (event*)arg;
	if (!evtimer_pending(ev, &tv2_tvl)) {
		evtimer_del(ev);
		evtimer_add(ev, &tv2_tvl);
	}
	
}


static void timer_test() {

#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif // _WIN32


	event_base* base = event_base_new();
	if (!base) {
		std::cout << "event_base_new failed" << std::endl;
	}

	//����һ����ʱ���¼�,�������˳־�����
	event* tv1 = event_new(base, -1, EV_PERSIST, timer_cb1, event_self_cbarg());
	event_add(tv1, &tv1_tvl);


	//���ǿ���ʹ�ú꺯������������ʱ���¼�������꺯�����Ƕ�event_new �ķ�װ ,�൱��event_new((b), -1, 0, (cb), (arg))
	//��ᷢ����û�����ó־����ԣ�����������Ҫ�ڻص������ֶ�����
	event* tv2 = evtimer_new(base, timer_cb2, event_self_cbarg());
	event_add(tv2, &tv2_tvl);

	std::thread t([base]()->void {event_base_dispatch(base); });
	t.join();

	event_base_free(base);


}