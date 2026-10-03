#include<iostream>
#include"calculator.h"
#include<cmath>
using namespace std;

//求和
node* polyAdd(node* poly1, node* poly2){
	node* head = createNode(0,0);
    node* cur = head;
    
    while(poly1 != nullptr && poly2 != nullptr) {
        int e1 = poly1->exp, e2 = poly2->exp;
        int c1 = poly1->coef, c2 = poly2->coef;

        if(e1 > e2) {
            cur->next = createNode(c1, e1); 
            poly1 = poly1->next;
            cur = cur->next;
        } else if(e1 < e2) {
            cur->next = createNode(c2, e2); 
            poly2 = poly2->next; 
            cur = cur->next;          
        } else {
            if(c1 + c2 != 0){
                cur->next = createNode(c1 + c2, e1);     //相加
                cur = cur->next;
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        
    }

    while(poly1 != nullptr) {
        cur->next = createNode(poly1->coef, poly1->exp);
        cur = cur->next;
        poly1 = poly1->next;
    } 
    while(poly2 != nullptr) {
        cur->next = createNode(poly2->coef, poly2->exp);
        cur = cur->next;
        poly2 = poly2->next;
    }

    node* res = head->next;
    free(head);
    return res;
}

//求差
node* polySub(node* poly1, node* poly2){
    node* head = createNode(0,0);
    node* cur = head;
    
    while(poly1 != nullptr && poly2 != nullptr) {
        int e1 = poly1->exp, e2 = poly2->exp;
        int c1 = poly1->coef, c2 = -1 *  poly2->coef;

        if(e1 > e2) {
            cur->next = createNode(c1, e1); 
            poly1 = poly1->next;
            cur = cur->next;
        } else if(e1 < e2) {
            cur->next = createNode(c2, e2); 
            poly2 = poly2->next; 
            cur = cur->next;          
        } else {
            if(c1 + c2 != 0){
                cur->next = createNode(c1 + c2, e1);     //相减
                cur = cur->next;
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while(poly1 != nullptr) {
        cur->next = createNode(poly1->coef, poly1->exp);
        cur = cur->next;
        poly1 = poly1->next;
    } 
    while(poly2 != nullptr) {
        cur->next = createNode(-1 * poly2->coef, poly2->exp);
        cur = cur->next;
        poly2 = poly2->next;
    }

    node* res = head->next;
    free(head);
    return res;	
}

//求X时多项式的值
int polyCalposX(node* a, int x){
	int ans = 0;
	node* cur = a;
	while(cur != nullptr) { // 遍历多项式逐个求值 
		int c = cur->coef, e = cur->exp;
		ans += c * pow(x, e);
		cur = cur->next;
	}
	return ans;
}

//求导函数
node* polyDerivedfunction(node* a){
	node* new_head = a;
	node* cur = new_head;
	while(cur != nullptr) { // 遍历多项式逐个求导数 
		cur->coef *= cur->exp;
		cur->exp--;
		cur = cur->next;
	}
	return new_head;
}

//处理多项式相乘
node* polyPlus(node* a, node* b){
	node* new_head = createNode(0, 0); //新多项式的哨兵节点
	if(a->coef == 0 || b->coef == 0) { //如果a, b其中有零多项式，那么直接返回零多项式 
		return new_head;
	}

	//基本思想：遍历a多项式的每一项，分别与b多项式的每一项相乘，得到的结果插入到新多项式中
	node* cur_a = a, *cur_b = b; //防止修改原指针 
	while(cur_a != nullptr) {
		int ca = cur_a->coef, ea = cur_a->exp;
		cur_b = b; //重新开始遍历b多项式 
		while(cur_b != nullptr) {
			node* tmp = new_head->next;
			node* pre = new_head; //记录tmp的前驱节点，方便插入新节点
			int c1 = ca * cur_b->coef, e1 = ea + cur_b->exp; // 乘积项的属性c1, e1 

			//将乘积项插入到新多项式中，按照指数从大到小的顺序插入
			if(tmp == nullptr) { //第一个为空时直接添加 
				tmp = createNode(c1, e1);
				pre->next = tmp;
			} else {
				while(tmp != nullptr && tmp->exp > e1) { //比较指数，直到找到相等或者小于e1的第一个位置 
					pre = tmp;
					tmp = tmp->next;
				}
				
				if(tmp == nullptr) {  //如果tmp为空，说明e1是最小的指数，直接插入到链表尾部 
					pre->next = createNode(c1, e1);
				} else if(tmp->exp == e1) {  //如果tmp的指数等于e1，说明已经有相同指数的项，直接相加 
					tmp->coef += c1;
					if(tmp->coef == 0) {  //如果相加后系数为0，则删除该节点 
						pre->next = tmp->next;
						delete tmp;
						continue; //继续下一次循环，避免访问已删除的节点
					}
				} else {	 //否则，说明tmp的指数小于e1，需要在pre和tmp之间插入新节点 
					node* new_node = createNode(c1, e1);
					pre->next = new_node;
					new_node->next = tmp;
				}
			}
		}
		cur_a = cur_a->next;
	} 

	//释放哨兵节点
	node* res = new_head->next;
	delete new_head;
	return res;
}
