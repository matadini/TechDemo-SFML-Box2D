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

#ifndef ASSETS_H
#define ASSETS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class Assets
{
public:
    enum Textures : int
    {
        Map,
        Wall,
        Enemy,
        Player,
        AppIcon,
    };

    enum Sounds : int
    {

    } ;

    enum Fonts : int
    {
        NOTATOL
    };

private:
    class Paths
    {
        public:

            const std::string TEXTURE_MAP    = std::string("textures/map.png");
            const std::string TEXTURE_WALL   = std::string("textures/wall.png");
            const std::string TEXTURE_ENEMY  = std::string("textures/enemy.png");
            const std::string TEXTURE_PLAYER = std::string("textures/player.png");
            const std::string TEXTURE_APP_ICON = std::string("textures/icon.png");

            const std::string FONT_NOTATOL = std::string("fonts/notalot.ttf");

            static Paths* get();

        private:
            static std::shared_ptr<Paths> m_ptr;
    };

    class BaseLoader
    {
    public:
        virtual void loadTextures(
                std::map<Textures,
                std::shared_ptr<sf::Texture>>& list) = 0;

        virtual void loadFonts(
                std::map<Fonts,
                std::shared_ptr<sf::Font>>& list) = 0;

        virtual void loadSoundBuffers(
                std::map<Fonts,
                std::shared_ptr<sf::SoundBuffer>>& list) = 0;
    };

    class FileLoader : public BaseLoader
    {
    public:
        void loadTextures(
                std::map<Textures,
                std::shared_ptr<sf::Texture>>& list);

        void loadFonts(
                std::map<Fonts,
                std::shared_ptr<sf::Font>>& list);

        void loadSoundBuffers(
                std::map<Fonts,
                std::shared_ptr<sf::SoundBuffer>>& list);
    };


    class ZipLoader : public BaseLoader
    {
    public:
        ZipLoader(const std::string& fileName);

        void loadTextures(
            std::map<Textures,
            std::shared_ptr<sf::Texture>>& list);

        void loadFonts(
                std::map<Fonts,
                std::shared_ptr<sf::Font>>& list);

        void loadSoundBuffers(
                std::map<Fonts,
                std::shared_ptr<sf::SoundBuffer>>& list);

    private:
        const std::string m_fileName;

        sf::Font* getFontFromZip(std::string name) const;
        sf::Texture* getTextureFromZip(std::string name) const;
        sf::SoundBuffer* getSoundBufferFromZip(std::string name) const;
    };

public:
    class Resources
    {
    public:
        Resources();

        Resources(std::string zipFile);

        sf::Font* getFont(Assets::Fonts id) const;
        sf::Texture* getTexture(Assets::Textures id) const;
        sf::SoundBuffer* getSoundBuffer(Assets::Sounds id) const;

    private:
        std::shared_ptr<BaseLoader> m_loader;

        std::map<Textures,
            std::shared_ptr<sf::Texture>> m_textures;

        std::map<Fonts,
            std::shared_ptr<sf::Font>> m_fonts;

        std::map<Sounds,
            std::shared_ptr<sf::SoundBuffer>> m_soundBuffers;
    };

};

#endif // ASSETS_H
