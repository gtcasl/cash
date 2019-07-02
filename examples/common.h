#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>

#define CHECK(x) do { if (!(x)) { std::cout << "FAILED: " << #x << std::endl; std::abort(); } } while (false)

inline bool readPGM(const char* filename,
                    uint32_t* width,
                    uint32_t* height,
                    std::vector<uint8_t>* image) {
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Error: invalid input file name." << std::endl;
    return false;
  }

  std::string line;

  // parse magic number
  std::getline(infile, line);
  if (line != "P5") {
    std::cerr << "Error: invalid file format." << std::endl;
    return false;
  }

  // parse comments
  do {
    std::getline(infile, line);
  } while (line[0] == '#');

  // parse image dimensions
  if (sscanf(line.c_str(), "%u %u", width, height) != 2) {
    std::cerr << "Error: invalid file format." << std::endl;
    return false;
  }

  std::getline(infile, line);
  if (line != "255") {
    std::cerr << "Error: invalid file format." << std::endl;
    return false;
  }

  // parse image data
  uint32_t image_size = *width * *height;
  image->resize(image_size);
  infile.read((char*)image->data(), image_size);

  return true;
}

inline bool writePGM(const std::vector<uint8_t>& image,
                     uint32_t width,
                     uint32_t height,
                     const char* filename) {
  std::ofstream outfile(filename);
  if (!outfile) {
    std::cerr << "Error: invalid output file name." << std::endl;
    return false;
  }

  outfile << "P5" << std::endl;
  outfile << "# Sobel filter output image" << std::endl;
  outfile << width << " " << height << std::endl;
  outfile << "255" << std::endl;
  outfile.write((const char*)image.data(), width * height);

  return true;
}
