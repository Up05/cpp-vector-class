#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define setSpeed(s, mag) setMag(s, mag)

struct Vector2{
    float x, y, x2, y2;
    float xs, ys;

    float acc, vel;

    float a, r;
    
    Vector2(float _x, float _y, float _x2, float _y2){
        xs = _x2 - _x;
        ys = _y2 - _y;
        x = _x; y = _y; x2 = _x2; y2 = _y2;
    }

    float getAngle(bool refresh){
        if(!a || refresh)
            a = atan(ys / xs);
        if(a && !refresh)  
            return a; 
        return atan(ys / xs);
    }

    float getRadius(bool refresh){
        if(!r || refresh)
            a = sqrt(xs*xs + ys*ys);
        if(r && !refresh)  
            return a; 
        return sqrt(xs*xs + ys*ys);
    }

    float setMag(float s, float mag){ // setSpeed()
        mag = mag - mag / s;
        vel = mag;
        return mag;
    }

    float getDist(){
        return sqrt(xs*xs + ys*ys); // xs = x2 - x
    }
    
    float getDist(float x, float y, float x2, float y2){
        float a = x2 - x;
        float b = y2 - y;
        return sqrt(a*a + b*b);
    }

    float *getLerp(){
        float a = (x + x2) / 2;
        float b = (y + y2) / 2;
        float *both = new float[2]{a, b};
        return both;
    }
    
    float *getNorm(){
        float a = 1 - 1 / xs;
        float b = 1 - 1 / ys;
        float *both = new float[2]{a, b};
        return both;
    }

    float constrain(float _x, float _y, float _x2, float _y2){
        if(x > _x && y > _y && x < _x2 && y < _y2){
            vel = 0.0f;
            return true;
        }
    } // ! ne

    float random(float minR, float maxR){
        float xs = cos(_rand() * 6.28f) * (_rand() * maxR - minR + minR);
        float ys = sin(_rand() * 6.28f) * (_rand() * maxR - minR + minR);
        return 0.01f;
    }

    private:
        float _rand(){
            return static_cast <float> (rand() / static_cast <float> (RAND_MAX));
        }
};




int main(){

    srand(time(NULL));

    Vector2 v(10.0f, 20.0f, 30.0f, 40.0f);

    
    std::cout << v.getAngle(false)      << std::endl; // 0.00040835 || -6.5848e-05 <- greičiausia likusi atmintis, nes aš niekad: a = 0;  ??
    std::cout << v.getDist()            << std::endl; // 28.2843
    std::cout << v.getDist(4, 8, 3, 2)  << std::endl; // 6.08276
    std::cout << v.random(0, 7)         << std::endl; // 0.01
    std::cout << v.setMag(8, 6)         << std::endl; // 5.25
    std::cout << (static_cast <float> (rand() / static_cast <float> (RAND_MAX))) << std::endl; // 0.286569
    
    /*
    PS C:\Users\\Desktop\c_C\Vector_class> g++ .\vector.cpp -o .\a.exe
    PS C:\Users\\Desktop\c_C\Vector_class> .\a.exe
    0.00040835
    28.2843
    6.08276
    0.01
    5.25
    0.286569
    PS C:\Users\\Desktop\c_C\Vector_class> 

    ¯\_(ツ)_/¯

    PS C:\Users\\Desktop\c_C\Vector_class> .\a.exe 
    -6.5848e-05
    28.2843
    6.08276
    */ 
    
    // std::cin.get();
}

