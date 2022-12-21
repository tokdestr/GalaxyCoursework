#ifndef GALAXY_H
#define GALAXY_H
#include<star.h>
class galaxy{
public:
    static double SystemMass;
    static double SystemImpulse;
    static double SystemMomentImpulse;
    static double SystemPotential;
    static double SystemKinetic;
    static double SystemFull;
    int num;
    static int UpdateNumber;
    static long int TimeFromStart;
    star **stars;
    int HeaviestStars[dimHeaviestStars];
    galaxy(int n = numStars);
    ~galaxy(){delete[] stars;}
    double border[dim];
    void move();
private:
    void SetImpulse();
    void SetKinetic();
    void SetImpulseMoment();
    void SetMass();
};
#endif // GALAXY_H
