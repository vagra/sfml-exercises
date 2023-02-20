#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

using namespace std;


const int INIT_WIDTH = 1600;
const int INIT_HEIGHT = 800;

const int ACTORS = 6;

const int MAX = 5000;

const int FRAME_WIDTH = 100;
const int FRAME_HEIGHT = 80;
const int ORIGIN_X = 50;
const int ORIGIN_Y = 56;
const float SCALE = 0.5f;

const int AGENT_WIDTH = 16;
const int AGENT_HEIGHT = 16;
const int AGENT_HALFW = 8;
const int AGENT_HALFH = 8;

const int GRID_WIDTH = 2000;
const int GRID_HEIGHT = 1200;

const int LCELL_WIDTH = 50;
const int LCELL_HEIGHT = 50;
const int TCELL_WIDTH = 100;
const int TCELL_HEIGHT = 100;

const string PNG_DIR = "../assets/soldiers/";
const string PNG_EXT = ".png";

const string ACTOR_PNG = "soldier-{}.png";

