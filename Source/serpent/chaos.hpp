////////////////////////////////////////////////////////////////////////////////////////
// MIT License
// Copyright (c) 2022 unmanned
//
// Rabinovich-fabrikant & Chen Lee: https://marmphco.com/dynamical/writeup.pdf
// Original MATLAB Code for Chua oscillator: http://www.chuacircuits.com/matlabsim.php
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cmath>

namespace cell {
////////////////////////////////////////////////////////////////////////////////////////
// Roessler ////////////////////////////////////////////////////////////////////////////
struct roessler
{
	float	x = 1.0f;
	float	y = 1.0f;
	float	z = 1.0f;

	float	a = 0.2f;
	float	b = 0.2f;
	float	c = 5.7f;

	float	delta = 0.01f;
    
    inline void iterate();
};

inline void roessler::iterate()
{
	x += (-y - z)*delta;
	y += (x + a * y)*delta;
	z += (b + z * (x - c))*delta;
}

////////////////////////////////////////////////////////////////////////////////////
// Hopf ////////////////////////////////////////////////////////////////////////////
struct hopf
{
	float	x = 0.01f;
	float	y = 0.01f;

	float	p = 0.11f;
    float   t = 0.01f;

    inline void iterate();
};

inline void hopf::iterate()
{
	x += t * ( -y + x * (p - (x*x + y*y)));
	y += t * (  x + y * (p - (x*x + y*y)));
}

////////////////////////////////////////////////////////////////////////////////////////
// Helmholz ////////////////////////////////////////////////////////////////////////////
struct helmholz
{
	float	x = 0.1f;
	float	y = 0.1f;
    float   z = 0.1f;

	float	gamma = 5.11f;
	float	delta = 0.55f;
    float   t     = 0.01;
    
    inline void iterate();
};

inline void helmholz::iterate()
{
	x += t * y;
	y += t * gamma * z;
    z += t * ( -z - delta * y - x - x * x );
}


//////////////////////////////////////////////////////////////////////////////////////
// Sprott ////////////////////////////////////////////////////////////////////////////
struct sprott
{
	float	x = 0.1f;
	float	y = 0.1f;
    float   z = 0.1f;

    float   t = 0.1;
    
    inline void iterate();
};

inline void sprott::iterate()
{
	x += t * y;
	y += t * (y * z - x);
    z += t * (1.0f - y * y);
}

////////////////////////////////////////////////////////////////////////////////////////
// Sprott-Linz /////////////////////////////////////////////////////////////////////////
struct linz
{
	float	x = 0.1f;
	float	y = 0.1f;
    float   z = 0.1f;

    float   a = 0.5f;
    float   t = 0.1;
    
    inline void iterate();
};

inline void linz::iterate()
{
	x += t * (y + z);
	y += t * (y * a - x);
    z += t * (x * x - z);
}

////////////////////////////////////////////////////////////////////////////////////////
// Sprott-Linz D ///////////////////////////////////////////////////////////////////////
struct linz_d
{
	float	x = 0.1f;
	float	y = 0.1f;
    float   z = 0.1f;

    float   a = 3.0f;
    float   t = 0.01;
    
    inline void iterate();
};

inline void linz_d::iterate()
{
	x += t * (-y);
	y += t * (x + z);
    z += t * (x * z + a*y*y);
}

////////////////////////////////////////////////////////////////////////////////////////
// Sprott 6-term ///////////////////////////////////////////////////////////////////////
struct sprott_st
{
	float	x = 0.1f;
	float	y = 0.1f;
    float   z = 0.1f;

	float	a = 0.8f;
	float	b = 0.5f;
    float   c = 0.1f;
    float   d = 1.0f;
    float   t = 0.01f;
    
    inline void iterate();
};

inline void sprott_st::iterate()
{
	x += t * y * a;
	y += t * (- y*z - x);
    z += t * (b * y * y - c * x - d);
}


////////////////////////////////////////////////////////////////////////////////////////
// Rayleigh-Benard /////////////////////////////////////////////////////////////////////
struct rayleigh
{
	double	x = 0.01f;
	double	y = 0.0f;
    double  z = 0.0f;

	float	a = 9.00f;
	float	r = 12.0f;
    float   b = 5.00f;

