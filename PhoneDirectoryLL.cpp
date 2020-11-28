// Program to implement a phone directory

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int BUFFERSIZE = 30;	// Maximum size for a name/category
const int PHONESIZE = 13;	// Maximum size for a phone number

// Structure used to define a phone directory entry
struct PDEntry
{
	char name[BUFFERSIZE];
	char phone[PHONESIZE];
	char category[BUFFERSIZE];
};

// type definition to define the data type for the list data
typedef PDEntry ListItemType;

// create the node structure
struct Node
{
	ListItemType item;
	Node* next;
};

//function identifiers
void displayWithNums(Node* head);

void displayAll(Node* head);

void updateEntry(Node** head);

Node* find(Node* head, int entryNum);

void addEntry(Node** head, ListItemType newData);

void clearList(Node** head);

void removeEntry(Node** head);

void getFile(Node** head);

void writeToFile(Node* head);

void displayCategory(Node* head);

ListItemType userAdd();

int main()
{
	int choice;

	Node* head = NULL;

	getFile(&head);
	system("cls");
	do
	{
		cout << "1. Add Entry\n";
		cout << "2. Change Entry\n";
		cout << "3. Display Names in Category\n";
		cout << "4. Display All\n";
		cout << "5. Remove Entry\n";
		cout << "6. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Gets the numeric entry from the menu
		cin >> choice;

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		cin.ignore();

		switch (choice)
		{
		case 1:
			addEntry(&head, userAdd());
			
			break;
		case 2:
			updateEntry(&head);
			break;
		case 3:
			displayCategory(head);
			break;
		case 4:
			displayAll(head);
			break;
		case 5:
			removeEntry(&head);
			break;
		}

	} while (choice != 6);

	writeToFile(head);
	clearList(&head);

	return 0;
}

//returns user input for a new directory entry
ListItemType userAdd() 
{
	//gets user input for the new entry
	ListItemType Add;
	cout << "What name would you like to add?\n";
	cin.getline(Add.name, BUFFERSIZE);
	cout << "\nWhat number would you like to add?\n";
	cin.getline(Add.phone, PHONESIZE);
	cout << "\nWhat category would you like to add?\n";
	cin.getline(Add.category, BUFFERSIZE);

	//returns the entire new entry
	return Add;
}

//adds new entry to the directory
void addEntry(Node** head, ListItemType newData)
{
	//creates a new node with new data, then inserts it into the first
	//position in the linked list
	Node* newNode = new Node();
	newNode->item = newData;
	newNode->next = *head;
	*head = newNode;
	cout << "\nEntry was successfully added.\n\n";
}

//removes the entry the user tells to remove
void removeEntry(Node** head)
{
	//Checks to see if there is anything in the directory and prints an error if it is empty
	if(*head == NULL)
	{
		cout << "\nERROR: No entries in directory.\n";
	}
	else 
	{
		int key;
		cout << "What entry number would you like to remove?\n";

		displayWithNums(*head);
		cin >> key;

		Node* temp = *head;

		Node* deleteNode = find(*head, key);
		//if the delete node is in the directory
		if (deleteNode != NULL) {
			//if the node is the first entry
			if (key == 1)
			{
				*head = temp->next;
			}
			else
			{
				//change the path from the previous node to the node 2 after it
				//to skip over the now deleted node
				Node* changePTR = find(*head, key - 1);
				changePTR->next = changePTR->next->next;
			}
			
			//deletes the specified entry from memory
			delete deleteNode;
			cout << "Entry was successfully deleted.\n";
		}
	}
	cout << "\n";
}

//finds node that user tells to find
Node* find(Node* head, int entryNum) 
{
	Node* temp = head;
	// Seaches the nodes one by one starting from head for the entered number.
	for(int i = 1; i < entryNum; i++ ) 
	{
		// Ends the search with an Error if it reaches the end without finding.
		if (temp->next == NULL) 
		{
			cout << "\nThe number you entered was not in the directory.\n";
			return NULL;
		}
		// Moves to the next node in list.
		else 
		{
			temp = temp->next;
		}
	}
	// returns found node.
	return temp;
}

