#include <QtCore/QCoreApplication>

#include <amqp.h>
#include <amqp_framing.h>
#include <amqp_tcp_socket.h>
#include <utils.h>
#include "utils.c"
#include <QThread>
#include <windows.h>

#include <QDebug>


extern void die_on_error(int, const char*);



/*
* 登录到中间件
*
* param[1] : 连接对象
* param[2] : 虚拟主机，默认为0
* param[3] : AMQP消息帧的最大大小，默认值为 AMQP_DEFAULT_FRAME_SIZE
* param[4] : 心跳 ，0为禁用心跳
* param[5] : 用户验证方法 ： 
			AMQP_SASL_METHOD_PLAIN , 后跟 const char* username 和 const char* passwd
			AMQP_SASL_METHOD_EXTERNAL, 后跟 const char* identity
* return : 成功返回 AMQP_RESPONSE_NORMAL 
*/
extern amqp_rpc_reply_t  amqp_login(amqp_connection_state_t state,char const *vhost, int channel_max,int frame_max, int heartbeat,amqp_sasl_method_enum sasl_method, ...);



/*
* 打开一个新的频道
*
* param[1] : 连接对象
* param[2] : 频道ID
* return :  结构体{ 缓存长度 和 缓存首地址 }
*/
extern amqp_channel_open_ok_t * amqp_channel_open(amqp_connection_state_t state, amqp_channel_t channel);



/*
* 返回最近的rpc回复
*
* param[1] : 连接对象
* return :  
*/
extern amqp_rpc_reply_t AMQP_CALL amqp_get_rpc_reply(amqp_connection_state_t state);



/**
* 申明一个队列
*
* @param [1] 连接对象
* @param [2] 频道
* @param [3] 队列名
* @param [4] passive
* @param [5] 是否持久化
* @param [6] 当前连接不在时，队列是否自动删除
* @param [7] 没有consumer时，队列是否自动删除
* @param [8] 其他拓展参数
* @returns amqp_queue_declare_ok_t
*/

extern amqp_queue_declare_ok_t * amqp_queue_declare(
	amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue,
	amqp_boolean_t passive, amqp_boolean_t durable, amqp_boolean_t exclusive,
	amqp_boolean_t auto_delete, amqp_table_t arguments);






/**
* qos是 quality of service，我们这里使用主要用于控制预取消息数，避免消息按条数均匀分配，需要和no_ack配合使用
*
* @param [1] 连接对象
* @param [2] 频道
* @param [3] 预取消息大小
* @param [4] 预取消息数目
* @param [5] 是否全局
* @returns amqp_queue_declare_ok_t
*/
amqp_basic_qos_ok_t *AMQP_CALL amqp_basic_qos(amqp_connection_state_t state,
	amqp_channel_t channel,
	uint32_t prefetch_size,
	uint16_t prefetch_count,
	amqp_boolean_t global);



/**
* 将一个消费者绑定到队列
*
* @param [in] state connection state
* @param [in] channel the channel to do the RPC on
* @param [in] queue queue
* @param [in] consumer_tag consumer_tag
* @param [in] no_local no_local
* @param [in] 是否要消息确认后 才从 队列中删除消息
* @param [in] exclusive exclusive
* @param [in] arguments arguments
* @returns amqp_basic_consume_ok_t
*/
extern amqp_basic_consume_ok_t * amqp_basic_consume(
	amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue,
	amqp_bytes_t consumer_tag, amqp_boolean_t no_local, amqp_boolean_t no_ack,
	amqp_boolean_t exclusive, amqp_table_t arguments);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	//先新建一个连接
	amqp_connection_state_t conn;
	conn = amqp_new_connection();
	//新建一个套接字
	amqp_socket_t* socket = nullptr;
	socket = amqp_tcp_socket_new(conn);
	//打开套接字
	const char* host_name = "127.0.0.1";
	int port = 5672;
	int socket_status = amqp_socket_open(socket, host_name, port);//返回 amqp_status_enum_类型
	//检查返回状态，失败就exit程序，并打印错误
	die_on_error(socket_status, "error in open socket");
	//登录
	auto login_status = amqp_login(conn, "/", 0, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "mikic", "mikic");
	die_on_amqp_error(login_status, "error in login"); //对返回值进行检查
	//打开一个新的频道
	int channelId = 1;
	amqp_channel_open(conn, channelId); 
	//返回某个连接最近的远程调用回复，可以检查是否这个回复出错,上面的channel_open并没有返回是否成功，所以我们只能主动查询
	auto rpc_reply  = amqp_get_rpc_reply(conn);
	die_on_amqp_error(rpc_reply, "open channel error"); //检查开启频道操作是否出错
	
	//声明一个交换机
	amqp_exchange_declare(conn, channelId, amqp_cstring_bytes("kernelExchange"), amqp_cstring_bytes("direct"), 0, 1, 0, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "exchange  error");
	//声明一个队列,持久化的，不会删除的队列
	amqp_queue_declare(conn, channelId, amqp_cstring_bytes("kernelQueue"), 0, 1, 0, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "queue  error");
	//将队列绑定到一个交换机上
	amqp_queue_bind(conn, channelId, amqp_cstring_bytes("kernelQueue")
		, amqp_cstring_bytes("kernelExchange"), amqp_cstring_bytes("kernelKey"), amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "bind  error");
	qDebug() << "send msg";
	//发送消息
	for (int i = 0; i < 300; ++i) {
		//消息属性的设置
		amqp_basic_properties_t props;
		props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
		props.content_type = amqp_cstring_bytes("text/plain");
		props.delivery_mode = 2;

		//发布消息
		int res = amqp_basic_publish(conn, channelId,
			amqp_cstring_bytes("kernelExchange"),amqp_cstring_bytes("kernelKey"),
			0, 0, &props, amqp_cstring_bytes("jmq message"));
		QThread::msleep(10);
	}


	amqp_basic_qos(conn, channelId, 0, 1, 0);
	//创建一个消费者绑定到队列
	amqp_basic_consume(conn, channelId, amqp_cstring_bytes("kernelQueue"),
		amqp_cstring_bytes("jmq"), 0, 1, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming error");
	
	qDebug() << "get start";
	timeval tim;
	tim.tv_sec = 1;
	tim.tv_usec = 0;
	amqp_envelope_t enve;

	for (int i = 0; i < 400; ++i) {
		std::string msg = "";
		amqp_maybe_release_buffers(conn);
		auto consume_reply =
			amqp_consume_message(conn, &enve, &tim, 0);
		if (consume_reply.reply_type != AMQP_RESPONSE_NORMAL) {
			qDebug() << "amqp_comsume_message error";
		}
		else {
			msg = (char*)enve.message.body.bytes;
			msg = msg.substr(0, enve.message.body.len);
			qDebug() << "msg = " << msg.data() << " num = " << i;
			QThread::msleep(10);
		}

	}

	QThread::msleep(1000);
	amqp_channel_close(conn, channelId, AMQP_REPLY_SUCCESS);
	amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
	amqp_destroy_connection(conn);
		


	/*									
	//声明一个队列,持久化的，不会删除的队列
	amqp_queue_declare(conn, channelId, amqp_cstring_bytes("kernelQueue"), 0, 1, 0, 0, amqp_empty_table);
	//预取消息控制
	amqp_basic_qos(conn, channelId, 0, 1, 0);
	//开启一个消费队列
	amqp_basic_consume(conn, channelId, amqp_cstring_bytes("kernelQueue"),
		amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "consuming error");
	*/
	



    return a.exec();
}
