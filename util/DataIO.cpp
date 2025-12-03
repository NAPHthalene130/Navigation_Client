#include "DataIO.h"
#include "MapPointButton.h"
#include "Edge.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QUrl>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include "MapDataContainer.h"
#include "NoticeDialog.h"
#include "MapPointButton.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/algorithm/string.hpp>

void DataIO::writeFile(const std::string& path, MapDataContainer* container)
{
    std::filesystem::path fsPath(path);
    if (!std::filesystem::exists(fsPath.parent_path()))
    {
        std::filesystem::create_directories(fsPath.parent_path());
    }
    std::ofstream outStream(fsPath.string(), std::ios::out | std::ios::binary);
    std:: string check = "MAPDATACHEEK@#$";
    outStream.write(check.c_str(), check.size());
    int type = 1;
    //[type][nameLen][name][x][y][pointType][contentLen][content]
    for (auto point : container->pointButtonContainer)
    {
        outStream.write(reinterpret_cast<const char*>(&type), sizeof(int));
        std::string name = point->getName();
        int nameLen = name.size();
        outStream.write(reinterpret_cast<const char*>(&nameLen), sizeof(int));
        outStream.write(name.c_str(), nameLen);
        int x = point->getX();
        outStream.write(reinterpret_cast<const char*>(&x), sizeof(int));
        int y = point->getY();
        outStream.write(reinterpret_cast<const char*>(&y), sizeof(int));
        int pointType = point->getType();
        outStream.write(reinterpret_cast<const char*>(&pointType), sizeof(int));
        std::string content = point->getContent();
        int contentLen = content.size();
        outStream.write(reinterpret_cast<const char*>(&contentLen), sizeof(int));
        outStream.write(content.c_str(), contentLen);
    }
    type = 2;
    //[type][name1Len][name1][name2Len][name2][edgeType]
    for (auto edge : container->edgeContainer)
    {
        outStream.write(reinterpret_cast<const char*>(&type), sizeof(int));
        std::string name1 = edge->getFirstPointButton()->getName();
        int name1Len = name1.size();
        outStream.write(reinterpret_cast<const char*>(&name1Len), sizeof(int));
        outStream.write(name1.c_str(), name1Len);
        std::string name2 = edge->getSecondPointButton()->getName();
        int name2Len = name2.size();
        outStream.write(reinterpret_cast<const char*>(&name2Len), sizeof(int));
        outStream.write(name2.c_str(), name2Len);
        int edgeType = edge->getType();
        outStream.write(reinterpret_cast<const char*>(&edgeType), sizeof(int));
    }
    type = 3;
    outStream.write(reinterpret_cast<const char*>(&type), sizeof(int));
    std::string endCheck = "MAPDATACHEEK@#$";
    outStream.write(endCheck.c_str(), endCheck.size());
}

void DataIO::writeNet(const std::string& ip, const std::string& port, MapDataContainer* container, const std::string& token)
{
    using boost::asio::ip::tcp;
    try {
        tcp::iostream stream(ip, port);
        if (!stream) {
            new NoticeDialog("错误","连接失败");
            return;
        }
        stream << "#NAVIGATION#CHECK\n";
        stream.flush();
        stream << "#NAVIGATION#@SAVE@" << token << "\n";
        stream.flush();
        std::string response;
        std::getline(stream, response);
        if (response == "#NAVIGATION#@TOKEN_OK") {
            stream << "#NAVIGATION#@CHECK2\n";
            stream.flush();
            //[CHECK]@[POINT]@[NAME]@[X]@[Y]@[TYPE]@[CONTENT]
            for (auto point : container->pointButtonContainer) {
                stream << "#NAVIGATION#@POINT@" << point->getName() << "@" << point->getX() << "@" << point->getY() << "@" << point->getType() << "@" << point->getContent() << "\r\n";
                stream.flush();
            }
            stream << "#NAVIGATION#@EDGES\n";
            stream.flush();
            //[CHECK]@[EDGE]@[firstName]@[secondNmae]@[type]
            for (auto edge: container->edgeContainer) {
                stream << "#NAVIGATION#@EDGE@" << edge->getFirstPointButton()->getName() << "@" << edge->getSecondPointButton()->getName() << "@" << edge->getType() << "\r\n";
                stream.flush();
            }
            stream << "#NAVIGATION#@END\n";
            stream.flush();
        } else if (response == "#NAVIGATION#@TOKEN_ERROR") {
            new NoticeDialog("错误","TOKEN已被使用");
        } else {
            new NoticeDialog("错误","地图保存失败，连接错误");
        }
        stream.close();
    } catch (std::exception& e) {
        new NoticeDialog("错误","连接发生错误");
        return;
    }
    new NoticeDialog("提示","地图保存成功");
}

