#include<iostream>
#include<string>
using namespace std;

class Node {
public:
	int rollNumber;
	string name;
	Node* next;
};

class CircularLinkedList {
private:
	Node* LAST;

public:
	CircularLinkedList() {
		LAST = NULL;
	}
	void addNode();
	bool search(int rollno, Node** Haryadi, Node** Rangga);
	bool listEmpty();
	bool delNode();
	void traverse();

};

void CircularLinkedList::addNode() {
	Node* newnode = new Node();
	cout << "Enter roll number: ";
	cin >> newnode->rollNumber;
	cout << "Enter name: ";
	cin >> newnode->name;

	if (listEmpty()) { // Beginning of the list
		newnode->next = newnode;
		LAST = newnode;
	}
	else {
		Node* Haryadi = LAST;
		Node* Rangga = LAST->next;

		while (Rangga != LAST && Rangga->rollNumber < newnode->rollNumber) {
			Haryadi = Rangga;
			Rangga = Rangga->next;
		}

		if (Rangga == LAST && Rangga->rollNumber < newnode->rollNumber) { // End of the list
			newnode->next = LAST->next;
			LAST->next = newnode;
			LAST = newnode;
		}
		else { // Between two nodes in the list
			newnode->next = Rangga;
			Haryadi->next = newnode;
		}
	}

	cout << "Record added successfully!" << endl;
}

bool CircularLinkedList::search(int rollno, Node** Haryadi, Node** Rangga) {
	*Haryadi = LAST->next;
	*Rangga = LAST->next;

	while (*Rangga != LAST){
		if (rollno == (*Rangga)->rollNumber) {
			return true;
		}
		*Haryadi = *Rangga;
		*Rangga = (*Rangga)->next;
	}

	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}

bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}

bool CircularLinkedList::delNode() {
	if (listEmpty()) {
		cout << "List is empty. Deletion failed!" << endl;
		return false;
	}

	int rollno;
	cout << "Enter the roll number to delete: ";
	cin >> rollno;

	Node* Haryadi = NULL;
	Node* Rangga = NULL;

	if (search(rollno, &previous, &current)) {
		if (Rangga == LAST) { // Beginning of the list
			if (LAST->next == LAST) { // If LAST points to itself
				delete LAST;
				LAST = NULL;
				cout << "Record deleted successfully!" << endl;
				return true;
			}
			else {
				LAST->next = current->next;
				LAST = LAST->next;
				delete Rangga;
				cout << "Record deleted successfully!" << endl;
				return true;
			}
		}
		else { // Between two nodes in the list
			Haryadi->next = Rangga->next;
			delete Rangga;
			cout << "Record deleted successfully!" << endl;
			return true;
		}
	}
	else {
		cout << "Record not found. Deletion failed!" << endl;
		return false;
	}
}

void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecord in the list are:\n";
		Node* RanggaNode = LAST->next;
		while (RanggaNode != LAST) {
			cout << RanggaNode->rollNumber << " " << RanggaNode->name << endl;
			RanggaNode = RanggaNode->next;
		}
		cout << LAST->rollNumber << " " << LAST->name << endl;
	}
}

int main() {
	CircularLinkedList obj;
	while (true) {
		try
		{
			cout << "\nMenu" << endl;
			cout << "1. Add a recorf to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-4): ";

			char ch;
			cin >> ch;

			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				obj.delNode();
				break;
			}
			case '3': {
				obj.traverse();
				break;
			}

			case '4': {
				return 0;
			}
			default: {
				cout << "invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e){
			cout << e.what() << endl;
		}
	}
	return 0;
}
