// *****************************************************************************
//  sm_Player   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_Player_h__
#define sm_Player_h__

#include "sm_entity.h"

typedef struct _TTF_Font TTF_Font;
class SMCrosshair;

class SMPlayer
	: public SMEntity
{
public:
	SMPlayer(const Base::cString & Type, const Base::cString & SubType,
		const Base::cString & Name);
	~SMPlayer();
	bool VInitialize();
	void VUpdate(const float DeltaTime);
	void VCleanup();
	void VRender(SDL_Surface * pDisplaySurface);
	void VOnCollided(const Base::cString & Type, const Base::cVector2 & PenentrationDistance);

private:
	void CheckCollisions(const Base::cVector2 & PredictedPos);

private:
	int				m_Score;
	Base::cString	m_ScoreText;
	SDL_Surface *	m_pScoreSurface;
	TTF_Font *		m_pFont;
	SDL_Color		m_TextColor;
	SMCrosshair *	m_pCrossHair;
	float			m_Angle;
	bool			m_bDirty;
};

#endif // sm_Player_h__