#include "BigInteger.h"


int main()
{
//    string sa = "12345678012345678";
 //   string sb = "123456789123456789";
 /*   string sa = "10000";
    string sb = "10000";*/
    string sa = "4800564564";
    string sb = "4864564";
   /* string sa = "100445566";
    string sb = "11445566";*/
    BigInteger a;
    a = sa;
    BigInteger b;
    b = sb;
    BigInteger c;
    c = a * b;

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    BigInteger d;
    d = a - b;
    cout << d << endl;

    BigInteger e;
    e = a / b;
    cout << e << endl;

    BigInteger in;
    cin >> in;
    cout << in << endl;


    return 0;
}