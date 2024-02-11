#pragma once

#include <iostream>
#include<string>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include <vector>
#include <thread>
#include <chrono>

#include "User.h"

#define MESSAGE_LENGTH 1024 

class Server
{
public:
	Server();

	void socket_file(); // Создание сокета
	void close_socket(); // Закрытие сокета
	void server_address(); // Настройка порта и привязка сокета
	void binding_soket();// Привязка сокета
	void connect(); // Постановка сервера на приём
	void connect_user();// Подключение пользователя
	static void receiving_user(int connect, char*); // Прием данных
	static std::string message(char* mess);// Перевод сообщения в стринг
	static void log(std::string mess);//Запись сообщения в log.txt
	void greeting();
	static void farewell(int user);
	void clean_console();
	void system_pause(int second);

	void server_start();
	void menu();


private:
	// -------------- переменные сети -----------
	int _socket_file_descriptor, _bind_status, _connection_status, _connection;
	struct sockaddr_in _server_address;
	struct sockaddr_in _client;
	socklen_t _length;
	char _message[MESSAGE_LENGTH];
	int _port;
	char _menu = 27;
	static std::string _user;
};
