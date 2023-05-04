#include "pch.h"
#include "ActionExpression.h"
#include <stack>
#include <sstream>
#include <string>
#include <regex>

using namespace std::string_literals;
using namespace std;

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionExpression);

	ActionExpression::ActionExpression() 
		: Action(ActionExpression::TypeIdClass())
	{
		_operatorsPrecedenceMap.Insert(std::make_pair("^", std::make_pair(4, OrderOfEvaluation::RightToLeft)));
		_operatorsPrecedenceMap.Insert(std::make_pair("*", std::make_pair(3, OrderOfEvaluation::LeftToRight)));
		_operatorsPrecedenceMap.Insert(std::make_pair("/", std::make_pair(3, OrderOfEvaluation::LeftToRight)));
		_operatorsPrecedenceMap.Insert(std::make_pair("+", std::make_pair(2, OrderOfEvaluation::LeftToRight)));
		_operatorsPrecedenceMap.Insert(std::make_pair("-", std::make_pair(2, OrderOfEvaluation::LeftToRight)));
	}

	ActionExpression* ActionExpression::Clone() const
	{
		return new ActionExpression{ *this };
	}

	void ActionExpression::Update(GameState&)
	{
		Vector<std::string> rpnExpression = ConvertRPN(expression);
		auto finalValue = Evaluate(rpnExpression);
		expression = std::to_string(finalValue);
	}

	Vector<std::string> ActionExpression::TokenizeString(std::string& stringToTokenize)
	{
		Vector <string> tokens;
		stringstream intermediate(stringToTokenize);
		std::string temp;
		while (getline(intermediate, temp, ' '))
		{
			tokens.PushBack(temp);
		}
		return tokens;
	}

	Vector<Signature> ActionExpression::Signatures()
	{
		return Vector<Signature>
		{
			{"Expression", Datum::DatumTypes::String, 1, offsetof(ActionExpression, expression)}
		};
	}

	Vector<std::string> ActionExpression::ConvertRPN(std::string algebraicExpression)
	{
		std::stack<std::string> operatorStack;
		Vector<std::string> infixParsedOutput;
		auto tokens = TokenizeString(algebraicExpression);

		for (auto& token : tokens)
		{
			if (IsNumber(token))
			{
				infixParsedOutput.PushBack(token);

			}
			else if (IsOperator(token) || IsBracket(token))
			{
				if (!IsOpenBracket(token))
				{
					while (!operatorStack.empty() && (IsClosedBracket(token) && !IsOpenBracket(operatorStack.top())) ||
						((IsOperator(operatorStack.top()) && _operatorsPrecedenceMap.Find(operatorStack.top())->second.second >= _operatorsPrecedenceMap.Find(token)->second.second &&
							(_operatorsPrecedenceMap.Find(token)->second.second == OrderOfEvaluation::LeftToRight))))
					{

						infixParsedOutput.PushBack(operatorStack.top());
						operatorStack.pop();


					}
					if (IsClosedBracket(token))
					{
						operatorStack.pop();
					}
				}
				if (!IsClosedBracket(token))
				{
					operatorStack.push(token);
				}
			}

			else
			{
				infixParsedOutput.PushBack(token);
			}
		}
		while (!operatorStack.empty())
		{
			infixParsedOutput.PushBack(operatorStack.top());
			operatorStack.pop();
		}

		return infixParsedOutput;

	}

	double ActionExpression::Evaluate(Vector<std::string> infixExpr)
	{
		Vector<double> numberStack;
		for (auto& token : infixExpr)
		{
			if (IsNumber(token))
			{
				numberStack.PushBack(std::stod(token));
			}
			else
			{
				double firstOperand = 0;
				double seconOperand = 0;

				if (IsOperator(token))
				{
					seconOperand = numberStack.Back();
					numberStack.PopBack();
					firstOperand = numberStack.Back();
					numberStack.PopBack();
				}
				if (token == "*")
				{
					numberStack.PushBack(firstOperand * seconOperand);
				}
				else if (token == "/")
				{
					numberStack.PushBack(firstOperand / seconOperand);
				}
				else if (token == "-")
				{
					numberStack.PushBack(firstOperand - seconOperand);
				}
				else if (token == "+")
				{

					numberStack.PushBack(firstOperand + seconOperand);
				}
				else if (token == "^")
				{
					numberStack.PushBack(std::pow(firstOperand, seconOperand));
				}
				else if (token.find(".") != std::string::npos)
				{
					_parentScope = this;
					_parentFound = false;
					Vector <string> tokens;
					stringstream intermediate(token);
					std::string temp;
					while (getline(intermediate, temp, '.'))
					{
						tokens.PushBack(temp);
					}

					while (_parentScope != nullptr && !_parentFound)
					{
						Datum& parentDatum = *_parentScope->Search("Name");

						for (std::size_t i = 0; i < parentDatum.Size(); ++i)
						{
							if (parentDatum.Find(tokens[0]) != parentDatum.Size())
							{
								_parentFound = true;
							}
						}
						if (!_parentFound)
							_parentScope = _parentScope->GetParent();

					}

					if (_parentScope->Search(tokens[1])->Type() == Datum::DatumTypes::Integer)
					{
						numberStack.PushBack(_parentScope->Search(tokens[1])->Get<std::int32_t>());
					}
					else
					{
						numberStack.PushBack(_parentScope->Search(tokens[1])->Get<float>());
					}


				}
				else
				{
					auto& datum = *Search(token);
					double d;
					if (datum.Type() == Datum::DatumTypes::Integer)
					{
						d = datum.Get<std::int32_t>();
					}
					else
					{
						d = datum.Get<float>();
					}

					numberStack.PushBack(d);

				}
			}

		}
		return numberStack.Back();
	}


	bool ActionExpression::IsNumber(const std::string& token)
	{
		return std::regex_match(token, std::regex{ R"z((\d+(\.\d*)?|\.\d+)([Ee][\+\-]?\d+)?)z" });
	}

	bool ActionExpression::IsOperator(const std::string& token)
	{
		return _operatorsPrecedenceMap.ContainsKey(token);
	}

	bool ActionExpression::IsOpenBracket(const std::string& token)
	{
		return token._Equal("(");
	}

	bool ActionExpression::IsClosedBracket(const std::string& token)
	{
		return token._Equal(")");
	}

	bool ActionExpression::IsBracket(const std::string& token)
	{
		return (IsOpenBracket(token) || IsClosedBracket(token));
	}



}