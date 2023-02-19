#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

#include "rapidcsv.h"

using namespace std;

const int INIT_WIDTH = 1600;
const int INIT_HEIGHT = 800;

const int ACTORS = 8;
const int ACTIONS = 12;
const int STEPS = 6;

const int FRAME_WIDTH = 80;
const int FRAME_HEIGHT = 80;
const int ORIGIN_X = 39;
const int ORIGIN_Y = 59;

const float SCALE = 2.0f;

const string PNG_DIR = "../assets/heros/";
const string PNG_EXT = ".png";

const string ACTOR_PNG = "helo{}.png";

const string ACTIONS_CSV = PNG_DIR + "/actions.csv";


