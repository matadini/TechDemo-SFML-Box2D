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


#include "game_world.h"

#include "box_creators.h"
#include "contact_detector.h"

GameWorld::GameWorld(Assets::Resources& resources) :
    m_boxWorld(BoxCreators::createWorld()),
    m_builder(new MapBuilder::TechDemo(m_boxWorld.get()))
{
   m_boxWorld.get()->SetContactListener(&m_contactDetector);

   m_builder->createArea(listIdentifiedBodies, resources);
   m_builder->createDynamicBodies(listMovableBodies, resources);
}

ContactDetector* GameWorld::getContactDetector()
{
    return &m_contactDetector;
}

MovableBody* GameWorld::getPlayer()
{
    for(std::shared_ptr<MovableBody>& item : listMovableBodies)
    {
        if(item->getBodyType() == BodyUserData::Type::Player){
            return item.get();
        }
    }
    return nullptr;
}

b2World* GameWorld::getBoxWorld() const
{
    return m_boxWorld.get();
}

void GameWorld::prepareWorld()
{
    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    m_boxWorld->Step(
            timeStep,
            velocityIterations,
            positionIterations);
}
