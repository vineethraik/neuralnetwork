/*c code*/

#include"neuralnetwork.h"



int main()
{
  srand(time(0));                 //importent to get good random weight
  dataset x,y;                    //input storage class
  vector<vector<double> > temp;   //var to store output

  readfile(x,"input.txt");        //gathering training data from input.txt file
  x.read();                       
  network a;
  vector<int> structure;          //variable which is used to define the structure of nn 
  structure.push_back(x.ilen);    //input neurons
  structure.push_back(5);         //2nd layer neurons
  structure.push_back(x.olen);    //output neurons
  a.init(x,structure);            //initializing neuron using dataset and structure
  a.readout();
  temp=a.feedforword();           
  x.compare(temp);
  a.backprop(5000);
  cout<<"\n";
  temp=a.feedforword();           
  x.compare(temp);
  cout<<"\n";
  //a.readout();
    
  
  return 0;
}

