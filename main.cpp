#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef vector<int> Ivec;
typedef vector<Ivec> Imatrix;
typedef vector<bool> Bvec;
typedef vector<Bvec> Bmatrix;
Ivec operator -(const Ivec &b,const Ivec &a){
Ivec temp;
    for(unsigned int x = 0;x<b.size();++x){
        if(find(a.begin(),a.end(),b[x])!=a.end()){
            temp.push_back(b[x]);
        }
    }return temp;
}
Ivec operator +(const Ivec &a,const Ivec &b){
   Ivec temp=a;
   for(unsigned int x = 0;x<b.size();++x){
        //if(find(a.begin(),a.end(),b[x])!=a.end()){
            temp.push_back(b[x]);
        //}
   }return temp;
}
Ivec range(int,int=0,int=1);
//int que(Ivec=Ivec(),Ivec=Ivec(),int=0);
int que(Bmatrix &,const int,Bmatrix &,const int &lastx=0,const int &lasty=0);
void removeDuplicates(Ivec &);
void printVec(const Ivec &,const bool =false);
void printVec(const Bvec &,const bool =false);
void printMatrix(const Bmatrix &);
void printMatrix(const Imatrix &);
Imatrix dia(const int &x,const int &y);

map<int,map<int,Imatrix> > diamap;
//map<Bmatrix,map<int,bool> > map2;
map<Bmatrix,bool> mapy;
//vector<Bmatrix> mapy;
//vector<Bmatrix> DPa;
int bsize =0;
int queens = 0;
int main(){
cout<<"board size:";
cin>>bsize;
cout<<"num of queens:";
cin>>queens;
Bmatrix c(bsize,Bvec(bsize,true));
Bmatrix c2(bsize,Bvec(bsize,false));
//for(int x = 8;x!=0;--x){
    //c.push_back(Bvec(8,true));
    //c2.push_back(Bvec(8,false));
//}
cout<<que(c,0,c2);
return 0;
}
void printVec(const Ivec &c,const bool a){
for(unsigned int x = 0;x<c.size();++x){
    if(a){
        cout<<c[x]<<" ";
    }else{cout<<c[x]<<endl;}
}
}
void printVec(const Bvec &c,const bool a){
for(unsigned int x = 0;x<c.size();++x){
    if(a){
        cout<<c[x]<<" ";
    }else{cout<<c[x]<<endl;}
}
}
void printMatrix(const Imatrix &c){
for(unsigned int x =0;x<c.size();++x){
    printVec(c[x],true);
    cout<<endl;}
}
void printMatrix(const Bmatrix &c){
for(unsigned int x =0;x<c.size();++x){
    printVec(c[x],true);
    cout<<endl;}
}
template<class T>
void removeDuplicates(T &c){
for(int x = c.size()-1;x!=-1;--x){
    if(find(c.begin(),c.begin()+x,c[x])!=c.begin()+x){
        c.erase(c.begin()+x);
    }
}
}
Imatrix dia(const int &x,const int &y){
map<int,map<int,Imatrix> >::iterator it;
it = diamap.find(x);

if(it!=diamap.end()){
    map<int,Imatrix>::iterator it2;
    it2 = diamap[x].find(y);
    if(it2!=diamap[x].end()){
        //cout<<"a"<<endl;
        return diamap[x][y];
    }
}
int tx = x;
int ty = y;
//+x,+y
Imatrix temp;
Ivec *tempc;
tempc = new Ivec(2);
while(tx!=bsize&&ty!=bsize){
    tempc->at(0)=tx;
    tempc->at(1)=ty;
    temp.push_back(*tempc);
    ++tx;
    ++ty;
}
//-x,+y
tx = x;
ty = y;
while(tx!=-1&&ty!=bsize){
    tempc->at(0)=tx;
    tempc->at(1)=ty;
    temp.push_back(*tempc);
    --tx;
    ++ty;
}
//-x,-y
tx = x;
ty = y;
while(tx!=-1&&ty!=-1){
    tempc->at(0)=tx;
    tempc->at(1)=ty;
    temp.push_back(*tempc);
    --tx;
    --ty;
}
//+x,-y
tx = x;
ty = y;
while(tx!=bsize&&ty!=-1){
    tempc->at(0)=tx;
    tempc->at(1)=ty;
    temp.push_back(*tempc);
    ++tx;
    --ty;
}
delete tempc;
diamap[x][y]=temp;
return temp;
}
int que(Bmatrix &c,const int q,Bmatrix &c2,const int &lastx,const int &lasty){
    /*
map<Bmatrix,map<int,bool> >::iterator it;
it = map2.find(c);
if(it!=map2.end()){
    map<int,bool>::iterator it2;
    it2 = map2[c].find(q);
    if(it2!=map2[c].end()){
        return 0;
    }
}*/
//if(lastx+queens-q>bsize)return 0;
map<Bmatrix,bool>::iterator it3;
//vector<Bmatrix>::iterator it3;
it3 = mapy.find(c2);
//it3 = find(mapy.begin(),mapy.end(),c2);
if(it3!=mapy.end()){
    //printMatrix(c2);
    return 0;
}

if(q==queens){
    printMatrix(c2);
    cout<<endl;
    mapy[c2]=false;
    //mapy.push_back(c2);
    return 1;
}
mapy[c2]=false;
int t = 0;
Bmatrix clone = c;
Bmatrix clone2 = c2;
//printMatrix(clone);
//printVec(clone[0]);
Imatrix diag;
//mapy.push_back(c2);
//cout<<q<<endl;
for(int x = lastx;x<bsize;++x){
	if(x+queens-q>bsize) break;
    for(int y = 0;y<bsize;++y){
		//cout<<x+queens-q+1<<endl;
        if(!c[x][y]){
            continue;
        }
        diag = dia(x,y);
        for(int x2 = diag.size()-1;x2!=-1;--x2){
            clone[diag[x2][0]][diag[x2][1]]=false;
        }
        for(int x2 = bsize-1;x2!=-1;--x2){
            clone[x][x2]=false;
            clone[x2][y]=false;
        }
        //if(q>9){
        //cout<<x<<" "<<y<<" "<<q<<" "<<t<<endl;
        //printMatrix(clone);}
        //if(clone[x][y]){
        clone2[x][y]=true;
        t+=que(clone,q+1,clone2,x,y);//}
        //mapy[clone2]=false;
        clone = c;
        clone2 = c2;
    }
}
//map2[c][q]=false;
//mapy[c2]=false;
//mapy.push_back(c2);
return t;
}
Ivec range(const int start,const int end,const int skip){
Ivec T;
if(end==0){
    for(int x = 0;x<start;++x){
        T.push_back(x);
    }
}else{
    for(int x = start;x<end;x+=skip){
        T.push_back(x);
    }
}
return T;
}

