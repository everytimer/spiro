#include "modmatrix.hpp"
namespace cell {



//////////////////////////////////////////////////////////////////////////////////
// PatchCord /////////////////////////////////////////////////////////////////////

void patchcord::process()
{
    spline.calcv();
    Point<float> car;
    float inc = 3.2/(float)iterations;
    float t = 0.0;
    for(int i = 0; i < iterations; i++)
    {
        car = spline.getft(t);
        data[i].x = car.x;
        data[i].y = car.y;
        t += inc;
    }
}

patchcord::patchcord(int j = 8): iterations(j)
{
    data = new point2d<float>[iterations];
}

patchcord::~patchcord()
{
    delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
// Socket ////////////////////////////////////////////////////////////////////////

void socket::collapse()
{
    for(int i = 0; i < cord.segments; i++)
    {
        cord.spline.p[i].x = bounds.xCentre;
        cord.spline.p[i].y = bounds.yCentre;
    }
    cord.process();
}


void socket::drag(const float x, const float y)
{          
    auto xe = x, ye = y;

    if(xe > *w) xe = *w;
    if(xe < 0) xe = 0;
    if(ye > *h) ye = *h;
    if(ye < 0) ye = 0;

    
    float xo = cord.spline.p[0].x;
    float yo = cord.spline.p[0].y;

    cord.spline.p[1].x = (xe - xo) * 0.333 + xo;
    cord.spline.p[2].x = (xe - xo) * 0.666 + xo;

    if(ye < yo)
    {
        cord.spline.p[1].y = abs(yo - ye) * 0.8333 + ye;
        cord.spline.p[2].y = abs(yo - ye) * 0.1666 + ye;
    }

    if(ye > yo)
    {
        cord.spline.p[1].y = abs(yo - ye) * 0.1666 + yo;
        cord.spline.p[2].y = abs(yo - ye) * 0.8333 + yo;
    }

    cord.spline.p[3].x = xe;
    cord.spline.p[3].y = ye;

    cord.process();
}

socket::socket(int n = 32): cord(n)
{

}

socket::~socket() 
{

}


//////////////////////////////////////////////////////////////////////////////////
// Patchbay //////////////////////////////////////////////////////////////////////

void patchbay::connect(socket* I, socket* O)
{
    I->drag(O->bounds.xCentre, O->bounds.yCentre);
    I->on = true;
    O->on = true;
    I->to = O;
    O->to = I;
}

void patchbay::disconnect(socket* I, socket* O)
{
    I->on = false;
    O->on = false;
    I->to = nullptr;
    O->to = nullptr;
}

void patchbay::draw()
{
    for(int i = 0; i < nodes; i++)
    {
        drawSquareFilled<uint>(&canvas, io[i].bounds, io[i].data);
    }
}

bool patchbay::down_test(float x, float y)
{
    auto stamp = canvas.get(x, y); 

    for(int i = 0; i < nodes; i++)
    {
        if(stamp == io[i].data) // Socket is hitted
        {
            std::cout<<"156:Button down on socket: "<<std::hex<<io[i].data<<"\n";
            // Temporary source is free /////////////////////////////////////
            if(io[i].on)   // Already connected?
            {
                src = io[i].to;
                src->drag(io[i].bounds.xCentre, io[i].bounds.yCentre);
                //src->collapse();
                io[i].collapse();
                std::cout<<"164:Button is down - already connected!\n";
                disconnect(&io[i], io[i].to);
                return true;
            }
            else
            {
                src = &io[i];
                std::cout<<"171:New source armed!\n";
                src->collapse();
                return true;
            }
        }
    }
    // Void hitted
    std::cout<<"178:Hit at void \n";
    if(src!=nullptr) 
    {
        src->collapse();
    }
    src = nullptr;
    return false;
}



bool patchbay::up_test(float x, float y)
{
    auto stamp = canvas.get(x, y); 

    for(int i = 0; i < nodes; i++)
    {
        if(stamp == io[i].data) // Socket is hitted
        {
            std::cout<<"197:Button up at socket: "<<std::hex<<io[i].data<<"\n";
            if(src == &io[i]) // Same socket is hitted
            {
                src->collapse();
                src = nullptr;
                std::cout<<"202:Self Hit\n";
                return false;
            }

            else // Other socket is hitted
            {
                // Temprary source is free //////////////
                if(src == nullptr) 
                {
                    std::cout<<"211:No Source ! \n";
                    return false;
                }
                else
                {

                    if(io[i].on)   // Already connected?
                    {
                        io[i].collapse();
                        io[i].to->collapse();
                        disconnect(&io[i], io[i].to);
                        //src->collapse();
                        std::cout<<"223:Already connected!\n";
                        connect(src, &io[i]);
                        src = nullptr;
                        return true;
                    }
                    else
                    {
                        std::cout<<"230:Connected!\n";
                        connect(src, &io[i]);
                        src = nullptr;
                        return true;
                    }
                }
            }
        }
    }

    // Void hitted
    std::cout<<"241:Hit at void \n";
    if(src!=nullptr) 
    {
        src->collapse();
    }
    
    src = nullptr;
    
    return false;
}

void patchbay::drag(float x, float y)
{
    if(src != nullptr)
    {
        src->drag(x, y);
    }
}


patchbay::patchbay(int w, int h, int n): canvas(w, h), nodes(n)
{
    std::cout<<"Width : "<<canvas.width<<"\n";
    std::cout<<"Height: "<<canvas.height<<"\n";
    std::cout<<"Nodes : "<<nodes<<"\n";
    io = new socket[nodes];
    for(int i = 0; i < nodes; i++)
    {
        io[i].w  = &canvas.width;
        io[i].h = &canvas.height;
    }
}

patchbay::~patchbay()
{
    src = nullptr;
    delete[] io;
}

void patchbay::set_socket(int xo, int yo, int radius, uint pos, uint data)
{
    if(pos<nodes)
    {
        io[pos].bounds.xCentre = xo;
        io[pos].bounds.yCentre = yo;
        io[pos].bounds.radius  = radius;
        io[pos].data = data;
        io[pos].collapse();
    }
}



};