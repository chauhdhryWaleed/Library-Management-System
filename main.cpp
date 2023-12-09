
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<Windows.h>
#include<conio.h>
#include<list>
using namespace std;


class book {

private:

	int issn;
	string title;
	int copiesAvailableAsReferenceBook, copiesAvailableAsIssuableBook;

	string* listofauthors;
	int noofauthors;



public:


	book()
	{
		issn = 0;
		title = " ";
		copiesAvailableAsIssuableBook = copiesAvailableAsReferenceBook = 0;
		listofauthors = nullptr;
		noofauthors = 0;

	}
	book(int a, string x, int b, int c, string* list, int e)
	{
		issn = a;
		title = x;
		copiesAvailableAsReferenceBook = b;
		copiesAvailableAsIssuableBook = c;
		noofauthors = e;
		for (int i = 0; i < e; i++)
		{
			listofauthors[i] = list[i];
		}
	}



	void bookinfo()
	{

		cout << "Enter issn of book " << endl;
		cin >> issn;

		cout << "enter the title of book " << endl;
		cin >> title;

		cout << "enter copies available as refernce" << endl;
		cin >> copiesAvailableAsReferenceBook;


		cout << "enter copies available as issueable" << endl;
		cin >> copiesAvailableAsIssuableBook;
		cout << "enter no of authors " << endl;
		cin >> noofauthors;

		listofauthors = new string[noofauthors];
		for (int i = 0; i < noofauthors; i++)
		{
			cout << "enter name of author no " << i + 1 << endl;
			cin >> listofauthors[i];
		}

	}

	int getissn()
	{
		return issn;
	}

	void Display()
	{
		cout << "\t \t The ISSN no of book is : ";
		cout << issn << endl;
		cout << endl;
		cout << "\t \t The title of book is : ";
		cout << title << endl;
		cout << endl;
		cout << "\t \t Authors of book are : ";

		for (int i = 0; i < noofauthors; i++)
		{
			cout << i + 1 << ")" << listofauthors[i] << " ";
		}
		cout << endl;
		cout << endl;
		cout << "\t \t No of issueable books are : ";
		cout << copiesAvailableAsIssuableBook << endl;
		cout << endl;
		cout << "\t \t No of reference books are : ";
		cout << copiesAvailableAsReferenceBook << endl;
		cout << endl;
		cout << endl;
	}
	void change()
	{
		int chose;

		do {
			cout << "Press 1 if you want to change the name of book " << endl;
			cout << "PRESS 2 if you want to change the no of issuable books" << endl;
			cout << "PRESS 3 if you want to change the no of reference books" << endl;
			cout << "PRESS 4 if you want to change the name of author " << endl;
			cin >> chose;

			if (chose == 1)
			{
				string a;
				cout << "Enter the new name of book " << endl;
				cin >> a;
				settitle(a);
			}
			if (chose == 2)
			{
				int a;
				cout << "Enter the new no of issuable books " << endl;
				cin >> a;
				setISSUABLEBOOKS(a);

			}

			if (chose == 3)
			{
				int a;
				cout << "Enter the new no of reference books " << endl;
				cin >> a;
				setREFBOOKS(a);
			}

			if (chose == 4)
			{
				cout << "Enter the new no of authors for the book " << endl;
				int x;
				cin >> x;
				string* arr = new string[x];

				for (int i = 0; i < x; i++)
				{
					cout << "Enter the name of author number " << i + 1 << endl;
					cin >> arr[i];
				}

				setLISTauthors(arr, x);
			}

		} while (chose < 1 || chose>4);


	}
	void settitle(string a)
	{
		title = a;
	}

	void setREFBOOKS(int x)
	{
		copiesAvailableAsReferenceBook = x;
	}
	void setISSUABLEBOOKS(int x)
	{
		copiesAvailableAsIssuableBook = x;
	}
	void setLISTauthors(string* arr, int a)
	{
		listofauthors = new string[a];
		noofauthors = a;
		for (int i = 0; i < a; i++)
		{
			listofauthors[i] = arr[i];
		}
	}
	bool operator ==(const book& b)const
	{
		if (b.issn == this->issn)
		{
			return true;
		}
		else
			return false;
	}
	friend ostream& operator <<(ostream& i, book b)
	{
		b.Display();
		return i;
	}

};


class hashtable {



private:

	int NoOfCurrentElements;
	int TotalCapacity;
	vector<list<book>>HASHTABLE;


public:


	hashtable()
	{
		NoOfCurrentElements = 0;
		TotalCapacity = 7;

		HASHTABLE.resize(7);

	}
	hashtable(int a)
	{
		NoOfCurrentElements = 0;
		TotalCapacity = a;

		HASHTABLE.resize(a);


	}


	bool loadsize()
	{
		if (NoOfCurrentElements < (TotalCapacity / 2)) //loadfactor is smaller than 0.5
		{
			return true;
		}
		else  //else loadfactor is greater than 0.5 we will need to double the capacity
			return false;
	}

