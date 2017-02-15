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


#include "enemy_behavior.h"

#include "movable_body.h"
#include "body_mover.h"
#include "observer.h"

EnemyBehavior::EnemyBehavior(MovableBody* baseBody)
    : m_ptr(baseBody) {}


/* Zwraca true gdy przeciwnik
 * zobaczyl gracza i sie poruszyl. */
bool EnemyBehavior::moved(const b2Body* playerBody)
{
    bool toReturn = false;

    if(playerBody != nullptr)
    {
        const Observer::Info
                isEnemySeePlayerData =
                    Observer::isBodySeeBody(
                        m_ptr->getBody(),
                        playerBody, 150);

        if(isEnemySeePlayerData.isSee)
        {
            BodyMover* movePtr = m_ptr->getMover();

            switch(isEnemySeePlayerData.side)
            {
                case Observer::Info::Side::Left: {
                    movePtr->move(BodyMover::Direction::Left);
                    break;
                }

                case Observer::Info::Side::Right: {
                    movePtr->move(BodyMover::Direction::Right);
                    break;
                }
            }
        }
        toReturn = isEnemySeePlayerData.isSee;
    }

    return toReturn;
}

/* Zwraca true gdy przeciwnik gracz
 * wskoczyl na przeciwnika i ten skoczyl
 * by go zrzucic. */
bool EnemyBehavior::jumped(const b2Body* playerBody)
{
    bool toReturn = false;

    if(playerBody != nullptr){
        const float enemyPositionY =
                m_ptr->getRenderBody()->getPosition().y;

        const float playerPositionY =
                playerBody->GetPosition().y*50;

        if(playerPositionY < enemyPositionY-10 ){

            m_ptr->getMover()->move(BodyMover::Direction::Jump);
            toReturn = true;
        }
    }

    return toReturn;
}
