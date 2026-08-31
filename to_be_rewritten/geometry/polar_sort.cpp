#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define FORR(x,a,b) for(int x=a;x<=b;x++)
using ld = long double;
using ll = long long;
typedef pair<int,int> ii;

constexpr auto eps = 1e-8;
inline int sgn(ld x) { return (abs(x) <= eps) ? 0 : (x < 0 ? -1 : 1); }
inline int sgn(ll x) { return (x == 0) ? 0 : (x < 0 ? -1 : 1); }

template<typename T>
struct _Point {
  T x = 0, y = 0;
  _Point() = default;
  _Point(T x, T y) : x(x), y(y) {}
  bool operator<(const _Point &p) const { return !sgn(p.x - x) ? sgn(y - p.y) < 0 : x < p.x; }
  bool operator==(const _Point &p) const { return !sgn(p.x - x) && !sgn(p.y - y); }
  _Point operator+(const _Point &p) const { return {x + p.x, y + p.y}; }
  _Point operator-(const _Point &p) const { return {x - p.x, y - p.y}; }
  _Point operator*(T a) const { return {x * a, y * a}; }
  _Point operator/(T a) const { return {x / a, y / a}; }
  T operator*(const _Point &p) const { return x * p.x + y * p.y; }  // dot
  T operator^(const _Point &p) const { return x * p.y - y * p.x; }  // cross
  friend auto &operator>>(istream &i, _Point &p) { return i >> p.x >> p.y; }
  friend auto &operator<<(ostream &o, _Point p) { return o << p.x << ' ' << p.y; }
};

using Point = _Point<ll>;

auto dist2(const Point &a) { return a * a; }

template<class RandomIt>
void polar_sort(RandomIt first, RandomIt last, Point origin = Point(0, 0)) {
  auto get_quad = [&origin](const Point& p) {
    Point diff = p - origin;
    if(diff.x > 0 && diff.y >= 0) return 1;
    if(diff.x <= 0 && diff.y > 0) return 2;
    if(diff.x < 0 && diff.y <= 0) return 3;
    return 4;
  };
  auto polar_cmp = [&origin, &get_quad](const Point& p1, const Point& p2) {
    int q1 = get_quad(p1), q2 = get_quad(p2);
    if(q1 != q2) return q1 < q2;
    ll cross = (p1 - origin) ^ (p2 - origin);
    return cross ? cross > 0 : dist2(origin - p1) < dist2(origin - p2);
  };
  sort(first, last, polar_cmp);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
}
