#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main ()
{srand(time(0));

    int randomnumber=rand()%100+1,attempt=10,attemptuser=0;

while(attempt>0)

  { 
    cout << "Introduce un numero";
    cin>>attemptuser;

  if(attemptuser==randomnumber){
    cout<<"Ai castigat!!";
  }

  

  if(attemptuser<randomnumber){

    cout<<"Prea mic,mai incearca!";
  }

  

  if(attemptuser>randomnumber){
    cout<<"Prea mare,mai incearca!";
  }

  
  
   if (attempt==0){
    cout<<"Ai pierdut!";
   }
   
attempt--;

   }
   return 0;
}

    