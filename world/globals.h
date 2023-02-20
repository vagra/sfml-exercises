#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

using namespace std;


const int INIT_WIDTH = 1600;
const int INIT_HEIGHT = 800;

const int ACTORS = 17;

const int MAX = 5000;

const int FRAME_WIDTH = 100;
const int FRAME_HEIGHT = 100;

const string PNG_DIR = "../assets/characters/";
const string PNG_EXT = ".png";

const string ACTOR_PNG = "actor-{}-0.png";
const string SHADOW_PNG = "shadow.png";

