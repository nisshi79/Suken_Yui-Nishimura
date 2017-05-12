#include "Utility.h"

//const char suken::Decimal::BITS = 12;
//
//suken::Decimal::Decimal() {
//	value = 0;
//}
//
//suken::Decimal::Decimal(int arg) {
//	value = (arg << BITS);
//}
//suken::Decimal::Decimal(float arg) {
//	value = (long long)(arg * (1 << BITS));
//}
//suken::Decimal::Decimal(double arg) {
//	value = (long long)(arg * (1 << BITS));
//}
//suken::Decimal::Decimal(const Decimal& arg) {
//	value = arg.value;
//}
//
//suken::Decimal& suken::Decimal::operator =(int arg) {
//	value = (arg << BITS);
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator =(float arg) {
//	value = (long long)(arg * (1 << BITS));
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator =(double arg) {
//	value = (long long)(arg * (1 << BITS));
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator =(const Decimal& arg) {
//	value = arg.value;
//	return *this;
//}
//
//suken::Decimal suken::Decimal::operator +(int arg) {
//	Decimal buf=arg;
//	buf.value += (arg << BITS);
//	return buf;
//}
//suken::Decimal suken::Decimal::operator +(float arg) {
//	Decimal buf = *this;
//	buf.value += (long long)(arg * (1 << BITS));
//	return buf;
//}
//suken::Decimal suken::Decimal::operator +(double arg) {
//	Decimal buf = *this;
//	buf.value += (long long)(arg * (1 << BITS));
//	return buf;
//}
//suken::Decimal suken::Decimal::operator +(const Decimal& arg) {
//	Decimal buf = *this;
//	buf.value += (arg.value);
//	return buf;
//}
//
//suken::Decimal suken::Decimal::operator -(int arg) {
//	Decimal buf = *this;
//	buf.value -= (arg << BITS);
//	return buf;
//}
//suken::Decimal suken::Decimal::operator -(float arg) {
//	Decimal buf = *this;
//	buf.value -= (long long)(arg * (1 << BITS));
//	return buf;
//}
//suken::Decimal suken::Decimal::operator -(double arg) {
//	Decimal buf = *this;
//	buf.value -= (long long)(arg * (1 << BITS));
//	return buf;
//}
//suken::Decimal suken::Decimal::operator -(const Decimal& arg) {
//	Decimal buf = *this;
//	buf.value -= (arg.value);
//	return buf;
//}
//
//suken::Decimal suken::Decimal::operator *(int arg) {
//	Decimal buf = *this;
//	buf.value *= (arg);
//	return buf;
//}
//suken::Decimal suken::Decimal::operator *(float arg) {
//	Decimal buf = *this;
//	buf.value *= arg;
//	return buf;
//}
//suken::Decimal suken::Decimal::operator *(double arg) {
//	Decimal buf = *this;
//	buf.value *= arg;
//	return buf;
//}
//suken::Decimal suken::Decimal::operator *(const Decimal& arg) {
//	Decimal buf = *this;
//	(buf.value *= (arg.value)) >> BITS;
//	return buf;
//}
//
//suken::Decimal suken::Decimal::operator /(int arg) {
//	Decimal buf = *this;
//	buf.value /= (arg);
//	return buf;
//}
//suken::Decimal suken::Decimal::operator /(float arg) {
//	Decimal buf = *this;
//	buf.value /= arg;
//	return buf;
//}
//suken::Decimal suken::Decimal::operator /(double arg) {
//	Decimal buf = *this;
//	buf.value /= arg;
//	return buf;
//}
//suken::Decimal suken::Decimal::operator /(const Decimal& arg) {
//	Decimal buf = *this;
//	(buf.value << BITS);
//	buf.value /= (arg.value);
//	return buf;
//}
//
//
//suken::Decimal& suken::Decimal::operator +=(int arg) {
//	value += (arg << BITS);
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator +=(float arg) {
//	value += (long long)(arg * (1 << BITS));
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator +=(double arg) {
//	value += (long long)(arg * (1 << BITS));
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator +=(const Decimal& arg) {
//	value += (arg.value);
//	return *this;
//}
//
//suken::Decimal& suken::Decimal::operator -=(int arg) {
//	value -= (arg << BITS);
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator -=(float arg) {
//	value -= (long long)(arg * (1 << BITS));
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator -=(double arg) {
//	value -= (long long)(arg * (1 << BITS));
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator -=(const Decimal& arg) {
//	value -= (arg.value);
//	return *this;
//}
//
//suken::Decimal& suken::Decimal::operator *=(int arg) {
//	value *= (arg);
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator *=(float arg) {
//	value *= arg;
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator *=(double arg) {
//	value *= arg;
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator *=(const Decimal& arg) {
//	(value *= (arg.value)) >> BITS;
//	return *this;
//}
//
//suken::Decimal& suken::Decimal::operator /=(int arg) {
//	value /= (arg);
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator /=(float arg) {
//	value /= arg;
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator /=(double arg) {
//	value /= arg;
//	return *this;
//}
//suken::Decimal& suken::Decimal::operator /=(const Decimal& arg) {
//	(value << BITS);
//	value /= (arg.value);
//	return *this;
//}