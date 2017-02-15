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


#include "render_nt.h"

#include "editor_globals.h"
#include "game_obj_register.h"

RenderNT::RenderNT(
        sf::RenderWindow* window) :
            m_window(window),
            m_renderEngine(new RenderEngine::Graphics()) {}

void RenderNT::refresh(const sf::View& camera)
{
    m_renderSurface.update(
                camera.getCenter(),
                m_window->getSize());
}

void RenderNT::drawMesh()
{
    int width = m_meshSize.x;
    int height =  m_meshSize.y;

    const int pion = height * EditorGlobals::MESH_ITEM_SIZE;
    const int poziom = width * EditorGlobals::MESH_ITEM_SIZE;

    /* Linie pionowe */
    for (int i = 0; i < width + 1; i++)
    {
        sf::Vertex vLine[] =
        {
            sf::Vertex(sf::Vector2f(
                (float)(i * EditorGlobals::MESH_ITEM_SIZE), 0.f)),

            sf::Vertex(sf::Vector2f(
                (float)(i * EditorGlobals::MESH_ITEM_SIZE), (float)pion))
        };

        m_window->draw(vLine, 2, sf::Lines);
    }

    /* Linie poziome */
    for (int i = 0; i < height + 1; i++)
    {
        sf::Vertex vLine[] =
        {
            sf::Vertex(sf::Vector2f(
                0.f, (float)(i * EditorGlobals::MESH_ITEM_SIZE))),

            sf::Vertex(sf::Vector2f(
                (float)poziom, (float)(i * EditorGlobals::MESH_ITEM_SIZE)))
        };

        m_window->draw(vLine, 2, sf::Lines);
    }
}

void RenderNT::render(GameMap& map)
{
    m_meshSize.x = map.width;
    m_meshSize.y = map.height;

    RenderEngine::InfoForEngine  info;
    info.map = &map;
    info.window = m_window;
    info.renderSurface = m_renderSurface;

    m_renderEngine->render(info);
}

/* Funkcja okresla ktore indeksy beda rysowane. */
void RenderNT::RenderSurface::update(
        sf::Vector2f viewCenterPosition,
        sf::Vector2u windowSize)
{
    float haldWindowWidth = windowSize.x / 2;
    float halfWindowHeight = windowSize.y / 2;

    this->HeightY
        = sf::Vector2f(
            viewCenterPosition.y - halfWindowHeight,
            viewCenterPosition.y + halfWindowHeight);

    this->WidthX
        = sf::Vector2f(
            viewCenterPosition.x - haldWindowWidth,
            viewCenterPosition.x + haldWindowWidth);

    WidthX.x = WidthX.x / EditorGlobals::MESH_ITEM_SIZE;
    WidthX.y = WidthX.y / EditorGlobals::MESH_ITEM_SIZE;

    HeightY.x = HeightY.x / EditorGlobals::MESH_ITEM_SIZE;
    HeightY.y = HeightY.y / EditorGlobals::MESH_ITEM_SIZE;
}
