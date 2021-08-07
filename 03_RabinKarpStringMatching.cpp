#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
 
#define d 10

void writeInTheFile(string pattern, int array[200]);
void rabinKarpSearching(string pat, string txt, int lineCount);


int matchCount=0;
int resultLocations[200];
int q = 101;

void writeInTheFile(string pattern,int array[200]){
	int i;
	fstream myfile;
	myfile.open ("results.txt", ios::app);
	if(myfile.is_open()){
		myfile<<"\n===Rabin Karp String Search==="<<endl<<endl;
		myfile<<"My birthDay : "<<pattern<<endl<<endl;
		myfile<<matchCount<<" no of matches found."<<endl<<endl;
		myfile<<"Matching Locations : "<<endl;
		for(i=0;i<matchCount;i++){
			myfile<<array[i]<<endl;
		}
		myfile.close();
	}
	else{
		cout<<"results.txt file cannot open"<<endl;
	}
}

void rabinKarpSearching(string pat,string txt,int lineCount){  
    int M=pat.length(); 
    int N=txt.length();
	int overrallLoc;  
    int i,j;  
    int p=0; 
    int t=0;   
    int h=1;  
  	for(i=0;i<M-1;i++){
        h=(h*d)%q;  
    }
	for(i=0;i<M;i++){  
        p=(d*p+pat[i])%q;  
        t=(d*t+txt[i])%q;  
    }
	for(i=0;i<=N-M;i++){
        if(p==t){
            for(j=0;j<M;j++){  
                if(txt[i+j]!=pat[j]){
                    break;  
                }
            }  
            if(j==M){
            	matchCount++;
            	overrallLoc = 50*(lineCount-1)+i+1;
            	resultLocations[matchCount-1]=overrallLoc;
            	cout<<overrallLoc<<endl;
            }
        }  
		if(i<N-M){  
            t=(d*(t-txt[i]*h)+txt[i+M])%q;
            if(t<0){
            	t=(t+q);  
            }
        }  
    }  
}

/* Driver code */
int main(){
	string pattern = "980802";
	int introLineCount=0;
	int lineCount=0;
	int i;
	string buffer, text;
	cout<<"===Rabin-Karp String Matching Implementation==="<<endl;
	fstream newfile;
	newfile.open("pi.txt");
	if (newfile.is_open()){
		while(!newfile.eof()){
			getline(newfile,buffer);
			introLineCount++;
			if(introLineCount>21){
				if(buffer!=""){
					lineCount++;
					for(i=0;i<54;i++){
						if(buffer[i]!=' '){
							text=text+buffer[i];
						}
						if(i==53){
							rabinKarpSearching(pattern,text,lineCount);
						}
					}
					text="";
				}
			}
		}
		writeInTheFile(pattern,resultLocations);
		cout<<"\n\nCount : "<<matchCount<<endl;
	}
	else{
		cout<<"pi.txt file cannot open"<<endl;
	}
	return 0;
}

