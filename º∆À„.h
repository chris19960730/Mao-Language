#include<stdio.h>
#include<malloc.h>
#include"基本操作.h"
#include"Print.h"                
double Analysis(char * sentence, struct mylist * head, int begin, int end){ //运算处理

	double result;        //运算结果
	struct  mylist * p1;
	int begin2, end2;        //导入下层函数
	int beginconst, endconst;     //导入常数处理
	int type;
	int typeconst;             //常数类型
	int i, j;
	int whetherget;
	int  * changei;
	double * changed;           //用于改变链表中的值
	double number;              //暂时存放数值
	int   whethersign(char c);    //判断是不是四则运算符或等号或分号
	double  sign_num(char x);  //化符号为数字
	int youxian(double x);      //判断优先级
	stack   s1, s2;                  //s1用于存放需要运算的值 s2用于暂时存放运算符的对应数字
	double conststringnumber(char * a, int begin, int end, int type);    //字符型数字转化为数字
	double constcharnumber(char x);              //将字符型数字转为数字(char x)
	initstack(&s1);
	initstack(&s2);                 //为s1,s2开空栈
	push(&s2, -1.0, 1);               //为s2添加优先性极低的-1，以便于之后处理
	for (i = begin; i <= end; i++){
		if (whethersign(*(sentence + i)) == 0){          //变量或数字
		
			for (p1 = head; p1 != NULL; p1 = p1->next){
				whetherget = 0;
				for (j = 0; j <= (p1->len) - 1; j++){
					if (p1->name[j] != *(sentence + i + j))
						whetherget = 1;
				}


				if ((whetherget == 0) && ((whethersign(*(sentence + i + j)) == 1) || (i + j == end))){
					//证明这就是要找的变量
					changei = &p1->int_value;                                        //将指针指向该变量
					changed = &p1->double_value;
					type = p1->type;
					i = i + p1->len - 1;
				}
			}
		}
		else if (*(sentence + i) == '='){
			end2 = end;
			end = i - 1;
			begin2 = i + 1;
			if (type == 1){
				*changed = Analysis(sentence, head, begin2, end2);
				*changei = (int)(*changed);
			}
			else{
				*changei = (int)(Analysis(sentence, head, begin2, end2));
				*changed = (double)(*changei);
			}
		}
	}
	for (i = begin; i <= end; i++){           //此时在该层只剩下计算部分
	
		switch (*(sentence + i)) {    //对字符进行判断
		
		case   '+':
		case   '-':
		case   '*':
		case   '/':      {
							 if (((*(sentence + i) == '+') || (*(sentence + i) == '-')) && ((i == begin) || (*(sentence + i - 1) == '+') || (*(sentence + i - 1) == '-') || (*(sentence + i - 1) == '*') || (*(sentence + i - 1) == '(') || (*(sentence + i - 1) == '/'))) {
								 //表明该为正负号，由于其优先性最高所以可以直接入栈
								 if (*(sentence + i) == '-')
									 push(&s2, 0.0, 1);         //负号进栈2
							 }
							 else{
								 while (youxian(stacktop(&s2)) >= youxian(sign_num(*(sentence + i)))) {
									 pop(&s2, &number);
									 calculatestack(&s1, number);
								 }                                  //将优先性高于该运算符的全部运算符依次出栈，并运算
								 number = sign_num(*(sentence + i));
								 push(&s2, number, 1);                     //将此运算符进栈
							 }
							 break;
		}
		case  '0':
		case  '1':
		case  '2':
		case  '3':
		case  '4':
		case  '5':
		case  '6':
		case  '7':
		case  '8':
		case  '9':     {
						   beginconst = i;
						   typeconst = 0;
						   while ((constcharnumber(*(sentence + i)) != 11) && (i <= end)) {
							   if (*(sentence + i) == '.') {
								   typeconst = 1;
							   }

							   i = i + 1;
						   }
						   endconst = i - 1;

						   i = i - 1;
						   push(&s1, conststringnumber(sentence, beginconst, endconst, typeconst), typeconst);
		}                       //对常数处理并入栈1
		default:      {
						  for (p1 = head; p1 != NULL; p1 = p1->next) {        //对变量的处理
						 
							  whetherget = 0;        //0代表找到，1代表没找到（变量）
							  for (j = 0; j <= (p1->len) - 1; j++){
							  
								  if (p1->name[j] != *(sentence + i + j))
									  whetherget = 1;

							  }

							  //判断是否是链表中的该变量	 

							  if ((whetherget == 0) && ((whethersign(*(sentence + i + j)) == 1) || (i + j == end))){
								  i = i + p1->len - 1;
								  number = p1->double_value;
								  push(&s1, number, p1->type);       //将该变量的值进栈
							  }                                 //证明该变量即为要寻找的变量
						  }


		}

		}
	}
	while ((stacktop(&s2) != -1.0) && (!emptystack(&s2))){         //将栈中剩余运算符全部弹出
		pop(&s2, &number);
		calculatestack(&s1, number);
	}
	pop(&s1, &result);            //s1栈最后一项即为结果
	return (result);
}


