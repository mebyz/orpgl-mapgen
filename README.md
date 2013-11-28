orpgl-mapgen
============

c++ / libnoise tool to generate tiled terrain for orgpl (heightmaps and datafiles)
  --------------
 | prerequistes |
/--------------/

1/COMP/LINK:

- you need to have libnoise source folder present in the project's root directory
- Unix/Macosx : g++ main.cpp noiseutils.cpp -o main -I/usr/local/include -I./ -L/usr/local/lib -lnoise

2/EXECUTION :
chmod +x main
main [TILESIZE] [TILEROWS]

ie: ./main 512 10 
=> will produce a 10x10 tile of 512x512 px images (BMP)
