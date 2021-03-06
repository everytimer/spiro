// https://github.com/Takemonist/catmull_rom

#ifndef IG_CATMULLROM_HPP_
#define IG_CATMULLROM_HPP_

#include <vector>

template<class T>
class Point
{
    private:
        std::vector<T> v = {0,0};
    public:
        Point(T num_1,T num_2){x = num_1;  y = num_2;}
        Point(){}
        T x;
        T y;
        Point operator+(Point v){
            Point ret;

            ret.x = this->x + v.x;
            ret.y = this->y + v.y;

            return ret;
        }
        Point operator-(Point v){
            Point ret;

            ret.x = this->x - v.x;
            ret.y = this->y - v.y;

            return ret;
        }
        Point operator+(T scalar){
            Point ret;

            ret.x = this->x + scalar;
            ret.y = this->y + scalar;

            return ret;
        }
        Point operator-(T scalar){
            Point ret;

            ret.x = this->x - scalar;
            ret.y = this->y - scalar;

            return ret;
        }
        Point operator*(T scalar){
            Point ret;

            ret.x = this->x * scalar;
            ret.y = this->y * scalar;

            return ret;
        }
        Point operator/(T scalar){
            Point ret;

            ret.x = this->x / scalar;
            ret.y = this->y / scalar;

            return ret;
        }
        template<class X, class Y>
        Point operator()(const X& x, const Y& y){ 
            this->x = x;
            this->y = y;
            return *this;
        }
};

    Point<double> operator*(double scaler, Point<double> v){
        return v*scaler;
    }

//////////////////////////////////////////////////////////////////////////////////
class catmullrom
{
    public:
        std::vector< Point<double> > p;
        std::vector< Point<double> > v;
        int points = 0;
        bool smooth;

        catmullrom(bool smooth = true){this->smooth = smooth;}

    void addpoint(Point<double> p)
    {
        this->p.push_back(p);
        v.resize(++points);
        if(points > 2) calcv();
    }

    void addpoint(double x,double y)
    {
        Point<double> p(x,y);
        this->p.push_back(p);
        v.resize(++points);
        if(points > 2) calcv();
    }

    Point<double> getft(double time)
    {
        Point<double> ret;
        int n = points-1;
        int i = (int)time;
        double t = time - i;
        if(i == n)
        {
            ret = (2*p[i]-2*p[0]+v[i]+v[0])*t*t*t
                + (-3*p[i]+3*p[0]-2*v[i]-v[0])*t*t
                + v[i]*t
                + p[i];
        }
        else
        {
            ret = (2*p[i]-2*p[i+1]+v[i]+v[i+1])*t*t*t
                + (-3*p[i]+3*p[i+1]-2*v[i]-v[i+1])*t*t
                + v[i]*t
                + p[i];
        }
        return ret;
    }

    void calcv()
    {
        Point<double> temp;
        if(smooth)
        {
            temp = (p[1]-p[points-2])/2;
            v.at(0) = temp;
            for(int i = 1;i < points-1;i++)
            {
                temp = (p[i+1]-p[i-1])/2;
                v.at(i) = temp;
            }
            temp = (p[0]-p[points-2])/2;
            v.at(points-1) = temp;
        }
        else
        {
            temp = (p[1]-p[0])*2-(p[2]-p[0])/2;
            v.at(0) = temp;
            for(int i = 1;i < points-1;i++)
            {
                temp = (p[i+1]-p[i-1])/2;
                v.at(i) = temp;
            }
            temp = (p[points-1]-p[points-2])*2-(p[points-1]-p[points-2])/2;
            v.at(points-1) = temp;
        }
    }
};

#endif /* IG_CATMULLROM_HPP_ */