int whethersign(char c){
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '=') || (c == ';'))
		return (1);
	else
		return (0);
}
int youxian(double x) {           //判断符号优先级，栈底符号优先级为-1最低 ， 加减号为2，乘除号为3，负号优先级最高为4 

	int a;
	 if (x == -1.0)     a= -1;
	else if ((x == 1.0) || (x == 2.0))          a = 2;
	else if ((x == 3.0) || (x == 4.0))           a = 3;            //定义   加减号为2        乘除号为3    负号为4 
	else if (x == 0.0)     a = 4;
	return (a);
}

double  sign_num(char x){

	double ret;                         
	if (x == '+')           ret = 1.0;                    //加号对应1
	else if (x == '-')            ret = 2.0;                   //减号对应2
	else if (x == '*')            ret = 3.0;                   //乘号对应3
	else if (x == '/')           ret = 4.0;                   //除号对应4 
	return (ret);
}

double conststringnumber(char * a, int begin, int end, int type){  //之后才知道了atoi 就这吧

	int i, j, point;
	double constcharnumber(char x);             //将字符型数字转为数字(char x)
	double ret = 0.0;
	double cifang;                           //计算该数字所处的数量级
	if (type == 0){                             //整形
	
		for (i = begin; i <= end; i++){
			cifang = 1;
			for (j = 1; j <= end - i; j++){
				cifang = cifang * 10;
			}

			ret = ret + constcharnumber(*(a + i))*cifang;

		}
	}
	else if (type == 1){
		for (i = begin; i <= end; i++){
			if (*(a + i) == '.')
				point = i;

		}
		for (i = begin; i <= point - 1; i++){
			cifang = 1;
			for (j = 1; j <= point - i - 1; j++){
				cifang = cifang * 10;
			}
			ret = ret + constcharnumber(*(a + i))*cifang;
		}
		for (i = point + 1; i <= end; i++){
			cifang = 1;
			for (j = 1; j <= i - point; j++){
				cifang = cifang / 10;
			}
			ret = ret + constcharnumber(*(a + i))*cifang;

		}

	}

	return (ret);                           //返还数字

}

double constcharnumber(char x){              //将字符型数字转为数字(char x)

	if (x == '0')
		return (0.0);
	else if (x == '1')
		return(1.0);
	else if (x == '2')
		return(2.0);
	else if (x == '3')
		return(3.0);
	else if (x == '4')
		return(4.0);
	else if (x == '5')
		return(5.0);
	else if (x == '6')
		return(6.0);
	else if (x == '7')
		return(7.0);
	else if (x == '8')
		return(8.0);
	else if (x == '9')
		return(9.0);
	else if (x == '.')
		return (10.0);
	else
		return (11.0);
}