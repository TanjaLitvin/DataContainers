#include<iostream>
using namespace std;

//#define BASE_CHECK
//#define COPYCONSTRUCTOR_CHECK
//#define OPERATORS_CHECK

template<typename T>class List;


template<typename T>

class Element
{
	T Data;      //�������� ��������
	Element<T>* pNext;  //����� ���������� ��������
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
		cout << "EConstructor:\t" << this << endl;
	}

	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List<T>;
	//friend List<T> operator+(const List<T>& left, const List<T>& right);
};
template<typename T>
int Element<T>::count = 0;

template<typename T>

class List
{
	Element<T>* Head; //����� ������ ������
	int size; //������ ������
public:
	int get_size()const
	{
		return this->size;
	}
	List()
	{
		this->Head = nullptr;
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(int size) :List()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(0);
	}

	List(initializer_list<T>il) :List()   //������������� "{}"                                                          
	{
		for (T const * it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	List(const List<T>& other)
	{
		this->Head = nullptr;
		this->size = 0;
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyConstructor:\t" << this << endl;
	}

	List(List&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "LMoveConstructor" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//   Operators

	T& operator[](int Index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;

	}
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	List<T>& operator=(List<T>&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}
	//   Adding elements:
	void push_front(T Data)
	{
		//1)������� ����� �������:
		Element<T>* New = new Element<T>(Data);
		//2)"����������� ����� ������� � ������(Head)":
		New->pNext = Head;
		//3)������ ��������� �� ����� �������:
		Head = New;
		size++;

	}
	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element<T>* Temp = Head; //1)������� �� ����� ������:
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//2)��������� �������:
		Temp->pNext = new Element<T>(Data);
		size++;
	}

	//  Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element<T>* Temp = Head; //1) ���������� ����� ���������� ��������:
		Head = Head->pNext;   //2) ��������� ������� �� ������:
		delete Temp;          //3) ������� ������� �� ������:
		size--;
	}
	void pop_back()
	{
		//	if (Head == nullptr)return;  //���� ������ ����,������� �� ���� ������,������� ����� �� ������� �� ������
		//	if (Head->pNext == nullptr)
		//	{
		//		pop_front();
		//		return;
		//	}

		if (Head == nullptr || Head->pNext == nullptr)
		{
			pop_front();
			return;
		}

		Element<T>* Temp = Head;  //������� �� ����� ������
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext; //������� �������
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Index, T Data)
	{

		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index >= size)
		{
			push_back(Data);
			return;
		}
		//1)����� �� ������ �������
		Element<T>* Temp = Head;

		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//2)��������� ����� �������
		Element<T>* New = new Element<T>(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index == size - 1)
		{
			pop_back();
			return;
		}
		if (Index >= size)
		{
			return;
		}

		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element<T>* to_del = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete to_del; size--;
	}
	void print()
	{
		//1)������� ��������
		Element<T>* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "���������� ��������� ������:\t" << size << endl;
	}
	friend List<T> operator+(const List<T>& left, const List<T>& right);
};

//template<typename T>

//List<T> operator+(const List<T>& left, const List<T>& right)
//{
//	List result = left;
//	for (Element<T>* Temp = right.Head; Temp; Temp = Temp->pNext)
//		result.push_back(Temp->Data);
//	return result;
//}
void main()
{
	setlocale(LC_ALL, "");
	int n;
#ifdef BASE_CHECK


	cout << "Vvedite razmer spiska:\t"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_front(555);
	list.print();
	list.pop_front();
	list.print();
	list.push_back(555);
	list.print();
	list.pop_back();
	list.push_back(555);

	list.print();
	list.pop_front();
	list.pop_front();

	list.pop_back();
	list.print();
	List list2;
	for (int i = 0; i < 3; i++)
	{

		list2.push_back(rand());
	}
	list2.print();
	int Index;
	int Data;
	cout << "������� ������ ������������ ��������:\t"; cin >> Index;
	cout << "������� ��������  ������������ ��������:\t"; cin >> Data;
	list.insert(Index, Data);
	list.print();
	cout << "������� ������ ���������� ��������:\t"; cin >> Index;

	list.erase(Index);
	list.print();

#endif // BASE_CHECK

#ifdef COPYCONSTRUCTOR_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	list1 = list1;
	for (int i = 0; i < list1.get_size(); i++)
	{
		cout << list1[i] << "\t" << endl;
	}
	List<int> list2;
	list2 = list1;
	list2.print();

#endif // COPYCONSTRUCTOR_CHECK

#ifdef OPERATORS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	list1.print();
	List<int> list2 = { 34,55,89 };
	list2.print();
	List<int> list3 = list1 + list2;
	list3.print();

#endif // OPERATORS_CHECK

	List<double> dbl_list = { 2.5,3.14,8,2 };
	dbl_list.print();
}