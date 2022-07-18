#pragma once
#include "sunnytcsbasicv3_global.h"

using namespace std;

#define META_REVERSE(type,val) SunnyTcsReverse<type,val>::value
#define META_PLUS(type,left,right) SunnyTcsPlus<type,left,right>::value
#define META_MINUS(type ,left,right) SunnyTcsMinus<type,left,right>::value
#define META_MULTIPLY(type,left,right) SunnyTcsMultiply<type,left,right>::value
#define META_DIVIDE(type,left,right) SunnyTcsDivide<type,left,right>::value


//ʵ�þ�̬����
namespace basic {


		//�Ӽ��˳�Ԫ���������Գ������ٱ�������ֵ
		template<typename _Ty,_Ty left , _Ty right>
		struct SunnyTcsPlus {
			static constexpr _Ty value = left + right;
		};
	
		template<typename _Ty, _Ty left, _Ty right>
		struct SunnyTcsMinus {
			static constexpr _Ty value = left - right;
		};
	
		template<typename _Ty, _Ty left, _Ty right>
		struct SunnyTcsMultiply {
			static constexpr _Ty value = left * right;
		};
	
		template<typename _Ty, _Ty left, _Ty right>
		struct SunnyTcsDivide {
			static constexpr _Ty value = left / right;
		};
	
		template<typename _Ty, _Ty left>
		struct SunnyTcsReverse {
			static constexpr _Ty value = -left;
		};


	static quint64 connectionID(QString ip, qint32 port)
	{
		QStringList ls = ip.split('.');
		quint64 result = 0;
		for (qint32 i = 0; i < ls.size(); ++i)
		{
			quint32 num = 0;
			string str = ls.at(i).toStdString();
			for (qint32 j = 0; j < str.size(); ++j)
			{
				num = num * 10 + (str[j] - '0');
			}
			result = result * 1000 + num;
		}

		result = result * 100000 + port;
		return result;
	}


	

	//S=(x1y2-x1y3+x2y3-x2y1+x3y1-x2y2) ���������
	static qreal triangularAera(qreal p1x, qreal p1y, qreal p2x, qreal p2y, qreal p3x, qreal p3y) {
		return qAbs((p1x*p2y - p1x*p3y + p2x*p3y - p2x* p1y + p3x*p1y - p3x*p2y) / 2.0);
	}

	//ֱ�߳���
	static qreal directLineLength(qreal p1x, qreal p1y, qreal p2x, qreal p2y) {
		return qAbs(qSqrt(qPow(qAbs(p1x - p2x), 2.0) + qPow(qAbs(p1y - p2y), 2.0)));
	}

	//�㵽ֱ�߾���
	static qreal pointToLineDistance(qreal x, qreal y, qreal p1x, qreal p1y, qreal p2x, qreal p2y) {
		qreal lineLen = directLineLength(p1x, p1y, p2x, p2y);
		if (lineLen == 0.0) {
			throw QString("x/0");
		}
		return triangularAera(x, y, p1x, p1y, p2x, p2y)*2.0 /lineLen;
	}


	//���ױ������ĵ���㹫ʽ
	static std::pair<qreal, qreal> bezierPointCoordinate(qreal st_x, qreal st_y,qreal ct_x,qreal ct_y ,qreal ed_x, qreal ed_y, qreal ratio) {
		qreal x = (1.0 - ratio)*(1.0 - ratio)*st_x + 2.0 * ratio *(1.0 - ratio) *ct_x + ratio * ratio * ed_x;
		qreal y = (1.0 - ratio)*(1.0 - ratio)*st_y + 2.0 * ratio *(1.0 - ratio) *ct_y + ratio * ratio * ed_y;
		return std::pair<qreal, qreal>(x, y);
	}

}