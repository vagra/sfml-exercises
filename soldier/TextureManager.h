#pragma once

#include "globals.h"

using namespace std;

const int PNG_WIDTH = 2400;
const int PNG_HEIGHT = 1280;

const int PNG_COLS = 24;
const int PNG_ROWS = 16;


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

private:
    static void listFiles();
    static void loadTextures();

    static inline unordered_map<string, sf::Texture*> textures;
    static inline unordered_map<string, string> files;
    static inline vector<string> order;
};

