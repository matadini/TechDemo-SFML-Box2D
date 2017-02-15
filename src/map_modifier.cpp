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


#include "map_modifier.h"

void
MapModifier::asEmpty::change(
        GameMap::Item* itemPtr)
{

}

void
MapModifier::asRotatingPlatform::change(
        GameMap::Item* itemPtr)
{
    itemPtr->height = 40;
    itemPtr->width = 120;
}

void MapModifier::asStandardItem::change(
        GameMap::Item* itemPtr)
{
    itemPtr->height = 40;
    itemPtr->width = 40;
}

void
MapModifier::asStandardMapTextureUp::change(
        GameMap::Item* itemPtr)
{
    itemPtr->height = 40;
    itemPtr->width = 40;
}

void MapModifier::init(
        std::map<
            GameObjRegister::Index,
            std::shared_ptr<MapModifier::Base>>& map)
{
    map[GameObjRegister::Index::Empty] =
            std::shared_ptr<MapModifier::Base>(
                new MapModifier::asEmpty());

    map[GameObjRegister::Index::MapRotatedPlatform ] =
                    std::shared_ptr<MapModifier::Base>(
                        new MapModifier::asRotatingPlatform());

    map[GameObjRegister::Index::MapFlor] =
                std::shared_ptr<MapModifier::Base>(
                        new MapModifier::asStandardItem());

    map[GameObjRegister::Index::Player] =
                std::shared_ptr<MapModifier::Base>(
                        new MapModifier::asStandardItem());

    map[GameObjRegister::Index::MapWall] =
                std::shared_ptr<MapModifier::Base>(
                        new MapModifier::asStandardItem());

    map[GameObjRegister::Index::MapFlorUp] =
                std::shared_ptr<MapModifier::Base>(
                    new MapModifier::asStandardMapTextureUp());
}
