#define stacksize   100
#define TRUE 1
#define FALSE 0
#include<stdio.h>
#include<stdlib.h>

typedef struct {                         //顺序栈
	double   data[stacksize];                //数字
	int    form[1000];                       //用来记录栈内每一位的数据类型
	int top;
}stack;


void   initstack(stack * s){         //对顺序栈的初始化
	s->top = -1;
}

int  emptystack(stack * s){              //判断是否栈空
	if (s->top == -1)
		return TRUE;
	else
		return FALSE;
}


int   fullstack(stack * s){          // 判断是否栈满

	if (s->top == stacksize - 1)
		return TRUE;
	else  return  FALSE;
}


int push(stack * s, double number, int type){     //将number进栈,同时将number type 赋值给form

	if (fullstack(s))   //栈满不能进行压栈操作了
		return  FALSE;
	else{
		s->top++;
		s->data[s->top] = number;
		s->form[s->top] = type;
		return   TRUE;
	}
}

int  pop(stack * s, double * number){          //将栈的栈顶元素出栈赋给number

	if (emptystack(s)){
		return  FALSE;
	}
	else{
		*number = s->data[s->top];
		s->top--;
		return   TRUE;
	}
}


double   stacktop(stack *s){          //取栈顶元素{
	double number_return;
	if (emptystack(s)){
		return  (number_return);
	}
	else{
		number_return = s->data[s->top];
		return   (number_return);
	}

}

int get(stack *s) {                                  //get只提取类型不出栈{
	int number_return = 0;
	if (emptystack(s)){
		return (number_return);
	}
	else{
		number_return = s->form[s->top];
		return (number_return);
	}
}

void   calculatestack(stack *s, double Operator) {               //栈的计算{
	double num1, num2;
	int num1_type, num2_type, type;
	if (Operator == 0.0){              //负号{
		s->data[s->top] = -s->data[s->top];

	}
	else{
		num1_type = get(s);
		pop(s, &num1);
		num2_type = get(s);
		pop(s, &num2);
		if ((num1_type == 0) && (num2_type == 0)){  //两变量均为整型才进行整型计算，否则均以浮点型进行
		
			type = 0;
		}
		else{
			type = 1;
		}                             
		if (Operator == 1.0) {                  //加法

			num1 = num1 + num2;
			push(s, num1, type);
		}
		else if (Operator == 2.0) {             //减法{
			num2 = num2 - num1;    //别减返了
			push(s, num2, type);
		}
		else if (Operator == 3.0) {             //乘法
		
			num1 = num1*num2;
			push(s, num1, type);
		}
		else if (Operator == 4.0){
		
			if (num1 == 0.0) {                 //除法除以0的情况 
			
				printf("divided by ZERO\n");
				exit(0);
			}
			else{
				if (type == 0) {                   //如果均为整形，先都强制转化为int型计算后再以double型保存，否则直接计算
				
					num2 = (double)((int)(num2) / (int)(num1));  // 别除反了
				}
				else{
				
					num2 = num2 / num1;
				}
				push(s, num2, type);
			}
		}
	}
}
