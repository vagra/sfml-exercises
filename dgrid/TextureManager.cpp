#include "TextureManager.h"

TextureManager::TextureManager()
{
}

void TextureManager::init() {

    cout << "init texture manager:" << endl;

    listFiles();

    loadTextures();

    cout << "init texture manager done." << endl << endl;
}

int TextureManager::getCount() {
    return int(textures.size());
}

sf::Texture* TextureManager::getTexture(string name)
{
    if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    else {
        return nullptr;
    }
}

sf::Texture* TextureManager::getTexture(int index)
{
    return getTexture(order.at(index));
}

sf::Texture* TextureManager::loadTexture(string name, string path)
{
    sf::Texture* pTexture = new sf::Texture();

    if (!pTexture->loadFromFile(path))
    {
        cout << fmt::format("error when load texture file: ", name) << endl;

        delete pTexture;
        return nullptr;
    }

    textures[name] = pTexture;

    order.push_back(name);
    return textures[name];
}

void TextureManager::listFiles() {
    cout << fmt::format("check png files in dir {}: ", PNG_DIR) << endl;

    files.clear();

    for (auto& png : filesystem::directory_iterator(PNG_DIR)) {
        if (png.path().extension() == PNG_EXT) {
            string path = png.path().string();
            string name = png.path().filename().string();

            cout << name << endl;

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

    cout << "\t\t done." << endl;
}


TextureManager::~TextureManager()
{
    for (auto const& [name, pointer] : textures) {
        delete pointer;
    }
}