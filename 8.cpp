#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int count_layer(vector<char> v, char c) {
  return count_if(v.begin(), v.end(), [c](char i) { return i == c; });
}

int main(int argc, char *argv[]) {
  const int PIXEL_W = 25;
  const int PIXEL_H = 6;
  const int IMAGE_SIZE = PIXEL_H * PIXEL_W;
  const int NUM_LAYERS = 100;
  assert(argc == 2);
  ifstream in(argv[1]);
  vector<char> pixels;
  vector<vector<char>> layers(NUM_LAYERS);
  vector<vector<int>> counts(3);

  int current_layer = 0;
  int current_pixel = 0;
  while (in) {
    layers[current_layer].push_back(in.get());
    current_pixel = (current_pixel + 1) % IMAGE_SIZE;
    if (current_pixel == 0) {
      current_layer++;
      if (current_layer == NUM_LAYERS) {
        break;
      }
    }
  }

  for (auto &layer : layers) {
    for (char c : {'0', '1', '2'}) {
      counts[c - '0'].push_back(count_layer(layer, c));
    }
  }

  int imin0 = distance(counts[0].begin(),
                       min_element(counts[0].begin(), counts[0].end()));
  cout << "Part 1: " << counts[1][imin0] * counts[2][imin0] << endl;

  vector<int> colors(IMAGE_SIZE, -1);

  // number of layers is NUM_LAYERS
  for (int i = 0; i < NUM_LAYERS; i++) {
    // number of pixels per layer is IMAGE_SIZE
    for (int j = 0; j < IMAGE_SIZE; j++) {
      if ((layers[i][j] != '2') && (colors[j] == -1)) {
        // '0' is black, '1' is white
        colors[j] = (layers[i][j] == '1') ? 1 : 0;
      }
    }
  }

  for (int i = 0; i < IMAGE_SIZE; i++) {
    if (colors[i]) {
      cout << '#';
    } else {
      cout << ' ';
    }
    if ((i + 1) % PIXEL_W == 0) {
      cout << endl;
    }
  }

  return 0;
}
