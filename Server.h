#pragma once

#include <iostream>
#include<string>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include <mysql/mysql.h>

#include <vector>
#include <map>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "User.h"

#define MESSAGE_LENGTH 1024 
//#define PORT 7777 // Будем использовать этот номер порта

class Server
{
public:
	Server();

	void socket_file(); // Создание сокета
	void close_socket(); // Закрытие сокета
	void server_address(); // Настройка порта и привязка сокета
	void binding_soket();// Привязка сокета
	void connect(); // Постановка сервера на приём
	void receiving_user(); // Прием данных
	std::string message();// Перевод сообщения в стринг
	void log(std::string mess);//Запись сообщения в log.txt
	void greeting();
	void farewell();
	void clean_console();
	void system_pause(int second);

	void server();


private:
	// -------------- переменные сети -----------
	int _socket_file_descriptor, _connection, _bind_status, _connection_status;
	struct sockaddr_in _server_address, _client;
	socklen_t _length;
	char _message[MESSAGE_LENGTH];

	// ---------------- переменные сервера ---------
	int _port;
	std::map <std::string, User> _users;

	char _menu = 27;
	

};
