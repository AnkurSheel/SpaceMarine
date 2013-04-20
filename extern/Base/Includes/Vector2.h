// *****************************************************************************
//  Vector2D   version:  1.0   Ankur Sheel  date: 2012/08/28
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Vector2_h__
#define Vector2_h__

#include "MathIncludes.h"

namespace Base
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Encapsulates a 2D vector with X and Y components .
	///
	///////////////////////////////////////////////////////////////////////////
	class cVector2
	{
	public:
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////
		cVector2();
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] X The X component of the vector
		/// @param[in] Y The Y component of the vector
		///
		///////////////////////////////////////////////////////////////////////
		cVector2(const float X, const float Y);
		///////////////////////////////////////////////////////////////////////
		/// Returns true if the vector is 0
		/// 
		/// @return True if the vector is 0
		///
		///////////////////////////////////////////////////////////////////////
		bool IsZero() const;	
		///////////////////////////////////////////////////////////////////////
		/// Gets the length of the vector
		///
		/// @return Length of the vector
		///
		///////////////////////////////////////////////////////////////////////
		float Length() const;
		///////////////////////////////////////////////////////////////////////
		/// Gets the squared length of the vector
		///
		/// @return Squared length of the vector 
		///
		///////////////////////////////////////////////////////////////////////
		float LengthSquared() const;
		///////////////////////////////////////////////////////////////////////
		/// Converts the Vector into a unit vector
		///
		///
		///////////////////////////////////////////////////////////////////////
		void Normalize();
		///////////////////////////////////////////////////////////////////////
		/// Calculates and returns the dot product
		/// 
		/// @param[in] inVec The vector with which the dot product needs to be 
		/// calculated
		/// @return The dot product between this vector and the one passed as a
		/// parameter
		/// 
		///////////////////////////////////////////////////////////////////////
		float Dot(const cVector2 & inVec) const;
		///////////////////////////////////////////////////////////////////////
		/// Get the perpendicular vector about the X axis.
		///
		/// @return perpendicular vector about the X axis.
		///
		///////////////////////////////////////////////////////////////////////
		cVector2 PerpendicularAboutXAxis() const;
		///////////////////////////////////////////////////////////////////////
		/// Get the perpendicular vector about the Y axis.
		///
		/// @return perpendicular vector about the Y axis.
		///
		///////////////////////////////////////////////////////////////////////
		cVector2 PerpendicularAboutYAxis() const;
		///////////////////////////////////////////////////////////////////////
		/// Gets the distance between this and the passed in vector
		///
		/// @param[in] inVec The vector with which the distance needs to be
		/// calculated
		/// @return Euclidean distance 
		///
		///////////////////////////////////////////////////////////////////////
		float Distance(const cVector2 & inVec) const;
		///////////////////////////////////////////////////////////////////////
		/// Gets the squared distance between this and the passed in vector
		///
		/// @param[in] inVec The vector with which the squared distance needs
		/// to be calculated
		/// @return Squared Euclidean distance 
		///
		///////////////////////////////////////////////////////////////////////
		float DistanceSquared(const cVector2 & inVec) const;
		///////////////////////////////////////////////////////////////////////
		/// Reflects the normalized vector it is operating upon.
		///
		/// @param[in] norm The normalized vector
		///
		///////////////////////////////////////////////////////////////////////
		void Reflect(const cVector2 & norm);
		///////////////////////////////////////////////////////////////////////
		/// Gets the reverse vector
		///
		/// @return Reverse of this vector
		///		 
		///////////////////////////////////////////////////////////////////////
		cVector2 GetReverse() const;
		///////////////////////////////////////////////////////////////////////
		/// Sets X and Y to their absolute values
		///
		///
		///////////////////////////////////////////////////////////////////////
		void AbsTo();
		///////////////////////////////////////////////////////////////////////
		/// Get the largest component and return a signed, unit vector
		/// containing only that component
		///
		/// @return A signed, unit vector containing only the largest component
		///
		///////////////////////////////////////////////////////////////////////
		cVector2 MajorAxis() const;
		///////////////////////////////////////////////////////////////////////
		/// Get the smallest component and return a signed, unit vector
		/// containing only that component
		///
		/// @return A signed, unit vector containing only the largest component
		///
		///////////////////////////////////////////////////////////////////////
		cVector2 MinorAxis() const;
		///////////////////////////////////////////////////////////////////////
		/// Changes the sign of the components
		///
		///
		///////////////////////////////////////////////////////////////////////
		void NegTo();

		const cVector2 & operator+=(const cVector2 & inVec);
		const cVector2 & operator-=(const cVector2 & inVec);
		const cVector2 & operator*=(const cVector2 & inVec);
		const cVector2 & operator*=(const float fVal);
		const cVector2 & operator/=(const float fVal);
		bool operator==(const cVector2 & inVec) const;
		bool operator!=(const cVector2 & inVec) const;
		float & operator[](const unsigned int i);
		const float operator[](const unsigned int i) const;
		static cVector2 Zero();
		static cVector2 GetDirection(const float fAngle);

	public:
		float	x;	/*!< X component of Vector2 */
		float	y;	/*!< Y component of Vector2 */
	};

	inline cVector2 operator*(const cVector2 & inVec1, const float fVal);
	inline cVector2 operator*(const float fVal, const cVector2 & inVec1);
	inline cVector2 operator/(const cVector2 & inVec1, const float fVal);
	inline cVector2 operator-(const cVector2 & inVec1, const cVector2 & inVec2);
	inline cVector2 operator+(const cVector2 & inVec1, const cVector2 & inVec2);
	inline cVector2 operator*(const cVector2 & inVec1, const cVector2 & inVec2);

	#include "Vector2.inl"
}
#endif // Vector2_h__