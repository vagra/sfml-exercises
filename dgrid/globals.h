#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

using namespace std;


const int INIT_WIDTH = 1600;
const int INIT_HEIGHT = 800;

const int ACTORS = 4;

const int MAX = 5000;

const int PNG_WIDTH = 64;
const int PNG_HEIGHT = 64;
const int SPRITE_WIDTH = 16;
const int SPRITE_HEIGHT = 16;
const int SPRITE_RADIUS = 4;
const int SPRITE_HALFW = 6;
const int SPRITE_HALFH = 6;

const int GRID_WIDTH = 2000;
const int GRID_HEIGHT = 1200;
const int CELL_WIDTH = 40;
const int CELL_HEIGHT = 40;

const int LCELL_WIDTH = 40;
const int LCELL_HEIGHT = 40;
const int TCELL_WIDTH = 100;
const int TCELL_HEIGHT = 100;


const string PNG_DIR = "../assets/tanks/";
const string PNG_EXT = ".png";

const string ACTOR_PNG = "tank-{}.png";

