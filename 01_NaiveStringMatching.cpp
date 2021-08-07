#include<iostream>
#include<fstream>
#include<cstring> 
using namespace std; 

void writeInTheFile(string pattern, int array[200]);
void naiveStringMatching(string pat, string txt, int lineCount);

int matchCount=0;
int resultLocations[200];

void writeInTheFile(string pattern, int array[200]){
	int i;
	fstream myfile;
	myfile.open ("results.txt", ios::app);
	if (myfile.is_open()){
		myfile<<"\n===Naive String Search==="<<endl<<endl;
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

  
void naiveStringMatching(string pat, string txt, int lineCount){ 
    int M = pat.length(); 
    int N = txt.length(); 
    int inLineLoc;
	int overrallLoc;
  	int i;
    for (i=0;i<=N-M;i++){ 
        int j; 
  		for (j = 0; j < M; j++){
        	if (txt[i+j]!=pat[j]){
        		break;
			} 
		}
        if (j==M){
        	matchCount++;
            inLineLoc= i; 
            overrallLoc=50*(lineCount-1)+inLineLoc+1;
            resultLocations[matchCount-1]=overrallLoc;
            cout<<overrallLoc<<endl;
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
	cout<<"===Naive String Matching Implementation==="<<endl;
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
							naiveStringMatching(pattern, text,lineCount);
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


