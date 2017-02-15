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

#ifndef RENDER_NT_H
#define RENDER_NT_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "game_map.h"

class RenderNT
{
public:

    RenderNT(sf::RenderWindow* window);

    void drawMesh();
    void render(GameMap& map);
    void refresh(const sf::View& camera);

private:
    struct RenderSurface
    {
        sf::Vector2f HeightY;
        sf::Vector2f WidthX;

        void update(
                sf::Vector2f viewCenterPosition,
                sf::Vector2u windowSize);
    };
    RenderSurface m_renderSurface;

    struct RenderEngine
    {
        struct InfoForEngine
        {
            GameMap* map;
            sf::RenderWindow* window;
            RenderSurface renderSurface;
        };

        struct Base
        {
            virtual ~Base() {}
            void virtual render(InfoForEngine& data) = 0;
        };

        struct Graphics : public Base
        {
            Graphics();
            ~Graphics();
            void render(InfoForEngine &data);

            struct Painter
            {
                struct Base {
                    void virtual draw(
                            GameMap::Item* item,
                            sf::RenderWindow* window) = 0;
                };

                struct MapFlor : public Base {
                    void draw(
                            GameMap::Item* item,
                            sf::RenderWindow* window);
                };

                struct MapWall : public Base {
                    void draw(
                            GameMap::Item* item,
                            sf::RenderWindow* window);
                };

                struct MapRotatingPlatform : public Base {
                    void draw(
                            GameMap::Item* item,
                            sf::RenderWindow* window);
                };

                struct MapInvisableWall : public Base {
                    void draw(
                            GameMap::Item* item,
                            sf::RenderWindow* window);
                };

                struct Player : public Base {
                    void draw(
                            GameMap::Item* item,
                            sf::RenderWindow* window);
                };
            };
        private:
            std::map<
                std::string,
                std::shared_ptr<Painter::Base>> m_painters;
        };
    };
    RenderEngine::Base* m_renderEngine;

    sf::Vector2i m_meshSize;
    sf::RenderWindow* m_window;
};

#endif // RENDER_NT_H
