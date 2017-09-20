#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include <stdlib.h> 
#include <sstream>
#include <algorithm>
#include <iterator>
#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;

string toPolishNotation(string input){
	queue<string> numbers;
	stack<string> operators;
	string result;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] >= '0'&&input[i] <= '9')
		{
			string number;
			//iterates untill the number ends
			for (; i+1< input.length() && (input[i] >= '0'&&input[i] <= '9'); i++)
			{
				number += input[i];
			}
			numbers.push(number);
			i--;
		} 
		else if (input[i] == '+' || input[i] == '-' || input[i] == '(')
		{
			string num;
			num += input[i];
			operators.push(num);
		}
		else if (input[i] == 'e')
		{
			numbers.push("2.71828");
		}
		else if (input[i] == '*' || input[i] == '/')
		{
			string num;
			num += input[i];
			if (!operators.empty()){
				if (operators.top() == "/" || operators.top() == "*")
				{
					numbers.push(operators.top());
					operators.pop();
					operators.push(num);
				}
				else{
					operators.push(num);
				}
			}
			else{
				operators.push(num);
			}
		}
		else if (input[i] == ')')
		{
			string num;
			num += input[i];
			while (!(operators.top() == "("))
			{
				numbers.push(operators.top());
				operators.pop();
			}
			operators.pop();
		}
		else if (input[i] == ',')
		{
			string num;
			num += input[i];
			while (!(operators.top() == "("))
			{
				numbers.push(operators.top());
				operators.pop();
			}
		}
		//tan sin cos cotg pow root log
		else
		{
			string functions = input.substr(i, 3);
			if (functions == "pow" || functions == "sin" || functions == "cos" || functions == "log" || functions=="tan"){
				operators.push(functions);
			}
			string  functions4= input.substr(i, 4);
			if (functions4 == "cotg" || functions4 == "sqrt"){
				operators.push(functions4);
			}
			string functions2 = input.substr(i, 2);
			if (functions2 == "pi"){
				numbers.push("3.14");
			}
		}
	}
	while (!operators.empty()){
		numbers.push(operators.top());
		operators.pop();
	}
	while (!numbers.empty()){
		result+=numbers.front()+" ";
		numbers.pop();
	}

	return result;
}

int main(){

		string input;
		stack<double> result;
		
		cin >> input;
		input += "aa";
		string rpn = toPolishNotation(input);
		istringstream iss(rpn);

		vector<string> splitted{ istream_iterator < string > {iss},
			istream_iterator < string > {} };
		for (int i = 0; i < splitted.size(); i++){
			double number = atoi(splitted[i].c_str());
			string operation = splitted[i];
			if (number || operation == "0"){
				result.push(number);
			}
			else{
				if (operation == "+"){
					double num1 = result.top();
					result.pop();
					double num2 = result.top();
					result.pop();
					result.push(num1 + num2);
				}
				if (operation == "*"){
					double num1 = result.top();
					result.pop();
					double num2 = result.top();
					result.pop();
					result.push(num1 * num2);
				}
				if (operation == "/"){
					double num1 = result.top();
					result.pop();
					double num2 = result.top();
					result.pop();
					result.push(num2 / num1);
				}
				if (operation == "-"){
					double num1 = result.top();
					result.pop();
					double num2 = result.top();
					result.pop();
					result.push(num2 - num1);
				}
				if (operation == "pow"){
					double num1 = result.top();
					result.pop();
					double num2 = result.top();
					result.pop();
					result.push(pow(num2, num1));
				}
				if (operation == "sin"){
					double num1 = result.top();
					result.pop();
					result.push(sin(num1));
				}
				if (operation == "cos"){
					double num1 = result.top();
					result.pop();
					result.push(cos(num1));
				}
				if (operation == "tan"){
					double num1 = result.top();
					result.pop();
					result.push(tan(num1));
				}
				if (operation == "log"){
					double num1 = result.top();
					result.pop();
					double num2 = result.top();
					result.pop();
					result.push(log(num2) / log(num1));
				}
				if (operation == "cotg"){
					double num1 = result.top();
					result.pop();
					result.push(1 / tan(num1));
				}
				if (operation == "sqrt"){
					double num1 = result.top();
					result.pop();
					result.push(sqrt(num1));
				}
			}
		}
		cout << result.top();


		return 0;
}
