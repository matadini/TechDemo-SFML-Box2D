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

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>

class Animator
{
public:
    Animator(
        sf::Shape* shape,
        sf::Vector2f frameSize);

    void work();
    void work(double externalIterator);

    void setAnimation(const int index);
    void setAnimationSpeed(const double newSpeed);

    sf::Shape* getShape() const;

private:
    double m_animationSpeed;
    double m_frameIterator;

    int m_selectedAnimation;
    int m_frameCount;
    int m_animationCount;

    sf::Vector2f m_frameSize;
    sf::Shape* m_shape;

    void updateShape(const int multiplier);
};
#endif // ANIMATOR_H
