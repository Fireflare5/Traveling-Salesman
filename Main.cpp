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

inline point2 operator*(const point2& v, float t) {
    return point2(v.e[0] * t, v.e[1] * t);
}

inline point2 operator*(float t, const point2& v) {
    return v * t;
}

inline point2 operator*(const point2& u, const point2& v) {
    return point2(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

inline point2 operator/(const point2& v, float t) {
    return v * (1/t);
}

inline point2 operator/(float t, const point2& v) {
    return point2(t / v.e[0], t / v.e[1]);
}

inline point2 operator/(const point2& u, const point2& v) {
    return u * (1/v);
}

inline point2 operator+(const point2& v, float t) {
    return point2(v.e[0] + t, v.e[1] + t);
}

inline point2 operator+(float t, const point2& v) {
    return v + t;
}

inline point2 operator+(const point2& u, const point2& v) {
    return point2(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

inline point2 operator-(const point2& v, float t) {
    return v + (-t);
}

inline point2 operator-(float t, const point2& v) {
    return (-v) + t;
}

inline point2 operator-(const point2& u, const point2& v) {
    return u + (-v);
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

inline float sum(const point2& v) {
    return v[0] + v[1];
}

inline float dot2(const point2& v) {
    return sum(v*v);
}

inline float hypot(const point2& u, const point2& v) {
    return sqrt(dot2(u - v));
}

inline void OptimizeTSP(const points& v) {
    int iii = 0;
    for(int i = 0; i < (v.e.size() - 1); i++) {
        for(int ii = 1 + i; ii < v.e.size(); ii++) {
            iii++;
            cout << hypot(v[i],v[ii]) << " " << iii << "{" << i << " " << ii << "}" << endl;
        }
    }
}

int main() {
    vector<point2> e = {point2(1,2),point2(3,4),point2(5,6),point2(7,8),point2(9,10)};
    points map(e);
    cout << map << endl;
    OptimizeTSP(map);
    return 0;
}