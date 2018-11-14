#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {
    T data;
    public:
        int x, y;
        Node* next;
        Node* down;
        void set_Data(T dat){
            data=dat;
        }
        T get_data(){
            return data;
        }
};

#endif
