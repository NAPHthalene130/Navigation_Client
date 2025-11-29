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
#include <string>
#include "MapDataContainer.h"
#include "NoticeDialog.h"

void DataIO::writeFile(const std::string& path, MapDataContainer* container)
{
    // TODO
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
    std::string endCheck = "MAPDATACHEECK@#$";
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
    std::string check = "MAPDATACHEECK@#$";
    std::string checkRead;
    checkRead.resize(check.size());
    inStream.read(&checkRead[0], check.size());
    if (checkRead != check)
    {
        new NoticeDialog("WARN","FILE CAN'T READ");
        return new MapDataContainer();
    }
    
    return new MapDataContainer();
}

MapDataContainer* DataIO::readNet(const std::string& ip, const std::string& port, const std::string& token)
{
    // TODO
    return new MapDataContainer();
}
