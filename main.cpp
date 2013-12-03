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

  module::RidgedMulti mountainTerrain;
  module::Billow baseFlatTerrain;
  module::ScaleBias flatTerrain;

  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;
  
  baseFlatTerrain.SetFrequency (2.0);
  flatTerrain.SetSourceModule (0, baseFlatTerrain);

  int tilesidelenght = atoi(argv[1]);
  int tilexnumber = atoi(argv[2]);

  flatTerrain.SetScale (0.125);
  flatTerrain.SetBias (-0.75);

  module::Perlin terrainType;
  terrainType.SetFrequency (10.0);
  terrainType.SetPersistence (0);


  module::Select finalTerrain;

  finalTerrain.SetSourceModule (0, flatTerrain);
  finalTerrain.SetSourceModule (1, mountainTerrain);
  finalTerrain.SetControlModule (terrainType);

  finalTerrain.SetEdgeFalloff (1.25);

  heightMapBuilder.SetSourceModule (finalTerrain);

  heightMapBuilder.SetDestNoiseMap (heightMap);
  heightMapBuilder.SetDestSize (tilesidelenght,tilesidelenght);
  for (int i = 0; i < tilexnumber; ++i) {
    for (int j = 0; j < tilexnumber; ++j) {
      float rx=i-0.00;
      float rl=i+1.00;
      float ry=j-0.00;
      float rh=j+1.00;

      heightMapBuilder.SetBounds (rx,rl,ry,rh);
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
      std::string ss = std::string("images/tile_")+ si.str() +std::string("_") + sj.str() + std::string(".bmp");
      ofstream myfile;
      writer.SetDestFilename(ss);
      writer.WriteDestFile ();
    }
  }
  return 0;
}
