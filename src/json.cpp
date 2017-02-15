/* TechDemo SFML/Box2D
Copyright (C) 2016 Matadini (matadini@hotmail.com)

This software is provided 'as-is', without any express
or implied warranty. In no event will the authors be
held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software
for any purpose, including commercial applications, and
to alter it and redistribute it freely, subject to the
following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.


External libraries used by TechDemo SFML/Box2D
-------------------------------
* Qt5 is licensed under the LGPL license
* PhysicsFS is licensed under the zlib license.
* SFML is licensed under the zlib license.
* Box2D is licensed under the zlib license. */


#include "json.h"

//Json::Fields
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "game_map.h"

Json::Fields* Json::Fields::m_ptr = nullptr;

Json::Fields::Fields() :
    ID("ID"),
    WIDTH("width"),
    HEIGHT("height"),
    CONTENT("content"),
    ROW("row"),
    X("x"),
    Y("y")
{

}

Json::Fields* Json::Fields::get()
{
    if(m_ptr == nullptr){
        m_ptr = new Fields();
    }
    return m_ptr;
}


Json::Fields::~Fields(){
    if(m_ptr != nullptr){
        delete m_ptr;
    }
}

// Json::Generator

Json::Generator::Generator(GameMap* base) : m_ptr(base) {}

QJsonDocument Json::Generator::getJsonDoc()
{
    QJsonObject main;
    main[Fields::get()->WIDTH] = m_ptr->width;
    main[Fields::get()->HEIGHT] = m_ptr->height;

    int line = 0;

    QJsonArray array;
    for(std::vector<GameMap::Item>& vec : m_ptr->array)
    {
        QJsonArray lineArray;
        for(GameMap::Item& item : vec)
        {
            QJsonObject newJson;
            newJson[Fields::get()->ID] = QString::fromStdString(item.ID);
            newJson[Fields::get()->X] = QString::number(item.x);
            newJson[Fields::get()->Y] = QString::number(item.y);
            newJson[Fields::get()->WIDTH] = QString::number(item.width);
            newJson[Fields::get()->HEIGHT] = QString::number(item.height);

            lineArray.append(newJson);
        }

        QJsonObject additionalInfo;
        additionalInfo[Fields::get()->ROW] = line;

        lineArray.append(additionalInfo);

        ++line;
        array.append(lineArray);
    }

    main[Fields::get()->CONTENT] = array;

    return QJsonDocument(main);
}

GameMap* Json::Generator::getGameMapFromJson(QJsonDocument &source)
{

    QJsonObject jsonObj = source.object();
    const int height = jsonObj[Json::Fields::get()->HEIGHT].toInt();
    const int width =  jsonObj[Json::Fields::get()->WIDTH].toInt();

    GameMap* newMap = new GameMap(width, height, false);

    QJsonArray content = jsonObj[Json::Fields::get()->CONTENT].toArray();
    for(int i = 0; i < content.size(); ++i)
    {
        std::vector<GameMap::Item> newLine;
        QJsonArray singleRow = content.at(i).toArray();

        for(int j = 0; j < singleRow.size()-1; ++j)
        {
            QJsonObject item = singleRow.at(j).toObject();

            GameMap::Item newItem;
            newItem.ID = item[Json::Fields::get()->ID].toString().toStdString();
            newItem.x = item[Json::Fields::get()->X].toString().toInt();
            newItem.y = item[Json::Fields::get()->Y].toString().toInt();
            newItem.height = item[Json::Fields::get()->HEIGHT].toString().toInt();
            newItem.width = item[Json::Fields::get()->WIDTH].toString().toInt();

            newLine.push_back(newItem);

        }

        newMap->array.push_back(newLine);
    }

    return newMap;
}

// Json::File

Json::File::File() {}

bool Json::File::saveJsonMap(QJsonDocument& document, QString filePath) const
{
    bool toReturn = false;

    QString filePathToSave = filePath;

    if(!filePathToSave.isEmpty()){

        QFile outputFile(filePathToSave);
        outputFile.open(QIODevice::WriteOnly);
        outputFile.write(document.toJson());
        outputFile.close();

        toReturn = true;
    }

    return toReturn;
}

QJsonDocument Json::File::readJsonMap(QString filePath) const
{
    QJsonDocument jsonDocReaded;

    if(QFile::exists(filePath) && !filePath.isEmpty())
    {
        QString fileContentString;

        QFile jsonFile(filePath);
        if(jsonFile.open(QIODevice::ReadOnly)){
            fileContentString = jsonFile.readAll();
            jsonDocReaded = QJsonDocument::fromJson(fileContentString.toUtf8());
        }
        jsonFile.close();
    }

    return jsonDocReaded;
}
