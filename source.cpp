#include<iostream>
#include <time.h>
#include<string>
using namespace std;

const char *key="nuakzdt";

//Convert the key to a digital key
// n : u : a : k : z : d : t
// 3 : 5 : 0 : 2 : 6 : 1 : 4 

// mapping key
// a : d : k : n : t : u : z
// 0 : 1 : 2 : 3 : 4 : 5 : 6
// 2 : 5 : 3 : 0 : 6 : 1 : 4


char* const encipher(const char *const k,const char *const plaintext);
char* const decipher(const char *const k,const char *const ciphertext);

void main()
{
	char pt[100];
	cout<<"Enter path of plain text : "; cin>>pt;
	FILE *fptr=NULL;
	fptr=fopen(pt,"r");
	if(fptr == NULL){cout<<"\nFile not open error path \n\n"; return;}
	cout<<"\n";

	int count=0;
	while(!feof(fptr))
	{	
		char temp[100000];
		fgets(temp,100000,fptr);
		count++;
	}

	fcloseall();

	char **temp=new char*[count];
	for(int i=0;i<count;i++)temp[i]=new char[100000];

	char **temp2=new char*[count];

	fptr=fopen(pt,"r");
	for(int i=0;i<count;i++)
	{
		fgets(temp[i],100000,fptr);
		char *x=encipher(key,temp[i]);
		temp2[i]=x;
	}
	fcloseall();
	fptr=fopen("ciphertext.txt","w");
	for(int i=0;i<count;i++)
	{ 
		char *args="%s\n"; if(i==(count-1))args="%s";
		fprintf(fptr,args,temp2[i]); 
	}
	fcloseall();
	
	fptr=fopen("plainTEXT0.txt","w");
	for(int i=0;i<count;i++)
	{ 
		char *args="%s\n"; if(i==(count-1))args="%s";
		fprintf(fptr,args,decipher(key,temp2[i])); 
	}

/*cout<<"*******************************************\n";
for(int i=0;i<count;i++)
  { 
	  cout<<"time for encrypt message from number of character "<<strlen(temp[i])<<": ";
	  char *x;
	  clock_t start = clock();
	  x=encipher(key,temp[i]);
	  clock_t end = clock();
	  double d = ( end * (float)CLOCKS_PER_SEC * 0.001 ) - ( start * (float)CLOCKS_PER_SEC * 0.001 );
	  cout<<d<<" milliSec";	
	 
	  cout<<" , time for decrypt ciphertext : ";
	   start = clock();
	   x=encipher(key,x);
	   end = clock();
	   d = ( end * (float)CLOCKS_PER_SEC * 0.001 ) - ( start * (float)CLOCKS_PER_SEC * 0.001 );
	   cout<<d<<" milliSec\n";	
  }*/

	cout<<"\nThanks for use my program \1 ;) \n\n";

}

//

char* const encipher(const char *const k,const char *const plaintext)
{
	if(strcmp(k,key) != 0)return NULL; //check if correct key input

	//Convert the key to a digital key
	int *a=new int[strlen(k)];
	for(int i=0;i<strlen(k);i++)a[i]=0;
	for(int i=1;i<strlen(k);i++) 
	{ 
	   for(int j=i-1;j>=0;j--){ if(k[i] >= k[j])a[i]++; else a[j]++; } 
	}
		
	// mapping key
	int *map=new int[strlen(k)];
	for(int i=0;i<strlen(k);i++)map[i]=0;
	for(int i=0;i<strlen(k);i++)
	{
		int j=0;
		while((j<strlen(k)) && (a[j] != i))j++;
		map[i]=j;
	}

	int col=strlen(k);
	int row=strlen(plaintext)/col;
	int pv=(strlen(plaintext)%col),pl=strlen(plaintext);
	if(pv)row++;
	
	char **g=new char*[row];
	for(int i=0;i<row;i++)g[i]=new char[col];

	//stage one
	int i=0,j=0,t=0;
	for(;i<row;i++){ for(j=0;((j<col)&&(t<pl));j++){ g[i][j]=plaintext[t++]; } } 
	if(pv != 0){g[i-1][j++]='\b'; for(;j<col;j++){ g[i-1][j]=' '; } } 
	//if(pv != 0){g[i-1][j++]='\b'; char r='z'; for(;j<col;j++){ g[i-1][j]=r--; } }

	string temp="";
	for(i=0;i<col;i++){ for(j=0;j<row;j++){ if((g[j][map[i]] == '\0' )||(g[j][map[i]] == '\n' )||(g[j][map[i]] == '\t' ))temp+=' '; else temp+=g[j][map[i]]; } }

	//stage two
	t=0;
	for(i=0;i<row;i++){ for(j=0;j<col;j++){ g[i][j]=temp[t++]; } }

	temp="";
	for(i=0;i<col;i++){ for(j=0;j<row;j++){ if((g[j][map[i]] == '\0' )||(g[j][map[i]] == '\n' )||(g[j][map[i]] == '\t' ))temp+=' '; else temp+=g[j][map[i]]; } }

	//
	char *ci=new char[temp.length()+2]; 
	
	strcpy(ci,&temp[0]);

	delete []map;
	delete []a;

	return ci;
}

char* const decipher(const char *const k,const char *const ciphertext)
{
	if(strcmp(k,key) != 0)return NULL; //check if correct key input
	
	//Convert the key to a digital key
	int *a=new int[strlen(k)];
	for(int i=0;i<strlen(k);i++)a[i]=0;
	for(int i=1;i<strlen(k);i++) 
	{ 
	   for(int j=i-1;j>=0;j--){ if(k[i] >= k[j])a[i]++; else a[j]++; } 
	}

	// mapping key
	int *map=new int[strlen(k)];
	for(int i=0;i<strlen(k);i++)map[i]=0;
	for(int i=0;i<strlen(k);i++)
	{
		int j=0;
		while((j<strlen(k)) && (a[j] != i))j++;
		map[i]=j;
	}

	int col=strlen(k);
	int row=strlen(ciphertext)/col;
	int pv=(strlen(ciphertext)%col),pl=strlen(ciphertext);
	if(pv)row++;

	char **g=new char*[row];
	for(int i=0;i<row;i++)g[i]=new char[col];

	//stage one
	int i=0,j=0,t=0;
	for(i=0;i<col;i++){ for(j=0;j<row;j++,t++){ if((ciphertext[t] == '\0' )||(ciphertext[t] == '\n' )||(ciphertext[t] == '\t' ))g[j][map[i]]=' '; else g[j][map[i]]=ciphertext[t]; } }
	string temp="";
	for(i=0;i<row;i++)for(j=0;j<col;j++)temp+=g[i][j];

	//stage two
	t=0;
	for(i=0;i<col;i++){ for(j=0;j<row;j++,t++){ if((temp[t] == '\0' )||(temp[t] == '\n' )||(temp[t] == '\t' ))g[j][map[i]]=' '; else g[j][map[i]]=temp[t]; } }
	temp=""; for(i=0;i<row;i++)for(j=0;j<col;j++)temp+=g[i][j];

	//
	char *ci=new char[temp.length()+1]; 
	

	strcpy(ci,&temp[0]);
	for(i=0;ci[i]&&(ci[i] != '\b');i++);
	if(ci[i] == '\b')ci[i]=NULL;

	delete []map;
	delete []a;

	return ci;
}