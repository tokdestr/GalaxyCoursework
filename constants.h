#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QPainter>
const int dim = 2;
const int numStars = 500;
const int borderMassC1 = 10;
const int dimHeaviestStars = 3;
const double G = 6.67408e-11, systemRadius = 1e12, distConnect = 1e9, dt = 10000;
const double massSun   = 1.98892e30,
             massJup   = 1898.6e24,
             massUran  = 86.832e24,
             massEarth = 5.9742e24,
             massVenus = 4.867e24;
const double borderMass[] = {massVenus, massEarth, borderMassC1*massVenus, borderMassC1*massEarth,massUran, borderMassC1*massUran,massJup,  borderMassC1*massJup,massSun, borderMassC1*massSun};
const QColor colStar[] = {Qt::red, Qt::cyan, Qt::darkGreen, Qt::magenta, Qt::blue, Qt::darkBlue, Qt::darkYellow, Qt::yellow, Qt::white, Qt::black};
const int nColor = sizeof(colStar) / sizeof(colStar[0]);

#endif // CONSTANTS_H
