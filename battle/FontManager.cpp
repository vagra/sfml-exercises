#include "FontManager.h"

void FontManager::init() {

    cout << "init font manager:" << endl;

    listFiles();

    loadFonts();

    cout << "init font manager done." << endl << endl;
}

int FontManager::getCount() noexcept {
    return narrow_cast<int>(fonts.size());
}

vector<string>& FontManager::getNames() noexcept {
    return names;
}

sf::Font* FontManager::getFont(string name)
{
    if (fonts.find(name) != fonts.end()) {
        return fonts[name].get();
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
    auto font = make_unique<sf::Font>();

    if (!font->loadFromFile(path))
    {
        cout << fmt::format("error when load font file: ", name) << endl;

        font.reset();
        return nullptr;
    }

    fonts[name] = move(font);

    names.push_back(name);

    return fonts[name].get();
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
    string file_path = "";
    sf::Font* font = nullptr;

    for (auto const& file_name : names) {
        file_path = files[file_name];
        font = fonts[file_name].get();
        assert(font);
        cout << fmt::format("{}: {}\t\t{}",
            file_name, font->getInfo().family, file_path) << endl;
    }
}
