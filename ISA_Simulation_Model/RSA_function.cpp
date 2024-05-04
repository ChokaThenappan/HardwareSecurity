#include<iostream>
#include<math.h>
using namespace std;

int gcd(int a, int b) {
   int t;
   while(1) {
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b= t;
   }
}

double RSA_encrypt(int message, int PK_sender, int PK_receiver){
    double n= PK_sender * PK_receiver;//calculate n
    double track;
    double phi= (PK_sender-1)*(PK_receiver-1);
    double e=7;
    while(e<phi) {
        track = gcd(e,phi);
        if(track==1)
            break;
        else
            e++;
    }
    double d1=1/e;
    double d=fmod(d1,phi);
    double c = pow(message,e);
    c=fmod(c,n);
    return c;
}

double RSA_decrypt(int message, int PK_sender, int PK_receiver){
    double n= PK_sender * PK_receiver;//calculate n
    double track;
    double phi= (PK_sender-1)*(PK_receiver-1);
    double e=7;
    while(e<phi) {
        track = gcd(e,phi);
        if(track==1)
            break;
        else
            e++;
    }
    double d1=1/e;
    double d=fmod(d1,phi);
    double m = pow(message,d);
    m=fmod(m,n);
    return m;
}
double encrypt(int message, double e, double n){
    double e = 7;
    double c = pow(message,e); //encrypt the message
    return c;
}
int main() {
   //2 random prime numbers
   double p = 13;
   double q = 11;
   double n=p*q;//calculate n
   double track;
   double phi= (p-1)*(q-1);//calculate phi
   //public key
   //e stands for encrypt
   double e=7;
   //for checking that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
   while(e<phi) {
      track = gcd(e,phi);
      if(track==1)
         break;
      else
         e++;
   }
   //private key
   //d stands for decrypt
   //choosing d such that it satisfies d*e = 1 mod phi
   double d1=1/e;
   double d=fmod(d1,phi);
   cout <<"d" << d << endl;
   double message = 9;
   double c = pow(message,e); //encrypt the message
   double m = pow(c,d);
   c=fmod(c,n);
   m=fmod(m,n);
   cout<<"Original Message = "<<message;
   cout<<"\n"<<"p = "<<p;
   cout<<"\n"<<"q = "<<q;
   cout<<"\n"<<"n = pq = "<<n;
   cout<<"\n"<<"phi = "<<phi;
   cout<<"\n"<<"e = "<<e;
   cout<<"\n"<<"d = "<<d;
   cout<<"\n"<<"Encrypted message = "<<c;
   cout<<"\n"<<"Decrypted message = "<<m;
   return 0;
}