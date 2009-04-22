// configure, compile and install Gmsh as a library with
//
//   ./configure --disable-gui --disable-netgen --disable-chaco --prefix=/usr/local/
//   make install-lib
//
// Then compile this driver with "g++ celldriver.cpp -lGmsh -llapack -lblas -lgmp"
//
//
// This program creates .msh file chains.msh which represents the generators of 
// an two port transformer model's homology groups.


#include <stdio.h>
#include <sstream>
#include <gmsh/Gmsh.h>
#include <gmsh/GModel.h>
#include <gmsh/MElement.h>
#include <gmsh/CellComplex.h>
#include <gmsh/ChainComplex.h>

template <class TTypeA, class TTypeB>
bool convert(const TTypeA& input, TTypeB& output ){
  std::stringstream stream;
  stream << input;
  stream >> output;
  return stream.good();
}


int main(int argc, char **argv)
{
  GmshInitialize(argc, argv);
  GModel *m = new GModel();
  m->readGEO("transformer.geo");
  m->mesh(3);
  m->writeMSH("transformer.msh");
  
  printf("This model has: %d GRegions, %d GFaces, %d GEdges and %d GVertices. \n" , m->getNumRegions(), m->getNumFaces(), m->getNumEdges(), m->getNumVertices());
  
  std::vector<GEntity*> domain;
  std::vector<GEntity*> subdomain;
  
  // whole model
  for(GModel::riter rit = m->firstRegion(); rit != m->lastRegion(); rit++){
    GEntity *r = *rit;
    domain.push_back(r);
  }

  // the ports
  GModel::fiter sub = m->firstFace();
  GEntity *s = *sub;
  subdomain.push_back(s);
  s = *(++sub);
  subdomain.push_back(s);
  s =*(++sub);
  subdomain.push_back(s);
  s= *(++sub);
  subdomain.push_back(s);
  
  // create a cell complex
  CellComplex* complex = new CellComplex(domain, subdomain);

  printf("Cell complex of this model has: %d volumes, %d faces, %d edges and %d vertices\n",
         complex->getSize(3), complex->getSize(2), complex->getSize(1), complex->getSize(0));  
  
  // reduce the complex in order to ease homology computation
  complex->reduceComplex();
  
  // create a chain complex of a cell complex (construct boundary operator matrices)
  ChainComplex* chains = new ChainComplex(complex);
  // compute the homology using the boundary operator matrices
  chains->computeHomology();
  
  // write the reduced cell complex to a .msh file
  complex->writeComplexMSH("chains.msh");
  
  // Append the homology generators to the .msh file as post-processing views. 
  // To visualize the result, open chains.msh with Gmsh GUI and deselect all mesh
  // entities from Tools->Options->Mesh->Visibility.
  for(int j = 0; j < 4; j++){
    for(int i = 1; i <= chains->getBasisSize(j); i++){
    
      std::string generator;
      std::string dimension;
      convert(i, generator);
      convert(j, dimension);
      std::string name = dimension + "D Generator " + generator;
      
      Chain* chain = new Chain(complex->getCells(j), chains->getCoeffVector(j,i), complex, name);
      chain->writeChainMSH("chains.msh");
      delete chain;
      
    }
  }
  
    
  delete chains;
  delete complex;  
  delete m;
  GmshFinalize();
  
}




