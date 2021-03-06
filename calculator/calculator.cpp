//������� ���������� ��� ���������� �������� ��������������� ���������, �������
//����� �������� � ���� �������������� �����, � ����� ������� ������ � ��������� 
//�������� +,-,*,/,^ (���������� � �������). ���������� ������ ������������ 
//� ������ ������ � ����������� ������������ ��������. ������������� ���������� 
//��������� ��������� ������ � �������������� � ��� ������������.

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)

#include <iostream>
#include <windows.h>
using namespace std;

int priority(char); //������� ����������� ���������� ���������
double calculate(char*, int, int, int&); //����������� ������� ��� ���������� ����� ���������
double calcOper(double, char, double, int&); //������� ��������������� ���������� ���� �����

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char str[100]; //������ � ������� ����� ������� ������� ��� ����������
	int sizeStr = 0; //���������� ������� ������ (������ ��� � �� ������������ ��������� strlen(str), �������� ������������� �������)
	bool *errorInPut = new bool; //����� ������ ��� ����������� ������������ �����
	double result = 0;	//���������� ��� �������� ���������� ����������
	int error = 0;	//���������� ��� �������� ������ (1 - ������� �� ����, ����� �������� ������ �� �������������)
	do {
		*errorInPut = 0; //�������� ������� ������� ���������� ����� (��� ���������� ������� ������������)
		cout << "������� ������ (��� ��������) ��� ���������� ���������\n����� ������������ �������������� ����� � ������������ \".\" (�����)," << endl;
		cout << "������� ������ � ��������� ��������: +, -, *, /, ^ (���������� � �������)" << endl;
		cin >> str;	//���� ������ � ������
		int *countBrackets = new int; //������� ��������/�������� ������ (��� �������� ������������ �����)
		*countBrackets = 0;	//������������� "0"
		sizeStr = strlen(str);	//���������� ����� ��������� ������
		for (int i = 0; i < sizeStr; i++) { //��������� ���� ��� ����������� �������� ������
			if (!((*(str + i) >= 48 && *(str + i) <= 57) || priority(*(str + i)) > 0 || *(str + i) == '.')) { //�������� ������������ ����� ������� (������ ���� �����, �����, ������ � ��������� ��������� ����������)
				*errorInPut = 1;	//������ ����� ������ ��� ����������� ���������� ����� � ������
				cout << "������ �����: ������������� ������������� ������� � ������� " << i << endl;
				break;
			}
			if (*(str + i) == '(') { //�������� ������� �������� �� "("
				(*(countBrackets))++; //��� ���������� �������� ������ �������������� ���������� �������� ����������� ������
				if (!(i == 0 || (i > 0 && (priority(*(str + i - 1)) > 1 || *(str + i - 1) == '(')))) { //�������� ������� �������� �����
					*errorInPut = 1;
					cout << "������ �����: ����� \"(\" ������ ������ ���� ��������� ��� ��� ���� \"(\" � ������� " << i << endl;
					break;
				}
				if (!(i + 1 < sizeStr && ((*(str + i + 1) >= 48 && *(str + i + 1) <= 57)|| *(str + i + 1)=='('))) {	//�������� ������� �������� ������
					*errorInPut = 1;
					cout << "������ �����: ����� \"(\" ������ ������ ����� ��� ��� ���� \"(\" � ������� " << i << endl;
					break;
				}
			}
			if (*(str + i) == ')') { //�������� ������� �������� �� ")"
				(*(countBrackets))--; //��� ���������� �������� ������ �������������� ���������� �������� ����������� ������
				if (!(i > 0 && ((*(str + i - 1) >= 48 && *(str + i - 1) <= 57) || *(str + i - 1) == ')'))) { //�������� ������� �������� �����
					*errorInPut = 1;
					cout << "������ �����: ����� \")\" ������ ������ ����� ��� ��� ���� \")\" � ������� " << i << endl;
					break;
				}
				if (!(i == sizeStr - 1 || (i + 1 < sizeStr && (priority(*(str + i + 1)) > 1 || *(str + i + 1) == ')')))) {	//�������� ������� �������� ������
					*errorInPut = 1;
					cout << "������ �����: ����� \")\" ������ ������ ���� ��������� ��� ��� ���� \")\" � ������� " << i << endl;
					break;
				}
			}
			if (*(str + i) == '.') { //�������� ������� �������� �� "."
				if (!(i > 0 && *(str + i - 1) >= 48 && *(str + i - 1) <= 57)) { //�������� ������� �������� �����
					*errorInPut = 1;
					cout << "������ �����: ����� \".\" ������ ������ ����� � ������� " << i << endl;
					break;
				}
				if (!(i + 1 < sizeStr && *(str + i + 1) >= 48 && *(str + i + 1) <= 57)) {	//�������� ������� �������� ������
					*errorInPut = 1;
					cout << "������ �����: ����� \".\" ������ ������ ����� � ������� " << i << endl;
					break;
				}
			}
			if (priority(*(str + i)) > 1) { //�������� ������� �������� �� ����� ���������
				if (!(i > 0 && ((*(str + i - 1) >= 48 && *(str + i - 1) <= 57)) || priority(*(str + i - 1)) == 1)) { //�������� ������� �������� �����
					*errorInPut = 1;
					cout << "������ �����: ����� ������ ��������� ������ ������ ����� ��� ������ � ������� " << i << endl;
					break;
				}
				if (!(i + 1 < sizeStr && ((*(str + i + 1) >= 48 && *(str + i + 1) <= 57)) || priority(*(str + i + 1)) == 1)) {	//�������� ������� �������� ������
					*errorInPut = 1;
					cout << "������ �����: ����� ����� ��������� ������ ������ ����� ��� ������ � ������� " << i << endl;
					break;
				}
			}
		}
		if (*countBrackets != 0 && *errorInPut != 1) { //�������� ������������ ����������� ����������� � ����������� ������, ����� �� ����� ������ ���� ��� ������ ������
			*errorInPut = 1;
			cout << "������ �����: ����������� \"(\" �� ������������� ����������� \")\"" << endl;
		}
		cout << endl;
		delete countBrackets; //������������� ������������ ������
	} while (*errorInPut);
	delete errorInPut;//������������� ������������ ������
	//strcpy_s(str, { "(48.1-76.2/(25.7+4.9)+8.6)*21" });	//����������� ������,  ����� 1138,41
	//strcpy_s(str, { "25+(71.2-56.2+37/2^(2+1))*(18+4)" });  //����������� ������,  ����� 456,75
	//sizeStr = strlen(str);	//���.�������� ��� ������������ �������
	result = calculate(str, 0, sizeStr, error); //������ �������� ��� ����������
	if (error == 1) cout << "������ ����������: ������� �� ����" << endl;	//����� ������ ���� ��������� � �������� ����������
	else cout << "��������� ���������� ���������:   " << result << endl;	//����� �� ����� ����������
	}

