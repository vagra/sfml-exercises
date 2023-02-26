#include "TextureManager.h"

void TextureManager::init() {

    cout << "init texture manager:" << endl;

    listFiles();

    loadTextures();

    cout << "init texture manager done." << endl << endl;
}

int TextureManager::getCount() noexcept{
    return narrow_cast<int>(textures.size());
}

vector<string>& TextureManager::getNames() noexcept{
    return names;
}

sf::Texture* TextureManager::getTexture(string name)
{
    if (textures.find(name) != textures.end()) {
        return textures[name].get();
    }
    else {
        return nullptr;
    }
}

sf::Texture* TextureManager::getTexture(int index)
{
    return getTexture(names.at(index));
}

sf::Texture* TextureManager::loadTexture(string name, string path)
{
    auto texture = make_unique<sf::Texture>();

    if (!texture->loadFromFile(path))
    {
        cout << fmt::format("error when load texture file: ", name) << endl;

        texture.reset();
        return nullptr;
    }

    textures[name] = move(texture);

    names.push_back(name);

    return textures[name].get();
}

void TextureManager::listFiles() {
    cout << fmt::format("check png files in dir {}: ", PNG_DIR) << endl;

    files.clear();

    for (auto& png : filesystem::directory_iterator(PNG_DIR)) {
        if (png.path().extension() == PNG_EXT) {
            string path = png.path().string();
            string name = png.path().stem().string();

            files[name] = path;
        }
    }

    cout << "done." << endl;
}

void TextureManager::loadTextures() {
    cout << "load png files to texture manager...";

    textures.clear();

    for (auto const& [name, path] : files) {
        loadTexture(name, path);
    }

    cout << fmt::format("\t\t{} textures ready.", getCount()) << endl;

    printList();
}


void TextureManager::printMap() {
    for (auto const& [file_name, file_path] : files) {
        cout << fmt::format("{}: {}", file_name, file_path) << endl;
    }

    for (auto const& [file_name, texture] : textures) {
        cout << fmt::format("{}: {},{}", 
            file_name, texture->getSize().x, texture->getSize().y) << endl;
    }
}

void TextureManager::printList() {

    string file_path = "";
    sf::Texture* texture = nullptr;

    for (auto const& file_name : names) {
        file_path = files[file_name];
        texture = textures[file_name].get();
        assert(texture);
        cout << fmt::format("{}: {},{}\t{}",
            file_name, texture->getSize().x, texture->getSize().y, file_path) << endl;
    }
}