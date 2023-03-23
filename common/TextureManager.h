#pragma once

#include "headers.h"

const string PNG_EXT = ".png";

class TextureManager
{
public:
    static TextureManager& instance() {
        static TextureManager instance;
        return instance;
    }

    void loadTextures(string png_dir);
    sf::Texture* loadTexture(string name, string path);

    int getCount() noexcept;

    sf::Texture* getTexture(string name);
    sf::Texture* getTexture(int index);

    const vector<string>& names = m_names;

private:
    void listFiles(string png_dir);

    void printMap();
    void printList();

    unordered_map<string, unique_ptr<sf::Texture>> m_textures;
    unordered_map<string, string> m_files;
    vector<string> m_names;
};