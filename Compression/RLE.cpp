#include<iostream>
#include<string>

using namespace std;

string encode(string s)
{
	string res = "";
	s += " ";
	char prev = ' ';
	int cnt = 0;

	for (char x : s)
		if (x != prev) {
			if (cnt != 0) res += to_string(cnt) + prev;
			cnt = 1;
			prev = x;
		}
		else cnt++;

	return res;
}

string decode(string s)
{
	string res = "";
	int num = 0;

	for (char x : s)
		if (int(x) >= 48 && int(x) <= 57) num = num * 10 + int(x) - 48;
		else while (num > 0 && num--) res += x;

	return res;
}

int main()
{
	string s;
	/*--------------------------------------------------*/
	cout << "Input string encode: ";
	getline(cin, s);
	
	//encode
	s = encode(s);
	cout << "----> Encode string: " << s << endl;

	//check encode
	s = decode(s);
	cout << "----> Decode string: " << s << endl;

	cout << "\nInput string decode: ";
	getline(cin, s);

	/*--------------------------------------------------*/
	//decode
	s = decode(s);
	cout << "----> Decode string: " << s << endl;
	
	//check decode
	s = encode(s);
	cout << "----> Encode string: " << s << endl;

	return 0;
}