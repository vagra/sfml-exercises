#include "TextureManager.h"

// ---------------------------------------------
// public methods
// ---------------------------------------------

void TextureManager::loadTextures(string png_dir) {
    listFiles(png_dir);

    cout << "load png files to texture manager...";

    m_textures.clear();

    for (auto const& [name, path] : m_files) {
        loadTexture(name, path);
    }

    fmt::print("\t\t{} textures ready.\n", getCount());

    printList();
}

sf::Texture* TextureManager::loadTexture(string name, string path)
{
    if (m_textures.find(name) != m_textures.end()) {
        return m_textures[name].get();
    }

    auto texture = make_unique<sf::Texture>();

    if (!texture->loadFromFile(path))
    {
        texture.reset();

        throw runtime_error(
            fmt::format("texture file {} not exist.", path)
        );
    }

    m_textures[name] = move(texture);
    m_names.push_back(name);

    return m_textures[name].get();
}

int TextureManager::getCount() {
    return narrow_cast<int>(m_textures.size());
}

sf::Texture* TextureManager::getTexture(string name)
{
    if (m_textures.find(name) != m_textures.end()) {
        return m_textures[name].get();
    }
    
    throw runtime_error(
        fmt::format("texture with name of {} not exist.", name)
    );
}

sf::Texture* TextureManager::getTexture(int index)
{
    assert(index < m_names.size());
    return getTexture(m_names.at(index));
}

// ---------------------------------------------
// private methods
// ---------------------------------------------

void TextureManager::listFiles(string png_dir) {
    fmt::print("check png files in dir {}:\n", png_dir);

    m_files.clear();

    for (auto& png : filesystem::directory_iterator(png_dir)) {
        if (png.path().extension() == PNG_EXT) {
            string path = png.path().string();
            string name = png.path().stem().string();

            m_files[name] = path;
        }
    }

    cout << "done." << endl;
}


void TextureManager::printMap() {
    for (auto const& [file_name, file_path] : m_files) {
        fmt::print("{}: {}\n", file_name, file_path);
    }

    for (auto const& [file_name, texture] : m_textures) {
        fmt::print("{}: {},{}\n", 
            file_name, texture->getSize().x, texture->getSize().y);
    }
}

void TextureManager::printList() {
    string file_path = "";
    sf::Texture* texture = nullptr;

    for (auto const& file_name : m_names) {
        file_path = m_files[file_name];
        texture = m_textures[file_name].get();
        Ensures(texture);
        fmt::print("{}: {},{}\t{}\n",
            file_name, texture->getSize().x, texture->getSize().y, file_path);
    }
}