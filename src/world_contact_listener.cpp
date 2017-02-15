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


#include "world_contact_listener.h"

#include "body_user_data.h"


void WorldContactListener::BeginContact(b2Contact* contact)
{
    BodyUserData* bodyUserDataA = (BodyUserData*)(contact->GetFixtureA()->GetBody()->GetUserData());
    BodyUserData* bodyUserDataB = (BodyUserData*)(contact->GetFixtureB()->GetBody()->GetUserData());

    if(bodyUserDataA != nullptr && bodyUserDataB != nullptr){

        bool bodyIsPlayer =
                bodyUserDataA->getType() == BodyUserData::Type::Player ||
                bodyUserDataB->getType() == BodyUserData::Type::Player;

        bool bodyIsEnemy =
                bodyUserDataA->getType() == BodyUserData::Type::Enemy ||
                bodyUserDataB->getType() == BodyUserData::Type::Enemy;

        bool bodyIsWall =
                bodyUserDataA->getType() == BodyUserData::Type::Wall ||
                bodyUserDataB->getType() == BodyUserData::Type::Wall;

        /* Jezeli zachodzi jakas interesujace
         * nas kolizja informacje o niej
         * dodajemy do naszego dziennika-wektora. */
        if(bodyIsPlayer && bodyIsEnemy)
        {
            m_contactTypeList.push_back(ContactType::PlayerTouchEnemy);
        }
        if(bodyIsPlayer && bodyIsWall){

            m_contactTypeList.push_back(ContactType::PlayerTouchWall);
        }
    }
}

void WorldContactListener::EndContact(b2Contact* contact)
{
    BodyUserData* bodyUserDataA = (BodyUserData*)(contact->GetFixtureA()->GetBody()->GetUserData());
    BodyUserData* bodyUserDataB = (BodyUserData*)(contact->GetFixtureB()->GetBody()->GetUserData());

    if(bodyUserDataA != nullptr && bodyUserDataB != nullptr){

        bool bodyIsPlayer =
                bodyUserDataA->getType() == BodyUserData::Type::Player ||
                bodyUserDataB->getType() == BodyUserData::Type::Player;

        bool bodyIsEnemy =
                bodyUserDataA->getType() == BodyUserData::Type::Enemy ||
                bodyUserDataB->getType() == BodyUserData::Type::Enemy;

        bool bodyIsWall =
                bodyUserDataA->getType() == BodyUserData::Type::Wall ||
                bodyUserDataB->getType() == BodyUserData::Type::Wall;

        if(bodyIsPlayer && bodyIsEnemy)
        {
            auto iterator = std::find(
                        m_contactTypeList.begin(),
                        m_contactTypeList.end(),
                        ContactType::PlayerTouchEnemy);

            m_contactTypeList.erase(iterator);
        }
        if(bodyIsPlayer && bodyIsWall)
        {
            auto iterator = std::find(
                        m_contactTypeList.begin(),
                        m_contactTypeList.end(),
                        ContactType::PlayerTouchWall);

            m_contactTypeList.erase(iterator);
        }
    }
}

bool WorldContactListener::isContactListIsEmpty() const
{
    return m_contactTypeList.empty();
}

bool WorldContactListener::isContactListContains(ContactType type) const
{
    bool toReturn = true;

    auto iterator = std::find(
                m_contactTypeList.begin(),
                m_contactTypeList.end(),type);

    if(iterator == m_contactTypeList.end())
    {
        toReturn = false;
    }

    return toReturn;
}
