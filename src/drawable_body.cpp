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


#include "drawable_body.h"

#include "globals.h"
/* drawable_polygon_body.cpp */
DrawableBody::DrawableBody(b2Body* baseBody) :
    m_bodyPtr(baseBody),
    m_isVisable(true)
{

}

DrawableBody::~DrawableBody()
{

}

void DrawableBody::update(){
    this->synchronize(m_renderObj.get(), m_bodyPtr);
}

void DrawableBody::setColor(sf::Color newColor)
{
    this->m_renderObj.get()->setFillColor(newColor);
}

sf::Vector2f DrawableBody::getPosition() const
{
    const float bodyPositionX =
            this->m_bodyPtr->GetPosition().x*G_METERES_TO_PIXELS;

    const float bodyPositionY =
            this->m_bodyPtr->GetPosition().y*G_METERES_TO_PIXELS;

    sf::Vector2f toReturn(bodyPositionX,bodyPositionY);
    return toReturn;
}

float DrawableBody::getRotate() const
{
    return m_bodyPtr->GetAngle() * RADIANS_TO_PIXELS;
}


void DrawableBody::setTexture(sf::Texture& texture)
{
    this->m_renderObj->setTexture(&texture);
}


void DrawableBody::setPosition(const float32 x, const float32 y)
{
    m_bodyPtr->SetTransform(
                b2Vec2(
                    x*PIXELS_TO_METERES,
                    y*PIXELS_TO_METERES), 0.f);
    this->synchronize(m_renderObj.get(), m_bodyPtr);
}


void DrawableBody::setRotate(const float32 angle)
{

    m_bodyPtr->SetTransform(
                m_bodyPtr->GetPosition(),
                ( angle * PIXELS_TO_RADIANS));
    this->synchronize(m_renderObj.get(), m_bodyPtr);
}

void DrawableBody::synchronize(sf::Shape* view, b2Body* model) const
{
    float bodyPositionX = model->GetPosition().x * METERES_TO_PIXELS;
    float bodyPositionY = model->GetPosition().y * METERES_TO_PIXELS;
    float bodyRotate = model->GetAngle() * RADIANS_TO_PIXELS;

    view->setPosition(bodyPositionX, bodyPositionY);
    view->setRotation(bodyRotate);
}


void DrawableBody::render(sf::RenderWindow& window) const
{
    if(m_isVisable){
        window.draw(*m_renderObj.get());
    }
}

void DrawableBody::setVisable(const bool value)
{
    this->m_isVisable = value;
}

bool DrawableBody::isVisable() const
{
    return this->m_isVisable;
}

b2Body* DrawableBody::getBody()
{
    return m_bodyPtr;
}

DrawableBody* getBodyShape(
        std::vector<DrawableBody> list,
        const b2Body* body)
{
    DrawableBody* toReturn = nullptr;

    for(DrawableBody& item : list){
        if(item.getBody() == body){
            toReturn = &item;
            break;
        }
    }

    return toReturn;
}



DrawableBodyAnimated::DrawableBodyAnimated(
        b2Body* baseBody,
        Animator* animator)
            : DrawableBody(baseBody), m_animator(animator)
{
    m_renderObj.reset(m_animator->getShape());
}

DrawableBodyAnimated::~DrawableBodyAnimated()
{

}

void
DrawableBodyAnimated::render(sf::RenderWindow &window) const
{
    if(isVisable()){
        m_animator->work();
        window.draw(*m_animator->getShape());
    }
}

Animator*
DrawableBodyAnimated::getAnimator() const
{
    return m_animator.get();
}

DrawableBodyGenerated::DrawableBodyGenerated(b2Body* baseBody):
    DrawableBody(baseBody)
{
    m_renderObj.reset(generateView(m_bodyPtr));
}

DrawableBodyGenerated::~DrawableBodyGenerated()
{

}

void
DrawableBodyGenerated::render(sf::RenderWindow& window) const
{
    if(isVisable()){
        window.draw(*m_renderObj.get());
    }
}


sf::ConvexShape*
DrawableBodyGenerated::generateView(b2Body* body) const
{

    sf::ConvexShape* bodyView = new sf::ConvexShape();
    bodyView->setFillColor(sf::Color::White);

    for (b2Fixture* fixturePtr = body->GetFixtureList();
            fixturePtr != nullptr; fixturePtr = fixturePtr->GetNext())
    {

        b2Shape* shapeBuffer = fixturePtr->GetShape();
        if(shapeBuffer->m_type == b2Shape::Type::e_polygon)
        {
            b2PolygonShape* realBodyShape = static_cast<b2PolygonShape*>(shapeBuffer);

            const int vertexCount = realBodyShape->GetVertexCount();
            bodyView->setPointCount(vertexCount);

            for (int i = 0; i < vertexCount; ++i)
            {
                b2Vec2 currVerts = realBodyShape->GetVertex(i);

                float posX = currVerts.x * METERES_TO_PIXELS;
                float posY = currVerts.y * METERES_TO_PIXELS;

                bodyView->setPoint(i, sf::Vector2f(posX, posY));
            }

            bodyView->setOrigin(0, 0);
        }
    }

    return bodyView;
}
