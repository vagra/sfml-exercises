#pragma once

#include "globals.h"

class FontManager
{
public:
    static void init();

    static int getCount() noexcept;
    static vector<string>& getNames() noexcept;

    static sf::Font* getFont(string name);
    static sf::Font* getFont(int index);

    static sf::Font* loadFont(string name, string path);

private:
    static void listFiles();
    static void loadFonts();

    static void printMap();
    static void printList();

    static inline unordered_map<string, unique_ptr<sf::Font>> fonts;
    static inline unordered_map<string, string> files;
    static inline vector<string> names;
};

