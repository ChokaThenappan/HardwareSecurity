#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include "master.hpp"

using namespace std;
int seed = 33;

void printfun(){
    // cout << "Alice:temp_reg[0] = " << alice.temp_reg[0] << "|" << "temp_reg[1] = " << alice.temp_reg[1] << "|" << "temp_reg[2] = " << alice.temp_reg[2] << "|" << "temp_reg[3] = " << alice.temp_reg[3] << endl;
    // cout << "Alice:mem[0] = " << alice.mem[0] << "|" << "mem[1] = " << alice.mem[1] << "|" << "mem[2] = " << alice.mem[2] << "|" << "mem[3] = " << alice.mem[3] << "|" << "mem[4] = " << alice.mem[4] << "|" << "mem[5] = " << alice.mem[5] << "|" << "mem[6] = " << alice.mem[6] << "|" << "mem[7] = " << alice.mem[7] << "|" << "mem[8] = " << alice.mem[8] << "|" << "mem[9] = " << alice.mem[9] << endl;
    // cout << "Bob:temp_reg[0] = " << bob.temp_reg[0] << "|" << "temp_reg[1] = " << bob.temp_reg[1] << "|" << "temp_reg[2] = " << bob.temp_reg[2] << "|" << "temp_reg[3] = " << bob.temp_reg[3] << endl;
    // cout << "Bob:mem[0] = " << bob.mem[0] << "|" << "mem[1] = " << bob.mem[1] << "|" << "mem[2] = " << bob.mem[2] << "|" << "mem[3] = " << bob.mem[3] << "|" << "mem[4] = " << bob.mem[4] << "|" << "mem[5] = " << bob.mem[5] << "|" << "mem[6] = " << bob.mem[6] << "|" << "mem[7] = " << bob.mem[7] << "|" << "mem[8] = " << bob.mem[8] << "|" << "mem[9] = " << bob.mem[9] << endl;
    // cout << "Bob:arch_reg[0] = " << bob.arch_reg[0] << "|" << "arch_reg[1] = " << bob.arch_reg[1] << "|" << "arch_reg[2] = " << bob.arch_reg[2] << endl;

}

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
    alice.intialize_seed(1);

    //Intial Conditions
    alice.mem[0] = 3;
    alice.mem[1] = 6;
    bob.mem[0] = 3;
    bob.mem[1] = 2;
    
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