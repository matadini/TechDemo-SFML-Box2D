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


#include "editor.h"

#include <iostream>
#include "render_nt.h"
#include "json.h"
#include "mouse_manager.h"
#include "game_obj_register.h"
#include "map_modifier.h"

void Editor::run()
{
    int width = 0;
    std::cout << "Get width (X): ";
    std::cin >> width;

    int height = 0;
    std::cout << "Get height(Y): ";
    std::cin >> height;

    std::shared_ptr<GameMap> map(new GameMap(width,height));

    sf::RenderWindow window(
                sf::VideoMode(800,600, 16),
                std::string("hello"),
                sf::Style::Close);

    sf::View camera;
    camera = window.getDefaultView();

    sf::Vector2f startCameraPosition = camera.getCenter();

    const int viewMoveValue = 5;

    RenderNT render(&window);
    render.refresh(camera);

    MouseManager mouseIndex(&window);

    /* Modyfikatory obiektow mapy. */
    std::map<
        GameObjRegister::Index,
        std::shared_ptr<MapModifier::Base>> theModders;

    MapModifier::init(theModders);

    /* Ustawiamy stan poczatkowy na pusty element. */
    GameObjRegister::Index selectedIndex = GameObjRegister::Index::Empty;
    MapModifier::Base* magicPoint = theModders.at(selectedIndex).get();

    while(window.isOpen())
    {
        sf::Event myEvent;
        while(window.pollEvent(myEvent))
        {
            if(myEvent.type == sf::Event::Closed){
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                Json::Generator dec(map.get());
                QJsonDocument jsonDoc = dec.getJsonDoc();

                const std::string fileName = std::string("hello.json");

                Json::File fileDec;
                fileDec.saveJsonMap(jsonDoc, QString::fromStdString(fileName));

                std::cout << std::string("Saved as: ") + fileName;
            }


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                const std::string fileName = std::string("hello.json");

                Json::File fileDec;
                QJsonDocument jsonDoc = fileDec.readJsonMap(QString::fromStdString(fileName));

                Json::Generator dec;
                map.reset(dec.getGameMapFromJson(jsonDoc));

                std::cout << std::string("Readed from: ") + fileName;

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
            {
                int input = 0;
                for(auto& pair :GameObjRegister::get()->list )
                {
                    std::cout
                        << "No. "
                        << pair.first
                        << " Content: "
                        << pair.second
                        << "\n";
                }
                std::cin >> input;

                try
                {
                    selectedIndex = (GameObjRegister::Index)input;
                    magicPoint = theModders.at(selectedIndex).get();

                } catch (const std::out_of_range& ex){

                    std::cout << ex.what() << "\n";
                    magicPoint = nullptr;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if(camera.getCenter().x >= startCameraPosition.x+10)
                {
                    render.refresh(camera);
                    camera.move(-viewMoveValue, 0);
                    window.setView(camera);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if(camera.getCenter().x + (window.getSize().x/2) <= (map->width*40)-10)
                {
                    render.refresh(camera);
                    camera.move(viewMoveValue, 0);
                    window.setView(camera);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if(camera.getCenter().y >= startCameraPosition.y+10)
                {
                    render.refresh(camera);
                    camera.move(0, -viewMoveValue);
                    window.setView(camera);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if(camera.getCenter().y + (window.getSize().y/2) <= (map->height*40)-10)
                {
                    render.refresh(camera);
                    camera.move(0, viewMoveValue);
                    window.setView(camera);
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                MouseManager::Info infoMouse =
                        mouseIndex.getIndex(map.get(), &camera);
                if (infoMouse.isOk)
                {

                    GameMap::Item* itemPtr =
                            &map->array[infoMouse.x][infoMouse.y];

                    const std::string selectedIndexValue =
                            GameObjRegister::get()->list.at(selectedIndex);

                    if(itemPtr->ID != selectedIndexValue &&
                            magicPoint != nullptr)
                    {
                        itemPtr->ID = selectedIndexValue;
                        magicPoint->change(itemPtr);
                    }
                }
            }
        }

        /* Render */
        window.clear(sf::Color::Black);

        render.drawMesh();
        render.render(*map);

        window.display();
    }
}
