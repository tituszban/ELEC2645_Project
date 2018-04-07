#include "Block.h"

Block::Block(Matrix pos){
  double block_corners[][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
  };
  this->position = pos;
  for(int i = 0; i < CORNER_N; i++){
    this->_corners[i] = Matrix(1, 3, block_corners[i]) + pos;
  }
}

vector< vector<Matrix> > Block::getEdges(){
  vector< vector<Matrix> > outp;
  double block_pairs[][2] = {
    {0, 1},
    {0, 2},
    {0, 4},
    {3, 1},
    {3, 2},
    {3, 7},
    {5, 1},
    {5, 4},
    {5, 7},
    {6, 2},
    {6, 4},
    {6, 7}
  };

  for(int i = 0; i < EDGE_N; i++){
    vector<Matrix> edge;
    int p1 = block_pairs[i][0];
    int p2 = block_pairs[i][1];
    edge.push_back(this->_corners[p1]);
    edge.push_back(this->_corners[p2]);
    this->_corners[p1].print_matrix();
    this->_corners[p2].print_matrix();
    outp.push_back(edge);
  }
  return outp;
}
