#pragma once 
#ifndef CALCULATOR_H
#define CALCULATOR_H

// 基本数据类型与结构体定义
//typedef int datatype;
//typedef struct node *pointer;

struct node {
    int coef;           // 多项式项系数
    int exp;            // 多项式项指数
    node* next;            // 后继节点指针
};

//typedef pointer lklist;      // 单链表头指针类型

// 多项式的核心函数声明（polynode.cpp实现）
node* polyAdd(node* a, node* b);
node* polySub(node* a, node* b);
int polyCalposX(node* a, int x);
node* polyDerivedfunction(node* a);
node* polyPlus(node* a, node* b); 

//表达式的核心函数声明（polynode.cpp实现）


// main.cpp中已实现
node* createNode(int coef, int exp);
void freePoly(node* poly);

#endif 
