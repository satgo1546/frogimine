//=============================================================================
// ■ FM::Date
//-----------------------------------------------------------------------------
//   日期的类。
//   只能处理日期，不能处理时间，这点还请注意。
//   另外，只会按照既定规则行事。历法微调等不考虑在内。
//=============================================================================

class Date {
	//-------------------------------------------------------------------------
	// ● 定义
	//   数据类型是瞎选的。
	//-------------------------------------------------------------------------
public:
	long y;
	short m, d;
	// 常量定义在最后
	static const Date date_1899_12_31;
	static const Date date_1900_1_1;
	static const Date date_1_1_1;
	//-------------------------------------------------------------------------
	// ● 比较运算
	//-------------------------------------------------------------------------
	bool operator==(const Date& other) const {
		return y == other.y && m == other.m && d == other.d;
	}
	bool operator!=(const Date& other) const {
		return !(*this == other);
	}
	bool operator<(const Date& other) const {
		if (y < other.y) return true;
		if (y == other.y && m < other.m) return true;
		if (y == other.y && m == other.m && d < other.d) return true;
		return false;
	}
	bool operator>(const Date& other) const {
		return other < *this;
	}
	bool operator<=(const Date& other) const {
		return *this < other || *this == other;
	}
	bool operator>=(const Date& other) const {
		return *this > other || *this == other;
	}
	//-------------------------------------------------------------------------
	// ● 是否为闰年？
	//-------------------------------------------------------------------------
	static bool is_leap_year(long year) {
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}
	bool is_leap_year() {
		return is_leap_year(y);
	}
	//-------------------------------------------------------------------------
	// ● 本月天数
	//-------------------------------------------------------------------------
	static int days_in_month(long year, short month) {
		switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 4: case 6: case 9: case 11:
			return 30;
		case 2:
			return is_leap_year(year) ? 29 : 28;
		default:
			return -1;
		}
	}
	int days_in_month() {
		return days_in_month(y, m);
	}
	//-------------------------------------------------------------------------
	// ● 变成下一天
	//-------------------------------------------------------------------------
	Date& operator++() {
		d++;
		if (d > days_in_month()) {
			d = 1;
			m++;
			if (m > 12) {
				m = 1;
				y++;
			}
		}
		return *this;
	}
	Date operator++(int) {
		Date tmp(*this);
		operator++();
		return tmp;
	}
	//-------------------------------------------------------------------------
	// ● 计算两日期间相差的天数
	//   这个算法可能有点慢。
	//-------------------------------------------------------------------------
	int operator-(const Date& other) const {
		if (*this >= other) {
			int r = 0;
			for (Date i(other); i != *this; i++) r++;
			return r;
		} else {
			return -(other - *this);
		}
	}
	//-------------------------------------------------------------------------
	// ● 这天是星期几？
	//   0 = 星期日；1~6 = 星期一~星期六。
	//   因为计算方法的原因，只能计算1900年及以后的日期。
	//-------------------------------------------------------------------------
	int wday() {
		return (*this - date_1899_12_31) % 7;
	}
	//-------------------------------------------------------------------------
	// ● 是一年中的第几天？
	//-------------------------------------------------------------------------
	int yday() {
		Date jan1 = {y, 1, 1};
		return *this - jan1;
	}
};

// 这天是星期日
const Date Date::date_1899_12_31 = {1899, 12, 31};
// 这天是星期一
const Date Date::date_1900_1_1 = {1900, 1, 1};
// 这天也是星期一
const Date Date::date_1_1_1 = {1, 1, 1};
