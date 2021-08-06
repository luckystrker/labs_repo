#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct list{
  int field; // ���� ������
  struct list *next; // ��������� �� ��������� �������
  struct list *prev; // ��������� �� ���������� �������
};


struct list * init(int a){  // �- �������� ������� ����
  struct list *lst;
  // ��������� ������ ��� ������ ������
  lst = (struct list*)malloc(sizeof(struct list));
  lst->field = a;
  lst->next = lst; // ��������� �� ��������� ����
  lst->prev = lst; // ��������� �� ���������� ����
  return(lst);
}

struct list * addelem(list *lst, int number){
  struct list *temp, *p;
  temp = (struct list*)malloc(sizeof(list));
  p = lst->next; // ���������� ��������� �� ��������� ����
  lst->next = temp; // ���������� ���� ��������� �� �����������
  temp->field = number; // ���������� ���� ������ ������������ ����
  temp->next = p; // ��������� ���� ��������� �� ��������� ����
  temp->prev = lst; // ��������� ���� ��������� �� ���������� ����
  p->prev = temp;
  return(temp);
}

void deletelem(list*& phead, int key) // �������� ������� �������� � ��������� ���������
{
	if (phead == NULL)return;
	list* p = phead, * found = NULL;
	do
	{
		if (p->field == key)
		{
			found = p;
			break;
		}
		p = p->next;
	} while (p != phead);
	if (found == NULL)
	{
		cout << "Element not found\n";
		return;
	}
	if (found == phead)
	{
		list* plast = phead;
		do
		{
			plast = plast->next;
		} while (plast->next != phead);
		if (phead == phead->next)phead = NULL;
		else phead = phead->next;
		plast->next = phead;
		delete found;
		return;
	}
	if (found->next == phead)
	{
		list* pplast = phead;
		do
		{
			pplast = pplast->next;
		} while (pplast->next->next != phead);
		pplast->next = phead;
		delete found;
		return;
	}
	list* pplast = phead;
	do
	{
		pplast = pplast->next;
	} while (pplast->next != found);
	pplast->next = found->next;
	delete found;
	return;
}

void listprint(list *lst){ // ����� ������
  struct list *p;
  p = lst;
  do {
    printf("%d ", p->field); // ����� �������� �������� p
    p = p->next; // ������� � ���������� ����
  } while (p != lst); // ������� ��������� ������
  cout << endl;
}

void search(list* ph, int key)  // ����� �������� �� ���������� ��������
{
	int a = 1;
	list* p = ph, * found = NULL;
	do
	{
		if (p->field == key)
		{
			found = p;
			break;
		}
		p = p->next;
		a++;
	} while (p != ph);
	if (found == NULL)
	{
		cout << "Element not found\n";
		return;
	}
	cout << a << endl;
}


struct list* initList(char*filename) {  // ������������� ������
	ifstream input;
	input.open(filename, ios_base::in);
	int a;
	input >> a;
	cout << a << " ";
	list *lst = init(a);
	while(!input.eof()) {
		input >> a;
		cout << a << " ";
		addelem(lst, a);
	}
	cout << endl;
	input.close();
	return lst;
}

void sort(list* Head)
{
	while (true)
	{
		bool swapped = false;

		list* p = Head;
		while (p->next->field != Head->field)
		{
			if (p->field > p->next->field) {
				double tmp = p->field;
				p->field = p->next->field;
				p->next->field = tmp;
				swapped = true;
			}
			p = p->next;
		}


		if (!swapped) break;
	}

}



int main() {
	char * filename;
	int num;
	filename = (char*)malloc(100*sizeof(int));
	cout << "Hello, it's fourth and fifth lab. Enter the name of file: ";
	cin >> filename;
	list *head, *cur;
	head = initList(filename);
	int choice = 0;
	cout << "File opened and entered" << endl << "What would you want now?" << endl << "1 - add new element, 2 - delete an element, 3 - sort list," << endl << "4 - output the list, 5- find element in list, 228 - exit the program" << endl;
	while (choice != 228) {
		cin >> choice;
		switch(choice) {
			case 1:
				cout << "Enter the element: ";
				cin >> num;
				addelem(head, num);
				break;
			case 2:
				cout << "Enter the element: ";
				cin >> num;
				deletelem(head, num);
				break;
			case 3:
				sort(head);
				cout << "List sorted" << endl;
				break;
			case 4:
				listprint(head);
				break;
			case 5:
				cout << "Enter the element: ";
				cin >> num;
				search(head, num);
				break;
			case 228: 
				cout << "Bye!";
				break;
			default:
				cout << "Wrong input!";
				break;
		} 
	}
	return 0;
}
