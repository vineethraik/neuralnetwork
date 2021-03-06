#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
using namespace std;

/* ________********       sigmoid       ********________ */
#define lrate .01

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


class neuron{
private:
int len;
vector<double> preinput;
vector<double> wt;
vector<double> diff;
double preout;
double out;
double out_diff;
public:
neuron(int inputlen);
void clear();
double forword(vector<double>& input);
vector<double> backprop(double var);
int getlen(){return len;};
void readwt(int n);
void readdiff();
};


neuron::neuron(int inputlen){
len=inputlen+1;
out=0;
preout=0;
out_diff=0;
wt.clear();
diff.assign(len,0);
preinput.assign(len-1,0);
for(int i=0;i<len;i++)
  wt.push_back((-9999+(rand()%19999))/1000.0);
}



double neuron::forword(vector<double>& input){
  double temp=0;
  diff.clear();
  for(int i=0;i<len-1;i++){
  temp+=input[i]*wt[i];
  diff.push_back(input[i]-preinput[i]);
  }
  temp+=wt[len-1];
  out=sigmoid(temp);
  out_diff=out-preout;
  preout=out;
  preinput=input;
  return out;
}


vector<double> neuron::backprop(double var){
out_diff=var;
vector<double> result;
for(int i=0;i<len-1;i++){
wt[i]+=lrate*out_diff*diff[i];
result.push_back(sigmoid(out_diff*wt[i]));
}
return result;
}


void neuron::clear(){
len=0;
preinput.clear();
wt.clear();
diff.clear();
preout=0;
out=0;
out_diff=0;
}


void neuron::readwt(int n){
  cout<<"neuron"<<n<<"  ";
    for (int j = 0; j <len; j++)
      cout<<wt[j]<<"   ";
    cout<<"\n";
}

void neuron::readdiff(){
    for (int j = 0; j <len; j++)
      cout<<diff[j]<<"   ";
    cout<<"\n";
}


/* ________********       LAYER       ********________ */


class layer{
private:
int len;
int inputlen;
vector<neuron> neurons;
vector<double> out;
public:
layer(int neuronlen,int inlen);
vector<double> feedforword(vector<double> input);
vector<double> backprop(vector<double> var);
void readout(int n);
};


layer::layer(int neuronlen,int inlen){
  len=neuronlen;
  inputlen=inlen;
  neurons.clear();
  for(int i=0;i<neuronlen;i++)
    neurons.push_back(neuron(inlen));
}

vector<double> layer::feedforword(vector<double> input){
vector<double> temp; 
for(int i=0;i<len;i++)
temp.push_back(neurons[i].forword(input));
out=temp;
return temp;
}

vector<double> layer::backprop(vector<double> var){
  vector<vector<double> > result;
  vector<double> res(inputlen,0);
  for(int i =0;i<len;i++){
   result.push_back( neurons[i].backprop(var.at(i)));
  }
  for(int i=0;i<inputlen;i++){
    for(int j=0;j<len;j++)
      res[i]+=result[j][i]/len;
  }
  return res;
}

void layer::readout(int n){
  cout<<"layer"<<n<<"\n";
  for(int i=0;i<len;i++)
    neurons[i].readwt(i);
    cout<<"\n";
}


/* ________********       NETWORK       ********________ */


class network
{
private:
int len;
int inlen;
int outlen;
vector<layer> layers;
dataset input;
public:
void init(dataset,vector<int>);
vector<vector<double> > feedforword();
vector<double> backprop(int);
string exportdatatostring();
void readout();
};


void network::init(dataset in,vector<int> structure){
  len=structure.size();
  inlen=structure[0];
  outlen=structure[len-1];
  input=in;
  layers.clear();
  layers.push_back(layer(structure[0],structure[0]));

  for(int i=1;i<len;i++)
    layers.push_back(layer(structure[i],structure[i-1]));  
}


vector<vector<double> > network::feedforword(){
  vector<double> temp;
  vector<vector<double> > result;
  
  for(int i=0;i<input.setlen;i++){
    temp=layers[0].feedforword(input.set[i]);
    for(int j=1;j<layers.size();j++)
    temp=layers[j].feedforword(temp);
    result.push_back(temp);
  }
 
  return result;
}

vector<double> network::backprop(int itr){
  vector<double> temp;
  vector<double> temp1;

 for(int k=0;k<itr;k++){
   for(int i=0;i<input.setlen;i++){
    temp1=layers[0].feedforword(input.set[i]);
    for(int j=1;j<layers.size();j++)
    temp1=layers[j].feedforword(temp1);
    temp.assign(input.set[i].begin()-1+input.ilen,input.set[i].end());
    for(int j=0;j<temp.size();j++){
      temp[j]=temp[j]-temp1[j];
    }
    temp=layers[len-1].backprop(temp);
    for(int j=len-2;j>=0;j--){
      temp=layers[j].backprop(temp);
    }
   }
 } 
 return temp;
}


void network::readout(){
for(int i=0;i<len;i++)
    layers[i].readout(i);
    cout<<" \n";
}


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