#include<iostream>
using namespace std;

//#define BASE_CHECK
#define COPYCONSTRUCTOR_CHECK
//#define OPERATORS_CHECK

class Element
{
	int Data;      //значение элемента
	Element* pNext;  //адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
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
	friend class List;
	friend List operator+(const List& left, const List& right);
};
int Element::count = 0;
class List
{
	Element* Head; //адрес начала списка
	int size; //размер списка
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
	List(initializer_list<int>il) :List()   //инициализация "{}"                                                          
	{
		for (int const * it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other)
	{
		this->Head = nullptr;
		this->size = 0;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
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

	int& operator[](int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;

	}
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}
	//   Adding elements:
	void push_front(int Data)
	{
		//1)создаем новый элемент:
		Element* New = new Element(Data);
		//2)"привязываем новый элемент к голове(Head)":
		New->pNext = Head;
		//3)голову переводим на новый элемент:
		Head = New;
		size++;

	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head; //1)доходим до конца списка:
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//2)Добавляем элемент:
		Temp->pNext = new Element(Data);
		size++;
	}

	//  Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* Temp = Head; //1) Запоминаем адрес удаляемого элемента:
		Head = Head->pNext;   //2) Исключаем элемент из списка:
		delete Temp;          //3) Удаляем элемент из памяти:
		size--;
	}
	void pop_back()
	{
		//	if (Head == nullptr)return;  //если список пуст,удалять из него нечего,поэтому сразу же выходим из метода
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

		Element* Temp = Head;  //Доходим до конца списка
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext; //удаляем элемент
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Index, int Data)
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
		//1)Дойти до нужной позиции
		Element* Temp = Head;

		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//2)Добавляем новый элемент
		Element* New = new Element(Data);
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

		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* to_del = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete to_del; size--;
	}
	void print()
	{
		//1)создаем итератор
		Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка:\t" << size << endl;
	}
	friend List operator+(const List& left, const List& right);
};

List operator+(const List& left, const List& right)
{
	List result = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);
	return result;
}
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
	cout << "Введите индекс добавляемого элемента:\t"; cin >> Index;
	cout << "Введите значение  добавляемого элемента:\t"; cin >> Data;
	list.insert(Index, Data);
	list.print();
	cout << "Введите индекс удаляемого элемента:\t"; cin >> Index;

	list.erase(Index);
	list.print();

#endif // BASE_CHECK

#ifdef COPYCONSTRUCTOR_CHECK
	List list1 = { 3,5,8,13,21 };
	list1 = list1;
	for (int i = 0; i < list1.get_size(); i++)
	{
		cout << list1[i] << "\t" << endl;
	}
	List list2;
	list2 = list1;
	list2.print();

#endif // COPYCONSTRUCTOR_CHECK

#ifdef OPERATORS_CHECK
	List list1 = { 3,5,8,13,21 };
	list1.print();
	List list2 = { 34,55,89 };
	list2.print();
	List list3 = list1 + list2;
	list3.print();

#endif // OPERATORS_CHECK
}
