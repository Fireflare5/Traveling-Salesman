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
            return *this += -v;
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

inline ostream& operator<<(ostream& out, const point2& v) {
    return out << v[0] << " " << v[1];
}

class points
{
    public:
        vector<point2> e;
        points(vector<point2> e1) : e{e1} {}
        point2 operator[](int i) const {return e[i];}
};

inline ostream& operator<<(ostream& out, const points& v) {
    for(int i = 0; i < v.e.size(); i++) {
        out << "{"<< v[i] << "}" << " ";
    }
    return out;
}

inline int sum(int n) {
    return (n * (n - 1)) / 2;
}

inline void OptimizeTSP(const points& v) {
    for(int i = 0; i < sum(v.e.size()); i++) {
        cout << i << endl;
    }
}

int main() {
    vector<point2> e = {point2(1,2),point2(3,4),point2(5,6),point2(7,8),point2(9,10)};
    points map(e);
    cout << map << endl;
    OptimizeTSP(map);
    return 0;
}