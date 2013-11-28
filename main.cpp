#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include <sstream>
#include <noise/noise.h>
#include "noiseutils.h"

using namespace noise;

int main (int argc, char** argv)
{
  int tilesidelenght = atoi(argv[1]);
  int tilexnumber = atoi(argv[2]);
  module::Perlin myModule;
  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;
  heightMapBuilder.SetSourceModule (myModule);
  heightMapBuilder.SetDestNoiseMap (heightMap);
  heightMapBuilder.SetDestSize (tilesidelenght,tilesidelenght);
  for (int i = 0; i < tilexnumber; ++i) {
  for (int j = 0; j < tilexnumber; ++j) {
  heightMapBuilder.SetBounds (i, i+1.0, j, j+1.0);
  heightMapBuilder.Build ();

  utils::RendererImage renderer;
  utils::Image image;
  renderer.SetSourceNoiseMap (heightMap);
  renderer.SetDestImage (image);
  std::string result = renderer.Render ();

 utils::WriterBMP writer;
  writer.SetSourceImage (image);
  std::stringstream si;
  si << i;
  std::stringstream sj;
  sj << j;
  std::string ss = std::string("tile_")+ si.str() +std::string("_") + sj.str() + std::string(".bmp");
  std::string js = std::string("tile_")+ si.str() +std::string("_") + sj.str() + std::string(".js");
  ofstream myfile;
char tab2[1024];
strcpy(tab2, js.c_str());
  myfile.open(tab2);
  myfile << result;
  myfile.close();

  writer.SetDestFilename(ss);
  writer.WriteDestFile ();
  }
  }
  return 0;
}
