#pragma once

#include "globals.h"

using namespace std;

class FontManager
{
public:
    FontManager();
    ~FontManager();

    static void init();
    static int getCount();

    static sf::Font* getFont(string name);
    static sf::Font* getFont(int index);
    static sf::Font* loadFont(string name, string path);

    static const vector<string>& getNames();

private:
    static void listFiles();
    static void loadFonts();

    static void printMap();
    static void printList();

    static inline unordered_map<string, sf::Font*> fonts;
    static inline unordered_map<string, string> files;
    static inline vector<string> names;
};

