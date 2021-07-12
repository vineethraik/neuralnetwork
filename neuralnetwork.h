#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
using namespace std;

/* ________********       constents      ********________ */
#define lrate_wt .3
#define lratew_input .1
#define xtt false

/* ________********       sigmoid       ********________ */

double sigmoid(double x){
  return (1/(1+exp(-x)));
}



/* ________********       DATASET       ********________ */
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

/* ________********       NEURON       ********________ */

/* ________********       READ DATA FUNCTION       ********________ */

void readfile(dataset& in,string filename){
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