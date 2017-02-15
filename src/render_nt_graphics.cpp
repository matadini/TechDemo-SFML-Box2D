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

#include "game_obj_register.h"


RenderNT::RenderEngine::Graphics::Graphics()
{

    m_painters[GameObjRegister::get()->list.at(
                GameObjRegister::Index::MapFlor)] =
                    std::shared_ptr<Graphics::Painter::Base>(
                        new Graphics::Painter::MapFlor());

    m_painters[GameObjRegister::get()->list.at(
                GameObjRegister::Index::MapWall)] =
                    std::shared_ptr<Graphics::Painter::Base>(
                        new Graphics::Painter::MapWall());


    m_painters[GameObjRegister::get()->list.at(
                GameObjRegister::Index::MapRotatedPlatform)] =
                    std::shared_ptr<Graphics::Painter::Base>(
                        new Graphics::Painter::MapRotatingPlatform());


    m_painters[GameObjRegister::get()->list.at(
                GameObjRegister::Index::MapInvisableWall)] =
                    std::shared_ptr<Graphics::Painter::Base>(
                        new Graphics::Painter::MapInvisableWall());

    m_painters[GameObjRegister::get()->list.at(
                GameObjRegister::Index::Player)] =
                    std::shared_ptr<Graphics::Painter::Base>(
                        new Graphics::Painter::Player());
}

RenderNT::RenderEngine::Graphics::~Graphics() {}

void RenderNT::RenderEngine::Graphics::render(InfoForEngine &data)
{
    int startI = 0;
    int finishI = data.map->height;

    int startJ = 0;
    int finishJ = data.map->width;

    bool widthCondition = (
                data.renderSurface.WidthX.x >= 0 &&
                data.renderSurface.WidthX.y <= data.map->width);

    bool heightCondition = (
                data.renderSurface.HeightY.x >= 0 &&
                data.renderSurface.HeightY.y <= data.map->height);

    if(widthCondition && heightCondition)
    {
        startI = data.renderSurface.HeightY.x;
        finishI = data.renderSurface.HeightY.y;

        startJ = data.renderSurface.WidthX.x;
        finishJ = data.renderSurface.WidthX.y;
    }

    for(int i = startI; i < finishI; ++i)
    {
        for(int j = startJ; j < finishJ; ++j)
        {
            GameMap::Item* item = &data.map->array[ i ][ j ];

            try
            {
                Graphics::Painter::Base* painter = this->m_painters.at(item->ID).get();
                painter->draw(item, data.window);

            } catch (const std::out_of_range& ex) {

            }
        }
    }
}
