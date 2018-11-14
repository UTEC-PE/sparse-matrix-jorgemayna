#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"
#include <stdlib.h>

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;
    public:
        Matrix(){
            rows=0;
            columns=0;
            hRows=nullptr;
            hColumns=nullptr;
        };
        int get_rows(){
            return rows;
        }
        void set_rows(int x){
            rows=x;
        }
        int get_col(){
            return columns;
        }
        void set_col(int x){
            columns=x;
        }
        //----------------------------------------------------------------CONSTRUCTOR
        Matrix(int sizeX, int sizeY){
            if(sizeX<0 || sizeY<0){
                cout<<"El tamaño de la matriz debe ser positivo"<<endl;
                exit(1);
            }
            hRows=new Node<T>;
            Node<T>* temp=hRows;
            temp->next=nullptr;
            for(int i=1;i<=sizeX;i++){
                temp->x=i;
                temp->y=0;
                if(i!=sizeX){
                    temp->down=new Node<T>;
                    temp=temp->down;
                    temp->next=nullptr;
                }else{
                    temp->down=nullptr;
                }
            }
            hColumns=new Node<T>;
            temp=hColumns;
            temp->down=nullptr;
            for(int i=1;i<=sizeY;i++){
                temp->x=0;
                temp->y=i;
                if(i!=sizeY){
                    temp->next=new Node<T>;
                    temp=temp->next;
                    temp->down=nullptr;
                }else{
                    temp->next=nullptr;
                }

            }
            columns=sizeY;
            rows=sizeX;

        };
        //--------------------------------------------------------------------SET
        void set(int x, int y, T data){
            if(x>rows || x<1){
                cout<<"Indice x incorrecto"<<endl;
                return;
            }
            if(y>columns || y<1){
                cout<<"Indice y incorrecto"<<endl;
                return;
            }

            if((*this)(x,y)!=0){
                Node<T>* temp=hRows;
                for(int i=1;i<x;i++){
                    temp=temp->down;
                }
                while(temp->next->y!=y){
                    temp=temp->next;
                }
                if(data==0){
                    temp->next=temp->next->next;
                    temp=hColumns;
                    for(int i=1;i<y;i++){
                        temp=temp->next;
                    }
                    while(temp->down->x!=x){
                        temp=temp->down;
                    }
                    Node<T>* temp1=temp->down;
                    temp->down=temp->down->down;
                    delete temp1;
                    return;
                }
                temp->next->set_Data(data);
                return;
            }else{
                if(data==0){
                    return;
                }
                Node<T>* nodo=new Node<T>;
                nodo->x=x;
                nodo->y=y;
                nodo->set_Data(data);
                Node<T>* temp=hRows;
                for(int i=1;i<x;i++){
                    temp=temp->down;
                }
                while(temp->next==nullptr || temp->next->y<y){
                    if(temp->next==nullptr){
                        break;
                    }
                    temp=temp->next;
                }
                nodo->next=temp->next;
                temp->next=nodo;

                temp=hColumns;
                for(int i=1;i<y;i++){
                    temp=temp->next;
                }
                while(temp->down==nullptr || temp->down->x<x){
                    if(temp->down==nullptr){
                        break;
                    }
                    temp=temp->down;
                }
                nodo->down=temp->down;
                temp->down=nodo;
            }

        };
        //----------------------------------------------------------------SOBRECARGA "()"
        T operator()(int x, int y){
            if(x>rows || x<1){
                cout<<"Indice x incorrecto"<<endl;
                return 0;
            }
            if(y>columns || y<1){
                cout<<"Indice y incorrecto"<<endl;
                return 0;
            }
            Node<T>* temp=hRows;
            for(int i=1;i<x;i++){
                temp=temp->down;
            }
            while(temp->y!=y){
                temp=temp->next;
                if(temp==nullptr || temp->y>y){
                    return 0;
                }
            }
            return temp->get_data();
        };
        //-------------------------------------------------------------MULTIPLICACION CON OTRA MATRIZ
        Matrix<T> operator*(Matrix<T> other){
            try{
                if(columns!=other.get_rows()){
                    throw "Se nesesita matrices de la forma MxN - NxP";
                }
                Matrix<T> a(rows,other.get_col());
                for(int i = 1;i<=rows;i++){
                    for(int j=1;j<=other.get_col();j++){
                        int sum=0;
                        for(int z=1;z<=columns;z++){
                            sum=sum+(*this)(i,z)*other(z,j);
                        }
                        a.set(i,j,sum);
                    }
                }
                return a;
            }catch(const char* msg){
                cerr<<msg<<endl;
            }
        };
        //-------------------------------------------------------------MULTIPLICAION CON ESCALAR
        Matrix<T> operator*(T scalar){
            Matrix<T> help(rows,columns);
            for(int i=1;i<=rows;i++){
                for(int j=1;j<=columns;j++){
                    help.set(i,j,(*this)(i,j)*scalar);
                }
            }
            return help;
        };
        //--------------------------------------------------------------SUMA
        Matrix<T> operator+(Matrix<T> other){
            try{
                if(rows!=other.rows || columns!=other.columns){
                    throw "Las matrices no tienen las mismas dimenciones!";
                }
                Matrix<T> help(rows,columns);
                for(int i=1;i<=rows;i++){
                    for(int j=1;j<=columns;j++){
                        help.set(i,j,(*this)(i,j)+other(i,j));
                    }
                }
                return help;
            }catch(const char* msg){
                cerr<<msg<<endl;
            }
        };
        //---------------------------------------------------------------RESTA
        Matrix<T> operator-(Matrix<T> other){
            try{
                if(rows!=other.rows || columns!=other.columns){
                    throw "Las matrices no tienen las mismas dimenciones!";
                }
                Matrix<T> help(rows,columns);
                for(int i=1;i<=rows;i++){
                    for(int j=1;j<=columns;j++){
                        help.set(i,j,(*this)(i,j) - other(i,j));
                    }
                }
                return help;
            }catch(const char* msg){
                cerr<<msg<<endl;
            }
        };
        //-------------------------------------------------------------------TRANSPUESTA
        Matrix<T> transposed(){
            Matrix<T> a(columns,rows);
            for(int i=1;i<=rows;i++){
                    for(int j=1;j<=columns;j++){
                        a.set(j,i,(*this)(i,j));
                    }
                }
            return a;
        };
        //-------------------------------------------------------------------REZIZE
        void rezize(int x, int y){
            for(int i=1;i<=rows;i++){
                for(int j=1;j<=columns;j++){
                    set(i,j,0);
                }
            }
            set_rows(x);
            set_col(y);
            Node<T>* temp=hRows;
            while(temp->x!=x){
                if(temp->down==nullptr){
                    temp->down=new Node<T>;
                    temp->down->next=nullptr;
                    temp->down->x=temp->x + 1;
                    temp->down->y=0;
                    temp->down->down=nullptr;
                }
                temp=temp->down;
            }
            if(temp->down!=nullptr){
                Node<T>* temp1=temp->down;
                temp->down=nullptr;
                while(temp1!=nullptr){
                    temp=temp1;
                    temp1=temp1->down;
                    delete temp;
                }
            }

            temp=hColumns;
            while(temp->y!=y){
                if(temp->next==nullptr){
                    temp->next=new Node<T>;
                    temp->next->down=nullptr;
                    temp->next->x=0;
                    temp->next->y=temp->y + 1;
                    temp->next->next=nullptr;
                }
                temp=temp->next;
            }
            if(temp->next!=nullptr){
                Node<T>* temp1=temp->next;
                temp->next=nullptr;
                while(temp1!=nullptr){
                    temp=temp1;
                    temp1=temp1->next;
                    delete temp;
                }
            }
        }
        //-------------------------------------------------------------------IGUALDAD
        Matrix<T> operator=(Matrix<T> other){
            if(rows!=other.get_rows() || columns!=other.get_col()){
                rezize(other.get_rows(),other.get_col());
            }
            for(int i=1;i<=rows;i++){
                for(int j=1;j<=columns;j++){
                    set(i,j,other(i,j));
                }
            }
            return (*this);

        };
        void printm(){
            for(int i=1;i<=rows;i++){
                for(int j=1;j<=columns;j++){
                    cout <<(*this)(i,j)<<" ";
                }
                cout<<endl;
            }
        }
        //----------------------------------------------------------------DESTRCUTOR

        ~Matrix(){
            /*for(int i=1;i<=rows;i++){
                for(int j=1;j<=columns;j++){
                    set(i,j,0);
                }
            }
            rezize(1,1);
            delete hRows;
            delete hColumns;
            */


        };
};

#endif
