#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<string>
using namespace std;

class inputset{
  private:
  int i,j,temp;
  public:
  int setlen=0;
  int len=0;
  vector<vector<int> > set;
  void read(){
    for ( i = 0; i <setlen; i++)
  {
    for ( j = 0; j <len; j++)
    {
      cout<<set[i][j]<<"\t";
    }
    cout<<"\n";
  }
  };
    
};



class nuron{
private:
int len;
vector<int> wt;
public:
void init(int inputlen,int seed);
float out(float *input);
float derv(int id);
int getlen(){return len;};
};



class layer{
private:
int len;
nuron *n;
public:
void init(int nuronlen,int seed);
void input(inputset input);
void connect(layer x);
};



class network
{
private:
int len;
int inlen;
int outlen;
layer ly;
inputset input;
public:
void init(inputset in,layer& l){input=in;ly=l;};
void learn(int itr);
string exportdatatostring();

};




void readfile(inputset& in,string filename){
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
      if(word=="len"){
          ss>>i;
          in.len=i;
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