MapDataContainer* DataIO::readFile(const std::string& path)
{
    // TODO
    std::filesystem::path fsPath(path);
    if (!std::filesystem::exists(fsPath))
    {
        return nullptr;
    }
    std::ifstream inStream(fsPath.string(), std::ios::in | std::ios::binary);
    std::string check = "MAPDATACHEEK@#$";
    std::string checkRead;
    checkRead.resize(check.size());
    inStream.read(&checkRead[0], check.size());
    if (checkRead != check)
    {
        new NoticeDialog("WARN","FILE CAN'T READ");
        return new MapDataContainer();
    }
    int type = 0;
    inStream.read(reinterpret_cast<char*>(&type), sizeof(int));
    MapDataContainer *container = new MapDataContainer();
    //[type][nameLen][name][x][y][pointType][contentLen][content]
    while (type != 2) {
        int nameLen = 0;
        inStream.read(reinterpret_cast<char*>(&nameLen), sizeof(int));
        std::string name;
        name.resize(nameLen);
        inStream.read(name.data(), nameLen);
        int x,y,pointType;
        inStream.read(reinterpret_cast<char*>(&x), sizeof(int));
        inStream.read(reinterpret_cast<char*>(&y), sizeof(int));
        inStream.read(reinterpret_cast<char*>(&pointType), sizeof(int));
        int contentLen = 0;
        inStream.read(reinterpret_cast<char*>(&contentLen), sizeof(int));
        std::string content;
        content.resize(contentLen);
        inStream.read(content.data(), contentLen);

        MapPointButton *newButton = new MapPointButton();
        newButton->setName(name);
        newButton->setContent(content);
        newButton->setType(pointType);
        newButton->setX(x);
        newButton->setY(y);

        container->addMapPointButton(newButton);

        inStream.read(reinterpret_cast<char*>(&type), sizeof(int));
    }
    std::map<std::string, MapPointButton*> nameToMapPointButtonPtr;
    for (auto button: container->pointButtonContainer) {
        nameToMapPointButtonPtr[button->getName()] = button;
    }
    //[type][name1Len][name1][name2Len][name2][edgeType]
    while (type != 3) {
        int name1Len = 0;
        inStream.read(reinterpret_cast<char*>(&name1Len), sizeof(int));
        std::string name1;
        name1.resize(name1Len);
        inStream.read(name1.data(), name1Len);
        int name2Len = 0;
        inStream.read(reinterpret_cast<char*>(&name2Len), sizeof(int));
        std::string name2;
        name2.resize(name2Len);
        inStream.read(name2.data(), name2Len);
        int edgeType = 0;
        inStream.read(reinterpret_cast<char*>(&edgeType), sizeof(int));
        Edge* edge = new Edge(nameToMapPointButtonPtr[name1], nameToMapPointButtonPtr[name2]);
        edge->setType(edgeType);
        container->edgeContainer.push_back(edge);

        inStream.read(reinterpret_cast<char*>(&type), sizeof(int));
    }

    check = "MAPDATACHEEK@#$";
    checkRead.resize(check.size());
    inStream.read(checkRead.data(), checkRead.size());
    if (checkRead != check) {
        //TODO:读取成功但结尾验证失败
    } else {
        // TODO:读取成功
    }
    return container;
}

MapDataContainer* DataIO::readNet(const std::string& ip, const std::string& port, const std::string& token)
{
    MapDataContainer* tempMapDataContainer = new MapDataContainer();
    using boost::asio::ip::tcp;
    try {
        tcp::iostream stream(ip, port);
        if (!stream) {
            new NoticeDialog("错误","连接失败");
            return new MapDataContainer();
        }
        stream << "#NAVIGATION#CHECK\n";
        stream << "#NAVIGATION#@LOAD@" << token << "\n";
        stream.flush();
        std::string response;
        std::getline(stream, response);
        if (response == "#NAVIGATION#@TOKEN_OK") {
            std::vector<std::string> command;
            while (std::getline(stream, response)) {
                command.push_back(response);
                if (response == "#NAVIGATION#@END") {
                    break;
                }
            }
            std::map<std::string, MapPointButton*> nameToMapPointButtonPtr;
            for (auto command : command) {
                if (command == "#NAVIGATION#@END") {
                    continue;
                }
                std::vector<std::string> commandTokens;
                boost::split(commandTokens, command, boost::is_any_of("@"));
                if (commandTokens[0] != "#NAVIGATION#") {
                    continue;
                }

                //[CHECK]@[POINT]@[NAME]@[X]@[Y]@[TYPE]@[CONTENT]
                if (commandTokens[1] == "POINT") {
                    MapPointButton* newPoints = new MapPointButton();
                    std::string name = commandTokens[2];
                    int x = std::stoi(commandTokens[3]);
                    int y = std::stoi(commandTokens[4]);
                    int type = std::stoi(commandTokens[5]);
                    std::string content = commandTokens[6];
                    newPoints->setName(name);
                    newPoints->setX(x);
                    newPoints->setY(y);
                    newPoints->setType(type);
                    newPoints->setContent(content);
                    tempMapDataContainer->addMapPointButton(newPoints);
                }
                if (commandTokens[1] == "EDGES") {
                    for (auto button: tempMapDataContainer->pointButtonContainer) {
                        nameToMapPointButtonPtr[button->getName()] = button;
                    }
                }
                //[CHECK]@[EDGE]@[firstName]@[secondNmae]@[type]
                if (commandTokens[1] == "EDGE") {
                    std::string firstName = commandTokens[2];
                    std::string secondName = commandTokens[3];
                    int type = std::stoi(commandTokens[4]);
                    Edge* edge = new Edge(nameToMapPointButtonPtr[firstName], nameToMapPointButtonPtr[secondName]);
                    edge->setType(type);
                    tempMapDataContainer->edgeContainer.push_back(edge);
                }
            }
            stream.close();
        } else if (response == "#NAVIGATION#@TOKEN_ERROR") {
            new NoticeDialog("错误","TOKEN未找到");
        } else {
            new NoticeDialog("错误","连接错误");
        }
    } catch (const std::exception& e) {
        new NoticeDialog("错误", e.what());
    }
    return tempMapDataContainer;
}
