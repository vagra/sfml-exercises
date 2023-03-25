#pragma once
#pragma warning(disable: 26440)

#include "headers.h"

const string FONT_DIR = "../assets/fonts/";
const string FONT_EXT = ".ttf";

class FontManager
{

public:
    static FontManager& instance() {
        static FontManager instance;
        return instance;
    }

    /* public methods */

    void loadFonts();
    sf::Font* loadFont(string name, string path);

    int getCount();

    sf::Font* getFont(string name);
    sf::Font* getFont(int index);

    /* const member accessrs */

    const vector<string>& names = m_names;

private:

    /* private methods */

    void listFiles();

    void printMap();
    void printList();

    /* private members */

    unordered_map<string, unique_ptr<sf::Font>> m_fonts;
    unordered_map<string, string> m_files;
    vector<string> m_names;
};