	void insert(book obj)
	{
		if (loadsize() == false) // if loadfactor greater than 0.5 than we assign a newsize(prime no) greater than double the previous size 
		{

			int newsize = getnewsize();
			HASHTABLE.resize(newsize);

			rehash(HASHTABLE, newsize);// we create a new hashtable and rehash the previous elemts in to new one and then assign that new table to previous one
		}
		int index = hashfun(obj.getissn());
		HASHTABLE[index].push_back(obj);
		NoOfCurrentElements++;

	}

	void rehash(vector<list<book>>obj, int a)
	{
		vector<list<book>>temp;
		temp.resize(a);



		for (int i = 0; i < TotalCapacity; i++)
		{
			while (!HASHTABLE[i].empty()) //checks if list is empty or not
			{
				//using vector funs to pop the previous book objs from the list to insert in the new one
				book b = HASHTABLE[i].back();
				HASHTABLE[i].pop_back();

				int index = hashfun(b.getissn());
				temp[index].push_back(b);


			}
		}

		HASHTABLE.clear();// clearing the previous one
		HASHTABLE = temp;


	}

	void REMOVE(int issn)// removes the book record
	{
		int index = hashfun(issn);


		list<book>::iterator i; //using iterator for traversing on the list


		bool found = false;
		for (i = HASHTABLE[index].begin(); i != HASHTABLE[index].end(); i++)
		{
			book b = *i;
			if (b.getissn() == issn)
			{
				found = true;
				HASHTABLE[index].remove(b);
				cout << "book with issn " << issn << " has been removed " << endl;
				break;
			}



		}
		if (!found)
		{
			cout << "book with issn " << issn << " was not found in the records " << endl;
		}

	}


	void search(int issn)// search a book record
	{
		int index = hashfun(issn);


		list<book>::iterator i;

		bool found = false;

		for (i = HASHTABLE[index].begin(); i != HASHTABLE[index].end(); i++)
		{
			book b = *i;
			if (issn == b.getissn())
			{
				found = true;
				cout << *i;
				break;
			}
		}
		if (!found)
		{
			cout << "book with issn " << issn << " was not found in the book records " << endl;
		}



	}

	void modify(int issn) // modifes record of a book
	{
		int index = hashfun(issn);


		list<book>::iterator i;

		bool found = false;

		for (i = HASHTABLE[index].begin(); i != HASHTABLE[index].end(); i++)
		{
			book b = *i;
			if (issn == b.getissn())
			{
				found = true;

				b.change();

				*i = b; //assigning the modified value 
				break;
			}
		}
		if (!found)
		{
			cout << "book with issn " << issn << " was not found in the book records " << endl;
			cout << endl;
		}

	}





	int getnewsize() // generating a prime no greater than twice the size of table
	{
		int i = TotalCapacity * 2 + 1;


		for (int j = i; j < 6 * i + 1; j++)
		{
			if (checkprime(j))
			{
				i = j;
				break;
			}
		}
		TotalCapacity = i;
		return i;
	}

	int hashfun(int issn)
	{

		srand(issn);

		int a = rand() % issn;
		if (a == 0)  // A should not be zero
		{
			while (a == 0)
			{
				a = rand() % issn;
			}
		}
		int b = rand() % issn;



		int p = generateprime(issn);  // it will generate a prime no


		return (((a * issn + b) % p) % TotalCapacity);

	}


	int generateprime(int limit) //will generate a prime greater than the issn no 
	{
		int prime = limit + 1;

		while (1)
		{
			if (checkprime(prime))
			{
				break;
			}
			else
				prime++;
		}
		return prime;
	}
	bool checkprime(int n)
	{
		if (n <= 1)
		{
			return false;
		}

		for (int i = 2; i <= sqrt(n); i++)
		{
			if (n % i == 0)
			{
				return false;
			}
		}
		return true;




	}

	~hashtable()
	{
		HASHTABLE.clear();
	}

};

int main()
{


	hashtable h;

	int choice;
	do
	{
		book obj;
		cout << "\t \t \t WELCOME TO Chaudhry's LIBRARY " << endl;
		cout << endl;
		cout << endl;
		cout << "IF you want to ADD a new book record PRESS 1 " << endl;
		cout << endl << endl;
		cout << "IF you want to REVIEW book record PRESS 2 " << endl;
		cout << endl << endl;
		cout << "IF you want to UPDATE book record PRESS 3 " << endl;
		cout << endl << endl;
		cout << "IF you want to DELETE a book record PRESS 4 " << endl;
		cout << endl << endl;

		cout << "IF you want to TERMINATE PRESS -1 " << endl;
		cin >> choice;
		cout << endl;


		if (choice == 1)
		{
			obj.bookinfo();
			h.insert(obj);

		}
		if (choice == 2)
		{
			cout << "Enter the issn against which you want to search a record " << endl;
			int a;
			cin >> a;
			h.search(a);

		}
		if (choice == 3)
		{

			cout << "enter the issn against which you want to modify a record " << endl;
			int a;
			cin >> a;
			h.modify(a);

		}
		if (choice == 4)
		{
			cout << "enter the issn against which you want to delete record " << endl;
			int a;
			cin >> a;
			h.REMOVE(a);

		}




	} while (choice != -1);


}
