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

#include "assets.h"

#include <physfs.h>
#include <iostream>

/* Zip loader .cpp */
Assets::ZipLoader::ZipLoader(const std::string& fileName)
    : m_fileName(fileName) { }


void Assets::ZipLoader::loadTextures(
        std::map<Textures,
        std::shared_ptr<sf::Texture>>& list)
{
    PHYSFS_init(nullptr);
    PHYSFS_addToSearchPath(m_fileName.c_str(), 1);


    std::shared_ptr<sf::Texture> textureMap(
                getTextureFromZip(Paths::get()->TEXTURE_MAP));

    std::shared_ptr<sf::Texture> textureWall(
                getTextureFromZip(Paths::get()->TEXTURE_WALL));

    std::shared_ptr<sf::Texture> textureEnemy(
                getTextureFromZip(Paths::get()->TEXTURE_ENEMY));

    std::shared_ptr<sf::Texture> texturePlayer(
                getTextureFromZip(Paths::get()->TEXTURE_PLAYER));


    list[Assets::Textures::Map]     = textureMap;
    list[Assets::Textures::Wall]    = textureWall;
    list[Assets::Textures::Enemy]   = textureEnemy;
    list[Assets::Textures::Player]  = texturePlayer;

    PHYSFS_deinit();
}

sf::Texture*
Assets::ZipLoader::getTextureFromZip(std::string name) const
{
    sf::Texture* texturePtr = nullptr;

    if(PHYSFS_exists(name.c_str()))
    {
        PHYSFS_File* fileFromZip = PHYSFS_openRead(name.c_str());

        const int fileLenght = PHYSFS_fileLength(fileFromZip);
        char* buffer = new char[fileLenght];
        int readLength = PHYSFS_read (fileFromZip, buffer, 1, fileLenght);

        texturePtr = new sf::Texture();
        texturePtr->loadFromMemory(buffer, readLength);

        delete[] buffer;

        PHYSFS_close(fileFromZip);

    } else {
        std::cout << name + " - doesn't exists. \n";
    }
    return texturePtr;
}


/* Zip loader. */
void Assets::ZipLoader::loadFonts(
        std::map<Fonts,
        std::shared_ptr<sf::Font> > &list)
{
    PHYSFS_init(nullptr);
    PHYSFS_addToSearchPath(m_fileName.c_str(), 1);

    std::shared_ptr<sf::Font> textureAppIcon(
                getFontFromZip(Paths::get()->FONT_NOTATOL));

    list[Assets::Fonts::NOTATOL] = textureAppIcon;

    PHYSFS_deinit();
}


void Assets::ZipLoader::loadSoundBuffers(
        std::map<Fonts,
        std::shared_ptr<sf::SoundBuffer> > &list)
{
    PHYSFS_init(nullptr);
    PHYSFS_addToSearchPath(m_fileName.c_str(), 1);

    /* Na razie nie mamy zasobow
     * ktore moglibysmy ladowac */
    PHYSFS_deinit();
}

sf::Font*
Assets::ZipLoader::getFontFromZip(std::string name) const
{
    sf::Font* ptrToReturn = nullptr;

    if(PHYSFS_exists(name.c_str()))
    {
        std::cout << name + " - exists. \n";

        PHYSFS_File* fileFromZip = PHYSFS_openRead(name.c_str());

        const int fileLenght = PHYSFS_fileLength(fileFromZip);
        char* buffer = new char[fileLenght];
        int readLength = PHYSFS_read (fileFromZip, buffer, 1, fileLenght);

        ptrToReturn = new sf::Font();
        ptrToReturn->loadFromMemory(buffer, readLength);

        PHYSFS_close(fileFromZip);

    } else {
        std::cout << name + " - doesn't exists. \n";
    }

    return ptrToReturn;
}

sf::SoundBuffer*
Assets::ZipLoader::getSoundBufferFromZip(std::string name) const
{
    sf::SoundBuffer* soundBufferPtr = nullptr;

    if(PHYSFS_exists(name.c_str()))
    {
        PHYSFS_File* fileFromZip = PHYSFS_openRead(name.c_str());

        const int fileLenght = PHYSFS_fileLength(fileFromZip);
        char* buffer = new char[fileLenght];
        int readLength = PHYSFS_read (fileFromZip, buffer, 1, fileLenght);

        soundBufferPtr = new sf::SoundBuffer();
        soundBufferPtr->loadFromMemory(buffer, readLength);

        delete[] buffer;

        PHYSFS_close(fileFromZip);

    } else {
        std::cout << name + " - doesn't exists. \n";
    }

    return soundBufferPtr;
}
