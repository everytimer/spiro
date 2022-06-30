#include "Socket.h"



Sockets::Sockets(int w, int h, int n)
{
    bay = new cell::patchbay(w, h, n);
    /////////////////////////////////////////////////
    // Inputs ///////////////////////////////////////
    // Operator A ///////////////////////////////////
    bay->set_socket(  37,   7, 5,  0, 0x0FF00005, 1);
    bay->set_socket(  37,  31, 5,  1, 0x0FE00000, 1);
    bay->set_socket(  37,  55, 5,  2, 0x0FD00000, 1);
    bay->set_socket(  37,  79, 5,  3, 0x0FC00002, 1);
    bay->set_socket(  37, 103, 5,  4, 0x0FB00003, 1);
    bay->set_socket(  37, 127, 5,  5, 0x0FA00004, 1);
    // Operator B ///////////////////////////////////
    bay->set_socket( 133,   7, 5,  6, 0x0F900005, 1);
    bay->set_socket( 133,  31, 5,  7, 0x0F800000, 1);
    bay->set_socket( 133,  55, 5,  8, 0x0F700000, 1);
    bay->set_socket( 133,  79, 5,  9, 0x0F600002, 1);
    bay->set_socket( 133, 103, 5, 10, 0x0F500003, 1);
    bay->set_socket( 133, 127, 5, 11, 0x0F400004, 1);
    // Operator C ///////////////////////////////////
    bay->set_socket( 229,   7, 5, 12, 0x0F300005, 1);
    bay->set_socket( 229,  31, 5, 13, 0x0F200000, 1);
    bay->set_socket( 229,  55, 5, 14, 0x0F100000, 1);
    bay->set_socket( 229,  79, 5, 15, 0x0F000002, 1);
    bay->set_socket( 229, 103, 5, 16, 0x0EF00003, 1);
    bay->set_socket( 229, 127, 5, 17, 0x0EE00004, 1);
    // Operator D ///////////////////////////////////
    bay->set_socket( 325,   7, 5, 18, 0x0ED00005, 1);
    bay->set_socket( 325,  31, 5, 19, 0x0EC00000, 1);
    bay->set_socket( 325,  55, 5, 20, 0x0EB00000, 1);
    bay->set_socket( 325,  79, 5, 21, 0x0EA00002, 1);
    bay->set_socket( 325, 103, 5, 22, 0x0E900003, 1);
    bay->set_socket( 325, 127, 5, 23, 0x0E800004, 1);
    /////////////////////////////////////////////////
    // Outputs //////////////////////////////////////
    // Operator A ///////////////////////////////////
    bay->set_socket(  75,   7, 5, 24, 0x08F00005, 0);
    bay->set_socket(  75,  31, 5, 25, 0x08E00005, 0);
    bay->set_socket(  75,  55, 5, 26, 0x08D00005, 0);
    // Operator B ///////////////////////////////////
    bay->set_socket( 171,   7, 5, 27, 0x08C00005, 0);
    bay->set_socket( 171,  31, 5, 28, 0x08B00005, 0);
    bay->set_socket( 171,  55, 5, 29, 0x08A00005, 0);
    // Operator C ///////////////////////////////////
    bay->set_socket( 267,   7, 5, 30, 0x08900005, 0);
    bay->set_socket( 267,  31, 5, 31, 0x08800005, 0);
    bay->set_socket( 267,  55, 5, 32, 0x08700005, 0);
    // Operator D ///////////////////////////////////
    bay->set_socket( 363,   7, 5, 33, 0x08600005, 0);
    bay->set_socket( 363,  31, 5, 34, 0x08500005, 0);
    bay->set_socket( 363,  55, 5, 35, 0x08400005, 0);
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    bay->draw();
};

Sockets::~Sockets()
{
    delete bay;
}

void Sockets::drawIns(juce::Graphics& g, juce::Colour colour, int io = -1)
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
        g.setColour (colour_set[j].withAlpha(alpha));
        for(int i=0; i<bay->io[j].cord.iterations; i++)
        {
            pre = car;
            car = bay->io[j].cord.data[i];
            g.drawLine(pre.x, pre.y, car.x, car.y, 3.0f);
        }
    }
}


void Sockets::paint (juce::Graphics& g)
{
    //g.fillAll (cGreyLcd.withAlpha (0.1f));
    // g.setColour(colour_set[0]);
    // g.drawRect (area);

    drawCords(g, 0.5f);
    drawSockets(g, colour_set[0]);
    // drawIns(g, cAsphaltGrey, 0);
}

void Sockets::resized ()
{
    area = getLocalBounds();
}
        
void Sockets::mouseDown(const juce::MouseEvent& event)
{
    if (bay->down_test(event.x, event.y))
    setMouseCursor (juce::MouseCursor::CrosshairCursor);
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
    setMouseCursor (juce::MouseCursor::NormalCursor);
    repaint();
}
