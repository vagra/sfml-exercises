#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <cmath>
#include <array>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

#include "rapidcsv.h"

using namespace std;

const int INIT_WIDTH = 800;
const int INIT_HEIGHT = 800;

const int ACTOR_TYPES = 8;
const int ACTIONS = 11;

const int MAX = 1000;

const int FRAME_WIDTH = 80;
const int FRAME_HEIGHT = 80;
const int ORIGIN_X = 39;
const int ORIGIN_Y = 59;

const float SCALE = 1.0f;

const int AGENT_WIDTH = 20;
const int AGENT_HEIGHT = 20;
const int AGENT_HALFW = 10;
const int AGENT_HALFH = 10;

const int GRID_WIDTH = 2000;
const int GRID_HEIGHT = 1200;

const int LCELL_WIDTH = 50;
const int LCELL_HEIGHT = 50;
const int TCELL_WIDTH = 100;
const int TCELL_HEIGHT = 100;

const string PNG_DIR = "../assets/heros/";
const string PNG_EXT = ".png";

const string ACTOR_PNG = "helo{}.png";

const string ACTIONS_CSV = PNG_DIR + "/actions.csv";


