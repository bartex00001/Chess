#include "Square.h"

Square::Square() {

}
Square::Square(float posx, float posy) {
	positionx = posx;
	positiony = posy;

}

float Square::getPositionx() {
	return(positionx);
}

float Square::getPositiony() {
	return(positiony);
}

