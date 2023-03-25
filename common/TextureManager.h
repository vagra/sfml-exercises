#pragma once
#pragma warning(disable: 26440)

#include "headers.h"

const string PNG_EXT = ".png";

class TextureManager
{
public:
    static TextureManager& instance() {
        static TextureManager instance;
        return instance;
    }

    /* public methods */

    void loadTextures(string png_dir);
    sf::Texture* loadTexture(string name, string path);

    int getCount();

    sf::Texture* getTexture(string name);
    sf::Texture* getTexture(int index);

    /* const member accessers */

    const vector<string>& names = m_names;

private:

    /* private methods */

    void listFiles(string png_dir);

    void printMap();
    void printList();

    /* private members */

    unordered_map<string, unique_ptr<sf::Texture>> m_textures;
    unordered_map<string, string> m_files;
    vector<string> m_names;
};