#pragma once

#include "globals.h"

using namespace std;

const int PNG_WIDTH = 1200;
const int PNG_HEIGHT = 800;

const int PNG_COLS = 12;
const int PNG_ROWS = 8;


const int SHADOW_OFFX = 30;
const int SHADOW_OFFY = 80;

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
    static void addShadows();

    static void addShadow(sf::Texture& sheetTexture);

    static inline unordered_map<string, sf::Texture*> textures;
    static inline unordered_map<string, string> files;
    static inline std::vector<string> order;
};