//updates the entry the user tells to change
void updateEntry(Node** head)
{
	//Checks to see if there is anything in the directory and prints an error if it is empty
	if (*head == NULL)
	{
		cout << "\nERROR: No entries in directory.\n\n";
	}
	else
	{
		cout << "What entry would you like to update?\n\n";

		displayWithNums(*head);

		int key;
		cin >> key;

		Node* temp = find(*head, key);
		//if the number entered is outside the linked list
		if (temp != NULL) 
		{
			//display the specified entry's data one at a time and let user choose which to edit
			cout << "Enter the line number you wish to change:\n";
			printf("\n1. %20s", temp->item.name);
			printf("\n2. %20s", temp->item.phone);
			printf("\n3. %20s", temp->item.category);
			printf("\n\n");
			int lineNum;
			cin >> lineNum;

			//initializes userchange to the entry's original data
			ListItemType userChange;
			snprintf(userChange.name, BUFFERSIZE, temp->item.name);
			snprintf(userChange.phone, PHONESIZE, temp->item.phone);
			snprintf(userChange.category, BUFFERSIZE, temp->item.category);

			cin.ignore();
			//switch based off the user input for which entry's data to change
			switch (lineNum)
			{
			case 1:
				cout << "What would you like to change the name to?\n";
				cin.getline(userChange.name, BUFFERSIZE);
				break;
			case 2:
				cout << "What would you like to change the phone number to?\n";
				cin.getline(userChange.phone, PHONESIZE);
				break;
			case 3:
				cout << "What would you like to change the category to?\n";
				cin.getline(userChange.category, BUFFERSIZE);
				break;
			default:
				cout << "That was not an option.\n";
				break;
			}

			//change the entries data to the new data
			temp->item = userChange;
			cout << "\nEntry was successfully updated.\n\n";
		}
	}
}

//displays every entry in the linked list
void displayAll(Node* head)
{
	//if there aren't entries in the list, tell the user there are no entries
	if (head == NULL)
	{
		cout << "\nNo entries in directory.\n\n";
	}
	else 
	{
		printf("\nDirectory: \n\n");
		Node* current = head;

		//displays all the entries in the list
		while (current != NULL)
		{
			printf("%20s", current->item.name);
			printf("%20s", current->item.phone);
			printf("%20s", current->item.category);
			printf("\n");

			current = current->next;
		}
		printf("\n");
	}
}

//displays every entry in the linked list with a specific category
void displayCategory(Node* head)
{
	//if there are no entries in the list, tells the user there are no entires
	if (head == NULL)
	{
		cout << "\nNo entries in directory.\n\n";
	}
	//enters a catagory name
	else
	{
		bool categoryExists = false;
		char entryCat[BUFFERSIZE];
		printf("\nEnter category name\n");
		cin.getline(entryCat, BUFFERSIZE);
		printf("\n");

		Node* current = head;

		//displays each entry with the specified category
		while (current != NULL)
		{
			//checks if the specified category is the same as the category of the entry
			if (strcmp(current->item.category, entryCat) == 0)
			{
				printf("%20s", current->item.name);
				printf("%20s", current->item.phone);
				printf("%20s", current->item.category);
				printf("\n");
				categoryExists = true;
			}

			current = current->next;
		}
		//if the category doesn't exist then displays a message to the user
		if (!categoryExists) 
		{
			cout << "Category does not exist.\n";
		}
		printf("\n");
	}
}

//displays directory in linked list with numbers counting up
void displayWithNums(Node* head) 
{
	Node* current = head;
	int count = 1;

	//displays every entry with a number in front of it
	while (current != NULL)
	{
		printf("%5i.", count);
		printf("%20s", current->item.name);
		printf("%20s", current->item.phone);
		printf("%20s", current->item.category);
		printf("\n");
		count++;
		current = current->next;
	}
}

//Recursive function that deletes the entire linked list
void clearList(Node** head) 
{
	Node* current = *head;

	//if current node is not null it goes to the next node
	if (current != NULL) 
	{
		clearList(&current->next);
	}
	//after iterating through all the nodes it deletes them node by node starting from the last node
	delete current;
}

//writes the data.txt file to our linked list
void getFile(Node** head) 
{
	Node* temp = NULL;
	temp = *head;

	ifstream inFile;

	inFile.open("Data.txt");

	//checks if file is valid
	if (!inFile)
	{
		cout << "\nERROR: Input file cannot be opened.\n";
	}
	else 
	{
		ListItemType add;
		//gets every line of text from the file and puts it into the linked list
		while (!inFile.eof() && inFile.peek() != EOF)
		{
			inFile.getline(add.name, BUFFERSIZE);
			inFile.getline(add.phone, PHONESIZE);
			inFile.getline(add.category, BUFFERSIZE);
			addEntry(head, add);
		}
	}

	inFile.close();
}

//Writes to a file
void writeToFile(Node* head) 
{
	ofstream outFile;
	Node* temp = head;
	outFile.open("Data.txt");

	//if file is not open, it wont write to file
	if (!outFile) 
	{
		cout << "ERROR: File was not opened correctly.";
	}
	else 
	{
		//writes each entry into the file line by line
		while (temp != NULL)
		{
			outFile << temp->item.name << "\n";
			outFile << temp->item.phone << "\n";
			outFile << temp->item.category << "\n";
			temp = temp->next;
		}
	}
}