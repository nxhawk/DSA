#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

//function check is exist word in library => index
int isExist(string ch, vector<string> lib)
{
	for (int i = 0; i < lib.size(); i++)
		if (ch == lib.at(i)) return i;
	return -1;
}

//print library (key, word)
void printLib(vector<string> lib)
{
	cout << "Open Library\n";
	for (int i = 0; i < lib.size(); i++) cout << i << ": " << lib.at(i) << endl;
	cout << "Close Library\n\n";
}

//print vector Encode 
void printEncode(vector<int> res)
{
	cout << "Encode string: ";
	for (int x : res) cout << x << " ";
	cout << endl;
}

//encode (string, library = null) => vector encode (& library)
vector<int> encode(string s, vector<string>& lib)
{
	//init library order
	string tmp = s;
	sort(tmp.begin(), tmp.end());

	lib.clear();// clear to create new lib
	for (char ch : tmp)
	{
		string x(1, ch);
		if (isExist(x, lib) == -1) lib.push_back(x);
	} 
	
	//encode and add word to library
	string w = "";
	vector<int> res;//encode vector
	for (char k: s) {
		string wk = w + k;
		if (isExist(wk, lib) != -1) w = wk;
		else {
			res.push_back(isExist(w, lib));
			lib.push_back(wk);
			w = k;
		}
	}
	res.push_back(isExist(w, lib));
	
	return res;
}

//decode (encode vector, library) => string decode
string decode(vector<int> res, vector<string> &lib)
{
	//clear lib to only character
	while (lib.at(lib.size() - 1).length() == 2) lib.pop_back();
	
	string s = "", w = "";
	
	int c = res.at(0);
	w = lib.at(c);
	s += w;
	for (int i = 1; i < res.size(); i++)
	{
		c = res.at(i);
		if (c < lib.size()) {
			string tmp = w;
			w = lib.at(c);
			tmp += w[0];
			if (isExist(tmp, lib) == -1) lib.push_back(tmp);
		}else {
			string tmp = w + w[0];
			if (isExist(tmp, lib) == -1) lib.push_back(tmp);
			w = lib.at(c);
		}
		s += w;
	} 

	return s;
}

int main()
{
	string s;
	vector<string> lib;
	vector<int> res;

	cout << "Input string:  ";
	getline(cin, s);
	cout << endl;
	
	//encode
	res = encode(s, lib);
	printEncode(res);
	printLib(lib);

	//decode
	s = decode(res, lib);
	cout << "Decode string: " << s << endl;
	printLib(lib);

	//check encode
	res = encode(s, lib);
	printEncode(res);
	
	return 0;
}