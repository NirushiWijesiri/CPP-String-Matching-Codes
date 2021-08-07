#include<iostream>
#include<fstream>
#include<cstring>
using namespace std; 

#define d 10  

void writeInTheFile(string pattern, int array[200]);
void badCharHeuristic( string str, int size, int badchar[d]);
void boyerMooreSearching( string txt, string pat, int lineCount);


int matchCount=0;
int resultLocations[200];

void writeInTheFile(string pattern,int array[200]){
	int i;
	fstream myfile;
	myfile.open ("results.txt", ios::app);
	if (myfile.is_open()){
		myfile<<"\n===Boyer Moore String Search==="<<endl<<endl;
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

void badCharHeuristic(string str,int size,int badchar[d]){  
    int i;  
    for(i=0;i<d;i++){
    	badchar[i]=-1;  
	}  
    for(i=0;i<size;i++){
    	badchar[str[i]-'0']=i;
	}     
}  
  
void boyerMooreSearching(string txt,string pat,int lineCount){  
    int M=pat.length(); 
    int N=txt.length();  
	int overrallLoc;
    int badchar[d]; 
    badCharHeuristic(pat,M,badchar);    
    int s=0;
    while(s<=(N-M)){ 
        int j=M-1; 
        while(j>=0 && pat[j]==txt[s+j]){
        	j--;
		}  
        if(j<0){  
            matchCount++;         
            overrallLoc=50*(lineCount-1)+s+1;
            resultLocations[matchCount-1]=overrallLoc;
            cout<<overrallLoc<<endl;
			if(s+M<N){
				s=s+(M-badchar[txt[s+M]-'0']);
			}
			else{
				s=s+1;
			} 
        }  
  
        else{
        	s=s+max(1,j-badchar[txt[s+j]-'0']);
		}    
    }  
}

/* Driver code */
int main(){
	string pattern = "980802";
	int introLineCount=0;
	int lineCount=0;
	int i;
	string buffer;
	string text;
	cout<<"===Boyer-Moore String Matching Implementation==="<<endl;
	fstream newfile;
	newfile.open("pi.txt",ios::in);
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
							boyerMooreSearching(text, pattern, lineCount);
						}
					}
					text="";
				}
			}
		}
		writeInTheFile(pattern, resultLocations);
		cout<<"\n\nCount : "<<matchCount<<endl;
	}
	else{
		cout<<"pi.txt file cannot open"<<endl;
	}
	return 0;
}
