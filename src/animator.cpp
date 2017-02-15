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

#include "animator.h"

#include <iostream>

Animator::Animator(
        sf::Shape* shapeObj,
        sf::Vector2f frameSize) :
            m_animationSpeed(1),
            m_frameIterator(0.0),
            m_selectedAnimation(0),
            m_frameCount(0),
            m_animationCount(0),
            m_frameSize(frameSize),
            m_shape(shapeObj)
{
    const sf::Texture* shapeTexture = m_shape->getTexture();
    if (shapeTexture != nullptr)
    {
        const sf::Vector2u textureSize = shapeTexture->getSize();
        m_frameCount = textureSize.x / m_frameSize.x;
        m_animationCount = textureSize.y / m_frameSize.y;
        std::cout
            << "m_frameCount: "
            << m_frameCount
            << " m_animationCount: "
            << m_animationCount
            << "\n";

    } else {
        std::cout
            << __func__
            <<" -Texture of shape is NULL\n";
    }

}

void Animator::work()
{
    const int multiplier =
            (int)(m_frameIterator / this->m_frameCount);

    if (multiplier < this->m_frameCount)
    {
        updateShape(multiplier);

    } else {
        m_frameIterator = 0;
    }
    m_frameIterator += m_animationSpeed;
}

void Animator::work(double externalIterator)
{
    const int multiplier =
            (int)(externalIterator / this->m_frameCount);

    if (multiplier < this->m_frameCount)
    {
        updateShape(multiplier);

    } else {
        externalIterator = 0;
    }
    externalIterator += m_animationSpeed;
}

void Animator::updateShape(const int multiplier)
{
    m_shape->setTextureRect(
                    sf::IntRect(
                        multiplier * m_frameSize.x,
                        m_selectedAnimation*m_frameSize.y,
                        m_frameSize.x,
                        m_frameSize.y));
}

void Animator::setAnimation(const int index)
{
    if(index < m_animationCount){
        this->m_selectedAnimation = index;
    } else {
        std::cout << __func__ << " -index to hight";
    }
}

void Animator::setAnimationSpeed(const double newSpeed)
{
    if(newSpeed > 0){
        this->m_animationSpeed = newSpeed;
    } else {
        std::cout << __func__ << " -newSpeed to hight";
    }
}

sf::Shape* Animator::getShape() const
{
    return this->m_shape;
}
