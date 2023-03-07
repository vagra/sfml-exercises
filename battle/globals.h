#pragma once
#pragma warning(disable: 26481)

#include <fstream>
#include <iostream>
#include <filesystem>
#include <set>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <array>
#include <gsl/gsl>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

#include <rapidcsv.h>
#include <machine.hpp>

using namespace std;
using namespace gsl;

constexpr int INIT_WIDTH = 800;
constexpr int INIT_HEIGHT = 800;

constexpr int ACTOR_TYPES = 8;
constexpr int ACTIONS = 12;

constexpr int MAX = 1000;

constexpr int FRAME_WIDTH = 80;
constexpr int FRAME_HEIGHT = 80;
constexpr int ORIGIN_X = 39;
constexpr int ORIGIN_Y = 59;

constexpr float SCALE = 1.0f;

constexpr int AGENT_WIDTH = 20;
constexpr int AGENT_HEIGHT = 20;
constexpr int AGENT_HALFW = 10;
constexpr int AGENT_HALFH = 10;

constexpr int GRID_WIDTH = 2000;
constexpr int GRID_HEIGHT = 1200;

constexpr int LCELL_WIDTH = 50;
constexpr int LCELL_HEIGHT = 50;
constexpr int TCELL_WIDTH = 100;
constexpr int TCELL_HEIGHT = 100;

const string FONT_DIR = "../assets/fonts/";
const string FONT_EXT = ".ttf";

const string PNG_DIR = "../assets/heros/";
const string PNG_EXT = ".png";

const string ACTOR_PNG = "helo{}.png";

const string ACTIONS_CSV = PNG_DIR + "/actions.csv";


