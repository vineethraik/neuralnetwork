#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
using namespace std;

/*******************************constants**************************************/
#define lrate_wt .3
#define lratew_input .1
#define xtt false

/*******************************declaration**************************************/

class dataset;
class neuron;
class layer;
class network;

double sigmoid(double);
void readdatafile(dataset&,string);

/*******************************class dataset**************************************/
class dataset{
  private:

  public:
  int setlen;
  int len;
  int ilen;
  int olen;
  vector<vector<double> > set;
  dataset();
  void read();
  void compare(vector<vector<double> > input);
    
};

dataset::dataset(){
  setlen=0;
  len=0;
  ilen=0;
  olen=0;
}

void dataset::read(){
  int i,j;
    for ( i = 0; i <setlen; i++)
  {
    for ( j = 0; j <ilen; j++)
      cout<<set[i][j]<<"\t";
    cout<<":-  ";
    for ( j = ilen; j <len; j++)
      cout<<set[i][j]<<"\t";
    cout<<"\n";
  }
}

void dataset::compare(vector<vector<double> > input){
  for(int i=0;i<setlen;i++){
    for(int j=0;j<olen;j++)
      cout<<set[i][ilen+j]<<"\t";
    cout<<"|vs|\t";
    for(int j=0;j<olen;j++)
      cout<<input[i][j]<<"\t";
  cout<<"\n";
  }
}

/*******************************class neuron**************************************/
class neuron{
  private:
  layer ly;
  network net;
  public:
  neuron(int,layer,network);

  friend class layer;
  friend class network;
};
//initialization
neuron::neuron(int len,layer x,network y){
ly=x,net=y;
}

/*******************************class normalization layer**************************************/
class layer1{
  private:
  public:
  layer1();
};

layer1::layer1(){
  
}

/*******************************class layer**************************************/
class layer{
  private:
  network net;
  public:
  layer(int,network);

  friend class network;
  friend class neuron;
};

layer::layer(int len,network x){
net=x;
}

/*******************************class network**************************************/
class network{
  private:
  public:
  network();

  friend class layer;
  friend class neuron;
};

network::network(){

}

/*******************************function sigmoid**************************************/
inline double sigmoid(double x){
  return (1/(1+exp(-x)));
}

/*******************************function readdatafile**************************************/
void readdatafile(dataset& in,string filename){
string line;
string word;
vector<double> vtemp;
bool isinputpresent=false;
int i,j;
double temp;
stringstream ss;
  ifstream myfile (filename.c_str());
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )      // read inputs to input set from input.txt
    {
      ss<<line;
      ss>>word;
      if(word=="ilen"){
          ss>>i;
          in.ilen=i;
          ss.clear();
      }
      else if(word=="olen"){
          ss>>i;
          in.olen=i;
          in.len=in.ilen+in.olen;
          ss.clear();
      }
      else if(word=="setlen"){
            ss>>i;
            in.setlen=i;
            ss.clear();
            isinputpresent=true;
            break;
          }
          
      }
  }else {
    cout << "Unable to open file";
    exit(0);
  }

if(isinputpresent){
  //getline (myfile,line);
        for ( i = 0; i <in.setlen; i++)
    {
      getline (myfile,line);
      line.push_back(' ');
      ss<<line;
      for ( j = 0; j <in.len; j++)
      {
        ss>>temp;
        vtemp.push_back(temp);
      }
      in.set.push_back(vtemp);
      vtemp.clear();
      ss.str("");
    }
    myfile.close();

      }
}

/*******************************end**************************************/
