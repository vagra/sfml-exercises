#include "FontManager.h"

FontManager::FontManager()
{
}

void FontManager::init() {

    cout << "init font manager:" << endl;

    listFiles();

    loadFonts();

    cout << "init font manager done." << endl << endl;
}

int FontManager::getCount() {
    return (int)fonts.size();
}

const vector<string>& FontManager::getNames() {
    return names;
}

sf::Font* FontManager::getFont(string name)
{
    if (fonts.find(name) != fonts.end()) {
        return fonts[name];
    }
    else {
        return nullptr;
    }
}

sf::Font* FontManager::getFont(int index)
{
    return getFont(names.at(index));
}

sf::Font* FontManager::loadFont(string name, string path)
{
    sf::Font* pFont = new sf::Font();

    if (!pFont->loadFromFile(path))
    {
        cout << fmt::format("error when load font file: ", name) << endl;

        delete pFont;
        return nullptr;
    }

    fonts[name] = pFont;

    names.push_back(name);
    return fonts[name];
}

void FontManager::listFiles() {
    cout << fmt::format("check font files in dir {}: ", FONT_DIR) << endl;

    files.clear();

    for (auto& font : filesystem::directory_iterator(FONT_DIR)) {
        if (font.path().extension() == FONT_EXT) {
            string path = font.path().string();
            string name = font.path().stem().string();
            name = name.substr(0, name.find('-'));

            files[name] = path;
        }
    }

    cout << "done." << endl;
}

void FontManager::loadFonts() {
    cout << "load font files to font manager...";

    fonts.clear();

    for (auto const& [name, path] : files) {
        loadFont(name, path);
    }

    cout << fmt::format("\t\t{} fonts ready.", getCount()) << endl;

    printList();
}


void FontManager::printMap() {
    for (auto const& [file_name, file_path] : files) {
        cout << fmt::format("{}: {}", file_name, file_path) << endl;
    }

    for (auto const& [file_name, font] : fonts) {
        cout << fmt::format("{}: {}", 
            file_name, font->getInfo().family) << endl;
    }
}

void FontManager::printList() {
    for (auto const& file_name : names) {
        string file_path = files[file_name];
        sf::Font* font = fonts[file_name];
        cout << fmt::format("{}: {}\t\t{}",
            file_name, font->getInfo().family, file_path) << endl;
    }
}

FontManager::~FontManager()
{
    for (auto const& [name, pointer] : fonts) {
        delete pointer;
    }
}