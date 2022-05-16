#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <map>
#include "TextureHolder.h"
#include "Square.h"
#include "Piece.h"

bool move(Square* slctd, Square* trgt, sf::UdpSocket& sckt, sf::IpAddress& IP, unsigned short& PORT, sf::Packet& pck);

int main()
{	
	//kod debugowania = 1337
	bool turn=false, gamestarted=false, iswhite = true;
	sf::Packet pack;
	sf::UdpSocket socket;
	sf::IpAddress serveradress;
	unsigned short serverport;
	int serverconnectionstatus = 1, id, ctx, cty;
	float tx, ty; //koordy targetu do update




	std::cout << "Server IP: ";
	std::cin >> serveradress;
	std::cout << "Server Port: ";
	std::cin >> serverport;


	if (serverport != 1337) { // debug - wpisaæ w pole "port" 1337 aby przejsc do inicjalizacji gry
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

		std::cout << "Waiting for 2nd player" << std::endl;
		pack.clear();
		if (socket.receive(pack, serveradress, serverport) != sf::Socket::Done) {
			std::cout << "Failed to recieve initialization packet!" << std::endl;
			exit(2);
		}
		pack >> gamestarted;
		if (gamestarted) 
			std::cout << "Everything is ready!" << std::endl;

		else {
			std::cout << "2nd player didn't come, terminating..." << std::endl;
			exit(69);
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
			pcs[i]->SetPosition(sqrs[i][6]->getPositionx(), sqrs[i][6]->getPositiony());
			sqrs[i][6]->bindPiece(pcs[i]);
		}//8 bialych pionow
		if (i >= 8 && i < 10) {
			Piece* piece = new Piece(TXHOLDER.wBishop, i, 1, 0);
			pcs[i] = piece;
			if (i == 8) {
				pcs[i]->SetPosition(sqrs[2][7]->getPositionx(), sqrs[2][7]->getPositiony());
				sqrs[2][7]->bindPiece(pcs[i]);
			}
				
			if (i == 9) {
				pcs[i]->SetPosition(sqrs[5][7]->getPositionx(), sqrs[5][7]->getPositiony());
				sqrs[5][7]->bindPiece(pcs[i]);
			}
				
			
		}//2 biale gonce
		if (i >= 10 && i < 12) {
			Piece* piece = new Piece(TXHOLDER.wKnight, i, 2, 0);
			pcs[i] = piece;
			if (i == 10) {
				pcs[i]->SetPosition(sqrs[1][7]->getPositionx(), sqrs[1][7]->getPositiony());
				sqrs[1][7]->bindPiece(pcs[i]);
			}
				
			if (i == 11) {
				pcs[i]->SetPosition(sqrs[6][7]->getPositionx(), sqrs[6][7]->getPositiony());
				sqrs[6][7]->bindPiece(pcs[i]);
			}
				

		}//2 biale skoczki
		if (i >= 12 && i < 14) {
			Piece* piece = new Piece(TXHOLDER.wRook, i, 3, 0);
			pcs[i] = piece;
			if (i == 12) {
				pcs[i]->SetPosition(sqrs[0][7]->getPositionx(), sqrs[0][7]->getPositiony());
				sqrs[0][7]->bindPiece(pcs[i]);
			}

				if (i == 13) {
					pcs[i]->SetPosition(sqrs[7][7]->getPositionx(), sqrs[7][7]->getPositiony());
					sqrs[7][7]->bindPiece(pcs[i]);
			}


		}//2 biale wieze
		if (i == 14) {
			Piece* piece = new Piece(TXHOLDER.wQueen, i, 4, 0);
			pcs[i] = piece;
			pcs[i]->SetPosition(sqrs[3][7]->getPositionx(), sqrs[3][7]->getPositiony());
			sqrs[3][7]->bindPiece(pcs[i]);

		}//1 bialy hetman

		//czarne
		if (i >= 15 && i < 23) {
			Piece* piece = new Piece(TXHOLDER.bPawn, i, 0, 1);
			pcs[i] = piece;
			pcs[i]->SetPosition(sqrs[i-15][1]->getPositionx(), sqrs[i - 15][1]->getPositiony());
			sqrs[i-15][1]->bindPiece(pcs[i]);
		}//8 czarnych pionow
		if (i >= 23 && i < 25) {
			Piece* piece = new Piece(TXHOLDER.bBishop, i, 1, 1);
			pcs[i] = piece;
			if (i == 23) {
				pcs[i]->SetPosition(sqrs[2][0]->getPositionx(), sqrs[2][0]->getPositiony());
				sqrs[2][0]->bindPiece(pcs[i]);
			}

			if (i == 24) {
				pcs[i]->SetPosition(sqrs[5][0]->getPositionx(), sqrs[5][0]->getPositiony());
				sqrs[5][0]->bindPiece(pcs[i]);
			}


		}//2 czarne gonce
		if (i >= 25 && i < 27) {
			Piece* piece = new Piece(TXHOLDER.bKnight, i, 2, 1);
			pcs[i] = piece;
			if (i == 25) {
				pcs[i]->SetPosition(sqrs[1][0]->getPositionx(), sqrs[1][0]->getPositiony());
				sqrs[1][0]->bindPiece(pcs[i]);
			}

			if (i == 26) {
					pcs[i]->SetPosition(sqrs[6][0]->getPositionx(), sqrs[6][0]->getPositiony());
					sqrs[6][0]->bindPiece(pcs[i]);
			}


		}//2 czarne skoczki
		if (i >= 27 && i < 29) {
			Piece* piece = new Piece(TXHOLDER.bRook, i, 3, 1);
			pcs[i] = piece;
			if (i == 27) {
				pcs[i]->SetPosition(sqrs[0][0]->getPositionx(), sqrs[0][0]->getPositiony());
				sqrs[0][0]->bindPiece(pcs[i]);
			}

			if (i == 28) {
				pcs[i]->SetPosition(sqrs[7][0]->getPositionx(), sqrs[7][0]->getPositiony());
				sqrs[7][0]->bindPiece(pcs[i]);
			}


		}//2 czarne wieze
		if (i == 29) {
			Piece* piece = new Piece(TXHOLDER.bQueen, i, 4, 1);
			pcs[i] = piece;
			pcs[i]->SetPosition(sqrs[3][0]->getPositionx(), sqrs[3][0]->getPositiony());
			sqrs[3][0]->bindPiece(pcs[i]);

			

		}//1 czarny hetman

		//krole
		if (i == 30) {//bialy
			Piece* piece = new Piece(TXHOLDER.wKing, i, 5, 0);
			pcs[i] = piece;
			pcs[i]->SetPosition(sqrs[4][7]->getPositionx(), sqrs[4][7]->getPositiony());
			sqrs[4][7]->bindPiece(pcs[i]);

		}
		if (i == 31) {//czarny
			Piece* piece = new Piece(TXHOLDER.bKing, i, 5, 1);
			pcs[i] = piece;
			pcs[i]->SetPosition(sqrs[4][0]->getPositionx(), sqrs[4][0]->getPositiony());
			sqrs[4][0]->bindPiece(pcs[i]);

		}

		//30 i 31 to beda krole bialy i czarny
	}
	

	if (iswhite)
		turn = true;
		

	else if(!iswhite) 
		turn = false;
		


	Square* selected = nullptr;
	Square* target = nullptr;


	
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
								if (selected == nullptr) {
									selected = sqrs[i][j];
									std::cout << "clicked coords: " << selected->getPositionx() << "|" << selected->getPositiony() << std::endl;
									selected->setMark(true);
								}//pierwsze klikniecie

								else if (selected != nullptr){
									target = sqrs[i][j];

									if (selected != target) {
										
										if (move(selected, target, socket, serveradress, serverport, pack)) {
											std::cout << "made a move from  " << selected->getPositionx() << "|" << selected->getPositiony() << " to " << target->getPositionx() << "|" << target->getPositiony() << std::endl;
											selected->setMark(false);
											selected = nullptr;
											target = nullptr;
											turn = false;
											
										}
										else {
											
											selected->setMark(false);
											selected = nullptr;
											target = nullptr;
											std::cout << "wrong move!" << std::endl;
										}
										
									}
									
								}//drugie klikniecie

							}//is clicked

						}
					}
				}
				
				
			}//lewy
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (selected != nullptr) {
					selected->setMark(false);
					selected = nullptr;
				}

			}//prawy




		}//pollevent

		//UPDATE
		if (socket.isBlocking())
			socket.setBlocking(false);

		
		pack.clear();
		if (socket.receive(pack, serveradress, serverport) == sf::Socket::Done) {
			pack >> id >> tx >> ty;
			ctx = static_cast<int>(tx);
			cty = static_cast<int>(ty);
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (sqrs[i][j]->pce != nullptr && sqrs[i][j]->pce->getID() == id) {
						sqrs[ctx / 100][cty / 100]->bindPiece(sqrs[i][j]->pce);
						sqrs[ctx / 100][cty / 100]->pce->SetPosition(sqrs[ctx / 100][cty / 100]->getPositionx(), sqrs[ctx / 100][cty / 100]->getPositiony());
						sqrs[i][j]->pce = nullptr;
					}//if
				}
			}
		}


		
		



