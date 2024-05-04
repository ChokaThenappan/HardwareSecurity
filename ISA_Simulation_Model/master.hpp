#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cassert>
#include "slave.hpp"

using namespace std;

class master{ //Alice
        private:
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
        int temp_reg [4];
        int mem [10];
        int seed;
        //Function Blocks
        int *CSPRNG(int seed);
        void subract(int a, int b, int c){
            assert(a < 4);
            assert(b < 10);
            assert(c < 3);
            temp_reg[a] = mem[b] - temp_reg[c];
        }
        void send_data(int a, int b){
            assert(a < 4);
            assert(b < 2);
            network[b] = temp_reg[a]; 
        }
        void readmem(int a, int b){
            assert(a < 10);
            assert(b < 2);
            mem[a] = network[b];
        }
        void readtemp(int a, int b){
            assert(a < 10);
            assert(b < 2);
            temp_reg[a] = network[b];
        }
        void intialize_seed(int a){
            //srand(a);
            srand(temp_reg[a]);
        }
        void outRnd(int a){
            assert(a < 4);
            temp_reg[a]=rand()%10;
        }
        void outQnd(int a){
            assert(a < 10);
            mem[a]=rand()%10;
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
