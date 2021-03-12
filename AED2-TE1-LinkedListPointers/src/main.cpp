#include <iostream>
#include <list>

using namespace std;

class Collector {
    private:

        list <void*> recycleList;
    
    public:

        void recyclePointer(void* recycledNode){
            recycleList.push_front(recycledNode);
            cout << "Recycled: " << recycledNode << endl;
        }

        void* reusePointer(){
            void* voidPointer;
            voidPointer = recycleList.front();
            recycleList.pop_front();
            cout << "Reused: " << voidPointer << endl;
            return voidPointer;

        }

        bool isEmpty(){
            return recycleList.empty();
        }

};

Collector* collector = new Collector();

class Node {
    private:

        int value;
        Node* nextNodePointer;

    public:

        Node(int Value){
            value = Value;
            nextNodePointer = nullptr;
        }

        Node(int Value, Node* newNextNodePointer){
            value = Value;
            nextNodePointer = newNextNodePointer;
        }

        void setValue(int Value){
            value = Value;
        }

        void setNextNodePointer(Node* NextNodePointer){
            nextNodePointer = NextNodePointer;
        }

        int getValue(){
            return value;
        }

        Node* getNextNodePointer(){
            return nextNodePointer;
        }

        //Overloaded New and Delete:

        void* operator new(size_t size){
            void* newNode;
            if (collector->isEmpty()){
                newNode = malloc(size);
            } else{
                newNode = collector->reusePointer();
            }
            return newNode;
        }

        void operator delete(void* deletedNode){
            collector->recyclePointer(deletedNode);
            free(deletedNode);
        }

};

class List {

    private:

        Node* firstNodePointer;


    public:

        int getlength(){
            Node* reference = this->firstNodePointer;
            int length = 0;

            while (reference != nullptr){
                length++;
                reference = reference->getNextNodePointer();
            }
            
            return length;
        }

        List(){
            firstNodePointer = nullptr;
            this->printList();
        }

        List(int Value){
            firstNodePointer = new Node(Value);
            this->printList();
        }

        bool isEmpty(){
            return (firstNodePointer == nullptr);
        }

        void printList(){
            if (this->isEmpty()){
                cout << "[]" << endl;
            } else if (this->getlength() == 1){
                cout << "[" << this->firstNodePointer->getValue() << "]" << endl;
            } else{
                cout << "[" << this->firstNodePointer->getValue() << ",";
                Node* reference = this->firstNodePointer->getNextNodePointer();

                while (reference->getNextNodePointer() != nullptr){
                    cout << reference->getValue() << ",";
                    reference = reference->getNextNodePointer();
                }
                cout << reference->getValue() << "]" << endl;
            }
            
        }

        void addFirst(int newValue){
            firstNodePointer = new Node(newValue, firstNodePointer);
            this->printList();
        }

        void deleteFirst(){ 
            Node* newFirstNodePointer = firstNodePointer->getNextNodePointer();
            delete firstNodePointer;
            firstNodePointer = newFirstNodePointer;
            this->printList();
        }

};

int main(int arg_count, char *args[]) {

    List list = List(5);
    list.addFirst(10);
    list.addFirst(15);
    list.addFirst(20);
    list.deleteFirst();
    list.deleteFirst();
    list.addFirst(25);
    list.addFirst(30);
    list.deleteFirst();
    list.deleteFirst();
    list.deleteFirst();
    list.addFirst(35);
    list.addFirst(40);
    list.addFirst(45);
    
    return 0;
}
