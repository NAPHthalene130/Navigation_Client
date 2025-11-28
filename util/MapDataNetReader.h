#ifndef NAVIGATION_MPADATANETREADER_H
#define NAVIGATION_MPADATANETREADER_H
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <sstream>
class MapDataNetReader
{

private:
    const std::string kPort = "10086";
    const std::string kIp = "127.0.0.1";
    std::string data_;
    mutable std::mutex dataMutex_;
    MapDataNetReader() {
    }
    MapDataNetReader(const MapDataNetReader&) = delete;
    MapDataNetReader& operator=(const MapDataNetReader&) = delete;

    void ReadDataThreadFunc(const std::string& ip, const std::string& port);

public:
    static MapDataNetReader& getInstance(){
        static MapDataNetReader instance;
        return instance;
    }
    void readNetData();
    std::string getData() const {
        std::lock_guard<std::mutex> lock(dataMutex_);
        return data_;
    }
    ~MapDataNetReader(){
    }
};


#endif //NAVIGATION_MPADATANETREADER_H
