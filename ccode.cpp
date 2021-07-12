/*c code*/

#include"neuralnetwork.h"



int main()
{
  srand(time(0));                 //importent to get good random weight
  dataset x,y;                    //input storage class
  vector<vector<double> > temp;   //var to store output

  readfile(x,"t.txt");        //gathering training data from input.txt file
  //x.read();                       
  
    
  
  return 0;
}

