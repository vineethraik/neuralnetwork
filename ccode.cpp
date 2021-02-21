/*c code*/

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<math.h>
#include<string>
using namespace std;


class inputset{
    public:
    int setlen;
    int len;
    vector<vector<int> > set;
    
};

class nuron{
private:
int len;
int *wt;
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
layer *ly;
inputset input;
public:
void init(inputset in,layer *l){input=in;ly=l;};
void learn(int itr);
string exportdatatostring();

};

void readfile(inputset& in,char *filename){
string line;
string word;
int i;
stringstream ss;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )      // read inputs to input set from input.txt
    {
      ss<<line;
      ss>>word;
      if(word=="len"){
          ss>>i;

      }
    }
    myfile.close();
  }

  else cout << "Unable to open file";

}

int main()
{
    inputset x;
    readfile(x,"input.txt");
    

   return 0;
}

