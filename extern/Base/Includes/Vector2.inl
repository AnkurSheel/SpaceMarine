// *****************************************************************************
inline cVector2::cVector2()
: x(0)
, y(0)
{
}

// *****************************************************************************
inline cVector2::cVector2( const float fX, const float fY )
: x(fX)
, y(fY)
{
}

// *****************************************************************************
inline Base::cVector2 cVector2::Zero()
{
	return cVector2(0.0f, 0.0f);
}

// *****************************************************************************
inline bool cVector2::IsZero() const
{
	return LengthSquared() < EpsilonFloat;
}

// *****************************************************************************
inline float cVector2::Length() const
{
	return sqrt(LengthSquared());
}

// *****************************************************************************
inline float cVector2::LengthSquared() const
{
	return (x * x + y * y);
}

// *****************************************************************************
inline void cVector2::Normalize()
{
	float fLength = Length();

	if (fLength > EpsilonFloat)
	{
		x /= fLength;
		y /= fLength;
	}
}

// *****************************************************************************
inline float cVector2::Dot( const cVector2 & inVec ) const
{
	return x * inVec.x + y * inVec.y;
}

// *****************************************************************************
inline Base::cVector2 cVector2::PerpendicularAboutXAxis() const
{
	return cVector2(y, -x);
}

// *****************************************************************************
inline Base::cVector2 cVector2::PerpendicularAboutYAxis() const
{
	return cVector2(-y, x);
}

// *****************************************************************************
inline float cVector2::Distance( const cVector2 & inVec ) const
{
	return sqrt(DistanceSquared(inVec));
}

// *****************************************************************************
inline float cVector2::DistanceSquared( const cVector2 & inVec ) const
{
	float ySeparation = inVec.y - y;
	float xSeparation = inVec.x - x;

	return (ySeparation * ySeparation + xSeparation * xSeparation);
}

// *****************************************************************************
inline void cVector2::Reflect( const cVector2 & norm )
{
	*this += 2.0f * this->Dot(norm) * norm.GetReverse();
}

// *****************************************************************************
inline Base::cVector2 cVector2::GetReverse() const
{
	return cVector2(-x, -y);
}

// ******************************************************************************
inline void cVector2::AbsTo() 
{
	x = abs(x);
	y = abs(y);
}

// *******************************************************************************************
inline cVector2 cVector2::MajorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);
	
	if(absX > absY)
	{
		float signX = static_cast<float>(Sign(x));
		return cVector2(signX, 0);
	}
	else
	{
		float signY = static_cast<float>(Sign(y));
		return cVector2(0, signY);
	}
}

// *******************************************************************************************
inline cVector2 cVector2::MinorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);
	
	if(absX < absY)
	{
		float signX = static_cast<float>(Sign(x));
		return cVector2(signX, 0);
	}
	else
	{
		float signY = static_cast<float>(Sign(y));
		return cVector2(0, signY);
	}
}

// *******************************************************************************************
inline void cVector2::NegTo() 
{
	x = -x;
	y = -y;
}

// ******************************************************************************
inline const cVector2 & cVector2::operator+=( const cVector2 & inVec )
{
	x += inVec.x;
	y += inVec.y;

	return *this;
}

// *****************************************************************************
inline const cVector2 & cVector2::operator-=( const cVector2 & inVec )
{
	x -= inVec.x;
	y -= inVec.y;

	return *this;
}

// *****************************************************************************
inline const cVector2 & cVector2::operator*=(const cVector2 & inVec)
{
	x *= inVec.x;
	y *= inVec.y;

	return *this;
}

// *****************************************************************************
inline const cVector2 & cVector2::operator*=( const float fVal )
{
	x *= fVal;
	y *= fVal;

	return *this;
}

// *****************************************************************************
inline const cVector2 & cVector2::operator/=( const float fVal )
{
	x /= fVal;
	y /= fVal;

	return *this;
}

// *****************************************************************************
inline bool cVector2::operator==( const cVector2 & inVec ) const
{
	return (isEqual(x, inVec.x) && isEqual(y,inVec.y) );
}

// *****************************************************************************
inline bool cVector2::operator!=( const cVector2 & inVec ) const
{
	return (!isEqual(x, inVec.x) || !isEqual(y,inVec.y) );
}

// *****************************************************************************
inline float & cVector2::operator[](const unsigned int i)
{
	return *((&x) + i);
}

// *****************************************************************************
inline const float cVector2::operator[](const unsigned int i) const
{
	return *((&x) + i);
}

// *****************************************************************************
Base::cVector2 operator*( const cVector2 & inVec1, const float fVal )
{
	cVector2 result(inVec1);
	result *= fVal;
	return result;
}

// *****************************************************************************
Base::cVector2 operator*( const float fVal, const cVector2 & inVec1 )
{
	cVector2 result(inVec1);
	result *= fVal;
	return result;
}

// *****************************************************************************
Base::cVector2 operator/( const cVector2 & inVec1, const float fVal )
{
	cVector2 result(inVec1);
	result /= fVal;
	return result;
}

// *****************************************************************************
Base::cVector2 operator-( const cVector2 & inVec1, const cVector2 & inVec2 )
{
	cVector2 result(inVec1);
	result -= inVec2;
	return result;
}

// *****************************************************************************
Base::cVector2 operator+( const cVector2 & inVec1, const cVector2 & inVec2 )
{
	cVector2 result(inVec1);
	result += inVec2;
	return result;
}

// *****************************************************************************
Base::cVector2 operator*(const cVector2 & inVec1, const cVector2 & inVec2)
{
	cVector2 result(inVec1);
	result *= inVec2;
	return result;
}
