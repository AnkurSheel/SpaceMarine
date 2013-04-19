// ****************************************************************************
//  HashedString   version:  1.0   Ankur Sheel  date: 2012/12/26
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#ifndef HashedString_h__
#define HashedString_h__

#include "BaseDefines.h"
#include <memory>

namespace Base
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Stores a string with its hash. 
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class cHashedString
	{
	public:
		///////////////////////////////////////////////////////////////////////
		/// Default Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cHashedString();
		///////////////////////////////////////////////////////////////////////
		/// Constructor which takes in string as a parameter and stores the
		/// hash for it 
		///
		/// @param[in] string The string from which the hash has to be created
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API explicit cHashedString(const cString & string);
		///////////////////////////////////////////////////////////////////////
		/// Copy Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cHashedString(const cHashedString & other);
		///////////////////////////////////////////////////////////////////////
		/// Assignment Operator
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cHashedString operator =(const cHashedString & other);
		///////////////////////////////////////////////////////////////////////
		/// Returns the hash
		///
		/// @returns The calculated hash 
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API unsigned long GetHash() const;
		///////////////////////////////////////////////////////////////////////
		/// Returns the string
		///
		/// @returns The string
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API Base::cString GetString() const;
		///////////////////////////////////////////////////////////////////////
		/// Returns true if the checksum of o is equal to the checksum of this
		/// hashed string
		///
		/// @return True if the chcksums are equal. False otherwise
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API bool operator==(cHashedString const & other) const;
		///////////////////////////////////////////////////////////////////////
		/// Constructor which takes in string as a parameter and stores the
		/// hash for it 
		///
		/// @param[in] string The string from which the hash has to be created
		///
		///////////////////////////////////////////////////////////////////////		
		BASE_API static unsigned long CalculateHash(const cString & strIdent);

	private:
		unsigned long	m_lChecksum;	///< The hash associated with this string.
		cString			m_strIdent;	///< The string

	};
}
#endif // HashedString_h__