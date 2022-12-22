#include<iostream>
#include<string>
#include<stack>

using namespace std;

double evaluate(string s)
{
	stack<char> ops;
	stack<double> vals;
	int i = 0;
	while (i < int(s.length()))
	{
		char tok = s[i];//{}[]
		
		//get number
		bool isNum = false;
		int cii = int(s[i]) - 48;
		double num = 0;
		while (cii >= 0 && cii <= 9)
		{
			isNum = true;
			num = num * 10 + cii;
			cii = int(s[++i]) - 48;
		}
		//end

		if (isNum) {i--; vals.push(num);}//add last is number
		else if (tok == '+' || tok == '-' || tok == '*' || tok == '/') ops.push(tok);
		else if (tok == ')') {
			char     op = ops.top();  ops.pop();
			double val2 = vals.top(); vals.pop();
			double val1 = vals.top(); vals.pop();

			if (op == '+') vals.push(val1 + val2);
			else if (op == '-') vals.push(val1 - val2);
			else if (op == '*') vals.push(val1 * val2);
			else vals.push(val1 / val2);
		}
		i++;
	}
	return vals.top();
}

int main()
{
	string s;
	cout << "Input string: ";
	getline(cin, s);

	//caculate
	cout << "----> Result: " << evaluate(s) << endl;
	
	return 0;
}