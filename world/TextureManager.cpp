#include "TextureManager.h"

TextureManager::TextureManager()
{
}

void TextureManager::init() {

    cout << "init texture manager:" << endl;

    listFiles();

    loadTextures();

    addShadows();

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

void TextureManager::addShadows() {

    cout << "add shadows to character sprite sheets...";

    for (auto const& [name, pointer] : textures) {
        if (SHADOW_PNG == name) {
            continue;
        }
        addShadow(*pointer);
    }

    cout << "\t done." << endl;
}

void TextureManager::addShadow(sf::Texture& sheetTexture) {

    sf::Texture pShadowTexture = *textures[SHADOW_PNG];
    sf::RenderTexture renderTexture;

    if (!renderTexture.create(PNG_WIDTH, PNG_HEIGHT))
    {
        cout << endl << "error when create render texture!" << endl;
        return;
    }

    vector<sf::Sprite> shadows;

    for (int i = 0; i < PNG_COLS; i++) {
        for (int j = 0; j < PNG_ROWS; j++) {
            sf::Sprite shadow;
            shadow.setTexture(pShadowTexture);

            float x = float(i * FRAME_WIDTH) + SHADOW_OFFX;
            float y = float(j * FRAME_HEIGHT) + SHADOW_OFFY;
            shadow.setPosition(x, y);

            shadows.push_back(shadow);
        }
    }

    sf::Sprite sheet;
    sheet.setTexture(sheetTexture);
    sheet.setPosition(0, 0);

    renderTexture.clear(sf::Color::Transparent);

    for (auto& shadow : shadows) {
        renderTexture.draw(shadow);
    }

    renderTexture.draw(sheet);

    renderTexture.display();

    sheetTexture = renderTexture.getTexture();
}


TextureManager::~TextureManager()
{
    for (auto const& [name, pointer] : textures) {
        delete pointer;
    }
}