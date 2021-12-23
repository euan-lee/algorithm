#include <iostream>
using namespace std;

class Power{
    int kick;
    int punch;
public:
    Power(int kick=0,int punch=0){
        this->kick=kick;this->punch=punch;
    }
    void show();
    Power operator+ (Power op2);
    Power operator- (Power op2);
};

class Coord{
    int X,Y;
public:
    Coord(int X=0,int Y=0){
        this->X=X;this->Y=Y;
    }
    void show();
    Coord operator+(Coord c2);
    Coord operator-(Coord c2);
};

void Power::show(){
    cout<<"kick="<<kick<<','<<"punch="<<punch<<endl;
}
Power Power::operator+(Power op2){
    Power tmp;
    tmp.kick=this->kick+op2.kick;
    tmp.punch=this->punch+op2.punch;
    return tmp;
}
Power Power::operator-(Power op2){
    Power tmp;
    tmp.kick=this->kick-op2.kick;
    tmp.punch=this->punch-op2.punch;
    return tmp;
}


void Coord::show(){
    cout<<"Coord x="<<X<<','<<"Y="<<Y<<endl;
}
Coord Coord::operator+(Coord c2){
    Coord tmp;
    tmp.X=this->X+c2.X;
    tmp.Y=this->Y+c2.Y;
    return tmp;
}

Coord Coord::operator-(Coord c2){
    Coord tmp;
    tmp.X=this->X-c2.X;
    tmp.Y=this->Y-c2.Y;
    return tmp;
}

int main(){
    Power a(3,5),b(4,6),c;
    a.show();
    b.show();
    c=a-b;
    c.show();
    Coord x(3,5),y(4,6),z;
    x.show();
    y.show();
    z.show();
    z=y-x;
    z.show();
}