    float   t = 0.19f;
    
    inline void iterate();
};

inline void rayleigh::iterate()
{
	x = t * (- a*x + a*y);
	y = t * (r*x - y - x*z);
    z = t * (x*y - b*z);

}


////////////////////////////////////////////////////////////////////////////////////
// Wang ////////////////////////////////////////////////////////////////////////////
struct wang
{
	float	x = 0.1f;
	float	y = 0.1f;
    float   z = 0.1f;
    float   w;

	float	a = 27.5f;
	float	b = 3.0f;
    float   c = 19.3f;
    float   d = 3.3f;
    float   h = 2.9f;
    float   t = 0.001;
    
    inline void iterate();
};

inline void wang::iterate()
{
	x += t * a * (y - x);
	y += t * (b * x + c * y - x * z + w);
    z += t * (y * y - h * z);
    w  = d * -y;
}


///////////////////////////////////////////////////////////////////////////////////////
// Yu-Wang ////////////////////////////////////////////////////////////////////////////
struct yu_wang
{
	float	x = 0.1f;
	float	y = 0.1f;
    float   z = 0.1f;

	float	a = 10.0f;
	float	b = 40.0f;
    float   c = 2.0f;
    float   d = 2.5f;

    float   t = 0.001;
    
    inline void iterate();
};

inline void yu_wang::iterate()
{
	x += t * a * (y - x);
	y += t * (b * x - c * x * z);
    z += t * (pow(M_E, x*y) - d * z);

}


////////////////////////////////////////////////////////////////////////////////////////
// Three-Scroll Unified Chaotic System (TSUCS) /////////////////////////////////////////
struct tsucs
{
	float	x = 1.0f;
	float	y = 1.0f;
    float   z = 1.0f;

	float	a = 40.00f;
	float	b = 0.500f;
    float   c = 20.00f;
    float   d = 0.833f;
    float   e = 0.650f;

    float   t = 0.001f;
    
    inline void iterate();
};

inline void tsucs::iterate()
{
	x += t * (a*(y-x) + b*x*z);
	y += t * (c*y - x*z);
    z += t * (d*z + x*y - e*x*x);
}


////////////////////////////////////////////////////////////////////////////////////////
// Lorenz //////////////////////////////////////////////////////////////////////////////
struct lorenz
{
        float a = 10.0;
        float b = 28.0;
        float c = 8.0 / 3.0;
        float t = 0.01; 

        float x = 0.1; 
        float y = 0;
        float z = 0; 

        inline void iterate()
        {
                x += t * a * (y - x);
                y += t * (x * (b - z) - y);
                z += t * (x * y - c * z);
        }
};

////////////////////////////////////////////////////////////////////////////////////////
// Aizawa //////////////////////////////////////////////////////////////////////////////
struct aizawa
{
        float a = 0.95f;
        float b = 0.7f;
        float c = 0.6f;
        float d = 3.5f;
        float e = 0.25f;
        float f = 0.1f;

        float t = 0.01f; 

        float x = 0.1; 
        float y = 0;
        float z = 0; 

        inline void iterate()
        {
                x += t * ((z - b) * x - d * y);
                y += t * ((z - b) * y + d * x);
                z += t * (c + a*z - z*z*z/3.0f - (x*x+y*y)*(1.0f+e*z) + f*z*x*x*x);
        }
};


////////////////////////////////////////////////////////////////////////////////////////
// Halvorsen //////////////////////////////////////////////////////////////////////////////
struct halvorsen
{
        float a = 1.4;
        float t = 0.01; 

        float x = 0.1; 
        float y = 0;
        float z = 0; 

        inline void iterate()
        {
                x += t * (-a * x - 4.0f * y - 4.0f * z - y * y);
                y += t * (-a * y - 4.0f * z - 4.0f * x - z * z);
                z += t * (-a * z - 4.0f * x - 4.0f * y - x * x);
        }
};


////////////////////////////////////////////////////////////////////////////////////////
// Ikeda ///////////////////////////////////////////////////////////////////////////////
struct ikeda
{

	float u = 0.918;
	float x = 0.8;
	float y = 0.7;
	float t;

