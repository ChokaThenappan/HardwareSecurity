#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include "master.hpp"

using namespace std;


int main(){
    master alice;
    slave bob;

    //Initializing the network
    //Protocol 2
    alice.outQnd(0);
    bob.send_key(0);
    alice.readmem(1,0);
    alice.RSA_encrypt(0,0,1);
    alice.RSA_encrypt(1,1,1);
    alice.send_data(0,0);
    alice.send_data(1,1);
    
    bob.read(0,0);
    bob.read(1,1);
    bob.RSA_decrypt(0,2);
    bob.RSA_decrypt(1,3);
    bob.TRNG(0);
    bob.add(2,0);
    bob.store_temp(0,2);
    bob.store_temp(1,3);
    bob.RSA_encrypt(0,0,1);
    bob.send_info(0,0);

    alice.readtemp(0,0);
    alice.RSA_decrypt(0,1);

    //Intial Conditions
    int bob_number;
    alice.mem[0] = 3;
    bob.mem[0] = 3;
    alice.mem[1] = 6;
    cout << "Enter the number you want to multiply with Alice's number secretly (You are Bob): ";
    cin >> bob_number;
    alice.mem[1] = rand() % bob_number;
    bob.mem[1] = bob_number - alice.mem[1];
    
    //Multiplication
    //Protocol 1

    alice.intialize_seed(1);
    alice.outRnd(0);//
    alice.outRnd(1);//
    alice.subract(2,0,0);//
    alice.subract(3,1,1);//
    alice.send_data(2,0);//
    alice.send_data(3,1);//
    alice.outQnd(2);//
    //Bob
    bob.intialize_seed(2);
    bob.setRnd(0);
    bob.setRnd(1);
    bob.setRnd(2);
    bob.read(0,0);
    bob.read(1,1);
    bob.add(2, 0, 0);
    bob.add(3, 1, 1);
    bob.load(0, 2);
    bob.load(1,3);
    bob.mult();
    bob.store(2,2);
    printf("Final Answer = %d\n", bob.mem[2] + alice.mem[2]);

    return 0;

}
