#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mylist{				// 存放变量的内容
				
	int type;   // 变量的类型    '0'presents 'int'   ,   '1'presents 'double'
	char name[20];   // 变量的名字
	int int_value;           // int 的值
	double double_value; // double 的值
	int len;    //该变量的名称字符串的长度
	struct mylist *next;
	
};
void Print(char str[], struct mylist *head){
	char str_1[20];
	struct mylist *temp;
	temp = head;
	int i = 6;
	while (*(str + i) != ')'){ //将print的（）中的内容读取出并保存
	
		i++;
	}
	*(str + i) = '\0';
	strcpy(str_1, str + 6);    
	while (temp != NULL&&strcmp(temp->name, str_1)){//在链表中找到括号中的东西
	
		temp = temp->next;
	}
	if (temp != NULL){
		if (temp->type == 1){
			printf("%lf\n", temp->double_value);
		}   //输出double型的值
		else if (temp->type == 0){
			printf("%d\n", temp->int_value);
		}//输出int型的值
	}
	else{
		int n = 0;
		for (int j = 0; str_1[j] != '\0'; j++){
			if (str_1[j] == '.')   //记录是否存在小数点 n不为零则存在
				n++;
		}
		if (n != 0){
			printf("%lf\n", atof(str_1));
		}  // atof函数将字符串转化成浮点型(可保留正负号)
		else{
			printf("%d\n", atoi(str_1));
		}//atoi函数将字符串转化成整型(可保留正负号)
	}
}