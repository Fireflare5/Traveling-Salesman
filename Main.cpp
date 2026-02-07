#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class point2
{
    public:
        float e[2];
        point2() : e{0.0F,0.0F} {}
        point2(float e1, float e2) : e{e1,e2} {}
        float operator[] (int i) const {return e[i];}
        float& operator[] (int i) {return e[i];}
        point2 operator- () const {return point2(-e[0], -e[1]);}
        point2& operator+= (const point2& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            return *this;
        }
        point2& operator+= (float t) {
            e[0] += t;
            e[1] += t;
            return *this;
        }
        point2& operator-= (const point2& v) {
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            return *this;
        }
        point2& operator-= (float t) {
            return *this += -t;
        }
        point2& operator*= (const point2& v) {
            e[0] *= v.e[0];
            e[1] *= v.e[1];
            return *this;
        }
        point2& operator*= (float t) {
            e[0] *= t;
            e[1] *= t;
            return *this;
        }
        point2& operator/= (const point2& v) {
            e[0] /= v.e[0];
            e[1] /= v.e[1];
            return *this;
        }
        point2& operator/= (float t) {
            return *this *= 1.0F / t;
        }
};

class points
{
    public:
        vector<point2> e;
        points(vector<point2> )
};

int main() {

    return 0;
}