//rysowañsko
		_window.clear(sf::Color::Red);


		//rysowanie pol
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				_window.draw(*sqrs[i][j]);
			}
		}
		//rysowanie bierek
		for (int i = 0; i < 32; i++) {
			_window.draw(*pcs[i]);
		}

		_window.display();
	}//isopen

	return 0;
}


bool move(Square* slctd, Square* trgt, sf::UdpSocket &sckt, sf::IpAddress &IP, unsigned short &PORT, sf::Packet &pck) {
	sckt.setBlocking(true);
	if (slctd->pce == nullptr)
		return (false);

	pck.clear();
	pck << slctd->getPositionx() << slctd->getPositiony() << trgt->getPositionx() << trgt->getPositiony();
	sf::IpAddress a;// do zapchania
	unsigned short b;// do zapchania
	bool moveValuability;
	std::cout << "sending move to the server..." << std::endl;
	if (sckt.send(pck, IP, PORT) != sf::Socket::Done) {
		std::cout << "Failed to send a move to the server!" << std::endl;
		exit(5);
	}
	std::cout << "move sent" << std::endl;
	pck.clear();
	std::cout << "waiting for server..." << std::endl;
	if (sckt.receive(pck, a, b) != sf::Socket::Done) {
		std::cout << "Failed to receive a move from the server!" << std::endl;
		exit(5);
	}
	std::cout << "received!" << std::endl;
	pck >> moveValuability;
	pck.clear();
	if (moveValuability == true) {
		trgt->bindPiece(slctd->pce);
		trgt->pce->SetPosition(trgt->getPositionx(), trgt->getPositiony());
		slctd->pce = nullptr;
		return(true);
	}
	return(false);
}