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


#include "mouse_manager.h"

#include "editor_globals.h"

MouseManager::MouseManager(sf::RenderWindow* window) : m_window(window)
{
    m_startPositionX = m_window->getDefaultView().getCenter().x;
    m_startPositionY = m_window->getDefaultView().getCenter().y;
}

MouseManager::Info MouseManager::getIndex(GameMap* map, sf::View* view)
{
    int iMousePositionX =
            (int)sf::Mouse::getPosition(*m_window).x +
            (view->getCenter().x - m_startPositionX);

    int iMousePositionY =
            (int)sf::Mouse::getPosition(*m_window).y +
            (view->getCenter().y - m_startPositionY);

    int iSecondParam = (int)iMousePositionX / EditorGlobals::MESH_ITEM_SIZE;
    int iFirstParam = (int)iMousePositionY / EditorGlobals::MESH_ITEM_SIZE;

    bool heightCondition = iFirstParam >= 0 && iFirstParam < map->height;
    bool widthCondition = iSecondParam >= 0 && iSecondParam < map->width;
    bool mainChangeCondition = heightCondition && widthCondition;

    Info toReturn;
    toReturn.x = iFirstParam;
    toReturn.y = iSecondParam;
    toReturn.isOk = mainChangeCondition;

    return toReturn;
}
