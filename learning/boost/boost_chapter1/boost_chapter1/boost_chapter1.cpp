// boost_chapter1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "basic_ptimer.h"


int main()
{
	//------------------日期--------------------------------
	boost::timer t;
	std::cout << t.elapsed_max();
	std::string str = "you are mine";

	boost::progress_display _display(100);
	for (int i = 0; i < 100; ++i) {
		++_display;
	}

	std::cout <<"it has cost"<< t.elapsed()<<std::endl;
	boost::gregorian::date da1(2021, 2, 26);
	assert(!da1.is_infinity());
	std::cout << da1.day_of_week() << std::endl;
	std::cout << boost::gregorian::to_simple_string(da1) << std::endl;
	std::cout << boost::gregorian::to_iso_string(da1) << std::endl;
	
	boost::gregorian::date da2 = boost::gregorian::date_from_tm(  boost::gregorian::to_tm(da1) );
	std::cout << boost::gregorian::to_iso_extended_string(da2);

	boost::gregorian::days ds1(20);
	boost::gregorian::months ms(2);
	//ms.number_of_months;

	boost::gregorian::date_period pr1(da1, da2 += boost::gregorian::months(2));

	
	std::string st=boost::gregorian::gregorian_calendar::is_leap_year(2012)?"YES":"NO";
	std::cout << st << std::endl;
	char strc[] = "you";
	std::cout << strc<<std::endl;
	std::cout << *strc<<std::endl;
	//char* pter;
	//pter++;
	std::cout << strc + 1<<std::endl;
	//-----------------------------时间------------------------------
	boost::posix_time::time_duration t_dur(1, 50, 50, 3000);
	boost::posix_time::time_duration t_dur_fm_str = 
		boost::posix_time::duration_from_string("2:45:2:2000");
	boost::posix_time::hours t_hours (t_dur.hours());
	boost::posix_time::minutes t_mins (t_dur.minutes());
	boost::posix_time::seconds t_secs (t_dur.seconds());
	boost::posix_time::millisec t_msec (t_dur.total_milliseconds());
	std::cout<<boost::posix_time::to_simple_string(t_dur) << std::endl;
	std::cout << boost::posix_time::to_simple_string(t_dur_fm_str) << std::endl;

	unsigned short t_s=t_dur.num_fractional_digits();//微秒6位
	assert(t_dur.resolution() != boost::date_time::nano);
	std::cout << t_s << std::endl;
	//时间点 日期加时间段
	boost::posix_time::ptime t_pt(boost::gregorian::date(2020, 2, 14)
		, boost::posix_time::time_duration(1, 20, 20, 2000));

	boost::gregorian::date t_pt_date = t_pt.date();
	boost::posix_time::time_duration t_pt_dur = t_pt.time_of_day();
	std::cout << boost::gregorian::to_iso_string(t_pt_date) << std::endl;
	std::cout << boost::posix_time::to_iso_string(t_pt_dur) << std::endl;
	std::cout << boost::posix_time::to_simple_string(t_pt);

	std::tm t_m = boost::posix_time::to_tm(t_pt);
	assert(t_m.tm_year == 120);
	boost::posix_time::ptime t_pt2 = boost::posix_time::ptime_from_tm(t_m);

	boost::posix_time::ptime pp = boost::posix_time::from_time_t(
		boost::posix_time::to_time_t(t_pt));

	pp = boost::posix_time::from_time_t(std::time(0));//time_t类型
	assert(pp.date() == boost::gregorian::day_clock::local_day());//当前天

	//时间区间---------------------------------------
	boost::posix_time::ptime ppt(boost::gregorian::date(2015, 5, 5)
		, boost::posix_time::hours(10));
	boost::posix_time::time_period t_pd(ppt, boost::posix_time::hours(10));
	boost::posix_time::time_period t_pd2(ppt+ boost::posix_time::hours(10)
		, boost::posix_time::hours(10));
	assert(t_pd.end() == t_pd2.begin() && t_pd.is_adjacent(t_pd2));
	t_pd.shift(boost::posix_time::time_duration(1, 20, 20, 300000));
	t_pd.expand(boost::posix_time::hours(1));//左右扩张1小时
	//时间迭代器-----------------------------------------
	for (boost::posix_time::time_iterator iter(ppt, boost::posix_time::minutes(10));
		iter < ppt + boost::posix_time::hours(1); ++iter) {
		
		std::cout << *iter << std::endl;
	}

	//计时器-----------------------------------------
	basic_ptimer<boost::posix_time::second_clock> b_ter;
	//basic_ptimer<> b_ter;
	int couter = 0;
	while(couter<10000000){
		if(couter%10000==0)
			b_ter.elapsed();
		couter++;
	}
	assert(boost::gregorian::days(100) == 100_D);
	std::cout << boost::gregorian::to_simple_string("2019-9-9"_YMD) << std::endl;
	








}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
