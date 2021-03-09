#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
using namespace std;

/* ________********       DATASET       ********________ */
class dataset{
  private:

  public:
  int setlen;
  int len;
  int ilen;
  int olen;
  vector<vector<int> > set;
  dataset();
  void read();
    
};

dataset::dataset(){
  setlen=0;
  len=0;
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

/* ________********       NEURON       ********________ */


class neuron{
private:
int len;
vector<double> wt;

public:
neuron(int inputlen);
void clear();
double out(vector<int>& input);
double derv(int id,vector<int>& input);
int getlen(){return len;};
void readwt();
};


neuron::neuron(int inputlen){
len=inputlen+1;
vector<double> x;
for(int i=0;i<=inputlen;i++)
  wt.push_back((-9999+(rand()%19999))/1000.0);
}

void neuron::clear(){
len=0;
wt.clear();
}

void neuron::readwt(){
    for (int j = 0; j <len; j++)
      cout<<wt[j]<<"   ";
    cout<<"\n";
}


/* ________********       LAYER       ********________ */


class layer{
private:
int len;
int inputlen;
vector<neuron> n;
public:
layer(int neuronlen,int inlen);
void readout();
};


layer::layer(int neuronlen,int inlen){
  len=neuronlen;
  inputlen=inlen;
  n.clear();
  for(int i=0;i<neuronlen;i++)
    n.push_back(neuron(inlen));
}

void layer::readout(){
  for(int i=0;i<len;i++)
    n[i].readwt();
}


/* ________********       NETWORK       ********________ */


class network
{
private:
int len;
int inlen;
int outlen;
vector<layer> ly;
dataset input;
public:
void init(dataset in,vector<layer> l);
void learn(int itr);
string exportdatatostring();

};


void network::init(dataset in,vector<layer> l){
  input=in;
  ly=l;
};



/* ________********       READ DATA FUNCTION       ********________ */
void readfile(dataset& in,string filename){
string line;
string word;
vector<int> vtemp;
bool isinputpresent=false;
int i,j,temp;
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