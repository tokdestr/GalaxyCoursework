#include "cmath"
#include <constants.h>

#ifndef STAR_H
#define STAR_H


class star{
public:
    static int starCounter;
    double impulse;
    double kinetic;
    double ImpulseMoment;
    double x[dim];
    double v[dim];
    double m;
    double f[dim];
    QColor col;
    star(double *coord, double *speed, double mass);
    ~star(){starCounter--;}
    star& operator+(const star &a);
    int size;
    void SetImpulse();
    void SetKinetic();
    void SetImpulseMoment();
    double getMass();
   /* bool sortirovka(star &a, star &b);*/
private:
    void SetColor();
    void SetSize();
};
#endif // STAR_H
