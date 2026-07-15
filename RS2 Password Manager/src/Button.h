#pragma once
#include "ofMain.h"

class Button {
    int x, y;
    int cornerRadius = 0;
    float width, height;
    float labelOffsetX = 0;
    float labelOffsetY = 0;
    ofColor colour;
    ofColor textColour;
    ofColor borderColour;
    string imgPath, label;
    bool visible;
    ofRectangle btn;
    ofImage* imgPtr;
    ofTrueTypeFont* font;
    enum class Image { NONE, CUSTOM, DEFAULT };
    Image imgType;
    void mousePressed(ofMouseEventArgs& mouse);
    void setCommonValues(string label, int x, int y, ofTrueTypeFont* fnt);
    void draw(ofEventArgs&);
public:
    static ofEvent<string> buttonEvent;
    Button();
    ~Button();
    void create(string label, int x, int y, ofTrueTypeFont* fnt, ofImage* img);
    void create(string label, int x, int y, ofTrueTypeFont* fnt, string imgpath);
    void create(string label, int x, int y, float width, float height, int hex, ofTrueTypeFont* fnt);
    void setLabel(const string& newLabel);
    void setLabelOffset(int x, int y);
    void setCornerRadius(int radius);
    void setTextColour(ofColor colour);
    void setBorderColour(ofColor colour);
    void toggle(bool state);
};