    inline void iterate()
	{ 
        t  = 0.4f - 6.0f / (1.0f + x * x + y * y);
        x  = 1.0f + u * (x * cos(t) - y * sin(t));
        y  = u * (x * sin(t) + y * cos(t));
	}
};

////////////////////////////////////////////////////////////////////////////////////////
// Duffing /////////////////////////////////////////////////////////////////////////////
struct duffing
{
	float x = 0.1f;
	float y = 0.1f;

	float a = 2.75f;
	float b = 0.2f;

	inline void iterate()
	{
		x = y;
		y = (-b*x + a*y - y*y*y);
	}
};

////////////////////////////////////////////////////////////////////////////////////////
// Henon ///////////////////////////////////////////////////////////////////////////////
struct henon
{
	float x;
	float y;
    float dy, dx;

	float a = 1.4f;
	float b = 0.3f;

    float t = 1.0f;

	inline void iterate()
	{
		dx = t * (1.0f - a * x * x + y);
		dy = t * b * x;

        x = dx;
        y = dy;
	}
};


////////////////////////////////////////////////////////////////////////////////////////
// Gingerbreadman //////////////////////////////////////////////////////////////////////
struct gingerbreadman
{
	float x;
	float y;

	inline void iterate()
	{
		x = 1.0f - y + abs(x);
		y = x;
	}
};

////////////////////////////////////////////////////////////////////////////////////////
// Van Der Pol /////////////////////////////////////////////////////////////////////////
struct vanderpol
{
	float x = 0.1f;
	float y = 0.1f;
	float f = 1.2f;
    float t = 0.1f;
	float m = 1.0f;

	inline void iterate();
};

inline void vanderpol::iterate()
{
	x += t * y;
	y += t * (m * (f - x * x) * y - x);
}

////////////////////////////////////////////////////////////////////////////////////////
// Kaplan-Yorke ////////////////////////////////////////////////////////////////////////
struct kaplan_yorke
{
	float   x;
	float   y;
    long long a = 0xFFFFFFFF;
    long long b = 2147483647;
    float   t   = 0.1f;
	float   alpha;

	inline void iterate();
};

inline void kaplan_yorke::iterate()
{
    long long aa = 2 * a % b;
	x += t * (float(a) / float(b));
	y += t * (alpha*y + cos(4.0f * M_PI * x));
    a = aa;
}

////////////////////////////////////////////////////////////////////////////////////////
// Rabinovich-Fabrikant ////////////////////////////////////////////////////////////////
struct rabinovich_fabrikant
{
    float gamma = 0.87f;
    float alpha = 1.1f;
    float x = 0.1f, y = 0.1f, z = 0.1f;
    float t = 0.01f;

    inline void iterate();

};

inline void rabinovich_fabrikant::iterate() 
{
    x += t * (y*(x-1+x*x)+gamma*x);
    y += t * (x*(3*z+1-x*x)+gamma*y);
    z += t * (-2*z*(alpha+x*y));
}

////////////////////////////////////////////////////////////////////////////////////////
// Chen-Lee ////////////////////////////////////////////////////////////////////////////
struct chen_lee
{
    float a = 45.0f, b = 3.0f, c = 28.0f;
    float x = 1, y = 1, z = 1;
    float t = 0.0035f;

    inline void iterate();
};

inline void chen_lee::iterate()
{
    x += t * a * (y - x);
    y += t * ((c - a) * x - x*z + c*y);
    z += t * (x*y - b*z);
}

////////////////////////////////////////////////////////////////////////////////////////
// Chua ////////////////////////////////////////////////////////////////////////////////
struct chua
{
    float x = 1, y = 1, z = 1;  // Ins

    float alpha  =  15.6;
    float beta   =  28; 
    float ma     = -1.143;
    float mb     = -0.714;
    float h;
    float t = 0.1f;
    
    float dx;
    float dy;
    float dz;
   
    inline void iterate();
};

inline void chua::iterate()
{
    h  = ma * x + 0.5f * (ma - mb) * (abs(x + 1.0f) - abs(x - 1.0f));
    dx = t * (alpha * (y - x - h));
    dy = t * (x - y + z);
    dz = t * (- beta * y);

    x = dx;
    y = dy;
    z = dz;
}



};
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////