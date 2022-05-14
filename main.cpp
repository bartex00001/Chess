#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <map>
#include "TextureHolder.h"
#include "Square.h"
#include "Piece.h"

int main()
{	
	//kod debugowania = 1337
	bool turn;
	sf::Packet pack;
	sf::UdpSocket socket;
	sf::IpAddress serveradress;
	unsigned short serverport;
	int serverconnectionstatus = 1;
	bool iswhite=true;
	std::cout << "Server IP: ";
	std::cin >> serveradress;
	std::cout << "Server Port: ";
	std::cin >> serverport;


	if (serverport != 1337) { // debug - wpisaæ w pole port 1337 aby przejsc do inicjalizacji gry
		if (socket.bind(socket.getLocalPort()) != sf::Socket::Done) {
			std::cout << "Failed to bind a socket!" << std::endl;
			exit(4);
		}

		pack << serverconnectionstatus;
		if (socket.send(pack, serveradress, serverport) != sf::Socket::Done) {
			std::cout << "Failed to send connection initialization packet!" << std::endl;
			exit(2);
		}
		pack.clear();
		if (socket.receive(pack, serveradress, serverport) != sf::Socket::Done) {
			std::cout << "Failed to recieve initialization packet!" << std::endl;
			exit(2);
		}
		serverconnectionstatus = 0;
		pack >> serverconnectionstatus >> iswhite;
		std::cout << "CONNSTATUS: " << serverconnectionstatus << std::endl;
		std::cout << std::boolalpha;
		std::cout << "Is white? " << iswhite << std::endl;

		if (serverconnectionstatus != 2) {
			std::cout << "Connection not stablilized!" << std::endl;
			exit(3);
		}
}
	
	//---------------------------------------------------------------------------------------------------------
	

	//inicjalizacja okna
	TextureHolder TXHOLDER;
	sf::RenderWindow _window(sf::VideoMode(800, 800	), "Chess", sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(75);
	sf::Event event;
	sf::Vector2f mouse;


	//inicjalizacja szachownicy
	Square* sqrs[8][8];
	sf::Color* color = new sf::Color;
	*color = sf::Color::White;

	for (int i = 0; i < 8; i++) {
		if (*color == sf::Color::Blue)
			*color = sf::Color::White;

		else
			*color = sf::Color::Blue;

		for (int j = 0; j < 8; j++) {
			if (*color == sf::Color::Blue)
				*color = sf::Color::White;

			else
				*color = sf::Color::Blue;
			Square* field = new Square(0+100*i,0+100*j, *color);
			sqrs[i][j] = field;
		}
	}
	delete color;

	//inicjalizacja bierek
	Piece* pcs[32];

	for (int i = 0; i < 32; i++) {
		//biale
		if (i < 8) {
			Piece* piece = new Piece(TXHOLDER.wPawn, i, 0, 0);
			pcs[i] = piece;
		}//8 bialych pionow
		if (i >= 8 && i < 10) {
			Piece* piece = new Piece(TXHOLDER.wBishop, i, 1, 0);
			pcs[i] = piece;
		}//2 biale gonce
		if (i >= 10 && i < 12) {
			Piece* piece = new Piece(TXHOLDER.wKnight, i, 2, 0);
			pcs[i] = piece;
		}//2 biale skoczki
		if (i >= 12 && i < 14) {
			Piece* piece = new Piece(TXHOLDER.wRook, i, 3, 0);
			pcs[i] = piece;
		}//2 biale wieze
		if (i == 14) {
			Piece* piece = new Piece(TXHOLDER.wQueen, i, 4, 0);
			pcs[i] = piece;
		}//1 bialy hetman

		//czarne
		if (i >= 15 && i < 23) {
			Piece* piece = new Piece(TXHOLDER.bPawn, i, 0, 1);
			pcs[i] = piece;
		}//8 czarnych pionow
		if (i >= 23 && i < 25) {
			Piece* piece = new Piece(TXHOLDER.bBishop, i, 1, 1);
			pcs[i] = piece;
		}//2 czarne gonce
		if (i >= 25 && i < 27) {
			Piece* piece = new Piece(TXHOLDER.bKnight, i, 2, 1);
			pcs[i] = piece;
		}//2 czarne skoczki
		if (i >= 27 && i < 29) {
			Piece* piece = new Piece(TXHOLDER.bRook, i, 3, 1);
			pcs[i] = piece;
		}//2 czarne wieze
		if (i == 30) {
			Piece* piece = new Piece(TXHOLDER.bQueen, i, 4, 1);
			pcs[i] = piece;
		}//1 czarny hetman
		
		//31 i 32 to beda krole bialy i czarny
	}

	if (iswhite) 
		turn = true;

	else if(!iswhite) 
		turn = false;
		

/*
	//wypisanie pol do konsoli
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << sqrs[i][j]->getPositionx() << "|" << sqrs[i][j]->getPositiony() << std::endl;
		}
	}
	*/


	Square* selected = NULL;
	Square* target = NULL;


	
	while (_window.isOpen()) {

		while (_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				_window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if (turn == true) {
					mouse = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (sqrs[i][j]->Isclicked(mouse)) {
								if (selected == NULL) {
									selected = sqrs[i][j];
									std::cout << "clicked coords: " << selected->getPositionx() << "|" << selected->getPositiony() << std::endl;
									selected->setMark(true);
								}//pierwsze klikniecie

								else if (selected != NULL){
									target = sqrs[i][j];

									if (selected != target) {
										std::cout << "made a move from  " << selected->getPositionx() << "|" << selected->getPositiony() << " to " << target->getPositionx() << "|" << target->getPositiony() << std::endl;

										selected->setMark(false);
										selected = NULL;
										target = NULL;
										turn = false;
									}
									
								}//drugie klikniecie

							}//is clicked

						}
					}
				}
				
				
			}//lewy
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (selected != NULL) {
					selected->setMark(false);
					selected = NULL;
				}

			}//prawy




		}//pollevent


		_window.clear(sf::Color::Red);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				_window.draw(*sqrs[i][j]);
			}
		}
		
		_window.display();
	}//isopen

	return 0;
}