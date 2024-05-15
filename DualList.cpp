#include<iostream>
#include<stdexcept>
using namespace std;

template<typename T>
class LinkList;

template<typename T>
class ListNode
{
	friend class LinkList<T>;
public:
	ListNode(T t) :val(t), prev(NULL), next(NULL) {}
	ListNode() :val(0), prev(NULL), next(NULL) {}
private:
	T val;
	ListNode* prev;
	ListNode* next;
};


template<typename T>
class LinkList
{
	friend ostream& operator<<(ostream& out, LinkList<T>& l);   //直接打印链表
	friend class ListNode<T>;
public:
	LinkList()
	{
		this->length = 0;
		this->head = NULL;
		this->tail = NULL;
	}
	~LinkList()
	{
	    /*ListNode<T>* temp1 = head;
		ListNode<T>* temp2 = head;
		while (temp1 || temp1->next = temp2)
		{
			ListNode<T>* curr = temp1->next;
			delete temp1;
			temp1 = curr;
		}*/
	}
	//增
	ListNode<T>* CreateNode(const T& x);
	void PushBack(const T& x);		//尾插

	void PushFront(const T& x); //头插

	void Insert_pos(size_t pos, const T& x);
	void Insert_val(const T& n, const T& x);
	
	//删
	void PopBack();		//尾删
	void PopFront();            //头删
	void Delete_pos(size_t pos);
	void Delete_val(const T& x);

	//查
	ListNode<T>* Find(const T& x);


	ListNode <T>* Reverse();
	int Length();		//求表长
	void clear(ListNode<T>*& cur);
	void Print();
private:
	ListNode<T>* head; 
	ListNode<T>* tail;
	int length;
};

template<class T>
ostream& operator<<(ostream& out, LinkList<T>& l)
{
	ListNode<T>  *tmp = l._head;
	out << "List>>>:" ;
	while (tmp != NULL)
	{
		out << tmp->_data << "<-->";
		tmp = tmp->_next;
	}
	out << "NULL" << endl;
	return out;
}


template<typename T>
ListNode<T>* LinkList<T>::CreateNode(const T& x)
{
	ListNode<T>* newNode = new ListNode<T>(x);
	return newNode;
}

template<typename T>
void LinkList<T>::PushBack(const T& x) 	//尾插
{
	ListNode<T>* newNode=this->CreateNode(x);
	if (head==NULL)         //head==NULL
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	this->length++;
}

template<typename T>
void LinkList<T>::PushFront(const T& x) //头插
{
	ListNode<T>* newNode = this->CreateNode(x);
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
	this->length++;
}

template<typename T>
void LinkList<T>::Insert_pos(size_t pos, const T& x)
{
	if (pos<0 || pos>length)
	{
		throw std::out_of_range("Invaild Position");
	}
	if (head == NULL)
	{
		throw std::out_of_range("List is empty!!!");
	}
	ListNode<T>* begin = head;
	while (--pos)
	{
	   begin = begin->next;	
	}
	if (begin->next == NULL)
	{
		this->PushBack(x);
	}
	else
	{
		ListNode<T>* newNode = this->CreateNode(x);
		newNode->next = begin->next;
		begin->next->prev = newNode;   //差点少了
		begin->next = newNode;
		newNode->prev = begin;

	}
	this->length++;
}

template<typename T>
void LinkList<T>::Insert_val(const T& n, const T& x)
{
	if (head == NULL)
	{
		throw std::out_of_range("List is empty!!!");
	}
	if (Find(x) == NULL)
	{
		return;
	}
	else
	{
		ListNode<T>* now = this->Find(x);
		if (now == NULL)
		{
			return;
		}
		else
		{
			ListNode<T>* tmp = CreateNode(x);
			tmp->next = now->next;
			now->next = tmp;
		}
	}
	this->length++;
}


template<typename T>
void LinkList<T>::PopBack()	//尾删
{
	if (head == NULL)
	{
		throw std::out_of_range("List is empty!!!");
	}
	else if (head->next == NULL)
	{
		this->clear(head);
	}
	else
	{
		ListNode<T>* temp = tail;
		tail = tail->prev;
		clear(temp);
		tail->next = NULL;
	}
	this->length--;
}

template<typename T>
void LinkList<T>::PopFront()           //头删
{
	if (head == NULL)
	{
		throw std::out_of_range("List is empty!!!");
	}
	else if (head->next == NULL)
	{
		this->clear(head);
		this->length--;
	}
	else
	{
		ListNode<T>* temp = head;
		head = temp->next;
		clear(temp);
		temp = NULL;
		head->prev = NULL;
		this->length--;
	}
	
}

template<typename T>
void LinkList<T>::Delete_pos(size_t pos)
{
	if (pos <= this->length)
	{
	if (head == NULL)
	{
		cout << "List is empty!!!" << endl;
		return;
	}
	else if (head->next == NULL && pos == 1)
	{
		clear(head);
		this->length--;
	}
	else
	{
		ListNode<T>* begin = head->next;
		ListNode<T>* tmp = head;
		if (pos == 1)
		{
			this->PopFront();
		}
		else
		{
			pos = pos - 1;
			while (--pos)
			{
				if (begin->next != NULL)
				{
					begin = begin->next;
					tmp = tmp->next;
				}
			}
			tmp->next = begin->next;
			begin->next = tmp;
			this->length--;
		}
	}
	}
}

