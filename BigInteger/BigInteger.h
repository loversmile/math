#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#ifdef LINUX
#include <cstring>
#endif
using namespace std;

class BigInteger {
public:
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> s;

	BigInteger()
	{}

	BigInteger(long long num)
	{
		s.clear();
		do {
			s.push_back(num % BASE);
			num /= BASE;
		} while (num > 0);
	}

	BigInteger operator=(long long num)
	{
		s.clear();
		do {
			s.push_back(num % BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}

	BigInteger operator=(const string& str)
	{
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;
		for (int i = 0; i < len; i++)
		{
			int end = str.length() - i * WIDTH;
			int start = max(0, end - WIDTH);
#ifdef LINUX
			sscanf(str.substr(start, end - start).c_str(), "%d", &x);
#else
			sscanf_s(str.substr(start, end - start).c_str(), "%d", &x);
#endif
			s.push_back(x);
		}

		return *this;
	}

	BigInteger operator+(const BigInteger& b) const
	{
		BigInteger c;
		c.s.clear();
		int i, g;
		int x;
		for (i = 0, g = 0;; i++)
		{
			if (g == 0 && i >= s.size() && i >= b.s.size())
			{
				break;
			}
			x = g;
			if (i < s.size())
			{
				x += s[i];
			}
			if (i < b.s.size())
			{
				x += b.s[i];
			}
			c.s.push_back(x % BASE);
			g = x / BASE;
		}
		return c;
	}

	BigInteger operator+=(const BigInteger& b)
	{
		*this = *this + b;
		return *this;
	}

	BigInteger operator-(const BigInteger& b) const
	{
		BigInteger c;
		c.s.clear();
		int MAX = std::max(s.size(), b.s.size());
		for (int i = 0, g = 0;; i++)
		{
			if (i >= MAX)
			{
				break;
			}
			int x = g;
			if (i < s.size())
			{
				x += s[i];
			}
			if (i < b.s.size())
			{
				x -= b.s[i];
			}
			if (i == MAX - 1)
			{
				if (x != 0)
				{
					c.s.push_back(x % BASE);
				}
			}
			else
			{
				c.s.push_back(((x % BASE) + BASE) % BASE);
			}
			g = x >= 0 ? x / BASE : -1;
		}
		return c;
	}

	BigInteger operator-= (const BigInteger& b)
	{
		*this = *this - b;
		return *this;
	}

	BigInteger operator* (const BigInteger& b)
	{
		std::stringstream ss;
		for (int i = s.size() - 1; i >= 0; i--)
		{
			ss << s[i];
		}

		std::string operand1 = ss.str();
		ss.str("");
		for (int i = b.s.size() - 1; i >= 0; i--)
		{
			ss << b.s[i];
		}
		std::string operand2 = ss.str();
		std::vector<int> c, d, temp;

		for (int i = operand1.length() - 1; i >= 0; i--)
		{
			c.push_back(operand1[i] - '0');
		}
		for (int i = operand2.length() - 1; i >= 0; i--)
		{
			d.push_back(operand2[i] - '0');
		}
		int MAX = std::max(c.size(), d.size());
		for (int i = 0; i < MAX * 2 + 1; i++)
		{
			temp.push_back(0);
		}
		for (int i = 0; i < c.size(); i++)
		{
			for (int j = 0; j < d.size(); j++)
			{
				temp[i + j] += c[i] * d[j];
			}
		}
		for (int i = 0; i < 2 * MAX + 1; i++)
		{
			if (temp[i] > 9)
			{
				temp[i + 1] += temp[i] / 10;
				temp[i] %= 10;
			}
		}
		int m = 2 * MAX;
		while (temp[m] == 0)
		{
			m--;
		}
		BigInteger another;
		another.s.clear();

		int len = (m) / WIDTH + 1;

		for (int i = 0; i < len; i++)
		{
			another.s.push_back(0);
		}
		for (int i = 0; i < len; i++)
		{
			int x = 1;
			int k = 0;
			int end = std::min(m + 1, (i + 1) * WIDTH);
			int start = i * WIDTH;
			for (int j = start; j < end; j++)
			{
				k += x * temp[j];
				x *= 10;
			}
			another.s[i] = k;
		}
		return another;
	}

	BigInteger operator*= (const BigInteger& b)
	{
		*this = *this * b;
		return *this;
	}

	BigInteger operator/(const BigInteger& b)
	{
		if (*this < b) return 0;
		if (*this == b) return 1;

		BigInteger another;

		BigInteger zero = 0;
		while (*this >= b && *this >= zero)
		{
			*this -= b;
			another += 1;
		}
		return another;
	}

	BigInteger operator/=(const BigInteger& b)
	{
		*this = *this / b;
		return *this;
	}

	BigInteger operator%(const BigInteger& b)
	{
		BigInteger result;
		result = *this - (*this / b) * b;
		return result;
	}

	BigInteger operator%=(const BigInteger& b)
	{
		*this = *this % b;
		return *this;
	}

	bool operator>(const BigInteger& b)
	{
		return (BigInteger)b < *this;
	}
	bool operator<(const BigInteger& b)
	{
		if (s.size() != b.s.size())
		{
			return s.size() < b.s.size();
		}

		for (int i = s.size() - 1; i >= 0; i--)
		{
			if (s[i] != b.s[i])
			{
				return s[i] < b.s[i];
			}
		}


		return false;
	}

	bool operator<=(const BigInteger& b)
	{
		return !(*this > b);
	}

	bool operator>=(const BigInteger& b)
	{
		return !(*this < b);
	}

	bool operator==(const BigInteger& b)
	{
		return !(*this < b) && !(*this > b);

	}

	bool operator!=(const BigInteger& b)
	{
		return *this < b || *this > b;
	}

	friend ostream& operator << (ostream& out, const BigInteger& x)
	{
		out << x.s.back();//最高位不足8位的预防处理

		int i;

		for (i = x.s.size() - 2; i >= 0; i--) {

			char buf[20];
#ifdef LINUX
			sprintf(buf, "%08d", x.s[i]);//不足8位补0
#else
			sprintf_s(buf, "%08d", x.s[i]);//不足8位补0
#endif
			for (int j = 0; j < strlen(buf); j++)

				out << buf[j];

		}

		return out;
	}

	friend istream& operator >> (istream& in, BigInteger& x)
	{
		string s;
		if (!(in >> s))
		{
			return in;
		}
		x = s;
		return in;
	}
};



