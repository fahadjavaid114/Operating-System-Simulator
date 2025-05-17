#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
#include<sys/shm.h>
using namespace std;
int n1,n2,n3=0;
int main()
{
        cout<<"\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
	cout << "\t\t\tWELCOME TO CALCULATOR PROCCESS!"<<endl;
	cout<<"\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
 int *shared_memory;
int shmid;
shmid=shmget((key_t)1122,sizeof(int),0666);

shared_memory=(int*)shmat(shmid,NULL,0);
int new_data =*shared_memory-10 ;
*shared_memory=new_data;

if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }
int choice,chi;
do
{
cout<<"Press 1 to start proccess"<<endl;
cout<<"Press 0 to exit"<<endl;
cin>>choice;
if(choice==1)
{
cout<<"Press 1 to add"<<endl;
cout<<"Press 2 to subtract"<<endl;
cout<<"Press 3 to multiplication"<<endl;
cout<<"Press 4 to division"<<endl;
cout<<"Enter chi: ";
cin>>chi;
cout<<"Enter first number: ";
cin>>n1;
cout<<"Enter second number: ";
cin>>n2;

if(chi==1)
{
n3=n1+n2;
cout<<"Addition of "<<n1<<" and "<<n2<<" = "<<n3<<endl;
}
else if(chi==2)
{
n3=n1-n2;
cout<<"Subtraction of "<<n1<<" and "<<n2<<" = "<<n3<<endl;
}
else if(chi==3)
{
n3=n1*n2;
cout<<"Multiplication of "<<n1<<" and "<<n2<<" = "<<n3<<endl;
}
else if(chi==4)
{
n3=n1/n2;
cout<<"Division of "<<n1<<" and "<<n2<<" = "<<n3<<endl;
}
else
{
  choice=0;
}

}
if(choice!=0&& choice!=1)
{
 choice=0;
}
}while(choice==1);

{
  int *shared_memory;
int shmid;
shmid=shmget((key_t)1122,sizeof(int),0666);
shared_memory=(int*)shmat(shmid,NULL,0);
int new_data =*shared_memory+10 ;
*shared_memory=new_data;
if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }
    return 0;
}
return 0;
}
