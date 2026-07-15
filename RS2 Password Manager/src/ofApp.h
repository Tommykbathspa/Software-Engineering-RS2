#pragma once
#include "ofMain.h"
#include "Button.h"
#include "PasswordEntry.h"
#include "ScrollBar.h"


class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseScrolled(int x, int y, float scrollX, float scrollY);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void buttonEvent(string& label);

    // login / register screen
    string Email, Password, RePassword;
    bool emailInput, passwordInput, rePasswordInput;
    bool createAccountScreen;
    bool mainScreen;

    ofRectangle cardBG;
    ofRectangle emailBox, passwordBox, rePasswordBox, caEmailBox, caPasswordBox, caRePasswordBox;
    ofTrueTypeFont titleFont, headerFont, labelFont, smallFont;

    Button signInBtn, signUpBtn;
    Button registerBtn, loginAccountBtn;

    // main screen
    string searchString;
    bool searchInput;
    ofRectangle topBar, headerBar, searchBox, addNewBox;

    bool popupOpen;
    string popupName, popupUser, popupPass;
    bool popupNameInput, popupUserInput, popupPassInput;
    ofRectangle popupBG, popupNameBox, popupUserBox, popupPassBox;
    Button popupConfirmBtn, popupCancelBtn;

    bool editPopupOpen;
    int editingRow;
    string editName, editUser, editPass;
    bool editNameInput, editUserInput, editPassInput;
    ofRectangle editPopupBG, editNameBox, editUserBox, editPassBox;
    Button editConfirmBtn, editCancelBtn;

    vector<PasswordEntry> entries;
    vector<PasswordEntry> filteredEntries;
    vector<bool> passwordVisible;

    float scrollOffset;
    float rowHeight;
    ScrollBar scrollBar;
    Button logoutBtn;

    void drawLoginScreen();
    void drawMainScreen();
    void updateFilter();
};