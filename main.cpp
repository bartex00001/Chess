#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include<map>
#include "TextureHolder.h"
#include "Square.h"
#include "Piece.h"

int main()
{	
	/*
	sf::UdpSocket socket;
	sf::IpAddress sendingip;
	unsigned short sendingport;
	std::cout << "IP: ";
	std::cin >> sendingip;
	std::cout << "Port: ";
	std::cin >> sendingport;
	unsigned int receivingport = socket.getLocalPort();
	if (socket.bind(receivingport) != sf::Socket::Done) {
		std::cout << "Failed to bind a socket!" << std::endl;
		exit(4);
	}
	sf::Packet initpacket;
	int connectionstatus = 1; //0-brak 1-proba 2-nawiazana

	
	initpacket << connectionstatus;
	if (socket.send(initpacket, sendingip, sendingport) != sf::Socket::Done) {
		std::cout << "Failed to send connection initialization packet!" << std::endl;
		exit(2);
	}
	
	sf::IpAddress senderip;
	
	unsigned short senderport;
	Sleep(1000);
	if (socket.receive(initpacket, senderip, senderport) != sf::Socket::Done) {
		std::cout << "Failed to recieve initialization packet!" << std::endl;
		exit(2);
	}
	connectionstatus = 0;
	//if (!initpacket >> connectionstatus) {
		//std::cout << "Failed to read initpacket!" << std::endl;
		//exit(2);
	//}
	initpacket >> connectionstatus;
	std::cout << "CONNSTATUS: " << connectionstatus << std::endl;
	if (connectionstatus != 2) {
		std::cout << "Connection not stablilized!" << std::endl;
		exit(3);
	}
	

	*/
	
	sf::Packet pack;
	sf::UdpSocket socket;
	sf::IpAddress serveradress;
	unsigned short serverport;
	int serverconnectionstatus = 1;
	bool iswhite;
	std::cout << "Server IP: ";
	std::cin >> serveradress;
	std::cout << "Server Port: ";
	std::cin >> serverport;
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
	if (socket.receive(pack,serveradress,serverport) != sf::Socket::Done) {
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

	//inicjalizacja wszystkiego
	TextureHolder TXHOLDER;
	sf::RenderWindow _window(sf::VideoMode(800, 800	), "Chess", sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(75);
	sf::Sprite bG;
	bG.setTexture(TXHOLDER.bg);
	sf::Event event;



	//std::list<Square*>Squares;
	Square* sqrs[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Square* field = new Square(0+10*i,0+10*j);
			sqrs[i][j] = field;
		}
	}
	
	pack.clear();
	if (socket.receive(pack, serveradress, serverport) != sf::Socket::Done) {
		std::cout << "Failed to recieve ready packet!" << std::endl;
		exit(2);
	}
	Piece piece(TXHOLDER.bPawn, 0, 0, 1);
	if (piece.move(sqrs[1][1], &socket, serveradress, serverport, &pack) == false) {
		std::cout << "unvalid move!" << std::endl;
	}

	while (_window.isOpen()) {

		while (_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				_window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				
			}





		}


		_window.clear(sf::Color::White);
		_window.draw(bG);
		_window.display();
	}//isopen

	return 0;
}