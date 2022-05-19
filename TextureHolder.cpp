#include "TextureHolder.h"
TextureHolder::TextureHolder()
{
	//wPawn, wKnight, wBishop, wRook, wQueen, wKing, bPawn, bKnight, bBishop, bRook, bQueen, bKing,
	if (!wPawn.loadFromFile("textures/wPawn.png"))
		exit(1);
	if (!wKnight.loadFromFile("textures/wKnight.png"))
		exit(1);
	if (!wBishop.loadFromFile("textures/wBishop.png"))
		exit(1);
	if (!wRook.loadFromFile("textures/wRook.png"))
		exit(1);
	if (!wQueen.loadFromFile("textures/wQueen.png"))
		exit(1);
	if (!wKing.loadFromFile("textures/wKing.png"))
		exit(1);
	if (!bPawn.loadFromFile("textures/bPawn.png"))
		exit(1);
	if (!bKnight.loadFromFile("textures/bKnight.png"))
		exit(1);
	if (!bBishop.loadFromFile("textures/bBishop.png"))
		exit(1);
	if (!bRook.loadFromFile("textures/bRook.png"))
		exit(1);
	if (!bQueen.loadFromFile("textures/bQueen.png"))
		exit(1);
	if (!bKing.loadFromFile("textures/bKing.png"))
		exit(1);

}
