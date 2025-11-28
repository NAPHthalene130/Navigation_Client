#include "MapDataNetReader.h"
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
void MapDataNetReader::readNetData()
{
    std::thread([this]() {
        this->ReadDataThreadFunc(this->kIp, this->kPort);
    }).detach();
    std::cout << "Data reading thread detached. I/O is running in the background." << std::endl;
}

void MapDataNetReader::ReadDataThreadFunc(const std::string& ip, const std::string& port)
{
    using boost::asio::ip::tcp;
    std::string receivedData;

    try {
        boost::asio::io_context ioContext;
        tcp::resolver resolver(ioContext);
        tcp::socket socket(ioContext);

        auto endpoints = resolver.resolve(ip, port);
        connect(socket, endpoints);

        std::cout << "Successfully connected to " << ip << ":" << port << std::endl;

        boost::asio::streambuf response;

        read(socket, response, boost::asio::transfer_all());

        std::istream responseStream(&response);
        receivedData.assign(std::istreambuf_iterator<char>(responseStream), {});

    } catch (const boost::system::system_error& e) {
        std::cerr << "Boost.Asio Error in thread: " << e.what() << std::endl;
        receivedData = "Error: " + std::string(e.what());
    } catch (const std::exception& e) {
        std::cerr << "General Error in thread: " << e.what() << std::endl;
        receivedData = "Error: " + std::string(e.what());
    }

    {
        std::lock_guard lock(dataMutex_);
        this->data_ = std::move(receivedData);
    }
    std::cout << "Data reading completed. Data size: " << this->data_.size() << std::endl;
}
