#include<stdio.h>
#include<malloc.h>
#include"��������.h"
#include"Print.h"                
double Analysis(char * sentence, struct mylist * head, int begin, int end){ //���㴦��

	double result;        //������
	struct  mylist * p1;
	int begin2, end2;        //�����²㺯��
	int beginconst, endconst;     //���볣������
	int type;
	int typeconst;             //��������
	int i, j;
	int whetherget;
	int  * changei;
	double * changed;           //���ڸı������е�ֵ
	double number;              //��ʱ�����ֵ
	int   whethersign(char c);    //�ж��ǲ��������������ȺŻ�ֺ�
	double  sign_num(char x);  //������Ϊ����
	int youxian(double x);      //�ж����ȼ�
	stack   s1, s2;                  //s1���ڴ����Ҫ�����ֵ s2������ʱ���������Ķ�Ӧ����
	double conststringnumber(char * a, int begin, int end, int type);    //�ַ�������ת��Ϊ����
	double constcharnumber(char x);              //���ַ�������תΪ����(char x)
	initstack(&s1);
	initstack(&s2);                 //Ϊs1,s2����ջ
	push(&s2, -1.0, 1);               //Ϊs2��������Լ��͵�-1���Ա���֮����
	for (i = begin; i <= end; i++){
		if (whethersign(*(sentence + i)) == 0){          //����������
		
			for (p1 = head; p1 != NULL; p1 = p1->next){
				whetherget = 0;
				for (j = 0; j <= (p1->len) - 1; j++){
					if (p1->name[j] != *(sentence + i + j))
						whetherget = 1;
				}


				if ((whetherget == 0) && ((whethersign(*(sentence + i + j)) == 1) || (i + j == end))){
					//֤�������Ҫ�ҵı���
					changei = &p1->int_value;                                        //��ָ��ָ��ñ���
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
	for (i = begin; i <= end; i++){           //��ʱ�ڸò�ֻʣ�¼��㲿��
	
		switch (*(sentence + i)) {    //���ַ������ж�
		
		case   '+':
		case   '-':
		case   '*':
		case   '/':      {
							 if (((*(sentence + i) == '+') || (*(sentence + i) == '-')) && ((i == begin) || (*(sentence + i - 1) == '+') || (*(sentence + i - 1) == '-') || (*(sentence + i - 1) == '*') || (*(sentence + i - 1) == '(') || (*(sentence + i - 1) == '/'))) {
								 //������Ϊ�����ţ�������������������Կ���ֱ����ջ
								 if (*(sentence + i) == '-')
									 push(&s2, 0.0, 1);         //���Ž�ջ2
							 }
							 else{
								 while (youxian(stacktop(&s2)) >= youxian(sign_num(*(sentence + i)))) {
									 pop(&s2, &number);
									 calculatestack(&s1, number);
								 }                                  //�������Ը��ڸ��������ȫ����������γ�ջ��������
								 number = sign_num(*(sentence + i));
								 push(&s2, number, 1);                     //�����������ջ
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
		}                       //�Գ���������ջ1
		default:      {
						  for (p1 = head; p1 != NULL; p1 = p1->next) {        //�Ա����Ĵ���
						 
							  whetherget = 0;        //0�����ҵ���1����û�ҵ���������
							  for (j = 0; j <= (p1->len) - 1; j++){
							  
								  if (p1->name[j] != *(sentence + i + j))
									  whetherget = 1;

							  }

							  //�ж��Ƿ��������еĸñ���	 

							  if ((whetherget == 0) && ((whethersign(*(sentence + i + j)) == 1) || (i + j == end))){
								  i = i + p1->len - 1;
								  number = p1->double_value;
								  push(&s1, number, p1->type);       //���ñ�����ֵ��ջ
							  }                                 //֤���ñ�����ΪҪѰ�ҵı���
						  }


		}

		}
	}
	while ((stacktop(&s2) != -1.0) && (!emptystack(&s2))){         //��ջ��ʣ�������ȫ������
		pop(&s2, &number);
		calculatestack(&s1, number);
	}
	pop(&s1, &result);            //s1ջ���һ�Ϊ���
	return (result);
}


int whethersign(char c){
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '=') || (c == ';'))
		return (1);
	else
		return (0);
}
int youxian(double x) {           //�жϷ������ȼ���ջ�׷������ȼ�Ϊ-1��� �� �Ӽ���Ϊ2���˳���Ϊ3���������ȼ����Ϊ4 

	int a;
	 if (x == -1.0)     a= -1;
	else if ((x == 1.0) || (x == 2.0))          a = 2;
	else if ((x == 3.0) || (x == 4.0))           a = 3;            //����   �Ӽ���Ϊ2        �˳���Ϊ3    ����Ϊ4 
	else if (x == 0.0)     a = 4;
	return (a);
}

double  sign_num(char x){

	double ret;                         
	if (x == '+')           ret = 1.0;                    //�ӺŶ�Ӧ1
	else if (x == '-')            ret = 2.0;                   //���Ŷ�Ӧ2
	else if (x == '*')            ret = 3.0;                   //�˺Ŷ�Ӧ3
	else if (x == '/')           ret = 4.0;                   //���Ŷ�Ӧ4 
	return (ret);
}

double conststringnumber(char * a, int begin, int end, int type){  //֮���֪����atoi �����

	int i, j, point;
	double constcharnumber(char x);             //���ַ�������תΪ����(char x)
	double ret = 0.0;
	double cifang;                           //���������������������
	if (type == 0){                             //����
	
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

	return (ret);                           //��������

}

double constcharnumber(char x){              //���ַ�������תΪ����(char x)

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