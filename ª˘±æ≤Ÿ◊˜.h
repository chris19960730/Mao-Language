#define stacksize   100
#define TRUE 1
#define FALSE 0
#include<stdio.h>
#include<stdlib.h>

typedef struct {                         //˳��ջ
	double   data[stacksize];                //����
	int    form[1000];                       //������¼ջ��ÿһλ����������
	int top;
}stack;


void   initstack(stack * s){         //��˳��ջ�ĳ�ʼ��
	s->top = -1;
}

int  emptystack(stack * s){              //�ж��Ƿ�ջ��
	if (s->top == -1)
		return TRUE;
	else
		return FALSE;
}


int   fullstack(stack * s){          // �ж��Ƿ�ջ��

	if (s->top == stacksize - 1)
		return TRUE;
	else  return  FALSE;
}


int push(stack * s, double number, int type){     //��number��ջ,ͬʱ��number type ��ֵ��form

	if (fullstack(s))   //ջ�����ܽ���ѹջ������
		return  FALSE;
	else{
		s->top++;
		s->data[s->top] = number;
		s->form[s->top] = type;
		return   TRUE;
	}
}

int  pop(stack * s, double * number){          //��ջ��ջ��Ԫ�س�ջ����number

	if (emptystack(s)){
		return  FALSE;
	}
	else{
		*number = s->data[s->top];
		s->top--;
		return   TRUE;
	}
}


double   stacktop(stack *s){          //ȡջ��Ԫ��{
	double number_return;
	if (emptystack(s)){
		return  (number_return);
	}
	else{
		number_return = s->data[s->top];
		return   (number_return);
	}

}

int get(stack *s) {                                  //getֻ��ȡ���Ͳ���ջ{
	int number_return = 0;
	if (emptystack(s)){
		return (number_return);
	}
	else{
		number_return = s->form[s->top];
		return (number_return);
	}
}

void   calculatestack(stack *s, double Operator) {               //ջ�ļ���{
	double num1, num2;
	int num1_type, num2_type, type;
	if (Operator == 0.0){              //����{
		s->data[s->top] = -s->data[s->top];

	}
	else{
		num1_type = get(s);
		pop(s, &num1);
		num2_type = get(s);
		pop(s, &num2);
		if ((num1_type == 0) && (num2_type == 0)){  //��������Ϊ���ͲŽ������ͼ��㣬������Ը����ͽ���
		
			type = 0;
		}
		else{
			type = 1;
		}                             
		if (Operator == 1.0) {                  //�ӷ�

			num1 = num1 + num2;
			push(s, num1, type);
		}
		else if (Operator == 2.0) {             //����{
			num2 = num2 - num1;    //�������
			push(s, num2, type);
		}
		else if (Operator == 3.0) {             //�˷�
		
			num1 = num1*num2;
			push(s, num1, type);
		}
		else if (Operator == 4.0){
		
			if (num1 == 0.0) {                 //��������0����� 
			
				printf("divided by ZERO\n");
				exit(0);
			}
			else{
				if (type == 0) {                   //�����Ϊ���Σ��ȶ�ǿ��ת��Ϊint�ͼ��������double�ͱ��棬����ֱ�Ӽ���
				
					num2 = (double)((int)(num2) / (int)(num1));  // �������
				}
				else{
				
					num2 = num2 / num1;
				}
				push(s, num2, type);
			}
		}
	}
}
