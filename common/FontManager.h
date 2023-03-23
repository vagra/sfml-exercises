#pragma once

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

    void loadFonts();
    sf::Font* loadFont(string name, string path);

    int getCount() noexcept;

    sf::Font* getFont(string name);
    sf::Font* getFont(int index);

    const vector<string>& names = m_names;

private:
    void listFiles();

    void printMap();
    void printList();

    unordered_map<string, unique_ptr<sf::Font>> m_fonts;
    unordered_map<string, string> m_files;
    vector<string> m_names;
};