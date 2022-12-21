#include <star.h>
int star::starCounter = 0;
star::star(double *coord, double *speed, double mass){
    for(int k = 0; k < dim; ++k){
        x[k] = coord[k];
        v[k] = speed[k];
    }
    m = mass;
    impulse = m * sqrt(pow(v[0],2)+pow(v[1],2));
    kinetic = pow(impulse,2)/(2*m);
    SetColor();
    SetSize();
    starCounter++;
}
/*bool star::sortirovka(star &a,star &b){
    if (&a == nullptr){
        return 0;
    }
    else if (&b == nullptr){
        return 1;
    }
    else{
        return a.m > b.m;
    }
}*/

star& star::operator+(const star &a){
    m += a.m;
    for (int i = 0; i < dim; i++){
        x[i] = (x[i]*m+a.x[i]*a.m)/(m+a.m);
        v[i] = (v[i]*m+a.v[i]*a.m)/(m+a.m);
    }
    SetSize();
    SetColor();
    return *this;
};
void star::SetColor(){
    int i = 0;
    while (borderMass[i]<m){
        i++;
    }
    col = colStar[i];
}
void star::SetSize(){
    int i = 0;
    while (borderMass[i]<m){
        i++;
    }
    size = i;
}
double star::getMass(){
    if (sqrt(pow(x[0],2)+pow(x[1],2)) > systemRadius){
        return 0;
    }
    else{
        return m;
    }
}
void star::SetImpulse(){
    if (sqrt(pow(x[0],2)+pow(x[1],2)) > systemRadius){
        impulse = 0;
    }
    else{
        impulse = m * sqrt(pow(v[0],2)+pow(v[1],2));
    }
}
void star::SetKinetic(){
    if (sqrt(pow(x[0],2)+pow(x[1],2)) > systemRadius){
        kinetic = 0;
    }
    else{
        kinetic = pow(impulse,2)/(2*m);
    }
}
void star::SetImpulseMoment(){
    if (sqrt(pow(x[0],2)+pow(x[1],2)) > systemRadius){
        ImpulseMoment = 0;
    }
    else{
        ImpulseMoment = impulse * sqrt(pow(x[0],2)+pow(x[1],2));
    }
}
