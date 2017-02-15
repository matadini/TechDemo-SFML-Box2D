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

#ifndef CONTACT_DETECTOR_H
#define CONTACT_DETECTOR_H

#include <vector>
#include <Box2D/Box2D.h>


class ContactDetector : public b2ContactListener
{
public:
    struct Contact
    {
        enum Type : int
        {
            Empty,
            PlayerTouchEnemy,
            PlayerTouchWall
        };

        struct Info
        {
            Type type;
            b2Body* bodyPtrFirst;
            b2Body* bodyPtrSecond;
        };
    };

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    bool isContactListIsEmpty() const;
    bool isContactListContains(Contact::Type type) const;

    std::vector<Contact::Info> getContactList(Contact::Type type);

private:
    std::vector<Contact::Info> m_contactDiary;

    int getContactInfoItemIndex(const Contact::Info& data) const;

    bool isContactShouldBeServerd(Contact::Type type) const;
    bool isContactInfoExistsInDiary(const Contact::Info& data) const;

    Contact::Info constructContactInfo(
            Contact::Type type,
            b2Body* contactBodyA,
            b2Body* contactBodyB) const;

    Contact::Type getContactType(b2Body* bodyA, b2Body* bodyB) const;
};

#endif // CONTACT_DETECTOR_H
