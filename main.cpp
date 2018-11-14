
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(2, 2);
    Matrix<int> b(3, 2);


    a.set(1,1,3);
    a.set(1,2,3);
    a.set(2,1,2);
    a.set(2,2,2);

    b.set(1,1,1);
    b.set(1,2,1);
    b.set(2,1,1);
    b.set(2,2,1);
    b.set(3,1,1);
    b.set(3,2,1);



    a.printm();
    cout<<endl;
    b.printm();
    cout<<endl;
    a=b*a;
    a.printm();
    cout<<endl;
    b.printm();
    cout<<endl;
    b=b+a;
    a.printm();
    cout<<endl;
    b.printm();
    cout<<endl;
    b=b-a;
    a.printm();
    cout<<endl;
    b.printm();
    cout<<endl;
    a.printm();
    cout<<endl;
    b.printm();
    cout<<endl;
    b=b.transposed();
    cout<<endl;
    b.printm();

    system("PAUSE");
    return EXIT_SUCCESS;
}
