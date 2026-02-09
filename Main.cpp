#include <iostream>
#include <cmath>
#include <vector>
#include <ranges>
#include <algorithm>

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
    vector<int> cities(v.e.size());
    float total = 10000000000.0F;
    float x;
    float n;
    float ntotal = 0;
    int epoch = 10000;
    int temp = 6;
    srand(time(0));
    for(int i = 0; i < epoch; i++) {
        ntotal = 0;
        vector<int> ncities(v.e.size());
        for(int step1 = 0; step1 < (v.e.size() - 1); step1++) {
            x = 10000000000.0F;
            for(int step2 = 0; step2 < v.e.size(); step2++) {
                if(step2 == ncities[step1]) {
                    step2++;
                }
                if(step2 < v.e.size()) {
                    n = hypot(v[step2],v[ncities[step1]]);
                    if(n * (float((10 - temp) + (rand() % (2 * temp))) / 10.0F) < x && ranges::find(ncities,step2) == ncities.end()) {
                        x = n;
                        ncities[step1 + 1] = step2;
                    }
                }
            }
            ntotal += x;
        }
        ntotal += hypot(v[ncities[0]],v[ncities[ncities.size() - 1]]);
        if(ntotal < total) {
            total = ntotal;
            cities = ncities;
        }
    }
    cout << total << endl;
    for(int city: cities) {
        cout << city + 1 << " ";
    }
    cout << "\n";
}

int main() {
    vector<point2> e = {point2(0,4.15),point2(0.68,5.06),point2(-1.32,5.06),point2(-2.14,4.44),point2(-1.2,4.1),point2(-0.2,3.87),point2(-0.17,3.08),point2(-1.2,3.28),point2(-2.4,3.3),point2(-2.26,3.67),point2(0.93,3.7),point2(-0.7,2.68),point2(-1.84,2.68),point2(-0.59,4.82),point2(2.01,4.8),point2(2.01,2.85),point2(0.52,2.58),point2(-0.14,2),point2(-1.15,1.75),point2(0.65,1.78),point2(1.52,2.2),point2(1.93,3.93)};
    points map(e);
    cout << map << endl;
    OptimizeTSP(map);
    return 0;
}