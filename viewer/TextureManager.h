#pragma once

#include "globals.h"

using namespace std;

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    static void init();
    static int getCount();

    static sf::Texture* getTexture(string name);
    static sf::Texture* getTexture(int index);
    static sf::Texture* loadTexture(string name, string path);

    static const vector<string>& getNames();

private:
    static void listFiles();
    static void loadTextures();

    static inline unordered_map<string, sf::Texture*> textures;
    static inline unordered_map<string, string> files;
    static inline vector<string> names;
};

