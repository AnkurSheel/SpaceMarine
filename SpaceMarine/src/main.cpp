#include "includes.h"
#include "sm_game.h"

// *****************************************************************************
void CheckForMemoryLeaks() ;

int main(int argc, char* args[])
{
	CheckForMemoryLeaks() ;

	SMGame TheGame;
	TheGame.OnExecute();
	return 0;
}

// *****************************************************************************
void CheckForMemoryLeaks() 
{
#ifdef	_DEBUG
	// Get Current flag
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) ; 

	// Turn on leak-checking bit
	flag |= (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ; 

	// Set flag to the new value
	_CrtSetDbgFlag(flag) ; 
#endif	_DEBUG
}
