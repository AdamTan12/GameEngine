#ifndef ASSETS_H
#define ASSETS_H

#include <vector>
#include "Mesh.h"
using namespace std;

struct Assets {
    vector<Mesh*> meshes;    
    void initMeshes();
};

#endif