#pragma once
#include <vector>
#include "catmull_rom.hpp"
#include "containers.hpp"
#include "primitives.hpp"
#include <iostream>
using std::vector;
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
namespace cell {


//////////////////////////////////////////////////////////////////////////////////
// PatchCord /////////////////////////////////////////////////////////////////////

struct patchcord
{
        point2d<float>* data;
        const int   segments = 4;
        catmullrom  spline { segments };
        const int   iterations;
        void process();         // Fill spline data
        patchcord(int);
       ~patchcord();
};


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//  0x   | 00 | FF | 00 |  FF
// ______|____|____|____|_________
//       |    |    |    |> Cord #
//       |    |    |
//       |    |    |> Colour
//       |    |
//       |    |> ID
//       |
//       |> Output = 0; Input > 0
//
//////////////////////////////////////////////////////////////////////////////////
// Socket Data ///////////////////////////////////////////////////////////////////
class socket
{
    public:
        square<uint> bounds {0, 0, 0};
        patchcord cord;
        uint  data = 0;
        bool    io = 0;             // 0: Out - 1: In
        bool    on = false;         // Is connected ?
        socket* to = nullptr;
        const uint* w;
        const uint* h;
        void collapse();            // Collapse to centre
        void drag(const float, const float);    // Drag
        socket(int);  // cord(j) {}
       ~socket();
};

//////////////////////////////////////////////////////////////////////////////////
// Patchbay //////////////////////////////////////////////////////////////////////
class patchbay
{
    public:
        socket* io;
        frame<uint> canvas;
        socket* src = nullptr;
        socket* dst = nullptr;
        const int nodes;              // Number of sockets
        void draw();
        bool down_test(float, float);
        bool up_test(float, float);
        void set_socket(int, int, int, uint, uint);
        void drag(float x, float y);
        void connect(socket*, socket*);
        void disconnect(socket*, socket*);
        patchbay(int, int, int);
       ~patchbay();
};



};
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////