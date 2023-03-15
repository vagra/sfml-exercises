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
    
    throw runtime_error(
        fmt::format("texture with name of {} not exist.", name)
    );
}

sf::Texture* TextureManager::getTexture(int index)
{
    assert(index < names.size());
    return getTexture(names.at(index));
}

sf::Texture* TextureManager::loadTexture(string name, string path)
{
    if (textures.find(name) != textures.end()) {
        return textures[name].get();
    }

    auto texture = make_unique<sf::Texture>();

    if (!texture->loadFromFile(path))
    {
        texture.reset();
        
        throw runtime_error(
            fmt::format("texture file {} not exist.", path)
        );
    }

    textures[name] = move(texture);

    names.push_back(name);

    return textures[name].get();
}

void TextureManager::listFiles() {
    fmt::print("check png files in dir {}:\n", PNG_DIR);

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

    fmt::print("\t\t{} textures ready.\n", getCount());

    printList();
}


void TextureManager::printMap() {
    for (auto const& [file_name, file_path] : files) {
        fmt::print("{}: {}\n", file_name, file_path);
    }

    for (auto const& [file_name, texture] : textures) {
        fmt::print("{}: {},{}\n", 
            file_name, texture->getSize().x, texture->getSize().y);
    }
}

void TextureManager::printList() {

    string file_path = "";
    sf::Texture* texture = nullptr;

    for (auto const& file_name : names) {
        file_path = files[file_name];
        texture = textures[file_name].get();
        assert(texture);
        fmt::print("{}: {},{}\t{}\n",
            file_name, texture->getSize().x, texture->getSize().y, file_path);
    }
}