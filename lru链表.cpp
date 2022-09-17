#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <array>
#include <ctime>
#include <fstream>
#define UpBound 2  //模拟最大内存
using namespace std;
class knot{
public:
    int n_data=0;
    knot* p_NextKnot=NULL;
};
class chaintable{
public:
    knot* head=NULL;
    int count=0;

    void deltail(){//删除尾部
        if (head==NULL)return;
        if (head->p_NextKnot==NULL){
            delete head;
            head=NULL;
            --count;
        }

        knot** tp;
        tp=&head;
        while ((*tp)->p_NextKnot!=NULL){tp=&((*tp)->p_NextKnot);}
        delete (*tp);
        (*tp)=NULL;
        --count;
    }
    void ins(const int &n){//插入数值
        del(n);//只存一个
        if (count>=UpBound){deltail();}//模拟内存满了

        knot* current;
        current=new knot;
        current->n_data=n;
        current->p_NextKnot=head;
        head=current;
        ++count;
    }
    int del(const int &n){//给出要删的值，若存在，删除一个，返回1，否则返回0。
        knot** tp;
        tp=&head;
        while ((*tp)!=NULL){
            if ((*tp)->n_data==n){
                knot** ttp=tp;
                (*tp)=(*tp)->p_NextKnot;
                delete (*ttp);
                (*ttp)=NULL;
                --count;
                return 1;
            }
            tp=&((*tp)->p_NextKnot);
        }
        return 0;
    }
    int sea(const int &n){//询问是否存在，存在返回1，并置顶，否则返回0
        if (del(n)){
            ins(n);
            return 1;
        } else return 0;
    }
    void delall(knot* &p){//删除该节点往后
        if (p->p_NextKnot!=NULL){delall(p->p_NextKnot);}
        delete p;
        p=NULL;
        --count;
    }
    ~chaintable(){if (head!=NULL)delall(head);}//析构函数
};


int main() {
    chaintable lruCT;
    int n_Tdata;
    char order[10];

    cin>>order>>n_Tdata;
    while (cin.fail()== false){//读取操作，用EOF终止输入
        switch (order[0]) {
            case 'i':{
                lruCT.ins(n_Tdata);
                break;
            }
            case 'd':{
                cout<<lruCT.del(n_Tdata)<<endl;
                break;
            }
            case 's':{
                cout<<lruCT.sea(n_Tdata)<<endl;
                break;
            }
            case 'e':{
                return 0;//提供多一个程序出口,exit 0
            }
        }
        cin>>order>>n_Tdata;
    }

    return 0;
}