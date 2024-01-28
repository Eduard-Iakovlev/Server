# pragma once
#include <fstream>
#include <string>
#include <shared_mutex>

class Logger{
    public:
    Logger(std::string mess);
    ~Logger();

    void read_last_line();
    void apped_to_log();

    private:
    std::string _mess;
    std::ofstream _filestream;
    std::string _filename;
    std::string get_last_line();
    std::shared_mutex shared_mutex;
};