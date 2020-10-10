#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <stack>
#include <cctype>
#include <string>
using namespace std;

struct Node
{
	string eName;
	Node* prev;
	Node* next;	
};

class LRUCache
{
	map<int, Node*> lookupTbl;
	Node* head;
	Node* tail;
	int capacity;

public:
	LRUCache();
	void writeToCache(int ENum, string Ename);
	string readFromCache(int Enum);	
};

LRUCache::LRUCache()
{
	capacity = 4;
	head = 0;
	tail = 0;
}

void LRUCache::writeToCache(int aNum, string aname)
{
	Node* entry = 0;
	if (lookupTbl.size() < capacity) {
		Node* entry = new Node;
		entry->eName = aname;
		entry->prev = 0;

		if (head == 0) {
			entry->next = 0;
			head = entry;
			tail = head;
		}
		else {
			entry->next = head;
			head->prev = entry;
			head = entry;			
		}

		lookupTbl[aNum] = entry;
	}

	else { //capacity exceeded so identify LRU entry and delete it. Next insert the new entry

		map<int, Node*>::iterator mit = lookupTbl.begin();
		for (mit; mit != lookupTbl.end(); mit++)
		{
			if (mit->second == tail) {
				lookupTbl.erase(mit->first);
				break;
			}
		}

		Node* newtail = tail->prev;
		delete tail;		
		tail = newtail;
		tail->next = 0;

		Node* newEntry = new Node;
		newEntry->eName = aname;
		newEntry->prev = 0;
		newEntry->next = head;
		head->prev = newEntry;
		head = newEntry;
	}

}

string LRUCache::readFromCache(int Enum) 
{
	if (lookupTbl.find(Enum) != lookupTbl.end()) {
		
		Node* node = lookupTbl[Enum];
					

		//move to head of the list 
		if(node->prev!=0)
			node->prev->next = node->next;

		if(node->next!=0)
			node->next->prev = node->prev;

		if (node == tail) {
			tail = node->prev;
		}

		node->next = head;
		head->prev = node;
		head = node;
		head->prev = 0;		

		return node->eName;
	}
	else
	{
		return "Not Found in Cache";
	}
}

int main()
{
	LRUCache lrx;

	lrx.writeToCache(100, "Prabhu"); //Prabhu
	lrx.writeToCache(200, "Missier"); //Missier Prabhu
	lrx.writeToCache(300, "Joe"); //Joe Missier Prabhu	
	

	string name = lrx.readFromCache(100); //Prabhu Joe Missier
	name = lrx.readFromCache(200); //Missier Prabhu Joe
	name = lrx.readFromCache(300); //Joe Missier Prabhu
	
	name = lrx.readFromCache(200); //Missier Joe Prabhu

	lrx.writeToCache(500, "Rony"); //Rony Missier Joe prabhu

	lrx.writeToCache(700, "Sony"); //Sony Rony Missier Joe


	return 0;
}