#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

template<typename clock /*= boost::posix_time::microsec_clock*/>
class basic_ptimer {
public:
	basic_ptimer(){
		restart();
	}

	void restart() {
		_start_time = clock::local_time();
	}

	void elapsed()const {
		std::cout << clock::local_time() - _start_time << std::endl;
	}

private:
	boost::posix_time::ptime _start_time;
};
;

//""ÔËËã·ûÖØÔØ
boost::gregorian::days operator"" _D(unsigned long long n) {
	return boost::gregorian::days(n);
}

boost::gregorian::weeks operator"" _W(unsigned long long n) {
	return boost::gregorian::weeks(n);
}

boost::gregorian::date operator"" _YMD(const char* str, std::size_t) {
	return boost::gregorian::from_string(str);
}
