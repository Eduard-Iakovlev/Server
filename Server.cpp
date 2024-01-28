#include "Server.h"
#include "Logger.h"
#include "Consol_Input.h"
#include <ctime>
#include <iomanip>



Server::Server(){
	greeting();
}

//--------------------------------- Работа сети ----------------------------------------------
//----------- Создание сокета ---------------------------
void Server::socket_file() {
	_socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_file_descriptor == -1) {
		//std::cout << " Не удалось создать сокет!" << std::endl;
		log(" Не удалось создать сокет!");
		exit(1);
	}
}

//----------- Закрытие сокета ------------------------------
void Server::close_socket() {
	close(_socket_file_descriptor);
	auto now = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(now);
	std::cout << std::ctime(&end_time) << " сокет закрыт" << std::endl;

}

//------------ Настройка порта -------------
void Server::server_address() {
	Universal_Input<int> enter_port('0', '9');
	_server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	// Зададим номер порта для связи
	std::cout << " Введите номер порта: ";
	_port = enter_port.input();
	_server_address.sin_port = htons(_port);
	// Используем IPv4
	_server_address.sin_family = AF_INET;
}
// ------------ Привязка сокета ----------------------------------
void Server::binding_soket(){
	_bind_status = bind(_socket_file_descriptor, (struct sockaddr*)&_server_address,
		sizeof(_server_address));
	if (_bind_status == -1) {
		//std::cout << " Не удалось выполнить привязку сокета!" << std::endl;
		log(" Не удалось выполнить привязку сокета!");
		exit(1);
	}
}

//------------ Постановка сервера на прием ----------------------
void Server::connect() {
	_connection_status = listen(_socket_file_descriptor, 5);
	if (_connection_status == -1) {
		//std::cout << " Сокет не может прослушивать новые подключения!" << "\n";
		log(" Сокет не может прослушивать новые подключения!");
		exit(1);
	}
	else {
		std::cout << "\n Ожидание данных: " << "\n";
	}
	_length = sizeof(_client);
	_connection = accept(_socket_file_descriptor, (struct sockaddr*)&_client, &_length);
	if (_connection == -1) {
		//std::cout << " Сервер не может принять данные от клиента!" << "\n";
		log(" Сервер не может принять данные от клиента!");
		exit(1);
	}
}
//----------------------------------------

//-------------- Прием данных от пользователе --------------------
void Server::receiving_user() {
	memset(_message, 0, sizeof(_message));
	read(_connection, _message, sizeof(_message));
	log(message());
}

//------------- Перевод сообщения в string ---------------------------
std::string Server::message() {
	return std::string(_message);
}

// ------------ Запись сообщения в log.txt
void Server::log(std::string mess){
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    struct tm timeinfo;
    localtime_r(&time, &timeinfo); 

    std::ostringstream date_time_stream;
    date_time_stream << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S") << "." << std::setfill('0') << std::setw(3) << milliseconds.count();
    std::string date_time = date_time_stream.str();
	std::string message = date_time + " " + mess;

	Logger logger(message);

	std::thread apped(&Logger::apped_to_log, &logger);
	std::thread read(&Logger::read_last_line, &logger);

	apped.join();
	read.join();
}

//---------------- Приветствие ------------------------------------------------------------
void Server::greeting() {
	clean_console();
	std::cout << "\n          Сервер включён!\n\n";
}

//----------------- Прощание --------------------------------------------------------------
void Server::farewell() {
	std::cout << " Пользовател отключился от сети.\n";
}


//----------------- Очистка консоли -------------------------------------------------------
void Server::clean_console() {
	std::system("clear"); 
}

//------------------- Пауза ----------------------------------------------------------------
void Server::system_pause(int second){
	std::this_thread::sleep_for(std::chrono::seconds(second));
}

//----------------- Основная функция работы сервера -------------------------------------------
void Server::server(){
	socket_file();
	server_address();
	binding_soket();
	connect();

	while(true) {
		receiving_user();
	}
}


