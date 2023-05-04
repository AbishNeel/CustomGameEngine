#pragma once
#include "ActionList.h"

namespace FieaGameEngine
{
	class ActionExpression final :public Action
	{
		RTTI_DECLARATIONS(ActionExpression, Action);

	public:
		ActionExpression();
		void Update(GameState& gameState)override;

		ActionExpression* Clone() const override;

		Vector<std::string> TokenizeString(std::string& stringToTokenize);
		std::string expression;
		static Vector<Signature> Signatures();
		Vector<std::string> ConvertRPN(std::string algebraicExpression);
		double Evaluate(Vector<std::string> infixExpr);
		bool IsNumber(const std::string& token);
		bool IsOperator(const std::string& token);
		bool IsOpenBracket(const std::string& token);
		bool IsClosedBracket(const std::string& token);
		bool IsBracket(const std::string& token);

	private:
		enum  class OrderOfEvaluation 
		{ 
			LeftToRight, 
			RightToLeft 
		};

		bool _parentFound{ false };
		Scope* _parentScope{ this };
		
		HashMap<std::string, std::pair<std::int32_t, OrderOfEvaluation>> _operatorsPrecedenceMap;
	};

	ConcreteFactory(ActionExpression, Scope)
}