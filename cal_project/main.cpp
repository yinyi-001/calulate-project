#include<iostream>
#include"calculator.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// 多项式：辅助函数1：创建新节点
node* createNode(int coef, int exp) {
    node* newNode = new node();
    if (newNode == NULL) {
        cout << "分配内存失败" << endl;
        exit(EXIT_FAILURE);
    }
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// 多项式：辅助函数2：从输入创建多项式链表
node* createPoly() {
	cout << "请输入多项式的项数：" << endl;
    int n;
    cin >> n;
    node* head = nullptr, *tail = nullptr;
	cout << "请输入每一项的系数和指数（以空格分隔）：" << endl;
    for (int i = 0; i < n; i++) {
        int coef, exp;
        cin >> coef >> exp;
        node* newNode = createNode(coef, exp);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// 多项式：辅助函数3：释放多项式内存
void freePoly(node* poly) {
    node* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        delete temp;
    }
}

// 多项式：辅助函数4：打印多项式（仅输出系数和指数，空格分隔）
void printPoly(node* poly) {
    if (poly == NULL) {
        cout << "0" ; // 空多项式输出0
        return;
    }
    node* p = poly;
    int isFirst = 1;
    while (p != nullptr) {
        if (!isFirst) {
            printf(" "); // 项之间用空格分隔
        }
        // 直接输出当前项的系数和指数
        cout << p->coef << ',' << p->exp ;
        isFirst = 0;
        p = p->next;
    }
    cout << endl;
}

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul"); // >nul屏蔽输出代码页那行多余文字
#endif

	cout << "请选择你需要的功能 : " << endl;
	cout << "一元稀疏多项式简单计算器请输入1,算术表达式求值计算器请输入2。" << endl;
	int n; cin >> n;
	if(n == 1) { //多项式 
		int m = -5; // -5为default值 
		cout << "请输入你需要的功能：非负整数:求值, -1:相加, -2:相减, -3:求导函数, -4:相乘" << endl;
		cin >> m ;
		// cout << m << endl;
		if(m == -1) { // 相加 
			node* a = createPoly();
			node* b = createPoly();
			node* ans = polyAdd(a, b);
			printPoly(ans);
		} else if(m == -2) { // 相减 
			node* a = createPoly();
			node* b = createPoly();
			node* ans = polySub(a, b);
			printPoly(ans);
		} else if(m == -3) { // 求导函数 
			node* a = createPoly();
			node* ans = polyDerivedfunction(a);
			printPoly(ans);
		} else if(m == -4) { // 相乘 
			node* a = createPoly();
			node* b = createPoly();
			node* ans = polyPlus(a, b);
			printPoly(ans);
		} else if(m == -5) { // 未输入有效数据 
			cout << "未输入有效数据，退出程序" << endl;
		} else { // 求位于x处的值 
			int x;
			cin >> x;
			node* a = createPoly();
			int ans = polyCalposX(a, x);
			cout << ans << endl;
		}
	} else if (n == 2) { //表达式 
		
	} else {
		cout << "无效输入，退出程序" << endl;
	}
	
	return 0;
}