template<typename T>
void LinkList<T>::Delete_val(const T& x)
{
	if (head == NULL)
	{
		throw std::out_of_range("List is empty!!!");
	}
	else if (head->next == NULL && head->val == x)
	{
		clear(head);
		this->length--;
		return;
	}
	else
	{
		if (head->val == x)
		{
			PopFront();
			this->length--;
			return;
		}
		else
		{
			ListNode<T>* now = Find(x);
			if (now != NULL)
			{
				if (now->next == NULL)
				{
					PopBack();
					return;
				}
				if (now->next != NULL)
				{
					ListNode<T>* temp = now;
					now->prev->next = now->next;
					now->prev = now->next->prev;
					clear(now);
					return;
				}
			}
		}
	}
}

//——————————————————————————————
template<typename T>
void LinkList<T>::clear(ListNode<T>*& cur)
{
	cur->next = NULL;
	delete cur;
	cur = NULL;
}


template<typename T>
ListNode<T>* LinkList<T>::Find(const T& x)
{
	if (head == NULL)
	{
		throw std::out_of_range("List is empty!!!");
	}
	ListNode<T>* begin = head;
	while (begin->next)
	{
		if (begin->val == x)
		{
			return begin;
		}
		begin = begin->next;
	}
	return NULL;
}

template<typename T>
ListNode <T>* LinkList<T>::Reverse()
{
	if (head == NULL || head->next == NULL)
	{
		return NULL;
	}
	else
	{
		ListNode<T>* Newhead = head;
		ListNode<T>* Newtail = head;
		ListNode<T>* begin = head->next;
		ListNode<T>* tmp = NULL;
		head->next = NULL;
		while (begin)
		{
			tmp = begin;
			begin = begin->next;
			tmp->next = Newhead;
			Newhead->prev = tmp;
			Newhead = tmp;
		}
		this->head = Newhead;
		this->tail = Newtail;
	}
	return head;
}

template<typename T>
int LinkList<T>::Length()
{
	return this->length;
}

template<typename T>
void LinkList<T>::Print()
{
	ListNode<T>* src = head;
	cout << "List>>>:  ";
	while (src != NULL)
	{
		cout << src->val << "<-->";
		src = src->next;
	}
	cout << "NULL" << endl;
}

void Test1()
{
	LinkList<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();


	l.PopBack();
	l.PopBack();
	l.Print();
	l.PopBack();
	l.PopBack();
	l.Print();

    l.PushFront(1);
	l.PushFront(2);
	l.Print();
	l.PushFront(3);
	l.PushFront(4);
	l.Print();


	l.PopFront();
	l.Print();

	l.PopFront();
	l.PopFront();
	l.Print();
	
	l.PopFront();
	l.Print();
}
void Test2()
{
	LinkList<int> s;
	s.PushBack(1);
	s.PushBack(2);
	s.PushBack(3);
	s.PushBack(4);
	s.PushBack(5);
	s.Print();

	s.Find(4);
	s.Insert_pos(2, 6);
	s.Print();

	s.Insert_val(3, 7);
	s.Print();
	s.Delete_pos(10);
	s.Print();


	s.Delete_val(2);
	s.Print();

	s.Reverse();
	s.Print();
	
}
int main()
{
	//Test1();
	//Test2();
	LinkList<int> mylist;
	int select = 1;
	int Item;
	int pos;
flag:
	cout << endl << endl;;
	cout << "	* * * * * * * welcome to use  List  * * * * * * * *" << endl;
	void Menu();
	{
		cout << "	*	1. PushBack		2. PushFront      *" << endl;
		cout << "	*	3. Print		4. PopBack        *" << endl;
		cout << "	*	5. PopFront		6. Insert_pos     *" << endl;
		cout << "	*	7. Insert_val	        8. Delete_pos     *" << endl;
		cout << "	*	9. Delete_val	        10.Find           *" << endl;
		cout << "	*	11. length		12.clear	  *" << endl;
		cout << "	*	13. reverse		14.sort		  *" << endl;
		cout << "	*	15. clear	         0.exit		  *" << endl;
		cout << "	*        		    			  *" << endl;
		cout << "	*       Please select:			          *" << endl;
		cout << "	* * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	}
	while (select)
	{
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "请输入要后插的值(-1结束):>";
			while (cin >> Item, Item != -1)
			{
				mylist.PushBack(Item);
			}
			break;
		case 2:
			cout << "请输入要头插的值(-1结束):>";
			while (cin >> Item, Item != -1)
			{
				mylist.PushFront(Item);
			}
			break;
		case 3:
			mylist.Print();
			break;
		case 4:
			mylist.PopBack();
			break;
		case 5:
			mylist.PopFront();
			break;
		case 6:
			cout << "请输入要插入的位置:>";
			cin >> pos;
			cout << "请输入要插入的值:>";
			cin >> Item;
			mylist.Insert_pos(pos, Item);
			break;
		case 7:
			cout << "请输入要在i后插入的值:>";
			cin >> pos;
			cout << "请输入要插入的值x:";
			cin >> Item;
			mylist.Insert_val(pos, Item);
			break;
			break;
		case 8:
			cout << "请输入要删除的位置:>";
			cin >> pos;
			mylist.Delete_pos(pos);
			break;
		case 9:
			cout << "请输入要删除的值:>";
			cin >> Item;
			mylist.Delete_val(Item);
			break;
		case 10:
			cout << "请输入要查找的值:>";
			cin >> Item;
			mylist.Find(Item);
			break;
		case 11:
			mylist.Length();
			break;
		case 12:
			//mylist.clear();
			break;
		case 13:
			mylist.Reverse();
			break;
		case 14:
			//mylist.sort(/*0,a-1*/);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
		cout << endl;
		goto flag;
	}
	system("pause");
	return 0;
}