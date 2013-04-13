// ****************************************************************************
//  myString   version:  1.0   Ankur Sheel  date: 2011/03/08
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#ifndef myString_h__
#define myString_h__

#include "BaseDefines.h"
#include <string>
#include <iostream>
#include <vector>

namespace Base
{
	template<class T>
	class tOptional;
}

namespace Base
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief String class 
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class cString
	{
	public:
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cString();
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] s The char array to be used for initialization
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cString(const char * s);
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] s The string to be used for initialization
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cString(std::string const & s);
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] lpFmt The fromat control
		/// @param[in] ... variable number of arguments 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API explicit cString(const int iMaxSize, const char * const  lpFmt, ...);
		///////////////////////////////////////////////////////////////////////
		/// Copy Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cString(const cString & str); // ankur - move to private when changing back to char * instead of string
		///////////////////////////////////////////////////////////////////////
		/// Assignment Operator
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cString & operator=(const cString & str);
		///////////////////////////////////////////////////////////////////////
		/// Adds the passed in string to the current string
		///
		/// @param[in] str The string to be added to this string
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void operator +=(const cString & str);
		///////////////////////////////////////////////////////////////////////
		/// Returns true if the current string is less than the passed in string
		///
		/// @param[in] str The string to be compared to this string
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API bool operator <(const cString & str) const;
		//BASE_API bool operator == (const char * szRight) const;
		///////////////////////////////////////////////////////////////////////
		/// Returns true if the current string is equal to the passed in string
		///
		/// @param[in] str The string to be compared to this string
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API bool operator ==(const cString & str) const;
		///////////////////////////////////////////////////////////////////////
		/// Returns the character at the specified index in the string. Returns
		/// null, if the index is greater than the length of the string.
		///
		/// @param[in] index The index of the position of the element to be
		/// accessed
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API const char operator[](const unsigned int index) const;
		///////////////////////////////////////////////////////////////////////
		/// Returns the character at the specified index in the string. Returns
		/// null, if the index is greater than the length of the string.
		///
		/// @param[in] index The index of the position of the element to be
		/// accessed
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API char operator[](const unsigned int index);
		///////////////////////////////////////////////////////////////////////
		/// Returns the contents of a string as a C-style, null-terminated string.
		///
		/// @return The contents of a string as a C-style, null-terminated string.
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API const char * const GetData() const;
		///////////////////////////////////////////////////////////////////////
		/// Returns True if the string is empty.
		///
		/// @return True if the string is empty
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API bool IsEmpty() const ;
		///////////////////////////////////////////////////////////////////////
		/// Returns the length of the string
		///
		/// @return The length of the string
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API unsigned int GetLength() const;
		///////////////////////////////////////////////////////////////////////
		/// Returns the substring of the string from uiStartIndex to uiEndIndex.
		/// uiStartIndex anduiEndIndex are between 0 and string length
		///
		/// @param[in] uiStartIndex The start index for the substring
		/// @param[in] uiEndIndex The end index for the substring
		/// @return The substring of the string starting from uiStartIndex
		/// to uiEndIndex
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cString GetSubString(const unsigned int uiStartIndex,
			const unsigned int uiEndIndex) const;
		///////////////////////////////////////////////////////////////////////
		/// Searches the string for the first occurrence of a character starting
		/// from an offset.
		///
		/// @param[in] chChar The character to be found
		/// @param[in] iOffset The index to start the search from
		/// @return The index of the character when successful. Invalid optional
		/// otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindIndex(const char chChar,
			const int iOffset) const;
		///////////////////////////////////////////////////////////////////////
		/// Searches the string for the first occurrence of any of the passed in 
		/// characters starting from an offset.
		///
		/// @param[in] strChars The characters for which the function is to search
		/// @param[in] iOffset The index to start the search from
		/// @return The index of the first character that is found when successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindFirstOf(const cString & strChars,
			const int iOffset) const;
		///////////////////////////////////////////////////////////////////////
		/// Searches the string for the first character thats is not any of the passed in 
		/// characters starting from an offset.
		///
		/// @param[in] strChars The characters for which the function is to search
		/// @param[in] iOffset The index to start the search from
		/// @return The index of the first character that is found when successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindFirstNotOf(const cString & strChars,
			const int iOffset) const;
		///////////////////////////////////////////////////////////////////////
		/// Searches the string for the last occurrence of any of the passed in 
		/// characters till an offset.
		///
		/// @param[in] strChars The characters for which the function is to search
		/// @param[in] iOffset The index at which the search should end
		/// @return The index of the last character that is found when successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindLastOf(const cString & strChars,
			const int iOffset) const;
		///////////////////////////////////////////////////////////////////////
		/// Searches the string for the last character thats is not any of the
		///  passed in characters till an offset.
		///
		/// @param[in] strChars The characters for which the function is to search
		/// @param[in] iOffset The index at which the search should end
		/// @return The index of the last character that is found when successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindLastNotOf(const cString & strChars,
			const int iOffset) const;
		///////////////////////////////////////////////////////////////////////
		/// Case Insensitive comparison of current string with passed in string
		///
		/// @param[in] str The string to be compared
		/// @return True if the strings are identical. False otherwise
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API bool CompareInsensitive (const cString & str) const;
		///////////////////////////////////////////////////////////////////////
		/// Removes whitespace characters from the begining of the string
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void TrimLeft();
		///////////////////////////////////////////////////////////////////////
		/// Removes whitespace and EOL characters from the end of the string
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void TrimRight();
		///////////////////////////////////////////////////////////////////////
		/// Removes whitespace and EOL characters from the begining and end of
		/// the string
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void TrimBoth();
		///////////////////////////////////////////////////////////////////////
		/// Inserts a string at a specified index
		///
		/// @param[in] iIndex The index at which the string is to be added
		/// @param[in] strText The string which is to be added
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void Insert(const int iIndex, const cString & strText);
		///////////////////////////////////////////////////////////////////////
		/// Removes specified number of characters from a specified index
		///
		/// @param[in] iIndex The index from which the characters are to be
		/// removed
		/// @param[in] iQuantity The number of characters to be removed
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void Remove(const int iIndex, const int iQuantity);
		///////////////////////////////////////////////////////////////////////
		/// Tokenizes the string based on the token
		///
		/// @param[in] cToken The token based on which the string will be tokenized
		/// @param[in] vValue The tokenized strings
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void Tokenize(char cToken, std::vector<Base::cString> & vValue) const;
		///////////////////////////////////////////////////////////////////////
		/// Converts the string to an int value
		///
		/// @return The int value of this string if the conversion is successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> ToInt() const;
		///////////////////////////////////////////////////////////////////////
		/// Converts the string to a float value
		///
		/// @return The float value of this string if the conversion is successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<float> ToFloat() const;
		///////////////////////////////////////////////////////////////////////
		/// Converts the string to a bool value
		///
		/// @return The bool value of this string if the conversion is successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<bool> ToBool() const;
		///////////////////////////////////////////////////////////////////////
		/// Gets the extension from a file
		///
		/// @return The extension of the file
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cString GetExtensionFromFileName() const;
		///////////////////////////////////////////////////////////////////////
		/// Convert a time value to a string 
		///
		/// @return The time as a string
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API static cString TimeToString(time_t time);
		//BASE_API bool Compare (const cString & str) const;
		//BASE_API void operator += (const char * const str);
	private:
		std::string m_str;
	};

	//////////////////////////////////////////////////////////////////////////////
	/// Adds two strings together
	///
	/// @param[in] lhs The left hand string
	/// @param[in] rhs The right hand string
	/// @return A string object which is rhs appended to lhs
	///
	//////////////////////////////////////////////////////////////////////////////
	BASE_API cString operator + (const cString & lhs, const cString & rhs);
	//////////////////////////////////////////////////////////////////////////////
	/// Adds a character array and a string
	///
	/// @param[in] lhs The character array
	/// @param[in] rhs The string
	/// @return A string object which is rhs appended to lhs
	///
	//////////////////////////////////////////////////////////////////////////////
	BASE_API cString operator + (const char * lhs, const cString & rhs);
	//////////////////////////////////////////////////////////////////////////////
	/// Adds a string and a character array
	///
	/// @param[in] lhs The string
	/// @param[in] rhs The character array
	/// @return A string object which is rhs appended to lhs
	///
	//////////////////////////////////////////////////////////////////////////////
	BASE_API cString operator + (const cString & lhs, const char* rhs);
	//////////////////////////////////////////////////////////////////////////////
	/// Writes a string to the output stream
	///
	/// @param[in] os The output stream being written to
	/// @param[in] str The string to be written
	/// @return Writes the value of the specified string to the output stream
	///
	//////////////////////////////////////////////////////////////////////////////
	BASE_API std::ostream& operator << (std::ostream& os, const cString & str);
}
#endif // myString_h__