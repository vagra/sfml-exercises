#include "FontManager.h"

// ---------------------------------------------
// public methods
// ---------------------------------------------

void FontManager::loadFonts() {

    listFiles();

    cout << "load font files to font manager...";

    m_fonts.clear();

    for (auto const& [name, path] : m_files) {
        loadFont(name, path);
    }

    fmt::print("\t\t{} fonts ready.\n", getCount());

    printList();
}

sf::Font* FontManager::loadFont(string name, string path)
{
    if (m_fonts.find(name) != m_fonts.end()) {
        return m_fonts[name].get();
    }

    auto font = make_unique<sf::Font>();

    if (!font->loadFromFile(path))
    {
        font.reset();

        throw runtime_error(
            fmt::format("font file {} not exist.", path)
        );
    }

    m_fonts[name] = move(font);

    m_names.push_back(name);

    return m_fonts[name].get();
}

int FontManager::getCount() {
    return narrow_cast<int>(m_fonts.size());
}

sf::Font* FontManager::getFont(string name)
{
    if (m_fonts.find(name) != m_fonts.end()) {
        return m_fonts[name].get();
    }

    throw runtime_error(
        fmt::format("font with name of {} not exist.", name)
    );
}

sf::Font* FontManager::getFont(int index)
{
    assert(index < m_names.size());
    return getFont(m_names.at(index));
}


// ---------------------------------------------
// private methods
// ---------------------------------------------

void FontManager::listFiles() {
    fmt::print("check font files in dir {}:\n", FONT_DIR);

    m_files.clear();

    for (auto& font : filesystem::directory_iterator(FONT_DIR)) {
        if (font.path().extension() == FONT_EXT) {
            string path = font.path().string();
            string name = font.path().stem().string();
            name = name.substr(0, name.find('-'));

            m_files[name] = path;
        }
    }

    cout << "done." << endl;
}

void FontManager::printMap() {
    for (auto const& [file_name, file_path] : m_files) {
        fmt::print("{}: {}\n", file_name, file_path);
    }

    for (auto const& [file_name, font] : m_fonts) {
        fmt::print("{}: {}\n", 
            file_name, font->getInfo().family);
    }
}

void FontManager::printList() {
    string file_path = "";
    sf::Font* font = nullptr;

    for (auto const& file_name : m_names) {
        file_path = m_files[file_name];
        font = m_fonts[file_name].get();
        Ensures(font);
        fmt::print("{}: {}\n\t{}\n",
            file_name, font->getInfo().family, file_path);
    }
}