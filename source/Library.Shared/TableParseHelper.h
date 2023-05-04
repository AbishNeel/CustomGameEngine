#pragma once
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"
#include "Scope.h"
#include "Stack.h"

namespace FieaGameEngine
{
	/// <summary>
	/// ParseHelper that helps deserializing a Table/Scope object.
	/// </summary>
	class TableParseHelper final : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(TableParseHelper, IJsonParseHelper);

	public:
		/// <summary>
		/// Wrapper that can hold Table/Scope data and can be used to parse only Table/Scope objects.
		/// </summary>
		class TableWrapper final : public JsonParseCoordinator::Wrapper
		{
			friend TableParseHelper;

			RTTI_DECLARATIONS(TableWrapper, JsonParseCoordinator::Wrapper);

			struct Context final
			{
				std::string key;
				Scope* scope;
			};

		public:

			/// <summary>
			/// Virtual constructor for TableWrapper.
			/// </summary>
			/// <returns> A shared_ptr to a newly created TableWrapper instance. Cannot be discarded. </returns>
			[[nodiscard]] std::shared_ptr<Wrapper> Create() const override;

			std::shared_ptr<Scope> Data;
		};

		/// <summary>
		/// Default constructor for TableParseHelper
		/// </summary>
		TableParseHelper();

		/// <summary>
		/// Destructor for TableParseHelper that cleans up any memory allocated by the object.
		/// </summary>
		~TableParseHelper();

		/// <summary>
		/// Initialize method which initializes any data before parsing begins.
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// Copies the parsed data into the wrapper once the Helper is done parsing.
		/// </summary>
		/// <param name="wrapper"> The wrapper being used to share data between the ParseCoordinator and Helper. </param>
		/// <returns> True if the data was successfully copied, false if not. </returns>
		bool CopyData(JsonParseCoordinator::Wrapper& wrapper) override;

		/// <summary>
		/// Virtual constructor for TableParseHelper.
		/// </summary>
		/// <returns> A shared pointer to a newly created TableParseHelper instance. Cannot be discarded. </returns>
		[[nodiscard]] std::shared_ptr<IJsonParseHelper> Create() const override;

		/// <summary>
		/// Starts the handling of a passed in key-value pair.
		/// </summary>
		/// <param name="wrapper"> The wrapper being used to share data between the ParseCoordinator and Helper. </param>
		/// <param name="key"> The key of the key-value pair to be handled. </param>
		/// <param name="value"> The value of the key-value pair to be handled. </param>
		/// <param name="index"> Index of the element if it is an array element. Defaulted to 0. </param>
		/// <returns> True if the key-value pair was handled, false otherwise.</returns>
		bool StartHandler(JsonParseCoordinator::Wrapper& wrapper, const std::string& key, const Json::Value& value, std::size_t index = 0) override;

		/// <summary>
		/// Ends the handling of a value associated with a given key.
		/// </summary>
		/// <param name="wrapper"> The wrapper being used to share data between the ParseCoordinator and Helper. </param>
		/// <param name="key"> The key of the key-value pair to be handled. </param>
		/// <returns> True if the key-value pair was handled, false otherwise. </returns>
		bool EndHandler(JsonParseCoordinator::Wrapper& wrapper, const std::string& key) override;

	private:
		/// <summary>
		/// Sets the value of the Datum's element at the specified inde to the passed in value.
		/// </summary>
		/// <param name="datum"> The Datum to which the element is to be inserted/updated. </param>
		/// <param name="value"> The value to set the element's value to. </param>
		/// <param name="index"> The index of element whose value is to be set. Dafaulted to 0. </param>
		void SetDatumValue(Datum& datum, const Json::Value& value, std::size_t index = 0);

		HashMap<std::string, Datum::DatumTypes> _datumTypeMap;

		Stack<TableWrapper::Context> _contextStack;

		std::string _concreteTypeName{};
	};
}