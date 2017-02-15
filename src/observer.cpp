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


#include "observer.h"

#include <Box2D/Box2D.h>
const int Observer::METERES_TO_PIXELS = 50;
const float Observer::PIXELS_TO_METERES = 0.02f;

Observer::Info Observer::isBodySeeBody(
                    const b2Body* observer,
                    const b2Body* target,
                    const float seeRangeInPx)
{
    Info toReturn;

    const b2Vec2 targetPosition = target->GetPosition();
    const float targetPositionX = targetPosition.x;
    const float targetPositionY = targetPosition.y;

    b2Vec2 observerPosition = observer->GetPosition();
    const float observerPositionX = observerPosition.x;
    const float observerPositionY = observerPosition.y;

    if (targetPositionX < observerPositionX + seeRangeInPx*PIXELS_TO_METERES &&
        targetPositionX > observerPositionX - seeRangeInPx*PIXELS_TO_METERES &&
        targetPositionY < observerPositionY + seeRangeInPx*PIXELS_TO_METERES &&
        targetPositionY > observerPositionY - seeRangeInPx)
    {
        toReturn.isSee = true;

        if(targetPositionX < observerPositionX){
            toReturn.side = Observer::Info::Side::Left;
        } else {
            toReturn.side = Observer::Info::Side::Right;
        }
    } else {
        toReturn.isSee = false;
    }

    return toReturn;
}
