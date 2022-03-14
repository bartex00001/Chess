#include "TextureHolder.h"
TextureHolder::TextureHolder()
{
	//wPawn, wKnight, wBishop, wRook, wQueen, wKing, bPawn, bKnight, bBishop, bRook, bQueen, bKing, bg
	if (!wPawn.loadFromFile("wPawn.png"))
		exit(1);
	/*
	if (!wKnight.loadFromFile("EMPTY.png"))
		exit(1);
	if (!wBishop.loadFromFile("O.png"))
		exit(1);
	if (!wRook.loadFromFile("X.png"))
		exit(1);
	if (!wQueen.loadFromFile("X.png"))
		exit(1);
	if (!wKing.loadFromFile("X.png"))
		exit(1);
	if (!bPawn.loadFromFile("X.png"))
		exit(1);
	if (!bKnight.loadFromFile("X.png"))
		exit(1);
	if (!bBishop.loadFromFile("X.png"))
		exit(1);
	if (!bRook.loadFromFile("X.png"))
		exit(1);
	if (!bQueen.loadFromFile("X.png"))
		exit(1);
	if (!bKing.loadFromFile("X.png"))
		exit(1);
	*/
	if (!bg.loadFromFile("bg.png"))
		exit(1);

}
