#include "Button.h"

ofEvent<string> Button::buttonEvent;

Button::Button() {
    imgType = Image::NONE;
    visible = true;
    font = nullptr;
    imgPtr = nullptr;
    textColour = ofColor(255, 255, 255);
    borderColour = ofColor(255, 255, 255);
    ofAddListener(ofEvents().mousePressed, this, &Button::mousePressed);
    ofAddListener(ofEvents().draw, this, &Button::draw);
}

//--------------------------------------------------------------

void Button::create(string label, int x, int y, ofTrueTypeFont* fnt, ofImage* img) {
    setCommonValues(label, x, y, fnt);
    imgType = Image::DEFAULT;
    imgPtr = img;
    height = imgPtr->getHeight();
    width = imgPtr->getWidth();
    btn.set(x, y, width, height);
}

//--------------------------------------------------------------

void Button::create(string label, int x, int y, ofTrueTypeFont* fnt, string imgPath) {
    setCommonValues(label, x, y, fnt);
    this->imgPath = imgPath;
    imgType = Image::CUSTOM;
    imgPtr = new ofImage;
    imgPtr->load(imgPath);
    height = imgPtr->getHeight();
    width = imgPtr->getWidth();
    btn.set(x, y, width, height);
}

//--------------------------------------------------------------

void Button::create(string label, int x, int y, float width, float height, int hex, ofTrueTypeFont* fnt) {
    setCommonValues(label, x, y, fnt);
    this->width = width;
    this->height = height;
    colour.setHex(hex);
    btn.set(x, y, width, height);
}

//--------------------------------------------------------------

void Button::setCommonValues(string label, int x, int y, ofTrueTypeFont* fnt) {
    this->label = label;
    this->x = x;
    this->y = y;
    font = fnt;
}

//--------------------------------------------------------------

void Button::mousePressed(ofMouseEventArgs& mouse) {
    if (btn.inside(mouse.x, mouse.y)) {
        ofNotifyEvent(buttonEvent, label);
    }
}

//--------------------------------------------------------------

void Button::draw(ofEventArgs&) {
    if (visible) {
        if (imgType != Image::NONE) {
            ofSetColor(colour);
            imgPtr->draw(btn);
        }
        else {
            // clamp corner radius to half the smallest dimension
            float maxRadius = min(btn.width, btn.height) / 2.0f;
            float safeRadius = min((float)cornerRadius, maxRadius);

            ofSetColor(colour);
            ofDrawRectRounded(btn, safeRadius);

            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(borderColour);
            ofDrawRectRounded(btn, safeRadius);
            ofFill();
        }

        if (font != nullptr && font->isLoaded()) {
            ofSetColor(textColour);
            float textWidth = font->stringWidth(label);
            float textHeight = font->stringHeight(label);
            float textX = btn.x + (btn.width - textWidth) / 2 + labelOffsetX;
            float textY = btn.y + (btn.height + textHeight) / 2 + labelOffsetY;
            font->drawString(label, textX, textY);
        }
    }
}

//--------------------------------------------------------------

void Button::toggle(bool state) {
    if (!state) {
        visible = false;
        ofRemoveListener(ofEvents().mousePressed, this, &Button::mousePressed);
        ofRemoveListener(ofEvents().draw, this, &Button::draw);
    }
    else if (state) {
        visible = true;
        ofAddListener(ofEvents().mousePressed, this, &Button::mousePressed);
        ofAddListener(ofEvents().draw, this, &Button::draw);
    }
}

//--------------------------------------------------------------

void Button::setLabel(const string& newLabel) {
    label = newLabel;
}

//--------------------------------------------------------------

void Button::setLabelOffset(int x, int y) {
    labelOffsetX = x;
    labelOffsetY = y;
}

//--------------------------------------------------------------

void Button::setCornerRadius(int radius) {
    cornerRadius = radius;
}

//--------------------------------------------------------------

void Button::setTextColour(ofColor colour) {
    textColour = colour;
}

//--------------------------------------------------------------

void Button::setBorderColour(ofColor colour) {
    borderColour = colour;
}

//--------------------------------------------------------------

Button::~Button() {
    ofRemoveListener(ofEvents().mousePressed, this, &Button::mousePressed);
    ofRemoveListener(ofEvents().draw, this, &Button::draw);

    if (imgType == Image::CUSTOM && imgPtr != nullptr) {
        delete imgPtr;
        imgPtr = nullptr;
    }
}

//--------------------------------------------------------------