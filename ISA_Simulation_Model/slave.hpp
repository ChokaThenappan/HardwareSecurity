#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cassert>

using namespace std;

int network[2]; 

class slave{ //Bob
        private:
        int rand_reg [3];
        double Hidden_Key = 0.142857;
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
        public:
        double Public_Key = 7;
        int arch_reg [3];
        int temp_reg [4];
        int mem [10];
        int seed;
        //Function Blocks
        int *CSPRNG(int seed);
        void setRnd(int a){
            assert(a < 3);
            rand_reg[a] = rand()%10; 
        }
        void TRNG(int a){
            assert(a < 3);
            temp_reg[a] = rand()%10;
        }
        void add(int a, int b){
            assert(a < 4);
            assert(b < 4);
            temp_reg[a] = temp_reg[a] + temp_reg[b];
        }
        void intialize_seed(int a){
            //srand(a);
            srand(temp_reg[a]);
        }
        void load(int a, int b){
            assert(a < 3);
            assert(b < 4);
            arch_reg[a] = temp_reg[b];
        }
        void add(int a, int b, int c){
            assert(a < 4);
            assert(b < 10); 
            assert(c < 4);
            temp_reg[a] = mem[b] + temp_reg[c];
        }
        void mult(){
            arch_reg[2] = ((arch_reg[0]+rand_reg[0]) * (arch_reg[1]+rand_reg[1])) - rand_reg[2];
        }
        void store(int a, int b){
            assert(a < 10);
            assert(b < 3);
            mem[a] = arch_reg[b];
        }
        void read(int a, int b){
            assert(a < 4);
            assert(b < 2);
            temp_reg[a] = network[b];
        }
        void send_key(int b){
            assert(b < 2);
            network[b] = Public_Key; 
        }
        void send_info(int a, int b){
            assert(a < 4);
            assert(b < 2);
            network[b] = temp_reg[a]; 
        }
        void store_temp(int a, int b){
            assert(a < 10);
            assert(b < 4);
            mem[a] = temp_reg[b];
        }
        void RSA_encrypt(int a, int b, int d){
            double c = pow(mem[a],mem[d]);
            temp_reg[b]=c;
        }
        void RSA_decrypt(int a, int b){
            double m = pow(temp_reg[a],Hidden_Key);
            temp_reg[b]=round(m);
        }
};


