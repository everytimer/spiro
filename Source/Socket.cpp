#include "Socket.h"

Sockets::Sockets(int x, int y, int w, int h, int n)
{
    bay = new cell::patchbay(w, h, n);
    // Outputs /////////////////////////////////////////////
    bay->set_socket(  5,   5, 5, 0, 0x0FF000FF, 0);
    bay->set_socket(  5,  25, 5, 1, 0x0FE000FF, 0);
    bay->set_socket(  5,  45, 5, 2, 0x0FD000FF, 0);
    bay->set_socket(  5,  65, 5, 3, 0x0FC000FF, 0);
    bay->set_socket(  5,  85, 5, 4, 0x0FB000FF, 0);
    // Inputs //////////////////////////////////////////////
    bay->set_socket(293, 105, 5, 5, 0x1FA000FF, 1);
    bay->set_socket(293, 125, 5, 6, 0x1F9000FF, 1);
    bay->set_socket(293, 145, 5, 7, 0x1F8000FF, 1);
    bay->set_socket(293, 165, 5, 8, 0x1F7000FF, 1);
    bay->set_socket(293, 185, 5, 9, 0x1F6000FF, 1);

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
            bmp.setPixelColour (x, y, colour.withAlpha(alpha));
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
        g.setColour (cCordSet[j]);
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
    // g.setColour(cCordColourY);
    // g.drawRect (area);

    drawCords(g, opacity);
    drawSockets(g, cCordColourY);
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
