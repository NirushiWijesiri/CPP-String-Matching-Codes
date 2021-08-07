#include<iostream>
#include<fstream>
#include<cstring>
using namespace std; 

void writeInTheFile(string pattern,int array[200]);
void KMPSearching(string pat,string txt,int lineCount);
void computingLPSArray(string pat,int M,int* lps);

int matchCount=0;
int resultLocations[200];

void writeInTheFile(string pattern,int array[200]){
	int i;
	fstream myfile;
	myfile.open ("results.txt", ios::app);
	if (myfile.is_open()){
		myfile<<"\n===KMP String Search==="<<endl<<endl;
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
  
void KMPSearching(string pat,string txt,int lineCount){ 
    int M = pat.length(); 
    int N = txt.length(); 
    int inLineLoc;
	int overrallLoc; 
    int lps[M]; 
    computingLPSArray(pat,M,lps); 
  	int i = 0;  
    int j = 0; 
    while (i<N) { 
        if (pat[j]==txt[i]){ 
            j++; 
            i++; 
        }   
        if (j==M){ 
            matchCount++;
            inLineLoc=i-j; 
            overrallLoc=50*(lineCount-1)+inLineLoc+1;
            resultLocations[matchCount-1]=overrallLoc;
            cout<<overrallLoc<<endl;
            j=lps[j-1]; 
        } 
        else if(i<N && pat[j]!=txt[i]){  
            if (j!=0) 
                j=lps[j-1]; 
            else
                i=i+1; 
        } 
    } 
} 
  
void computingLPSArray(string pat,int M,int* lps){ 
    int len=0; 
  	lps[0]=0; 
    int i=1; 
    while(i<M) { 
        if(pat[i]==pat[len]){ 
            len++; 
            lps[i]=len; 
            i++; 
        } 
        else{  
            if(len!=0){ 
                len=lps[len-1];  
            } 
            else{ 
                lps[i]=0; 
                i++; 
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
	string buffer;
	string text;
	cout<<"===KMP String Matching Implementation==="<<endl;
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
							KMPSearching(pattern, text,lineCount);
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
