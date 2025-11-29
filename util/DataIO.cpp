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
    // TODO
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
        newButton->setType(type);
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
    // TODO
    return new MapDataContainer();
}
