#pragma once

#include "globals.h"

class TextureManager
{
public:
    static void init();

    static int getCount() noexcept;
    static vector<string>& getNames() noexcept;

    static sf::Texture* getTexture(string name);
    static sf::Texture* getTexture(int index);

    static sf::Texture* loadTexture(string name, string path);

private:
    static void listFiles();
    static void loadTextures();

    static void printMap();
    static void printList();

    static inline unordered_map<string, unique_ptr<sf::Texture>> textures;
    static inline unordered_map<string, string> files;
    static inline vector<string> names;
};

