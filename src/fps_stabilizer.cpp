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


#include "fps_stabilizer.h"

#include <iostream>

FpsStabilizer::FpsStabilizer(const int fpsValue) :
    m_sleepValue(0),
    m_showLog(false)
{
    m_maxFPS  = (fpsValue + ERROR_MARGIN);
    m_miniFPS = (fpsValue - ERROR_MARGIN);
}


void FpsStabilizer::setLog(const bool show){
    m_showLog = show;
}


void FpsStabilizer::work()
{
    m_timeBuffer = m_clockBuffer.restart();

    float currentFPS = getFPS();


    if (currentFPS < m_miniFPS)
    {
        m_sleepValue -= 0.001
                ;
    } else if (currentFPS > m_maxFPS){

        m_sleepValue += 0.001;
    }

    if(m_showLog){
        std::cout
            << "minFPS: " << m_miniFPS
            << " maxFPS: " << m_maxFPS
            << " currentFPS: " << currentFPS
            << "\n";
    }

    sf::sleep(sf::seconds((float)m_sleepValue));
}

double FpsStabilizer::getFPS(){

    return (1000000.0 / m_timeBuffer.asMicroseconds());
}
