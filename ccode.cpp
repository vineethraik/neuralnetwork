/*c code*/

#include"neuralnetwork.h"
#include<windows.h>



int main()
{
  srand(time(0));
  dataset x,y;
  readfile(x,"input.txt");
  network a;
  vector<int> structure;
  structure.push_back(x.ilen);
  structure.push_back(2);
  structure.push_back(x.olen);
  a.init(x,structure);
  a.readout();
  return 0;
}