double calculate(char* str, int startStr, int endStr, int &error) {	//�������� ����� ������ ������, ��������� ������� � ������, �������� ������� � ������ (������� ������� ���������) � ���������� ��� �������� ������)
	double number[3] = { 0.0,0.0,0.0 };	//������� ������ ��� �������� �������� �� ������ ����� � ������������� ���������� ��� ������� ������ ����� ������� (���������� 3-� ��������� � ��� ����� 3-� ��������� ������������� ����������)
	int operation[3] = { 0,0,0 };  //������� ������ ��� �������� �������� ������� � ������ � ����������� ���������� ��� ������� ������ ����� ������� (���������� 3-� ��������� � ��� ����� 3-� ��������� ������������� ����������)
	int numberPos = 0, operationPos = 0; //��������� ��� ������� �� �������� number � operation
	bool digit = 0;	//����� ��� ������ ������ ��������� � ������ (0 - ����� �� ����������, 1 - ���� ��� ���������� �����)
	double result;	//���������� ��� �������� � ������ ���������� ����������
	int i;	//�������� ��� ������� �� ������
	for (i = startStr; i < endStr; i++) { //��������� ���� ������������� ������� �� ������
		if (*(str + i) == '(') { //��� ���������� �������� ������ �������������� ����� ����� ������� ������ �������� � ������ ������ ��� ����������
			int countBrackets = 1;	//���������� ��� �������� ����������� ������: +1 ��� ���������� �������� ������, -1 ������������� �������� ������
			int start = i + 1;	//��������� ������� ������ ������, �������� ������� "("
			for (i++; i < endStr; i++) { //�������� ������� ��������� +1, ��������� ������� ��� ���������� ����� ��������� � ������ ����������� �������
				if (*(str + i) == '(') { //��� ���������� ��� ����� ����������� ������ ���������� �� � ����������� ������� ������
					countBrackets++;
					}
				else if (*(str + i) == ')') { //��� ���������� ����������� ������ �������������� ������� ������
					countBrackets--;
					if (countBrackets == 0) { //���� ������ ������ ������� (������� ����� "0") ������� �� �����
						break;
					}
				}
			}
			number[numberPos] = calculate(str, start, i, error); //���������� � ������� ��������� ������ � ������ ��������� ���������� ��������� �������� ��������� �� �������� ����� ������� ��� ����� ����� ������ ������� � ������������ �����������
			if (!numberPos) result = number[numberPos]; //���� ������ ������ ������ � ������� ����� ���������� � ���������� ��������� (�� ������ ���� ��� ����� ������������ �� ������ �������, ��� ���������� ����������) 
			numberPos++; //����������� �������� ������� �� ������ � ���������� �������
		}
		else if (priority(*(str + i)) == 0) { //��� ���������� ����� ��� �����
			if (!digit) { //���� ����� 0-������ �����
				digit = 1;	//�������� ����� �� 1 - ����� ��� �������
				number[numberPos] = atof(str + i);	//���������� ����� � ������ ����� number
				if (!numberPos) result = number[numberPos]; //���� ������ ������ ������ � ������� ����� ���������� � ���������� ��������� (�� ������ ���� ��� ����� ������������ �� ������ �������, ��� ���������� ����������) 
				numberPos++; //����������� �������� ������� �� ������ � ���������� �������
			}
		}
		else if (priority(*(str + i)) > 1) { //��� ���������� ��������� ����������
			digit = 0;	//������������� ����� ���������� ����� �� "0" ��� ����������� ���������� ������� ����.����� (����� ��� ������������ ������� ���������)
			if (operationPos == 0) { //���� ��� ������ ��������� ��������
				operation[operationPos] = i; //���������� ������� � ������ ������ ��������� � ����� operation
				operationPos++; //����������� �������� ������� �� ������ � ���������� ��������� ���������� ����������
			}
			else if (priority(*(str + i)) > priority(*(str + operation[operationPos - 1]))) { //��������� ������� ���������� ��������� ���������, ���� ������� �������� ��������� ���� �����������, ����� ���� ������
				operation[operationPos] = i; //���������� ������� � ������ ������ ��������� � ����� operation
				operationPos++; //����������� �������� ������� �� ������ � ���������� ��������� ���������� ����������
			}
			else {  //��������� ������� ���������� ��������� ���������, ���� ������� �������� ��������� ����� ��� ������ �����������, ����� ���������� ���������� ���������� ����� � �������� ������� ����������
				for (int j = operationPos; j > 0; j--) { //������ ����� ��� ������� � �������� ������� �������� ����� � ����������
					result = calcOper(number[j - 1], *(str + operation[j - 1]), number[j], error);	//���������� ���������� ���� ����� �� ������ number � ����� �������� ����� ����
					number[j - 1] = result;	//���������� ��������� ���������� � ����� number �� ������� ������ �����, ��� � � �������� �������� ����� ������������ ������ ��� ����������
				} //��������� ������ �� ����� �� ������� ��������� �������� ���������, ����� ����� �� ������ ��� ��������� � �������� � result, ������ ����� ��������� ����� ��������� ����������� ������� � ������������ �����������
				result = calcOper(result, *(str + i), calculate(str, i + 1, endStr, error), error); //��������� ��� ����� ����� ���������� � ����� ��������� ������� ������� � ���������� � result
				if (error > 0) return 0; //���� ��������� ������ ��� ��������
				return result;	//���������� ��������� ����������
			}
		}
	}
	if (operationPos) { //��� ���������� ����� ������ ���������� ����������� �������� � ���������� ������� � ������� number � operation
		//(� ������ ����� ������ ��� ������ ������ � �� �� ����� �������� � ������� ��� ������ ����������� ��� ����������) 
		for (int j = operationPos; j > 0; j--) {
			result = calcOper(number[j - 1], *(str + operation[j - 1]), number[j], error);
			number[j - 1] = result;
		}
	}
	if (error > 0) return 0; //���� ��������� ������ ��� ��������
	return result; //���������� ��������� ����������
}

int priority(char symbol) //������� ��� ����������� ���������� ��������
{
	if (symbol == '(' || symbol == ')')	//���� ������ ����� ���������� "1" (� ������ ��������� ������������ ������ ��� ����������� ����� ������� ������)
		return 1;
	//���������� �������� � ����. ������������������ �� ������� � ��������: 
	else if (symbol == '+' || symbol == '-')	
		return 2;//������ ��������� ��������
	else if (symbol == '*' || symbol == '/')
		return 3;//������� ��������� ��������
	else if (symbol == '^')
		return 4;//������� ��������� ��������
	else
		return 0;//���� ������ ����� ��� "." ���������� "0" (� ������ ��������� ������������ ������ ��� ����������� ����� ������� ��������� ���������)
}

double calcOper(double num1, char operat, double num2, int &error) { //������� ������������ ����������
	switch (operat)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		if (num2 == 0) { //���� ������� �� "0"
			error = 1;	//������������� ����� ������
			return 0;	//���������� "0"
		}
		return num1 / num2;	//��� ���������� ��������� �������
	case '^':
		return pow(num1, num2);
	}
}