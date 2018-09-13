#include <string>
#include <iostream>
#include <stdio.h>    
#include <stack> 
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

class Parser
{
private:
	map<char, int> op_precedence = 
	{
		{ '+', 10 },
		{ '-', 10 },
		{ '*', 20 },
		{ '/', 20 },
	};

	bool isOperator(char op)
	{
		if (op == '+') return true;
		if (op == '-') return true;
		if (op == '*') return true;
		if (op == '/') return true;

		return false;
	}

	bool isLeftBracket(char br)
	{
		if (br == '(') return true;

		return false;
	}

	bool isRightBracket(char br)
	{
		if (br == ')') return true;

		return false;
	}

public :
	string getPostfixExpression(string expression)
	{
		//cout << "Input:  " << expression << endl;

		string output;
		stack <char> operators;
		bool isOp = true;

		for (char ch : expression) 
		{
			if (isdigit(ch) || ch == '.')
			{
				if (isOp) output.push_back(' ');
				isOp = false;
				output.push_back(ch);
			}
			else if (isOperator(ch))
			{
				if (isOp)
				{
					output.push_back(' ');
					output.push_back('$');
					continue;
				}

				isOp = true;

				while (!operators.empty() && (op_precedence[operators.top()] >= op_precedence[ch]) && !isLeftBracket(operators.top()))
				{
					output.push_back(' ');
					output.push_back(operators.top());
					operators.pop();
				}
				operators.push(ch);
			}
			else if (isLeftBracket(ch))
			{
				operators.push(ch);
			}
			else if (isRightBracket(ch))
			{
				while (!isLeftBracket(operators.top()))
				{
					output.push_back(' ');
					output.push_back(operators.top());
					operators.pop();
				}
				operators.pop();
			}
		}

		while (!operators.empty())
		{
			output.push_back(' ');
			output.push_back(operators.top());
			operators.pop();
		}

		//cout << "Output: " << output << endl;
		return output;
	}
};

struct Node
{
	bool sign;
	string value;
	Node *left;
	Node *right;
};

class ExpressionTree
{
private:
	bool isOperator(string op)
	{
		if (op == "+") return true;
		if (op == "-") return true;
		if (op == "*") return true;
		if (op == "/") return true;

		return false;
	}

	bool isNumber(string nr)
	{
		try
		{
			stod(nr);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	Node *newNode(string value, bool sign)
	{
		Node *temp = new Node;
		temp->left = NULL;
		temp->right = NULL;
		temp->sign = sign;
		temp->value = value;
		return temp;
	};

public:
	Node *createExpressionTree(string postfixExpression)
	{
		stack<Node*> stack;
		Node *node, *left, *right;

		istringstream buf(postfixExpression);
		istream_iterator<string> beg(buf), end;
		vector<string> tokens(beg, end); 

		for (auto& value : tokens)
		{
			if (isNumber(value))
			{
				bool sign = false;
				while (!stack.empty() && stack.top()->value == "$")
				{
					sign = !sign;
					stack.pop();
				}

				node = newNode(value, sign);
				stack.push(node);
			}
			else if (isOperator(value))
			{
				bool sign = false;
				node = newNode(value, sign);

				right = stack.top();
				stack.pop();

				left = stack.top();
				stack.pop();

				node->left = left;
				node->right = right;

				stack.push(node);
			}
			else
			{
				node = newNode(value, false);
				stack.push(node);
			}
		}

		node = stack.top();
		stack.pop();

		return node;
	}

	void showExpressionTree(Node *tree)
	{
		if (tree == NULL)
		{
			return;
		}

		string sign = tree->sign ? "true" : "false";
		cout << "node : " << tree->value << " " << sign << endl;

		showExpressionTree(tree->left);
		showExpressionTree(tree->right);
	}

	double evaluateExpressionTree(Node *tree)
	{
		if (tree == NULL)
		{
			return 0;
		}

		if (tree->value == "+")
		{
			double left = evaluateExpressionTree(tree->left);
			double right = evaluateExpressionTree(tree->right);
			return  left + right ;
		}
		else if (tree->value == "-")
		{
			double left = evaluateExpressionTree(tree->left);
			double right = evaluateExpressionTree(tree->right);
			return  left - right;
		}
		else if (tree->value == "*")
		{
			double left = evaluateExpressionTree(tree->left);
			double right = evaluateExpressionTree(tree->right);
			return  left * right;
		}
		else if (tree->value == "/")
		{
			double left = evaluateExpressionTree(tree->left);
			double right = evaluateExpressionTree(tree->right);
			return  left / right;
		} 
		else if (isNumber(tree->value))
		{
			double result = stod(tree->value);
			return tree->sign ? -result : result;
		}

		return 0;
	}
};

double calc(string expression) 
{
	Parser parser;
	string postfixExpr = parser.getPostfixExpression(expression);

	ExpressionTree et;
	Node *tree = et.createExpressionTree(postfixExpr);

	double result = et.evaluateExpressionTree(tree);

	return result;
}

int main()
{
	//cout << "Result: " << calc("-1 + -2 * -(3 - 4 / 5)") << endl;
	//cout << "Result: " << calc("3 + 4 * 2 / (1 - 5)") << endl;
	//cout << "Result: " << calc("(2 / (1 + 5.23) * 4) - -6") << endl;
	cout.precision(20);
	cout << "Result: " << calc("86 + -56 * -22 / -73 * -96 - 48 - 5 * 25") << endl;
	cout << "Result: " << calc("1 + 1") << endl;
	cout << "Result: " << calc("8/16") << endl;
	cout << "Result: " << calc("3 -(-1)") << endl;
	cout << "Result: " << calc("2 + -2") << endl;
	cout << "Result: " << calc("10- 2- -5") << endl;
	cout << "Result: " << calc("(((10)))") << endl;
	cout << "Result: " << calc("3 * 5") << endl;
	cout << "Result: " << calc("-7 * -(6 / 3)") << endl;

	return 0;
}