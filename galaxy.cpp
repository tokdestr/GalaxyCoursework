#include "galaxy.h"
#include <cmath>
#include <algorithm>
int galaxy::UpdateNumber = 0;
long int galaxy::TimeFromStart = 0;
double galaxy::SystemMass = massSun;
double galaxy::SystemImpulse = 0;
double galaxy::SystemKinetic = 0;
double galaxy::SystemMomentImpulse = 0;
galaxy::galaxy(int n):num(n){
    stars = new star*[num];
    double x1[dim] = {0}, v1[dim] = {0};
    stars[0] = new star(x1, v1, massSun); // самый массивный объект в начале координат
    double rad;
    for(int i = 1; i < num; ++i){
        rad = 0;
        double R = rand() * systemRadius / RAND_MAX,
        fi  = (2 * M_PI * rand()) / RAND_MAX;
        /*theta = (M_PI * rand()) / RAND_MAX;*/
        x1[0] = R  * cos(fi);
        x1[1] = R  * sin(fi);
        /*if(dim == 3){
            x1[0] *= sin(theta);
            x1[1] *= sin(theta);
            x1[3] = R * cos(theta);
        }*/
        for(int k = 0; k < dim; ++k){
            rad += x1[k] * x1[k];
        }
// вторая космическая скорость
        double absV = sqrt(G * stars[0]->m / sqrt(rad)), alpha = (2 * M_PI * rand()) / RAND_MAX;
//если размерность 3, нужен еще один угол как для координат(два угла годятся и для плоскости, желающие могут сделать)
//            v1[0] = absV * cos(alpha);
//            v1[1] = absV * sin(alpha);
        v1[0] =  absV * sin(fi);
        v1[1] = -absV * cos(fi); // скорость направлена вдоль окружности с центром в начале координат
        stars[i] = new star(x1, v1, massEarth / num * (6 * i));
        SystemMass += stars[i] -> m;
        SystemImpulse += stars[i]->impulse;
        SystemMomentImpulse += stars[i]->ImpulseMoment;
    }

    for (int i = 0; i < dimHeaviestStars; i++){
            HeaviestStars[i] = i;
        }
        if (stars[HeaviestStars[2]]->m > stars[HeaviestStars[1]]->m){
            HeaviestStars[2] = 1;
            HeaviestStars[1] = 2;
        }
        for (int i = dimHeaviestStars; i<num; i++){
            for (int j = 0; j < dimHeaviestStars; j++){
                if ((stars[i]->m >= stars[HeaviestStars[j]]->m) and (i != HeaviestStars[j])){
                    for(int k = dimHeaviestStars - 1; k > j; k-- ){
                        HeaviestStars[k] = HeaviestStars[k-1];
                    }
                    HeaviestStars[j] = i;
                    break;
                }
            }
        }
};
void galaxy::SetMass(){
    SystemMass = 0;
    for (int i = 0; i<num; i++){
        if (stars[i] == nullptr){
            continue;
        }
        SystemMass += stars[i]->getMass();
    }
}
void galaxy::SetImpulse(){
    SystemImpulse = 0;
    for (int i = 0; i<num; i++){
        if (stars[i] == nullptr){
            continue;
        }
        SystemImpulse += stars[i]->impulse;
    }
}
void galaxy::SetKinetic(){
    SystemKinetic = 0;
    for (int i = 0; i<num; i++){
        if (stars[i] == nullptr){
            continue;
        }
        SystemKinetic += stars[i]->kinetic;
    }
}
void galaxy::SetImpulseMoment(){
    SystemMomentImpulse = 0;
    for (int i = 0; i<num; i++){
        if (stars[i] == nullptr){
            continue;
        }
        SystemMomentImpulse += stars[i]->ImpulseMoment;
    }
}
void galaxy::move(){
    double dist;
    double dCoord[dim];
    for(int i = 0; i < num; ++i){ // force nullification
        for(int k = 0; k < dim; ++k){
            if(stars[i]){
                stars[i]->f[k] = 0;
            }
        }
    }
    for(int i = 0; i < num; i++){
        if(stars[i]){
            for(int j = i + 1; j < num; j++){
                if(i != j && stars[j]){
                    dist = 0;
                    for(int k = 0; k < dim; ++k){
                        dCoord[k] = stars[i]->x[k] - stars[j]->x[k];
                        dist += dCoord[k] * dCoord[k];
                    }
                    if(sqrt(dist) < distConnect){
                        *stars[i] + *stars[j];
                        delete stars[j];
                        stars[j] = nullptr;
                        for (int k = 0; k < dimHeaviestStars; k++){
                            if(stars[HeaviestStars[k]] == nullptr){
                                HeaviestStars[k] = i;
                                if(HeaviestStars[1] == HeaviestStars[2]){
                                    for (int n = 0; n < num; n++){
                                        int m = 0;
                                        if (stars[n] == nullptr){
                                            continue;
                                        }
                                        if ((n != HeaviestStars[0]) and (n != HeaviestStars[1])){
                                            if ((m == 1) and (stars[n]->m > stars[HeaviestStars[2]]->m)){
                                                HeaviestStars[2] = n;
                                            }
                                            else if (m == 0){
                                                m++;
                                                HeaviestStars[2] = n;
                                            }
                                        }
                                    }
                                }
                                if (stars[HeaviestStars[2]]->m > stars[HeaviestStars[1]]->m){
                                    int tmp = HeaviestStars[2];
                                    HeaviestStars[2] = HeaviestStars[1];
                                    HeaviestStars[1] = tmp;
                                }
                                break;
                            }
                            else if (stars[i]->m >= stars[HeaviestStars[k]]->m){
                                if (i  == HeaviestStars[k]){
                                    break;
                                }
                                for(int l = dimHeaviestStars - 1; l > k; l-- ){
                                    HeaviestStars[l] = HeaviestStars[l-1];
                                }
                                HeaviestStars[k] = i;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < num; i++){
        if(stars[i]){
            for(int j = i + 1; j < num; j++){
                if(i != j && stars[j]){
                    dist = 0;
                    for(int k = 0; k < dim; ++k){
                        dCoord[k] = stars[i]->x[k] - stars[j]->x[k];
                        dist += dCoord[k] * dCoord[k];
                    }
                    // dist = sqrt(dist); // для знаменателя пока квадрат, потом возьмем корень
                    for(int k = 0; k < dim; ++k){
                        double tmp = G * stars[i]->m * stars[j]->m / dist;
                        stars[i]->f[k] -= tmp * dCoord[k] / sqrt(dist);
                        stars[j]->f[k] += tmp * dCoord[k] / sqrt(dist);
                    }
                }
            }
        }
    }
    for(int i = 0; i < num; ++i){
        if(stars[i]){
            for(int k = 0; k < dim; ++k){
                stars[i]->v[k] += dt * stars[i]->f[k] / stars[i]->m; //можно не делить на массу, а выше суммировать ускорение
            }
            for(int k = 0; k < dim; ++k){
                stars[i]->x[k] += dt * stars[i]->v[k];
            }
        stars[i]->SetImpulse();
        stars[i]->SetKinetic();
        stars[i]->SetImpulseMoment();
        }
    }
    SetMass();
    SetImpulse();
    SetKinetic();
    SetImpulseMoment();
    UpdateNumber++;
    TimeFromStart += dt;
}
