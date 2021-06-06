#include <iostream>
#include <string>
// #include <cmath>
// #include <cstdio>
// #include <vector>
// #include <tuple>
#include <random>



using namespace std;


#define PRIME_NUM 2069 //!< a carefully chosen prime number
static void println(string str)
{
    cout << str + "\n";
}

string genRandomString(const int len)
{
    static const char letters[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    string str;
    str.reserve(len);

    random_device generator; // use default_random_engine to have something deterministic
    uniform_int_distribution<int> distribution(0, sizeof(letters)-1);


    for (int i = 0; i<len; i++)
    {
        str += letters[distribution(generator)];
    }
    return str;

}



/*! Simple hashing function
    Works on strings
    \param key: some string
    \return hash table index
*/
int oha1(string key)
{
    int idx = 0;
    for (string::size_type i = 0; i < key.size(); i++)
    {
        idx += (i+1) * key[i];
    }
    return idx % PRIME_NUM;
}

int main ()
{


    int idx = oha1("defabcc");

    println(to_string(idx));

    string test = genRandomString(5);
    println(test);

    return 0;
}
