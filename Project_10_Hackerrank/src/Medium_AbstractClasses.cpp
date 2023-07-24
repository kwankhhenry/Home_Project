#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <fstream>
using namespace std;

struct Node{
   Node* prev;
   Node* next;
   int key;
   int value;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
   Node():prev(NULL),next(NULL),key(0),value(0){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache: public Cache{
    public:
        LRUCache(int cap) {
            map<int,Node*> mp;
            Cache::cp = cap; 
            tail = nullptr; 
            head = nullptr; 
            }
        void set(int key, int val) 
        {
            if(Cache::mp.find(key) != mp.end())
            {
                // Cache hit
                Node* hitptr = Cache::mp[key];
                Cache::mp[key]->value = val;
                
                if (hitptr == head)
                    head = hitptr->next;
                        
                if (hitptr == tail)
                    tail = hitptr->prev;
                    
                hitptr->prev->next = hitptr->next;
                hitptr->next->prev = hitptr->prev;
                    
                hitptr->next = head;
                hitptr->prev = tail;
                
                head = hitptr;
            }
            else
            {
                Node* p = new Node(key,val);
                // Cache miss
                if(head == nullptr && tail == nullptr)
                {
                    p->next = p;
                    p->prev = p;
                    head = p;
                    tail = p;
                }
                else
                {
                    p->next = head;
                    head = p;
                    
                    if(mp.size() == (size_t)cp)
                    {
                        //cout << "Head key: " << head->key << ", value is: " << head->value << endl;
                        //cout << "Erasing key: " << tail->key << ", value is: " << tail->value << endl;
                        Cache::mp.erase(tail->key);
                        p->prev = tail->prev;
                        delete tail;
                        tail = p->prev;
                    }
                    else
                    {
                        p->prev = tail;
                    }
                }
                Cache::mp.insert(pair<int,Node*>(key, p));
                //cout << "mpsize is: " << mp.size() << ", cp is: " << cp << "\n";
                
                /*Node* temp = head;
                for(int i = 0; i < mp.size(); i++)
                {
                    cout << temp->value;
                    temp = temp->next;
                }
                cout << "\n";*/
            }
            //cout << "Head is: " << head->key << ", value is: " << head->value << endl;
            //cout << "Tail is: " << tail->key << ", value is: " << tail->value << endl;
        }
        int get(int key) { 
            int result = Cache::mp.find(key) != Cache::mp.end() ? Cache::mp[key]->value : -1;
            return result;
        }
};

int main()
{
    std::ifstream file("input/Medium_AbstractClasses_input.txt");
    if(file.is_open())
    {
        int n, capacity,i;
        file >> n >> capacity;
        LRUCache l(capacity);
        for(i=0;i<n;i++) {
            string command;
            file >> command;
            if(command == "get") {
                int key;
                file >> key;
                cout << l.get(key) << endl;
            } 
            else if(command == "set") {
                int key, value;
                file >> key >> value;
                l.set(key,value);
            }
        }
        return 0;
    }
    file.close();

    return 0;
}