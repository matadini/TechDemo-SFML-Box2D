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

#include "body_mover.h"

#include <Box2D/Box2D.h>
#include "body_jump_validator.h"

BodyMover::BodyMover(b2Body* baseBody) :
    m_body(baseBody),
    m_bodyMaxSpeed(5.f),
    m_bodySpeedChangeValue(0.12f),
    m_bodyJumpForce(5.5f),
    m_canJump (true)
{ }


void BodyMover::setMaxSpeed(const float newBodyMaxSpeed)
{
    if(newBodyMaxSpeed > 0){
        this->m_bodyMaxSpeed = newBodyMaxSpeed;
    }
}


void BodyMover::setMoveSpeedChangeValue(const float newBodySpeed)
{
    this->m_bodySpeedChangeValue = newBodySpeed;
}

void BodyMover::setJumpForce(const float newBodySpeed)
{
    this->m_bodyJumpForce = newBodySpeed;
}

void BodyMover::move(Direction moveDir)
{
    switch(moveDir)
    {
        case Direction::Right:
        {
            const b2Vec2 oldVelocity = m_body->GetLinearVelocity();

            if(oldVelocity.x < m_bodyMaxSpeed)
            {
                const b2Vec2 newVelocity = b2Vec2(
                            oldVelocity.x + m_bodySpeedChangeValue, oldVelocity.y);

                m_body->SetLinearVelocity(newVelocity);
            }
            break;
        }

        case Direction::Left:
        {
            const b2Vec2 oldVelocity = m_body->GetLinearVelocity();

            if(oldVelocity.x > -m_bodyMaxSpeed){

                const b2Vec2 newVelocity = b2Vec2(
                            oldVelocity.x - m_bodySpeedChangeValue, oldVelocity.y);

                m_body->SetLinearVelocity(newVelocity);
            }
            break;
        }

        case Direction::Jump:
        {
            if(BodyJumpValidator::test(m_body)){
                const b2Vec2 oldVelocity = m_body->GetLinearVelocity();
                const b2Vec2 newVelocity = b2Vec2(oldVelocity.x, - m_bodyJumpForce);

                m_body->SetLinearVelocity(newVelocity);
            }
            break;
        }
    }
}

/* Nie uzywany */
bool BodyMover::jumpTest()
{
    bool toReturn = false;

    if(this->m_body->GetContactList() != nullptr){

        toReturn = true;
    }
    return toReturn;
}

