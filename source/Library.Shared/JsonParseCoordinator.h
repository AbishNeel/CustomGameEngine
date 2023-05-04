#pragma once
#include "RTTI.h"
#include "Vector.h"
#include <iostream>
#include <json/json.h>
#include <gsl/gsl>

namespace FieaGameEngine
{
	class IJsonParseHelper;

	/// <summary>
	/// Class that coordinates the parsing of a Json value/file by delegating the task to appropriate helpers.
	/// </summary>
	class JsonParseCoordinator
	{
	public:
		/// <summary>
		/// Wrapper class that is used to share data between ParseCoordinator and Helpers.
		/// </summary>
		class Wrapper : public RTTI
		{
			RTTI_DECLARATIONS(Wrapper, RTTI);

			friend JsonParseCoordinator;
		public:
			virtual [[nodiscard]] std::shared_ptr<Wrapper> Create() const = 0;

			virtual void Initialize() {};

			virtual void Cleanup() {};

			virtual ~Wrapper() = default;

			/// <summary>
			/// Function to get the current nesting depth of the Wrapper.
			/// </summary>
			/// <returns> The current nesting depth of the Wrapper. </returns>
			std::uint32_t Depth() const;

		protected:
			/// <summary>
			/// Function to increment the nesting depth of the Wrapper.
			/// </summary>
			void IncrementDepth();

			/// <summary>
			/// Function to decrement the nesting depth of the Wrapper.
			/// </summary>
			void DecrementDepth();

			std::uint32_t _nestingDepth{ 0 };
		};

		/// <summary>
		/// Constructor to construct a ParseCoordinator object by passing in a shared_ptr to a Wrapper.
		/// </summary>
		/// <param name="wrapper"> shared_ptr to a Wrapper. </param>
		explicit JsonParseCoordinator(std::shared_ptr<Wrapper> wrapper);

		JsonParseCoordinator(const JsonParseCoordinator& other) = delete;

		/// <summary>
		/// Move constructor to construct a ParseCoordinator by moving over the contents of an existing ParseCoordinator, onto the newly constructed one.
		/// </summary>
		/// <param name="other"> Rvalue reference to the ParseCoordinator to be moved onto the new object. </param>
		JsonParseCoordinator(JsonParseCoordinator&& other) noexcept;

		JsonParseCoordinator& operator=(const JsonParseCoordinator& rhs) = delete;

		/// <summary>
		/// Move assignment operator to move over the contents of an existing ParseCoordinator, onto "this" one.
		/// </summary>
		/// <param name="other"> Rvalue reference to the ParseCoordinator to be moved onto this object. </param>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& rhs) noexcept;

		/// <summary>
		/// Method to Clone the contents of the ParseCoordinator. Creates new instances of any owned Wrappers and Helpers.
		/// </summary>
		/// <returns> Pointer to the newly Cloned ParseCoordinator. </returns>
		gsl::owner<JsonParseCoordinator*> Clone() const;

		/// <summary>
		/// Function to add a Helper to the list of Helpers for the ParseCoordinator.
		/// </summary>
		/// <param name="helper"> shared_ptr to the Helper to be added. </param>
		void AddHelper(std::shared_ptr<IJsonParseHelper> helper);

		/// <summary>
		/// Function to remove an existing Helper from the list of Helpers from the ParseCoordinator.
		/// </summary>
		/// <param name="helper"> shared_ptr to the Helper to be removed. </param>
		void RemoveHelper(std::shared_ptr<IJsonParseHelper> helper);

		/// <summary>
		/// Function to get the Wrapper being used by the ParseCoordinator.
		/// </summary>
		/// <returns> shared_ptr to the Wrapper being used by the ParseCoordinator. </returns>
		std::shared_ptr<Wrapper> GetWrapper() const;

		/// <summary>
		/// Sets the Wrapper being used by the ParseCoordinator.
		/// </summary>
		/// <param name="wrapper"> shared_ptr to the Wrapper to set. </param>
		void SetWrapper(std::shared_ptr<Wrapper> wrapper);

		/// <summary>
		/// Function to deserialize an object with a given input stream.
		/// </summary>
		/// <param name="stream"> Reference to the input stream containing the data to be parsed. </param>
		void DeserializeObject(std::istream& stream);

		/// <summary>
		/// Function to deserialize an object with a given file name.
		/// </summary>
		/// <param name="filename"> The name of the file containing the data to be parsed. </param>
		void DeserializeObjectFromFile(const std::string& filename);

		/// <summary>
		/// Function to deserialize an object with a given Json string.
		/// </summary>
		/// <param name="jsonString"> The Json string to be parsed. </param>
		void DeserializeObject(const Json::String& jsonString);

		/// <summary>
		/// Function to get the list of all Helpers of the ParseCoordinator.
		/// </summary>
		/// <returns> Vector containing all the Helpers of the ParseCoordinator. </returns>
		Vector<std::shared_ptr<IJsonParseHelper>>& GetHelpers();

	private:
		/// <summary>
		/// Function to parse all the members of a given Json::Value object.
		/// </summary>
		/// <param name="jsonValue"> The Json::Value object to be parsed. </param>
		/// <param name="isArrayElement"> bool indicating whether or not the Json:Value object is an array element. Defaulted to false. </param>
		/// <param name="index"> The index of the object within it's array, if it is an array element. Defaulted to 0 if not an array element. </param>
		void ParseMembers(const Json::Value& jsonValue, std::size_t index = 0);

		/// <summary>
		/// Function to parse a key value pair of a string and Json::Value object.
		/// </summary>
		/// <param name="key"> The key corresponding to the Json::Value object. </param>
		/// <param name="jsonValue"> The Json::Value object to be parsed. </param>
		/// <param name="isArrayElement"> Whether or not the Json::Value is an array element. </param>
		/// <param name="index"> The index of the object within it's array, if it is an array element. Defaulted to 0 if not an array element. </param>
		void Parse(const std::string& key, const Json::Value& jsonValue, std::size_t index = 0);

		std::shared_ptr<Wrapper> _wrapper{ nullptr };

		Vector<std::shared_ptr<IJsonParseHelper>> _helpers{ 17 };
	};
}