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
#ifndef DRAWABLE_POLYGON_BODY_H
#define DRAWABLE_POLYGON_BODY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "animator.h"
/* Dawne DrawablePolygonBody */
class DrawableBody
{

protected:
    const int METERES_TO_PIXELS = 50;
    const float PIXELS_TO_METERES = 0.02f;

    const float RADIANS_TO_PIXELS = 180 / b2_pi;
    const float PIXELS_TO_RADIANS = b2_pi / 180;

public:
    DrawableBody(b2Body* baseBody);
    virtual ~DrawableBody();

    virtual void render(sf::RenderWindow& window) const = 0;

    void setColor(sf::Color newColor);
    void setRotate(const float32 angle);
    void setTexture(sf::Texture& texture);
    void setPosition(const float32 x, const float32 y);

    void setVisable(const bool value);
    bool isVisable() const;

    float   getRotate() const;
    b2Body* getBody();
    sf::Vector2f getPosition() const;

    void update();

protected:
    bool m_isVisable;
    b2Body* m_bodyPtr;

    std::shared_ptr<sf::Shape> m_renderObj;

    void synchronize(sf::Shape* view, b2Body* model) const;
};

class DrawableBodyGenerated : public DrawableBody
{
public:
    DrawableBodyGenerated(b2Body* baseBody);
    ~DrawableBodyGenerated();

    void render(sf::RenderWindow& window) const;

private:
    sf::ConvexShape* generateView(b2Body* body) const;
};


class DrawableBodyAnimated : public DrawableBody
{
public:
    DrawableBodyAnimated(
            b2Body* baseBody,
            Animator* animator);
    ~DrawableBodyAnimated();

    void render(sf::RenderWindow &window) const;

    Animator* getAnimator() const;

private:
    std::shared_ptr<Animator> m_animator;

};


#endif // DRAWABLE_POLYGON_BODY_H
