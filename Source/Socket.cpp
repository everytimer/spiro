#include "Socket.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sockets::Sockets(int w, int h, int n)
{
    bay = new cell::patchbay(w, h, n);
    /////////////////////////////////////////////////
    // Inputs ///////////////////////////////////////
    // Operator A ///////////////////////////////////
    bay->set_socket(  37,   7, 5,  0, 0x0FF00009, 1);
    bay->set_socket(  37,  31, 5,  1, 0x0FE00009, 1);
    bay->set_socket(  37,  55, 5,  2, 0x0FD00009, 1);
    bay->set_socket(  37,  79, 5,  3, 0x0FC00009, 1);
    bay->set_socket(  37, 103, 5,  4, 0x0FB00009, 1);
    bay->set_socket(  37, 127, 5,  5, 0x0FA00009, 1);
    // Operator B ///////////////////////////////////
    bay->set_socket( 137,   7, 5,  6, 0x0F900009, 1);
    bay->set_socket( 137,  31, 5,  7, 0x0F800009, 1);
    bay->set_socket( 137,  55, 5,  8, 0x0F700009, 1);
    bay->set_socket( 137,  79, 5,  9, 0x0F600009, 1);
    bay->set_socket( 137, 103, 5, 10, 0x0F500009, 1);
    bay->set_socket( 137, 127, 5, 11, 0x0F400009, 1);
    // Operator C ///////////////////////////////////
    bay->set_socket( 237,   7, 5, 12, 0x0F300009, 1);
    bay->set_socket( 237,  31, 5, 13, 0x0F200009, 1);
    bay->set_socket( 237,  55, 5, 14, 0x0F100009, 1);
    bay->set_socket( 237,  79, 5, 15, 0x0F000009, 1);
    bay->set_socket( 237, 103, 5, 16, 0x0EF00009, 1);
    bay->set_socket( 237, 127, 5, 17, 0x0EE00009, 1);
    // Operator D ///////////////////////////////////
    bay->set_socket( 337,   7, 5, 18, 0x0ED00009, 1);
    bay->set_socket( 337,  31, 5, 19, 0x0EC00009, 1);
    bay->set_socket( 337,  55, 5, 20, 0x0EB00009, 1);
    bay->set_socket( 337,  79, 5, 21, 0x0EA00009, 1);
    bay->set_socket( 337, 103, 5, 22, 0x0E900009, 1);
    bay->set_socket( 337, 127, 5, 23, 0x0E800009, 1);
    /////////////////////////////////////////////////
    // Outputs //////////////////////////////////////
    // Operator A ///////////////////////////////////
    bay->set_socket(  75,   7, 5, 24, 0x08F00009, 0);
    bay->set_socket(  75,  31, 5, 25, 0x08E00009, 0);
    bay->set_socket(  75,  55, 5, 26, 0x08D00009, 0);
    // Operator B ///////////////////////////////////
    bay->set_socket( 175,   7, 5, 27, 0x08C00009, 0);
    bay->set_socket( 175,  31, 5, 28, 0x08B00009, 0);
    bay->set_socket( 175,  55, 5, 29, 0x08A00009, 0);
    // Operator C ///////////////////////////////////
    bay->set_socket( 275,   7, 5, 30, 0x08900009, 0);
    bay->set_socket( 275,  31, 5, 31, 0x08800009, 0);
    bay->set_socket( 275,  55, 5, 32, 0x08700009, 0);
    // Operator D ///////////////////////////////////
    bay->set_socket( 375,   7, 5, 33, 0x08600009, 0);
    bay->set_socket( 375,  31, 5, 34, 0x08500009, 0);
    bay->set_socket( 375,  55, 5, 35, 0x08400009, 0);
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    bay->draw();
};

Sockets::~Sockets()
{
    delete bay;
}

void Sockets::drawOuts(juce::Graphics& g, juce::Colour colour, int io = -1)
{
    if(io>-1)
    {
    for(int j = 0; j < bay->nodes; j++)
    {
        if((bay->io[j].route == true)&&(io == 1))
        {
        g.setColour (colour);
        g.fillRect(  int(bay->io[j].bounds.xCentre - bay->io[j].bounds.radius + 2),
                         bay->io[j].bounds.yCentre - bay->io[j].bounds.radius + 2,
                         bay->io[j].bounds.radius * 2 - 3,
                         bay->io[j].bounds.radius * 2 - 3);
        }

        if((bay->io[j].route == false)&&(io == 0))
        {
        g.setColour (colour);
        g.fillRect(  int(bay->io[j].bounds.xCentre - bay->io[j].bounds.radius + 2),
                         bay->io[j].bounds.yCentre - bay->io[j].bounds.radius + 2,
                         bay->io[j].bounds.radius * 2 - 3,
                         bay->io[j].bounds.radius * 2 - 3);
        }
    }
    }
}


void Sockets::drawSockets(juce::Graphics& g, juce::Colour colour)
{
    auto yo = area.getY();
    auto xo = area.getX();
            
    auto h  = area.getHeight();
    auto w  = area.getWidth();
            
    static auto layer = juce::Image (juce::Image::PixelFormat::ARGB, w, h, true);
    static juce::Image::BitmapData bmp(layer, juce::Image::BitmapData::ReadWriteMode::readWrite);

    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            auto c = bay->canvas.get(x, y);
            float alpha = c ? 1.0f : 0.0f;
            bmp.setPixelColour (x, y, colour_set[c&0xFF].withAlpha(alpha));
        }
    }
    g.setOpacity (1.0f);
    g.drawImageAt(layer, xo, yo);
}

void Sockets::drawCords(juce::Graphics& g, float alpha)
{
    for(int j = 0; j < bay->nodes; j++)
    {
        cell::point2d<float> pre , car = bay->io[j].cord.data[0];
        g.setColour (colour_set[1].withAlpha(alpha));
        for(int i=0; i<bay->io[j].cord.iterations; i++)
        {
            pre = car;
            car = bay->io[j].cord.data[i];
            g.drawLine(pre.x, pre.y, car.x, car.y, 2.0f);
        }
    }
}


void Sockets::paint (juce::Graphics& g)
{
    drawCords(g, 1.0f);
    drawSockets(g, colour_set[0]);
}

void Sockets::resized ()
{
    area = getLocalBounds();
}
        
void Sockets::mouseDown(const juce::MouseEvent& event)
{
    auto t = bay->down_test(event.x, event.y);
    if (t == 1)
    {
        i_armed = true;
        setMouseCursor (juce::MouseCursor::CrosshairCursor);
    }
    if (t == -1)
    {
        o_armed = true;
        setMouseCursor (juce::MouseCursor::CrosshairCursor);
    }
    repaint();
}

void Sockets::mouseDrag (const juce::MouseEvent& event)
{
    bay->drag(event.x, event.y);
    repaint();
}

void Sockets::mouseUp (const juce::MouseEvent& event)
{
    bay->up_test(event.x, event.y);
    i_armed = false;
    o_armed = false;
    setMouseCursor (juce::MouseCursor::NormalCursor);
    repaint();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////