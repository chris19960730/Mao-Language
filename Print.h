#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mylist{				// ��ű���������
				
	int type;   // ����������    '0'presents 'int'   ,   '1'presents 'double'
	char name[20];   // ����������
	int int_value;           // int ��ֵ
	double double_value; // double ��ֵ
	int len;    //�ñ����������ַ����ĳ���
	struct mylist *next;
	
};
void Print(char str[], struct mylist *head){
	char str_1[20];
	struct mylist *temp;
	temp = head;
	int i = 6;
	while (*(str + i) != ')'){ //��print�ģ����е����ݶ�ȡ��������
	
		i++;
	}
	*(str + i) = '\0';
	strcpy(str_1, str + 6);    
	while (temp != NULL&&strcmp(temp->name, str_1)){//���������ҵ������еĶ���
	
		temp = temp->next;
	}
	if (temp != NULL){
		if (temp->type == 1){
			printf("%lf\n", temp->double_value);
		}   //���double�͵�ֵ
		else if (temp->type == 0){
			printf("%d\n", temp->int_value);
		}//���int�͵�ֵ
	}
	else{
		int n = 0;
		for (int j = 0; str_1[j] != '\0'; j++){
			if (str_1[j] == '.')   //��¼�Ƿ����С���� n��Ϊ�������
				n++;
		}
		if (n != 0){
			printf("%lf\n", atof(str_1));
		}  // atof�������ַ���ת���ɸ�����(�ɱ���������)
		else{
			printf("%d\n", atoi(str_1));
		}//atoi�������ַ���ת��������(�ɱ���������)
	}
}