#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    emailInput = false;
    passwordInput = false;
    rePasswordInput = false;
    createAccountScreen = false;
    mainScreen = false;
    Email = "";
    Password = "";
    RePassword = "";
    searchString = "Search";
    searchInput = false;
    popupOpen = false;
    editPopupOpen = false;
    editingRow = -1;
    editNameInput = false;
    editUserInput = false;
    editPassInput = false;
    popupName = "App/Website Name";
    popupUser = "Username";
    popupPass = "Password";
    popupNameInput = false;
    popupUserInput = false;
    popupPassInput = false;
    scrollOffset = 0;
    rowHeight = 80;

    titleFont.load("Bungee-Regular.ttf", 57);
    headerFont.load("Bungee-Regular.ttf", 32);
    labelFont.load("Antarctican_Headline_Medium.otf", 31);
    smallFont.load("Antarctican_Headline_Book.otf", 25);


    // card panel
    cardBG.set(130, 95, 1020, 565);

    // login input fields — just used as hit areas, drawn as underlines
    emailBox.set(255, 315, 690, 45);
    passwordBox.set(255, 455, 690, 45);

    // create account screen input hit areas — fields sit higher due to extra field
    caEmailBox.set(255, 245, 690, 45);
    caPasswordBox.set(255, 385, 690, 45);
    caRePasswordBox.set(255, 530, 690, 45);

    // login screen — Sign Up left outlined, Sign In right filled
    signUpBtn.create("Sign Up", 390, 580, 230, 58, 0xFAFAFA, &smallFont);
    signUpBtn.setCornerRadius(29);
    signUpBtn.setTextColour(ofColor(255, 64, 160));
    signUpBtn.setBorderColour(ofColor(255, 64, 160));

    signInBtn.create("Sign In", 640, 580, 230, 58, 0xFF40A0, &smallFont);
    signInBtn.setCornerRadius(29);
    signInBtn.setTextColour(ofColor(255, 255, 255));
    signInBtn.setBorderColour(ofColor(255, 64, 160));

    // create account screen — Sign In left outlined, Sign Up right filled
    loginAccountBtn.create("Sign In", 390, 580, 230, 58, 0xFAFAFA, &smallFont);
    loginAccountBtn.setCornerRadius(29);
    loginAccountBtn.setTextColour(ofColor(255, 64, 160));
    loginAccountBtn.setBorderColour(ofColor(255, 64, 160));
    loginAccountBtn.toggle(false);

    registerBtn.create("Sign Up", 640, 580, 230, 58, 0xFF40A0, &smallFont);
    registerBtn.setCornerRadius(29);
    registerBtn.setTextColour(ofColor(255, 255, 255));
    registerBtn.setBorderColour(ofColor(255, 64, 160));
    registerBtn.toggle(false);

    // main screen
    topBar.set(0, 0, 1280, 90);
    headerBar.set(0, 90, 1245, 65);
    searchBox.set(20, 18, 300, 54);
    addNewBox.set(358, 18, 200, 54);

    logoutBtn.create("Logout", 1100, 18, 155, 54, 0xFAFAFA, &smallFont);
    logoutBtn.setCornerRadius(27);
    logoutBtn.setTextColour(ofColor(255, 64, 160));
    logoutBtn.setBorderColour(ofColor(255, 255, 255));
    logoutBtn.toggle(false);

    // add popup
    popupBG.set(390, 210, 500, 320);
    popupNameBox.set(430, 270, 420, 45);
    popupUserBox.set(430, 340, 420, 45);
    popupPassBox.set(430, 410, 420, 45);

    popupConfirmBtn.create("Add", 490, 470, 120, 45, 0xFF40A0, &smallFont);
    popupConfirmBtn.setCornerRadius(22);
    popupConfirmBtn.toggle(false);

    popupCancelBtn.create("Cancel", 630, 470, 120, 45, 0xFAFAFA, &smallFont);
    popupCancelBtn.setCornerRadius(22);
    popupCancelBtn.setTextColour(ofColor(255, 64, 160));
    popupCancelBtn.setBorderColour(ofColor(255, 64, 160));
    popupCancelBtn.toggle(false);

    // edit popup
    editPopupBG.set(390, 210, 500, 320);
    editNameBox.set(430, 270, 420, 45);
    editUserBox.set(430, 340, 420, 45);
    editPassBox.set(430, 410, 420, 45);

    editConfirmBtn.create("Save", 490, 470, 120, 45, 0xFF40A0, &smallFont);
    editConfirmBtn.setCornerRadius(22);
    editConfirmBtn.toggle(false);

    editCancelBtn.create("Discard", 630, 470, 120, 45, 0xFAFAFA, &smallFont);
    editCancelBtn.setCornerRadius(22);
    editCancelBtn.setTextColour(ofColor(255, 64, 160));
    editCancelBtn.setBorderColour(ofColor(255, 64, 160));
    editCancelBtn.toggle(false);

    scrollBar.setup(1245, 155, 35, 565);

    ofAddListener(Button::buttonEvent, this, &ofApp::buttonEvent);
}

//--------------------------------------------------------------
void ofApp::update() {
    if (searchInput == false && searchString == "") {
        searchString = "Search";
    }
    if (popupNameInput == false && popupName == "") {
        popupName = "App/Website Name";
    }
    if (popupUserInput == false && popupUser == "") {
        popupUser = "Username";
    }
    if (popupPassInput == false && popupPass == "") {
        popupPass = "Password";
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (mainScreen == false) {
        drawLoginScreen();
    }
    else {
        drawMainScreen();
    }
}

//--------------------------------------------------------------
void ofApp::drawLoginScreen() {
    // gradient background — approximate with two rects blended
    ofBackgroundGradient(ofColor(255, 0, 180), ofColor(160, 80, 255), OF_GRADIENT_LINEAR);

    // title
    ofSetColor(255);
    titleFont.drawString("RS2 Password Manager", 135, 75);

    // card
    ofSetColor(235, 235, 235);
    ofDrawRectRounded(cardBG, 8);

    if (createAccountScreen == false) {
        ofSetColor(60, 60, 60);
        headerFont.drawString("Login Account", 460, 145);

        // email label + underline field
        ofSetColor(60, 60, 60);
        labelFont.drawString("Email Address", 255, 285);
        ofSetColor(emailInput ? 255 : 200, emailInput ? 100 : 200, emailInput ? 180 : 200);
        smallFont.drawString(Email.size() > 0 ? Email : "Enter your Email Address", 255, 335);
        ofSetColor(255, 64, 160);
        ofSetLineWidth(2);
        ofDrawLine(255, 348, 945, 348);

        // password label + underline field
        ofSetColor(60, 60, 60);
        labelFont.drawString("Password", 255, 415);
        ofSetColor(passwordInput ? 255 : 200, passwordInput ? 100 : 200, passwordInput ? 180 : 200);
        string displayPass = Password.size() > 0 ? string(Password.size(), '*') : "Enter your Password";
        smallFont.drawString(displayPass, 255, 468);
        ofSetColor(255, 64, 160);
        ofSetLineWidth(2);
        ofDrawLine(255, 481, 945, 481);
    }
    else {
        ofSetColor(60, 60, 60);
        headerFont.drawString("Create Account", 445, 145);

        // email
        ofSetColor(60, 60, 60);
        labelFont.drawString("Email Address", 255, 205);
        ofSetColor(emailInput ? 255 : 200, emailInput ? 100 : 200, emailInput ? 180 : 200);
        smallFont.drawString(Email.size() > 0 ? Email : "Enter your Email Address", 255, 265);
        ofSetColor(255, 64, 160);
        ofSetLineWidth(2);
        ofDrawLine(255, 278, 945, 278);

        // password
        ofSetColor(60, 60, 60);
        labelFont.drawString("Password", 255, 335);
        ofSetColor(passwordInput ? 255 : 200, passwordInput ? 100 : 200, passwordInput ? 180 : 200);
        string displayPass = Password.size() > 0 ? string(Password.size(), '*') : "Enter your Password";
        smallFont.drawString(displayPass, 255, 395);
        ofSetColor(255, 64, 160);
        ofSetLineWidth(2);
        ofDrawLine(255, 408, 945, 408);

        // re-enter password
        ofSetColor(60, 60, 60);
        labelFont.drawString("Re-enter Password", 255, 465);
        ofSetColor(rePasswordInput ? 255 : 200, rePasswordInput ? 100 : 200, rePasswordInput ? 180 : 200);
        string displayRePass = RePassword.size() > 0 ? string(RePassword.size(), '*') : "Re-enter your Password";
        smallFont.drawString(displayRePass, 255, 540);
        ofSetColor(255, 64, 160);
        ofSetLineWidth(2);
        ofDrawLine(255, 553, 945, 553);
    }
}

//--------------------------------------------------------------
void ofApp::drawMainScreen() {
    ofBackground(245, 245, 245);

    // top bar gradient
    ofMesh grad;
    grad.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    grad.addVertex(glm::vec3(0, 0, 0));       grad.addColor(ofColor(255, 0, 180));
    grad.addVertex(glm::vec3(1280, 0, 0));    grad.addColor(ofColor(160, 80, 255));
    grad.addVertex(glm::vec3(0, 90, 0));      grad.addColor(ofColor(255, 0, 180));
    grad.addVertex(glm::vec3(1280, 90, 0));   grad.addColor(ofColor(160, 80, 255));
    grad.draw();

    // search box
    if (searchInput == false) { ofSetColor(220, 180, 240, 180); }
    else { ofSetColor(255, 255, 255, 220); }
    ofDrawRectRounded(searchBox, 27);
    ofNoFill();
    ofSetLineWidth(1.5);
    ofSetColor(255, 255, 255);
    ofDrawRectRounded(searchBox, 27);
    ofFill();
    ofSetColor(searchInput ? 30 : 220, searchInput ? 30 : 220, searchInput ? 30 : 220);
    smallFont.drawString(searchString, 35, 53);
    // search icon
    ofSetColor(200, 200, 220);
    ofNoFill();
    ofSetLineWidth(2.5);
    ofDrawCircle(288, 44, 11);
    ofDrawLine(296, 52, 306, 62);
    ofFill();

    // add new box
    ofSetColor(255, 255, 255, 30);
    ofDrawRectRounded(addNewBox, 27);
    ofNoFill();
    ofSetLineWidth(1.5);
    ofSetColor(255, 255, 255);
    ofDrawRectRounded(addNewBox, 27);
    ofFill();
    ofSetColor(255);
    smallFont.drawString("Add New", 375, 53);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(533, 44, 11);
    ofFill();
    ofSetColor(255);
    ofDrawLine(533, 36, 533, 52);
    ofDrawLine(525, 44, 541, 44);

    // title
    ofSetColor(255);
    headerFont.drawString("Password Manager", 585, 65);

    // header bar
    ofSetColor(220, 220, 220);
    ofDrawRectangle(headerBar);
    ofSetColor(100, 100, 100);
    smallFont.drawString("App/Website Name", 160, 133);
    smallFont.drawString("Username", 560, 133);
    smallFont.drawString("Password", 940, 133);

    // scrollbar track
    ofSetColor(220, 220, 220);
    ofDrawRectangle(1245, 155, 35, 565);

    ofPushMatrix();
    ofTranslate(0, -scrollOffset);

    float viewStart = scrollOffset;
    float viewEnd = scrollOffset + 565;

    for (int i = 0; i < filteredEntries.size(); i++) {
        float rowY = 155 + i * rowHeight;
        if (rowY + rowHeight < viewStart || rowY > viewEnd) continue;

        if (i % 2 == 0) { ofSetColor(235, 235, 235); }
        else { ofSetColor(248, 248, 248); }
        ofDrawRectangle(0, rowY, 1245, rowHeight);

        ofSetColor(80, 80, 80);
        smallFont.drawString(filteredEntries[i].appName, 60, rowY + 50);
        smallFont.drawString(filteredEntries[i].username, 460, rowY + 50);

        // find entries index for passwordVisible
        int entriesIndex = -1;
        for (int j = 0; j < entries.size(); j++) {
            if (entries[j].appName == filteredEntries[i].appName) {
                entriesIndex = j;
                break;
            }
        }
        if (entriesIndex >= 0 && entriesIndex < passwordVisible.size() && passwordVisible[entriesIndex] == true) {
            smallFont.drawString(filteredEntries[i].password, 860, rowY + 50);
        }
        else {
            string masked = string(filteredEntries[i].password.size(), '*');
            smallFont.drawString(masked, 860, rowY + 50);
        }

        // pencil icon
        ofSetColor(120, 120, 120);
        ofSetLineWidth(1.5);
        ofNoFill();
        ofDrawLine(18, rowY + 28, 30, rowY + 16);
        ofDrawLine(30, rowY + 16, 36, rowY + 22);
        ofDrawLine(36, rowY + 22, 24, rowY + 34);
        ofDrawLine(24, rowY + 34, 18, rowY + 28);
        ofDrawLine(18, rowY + 28, 15, rowY + 38);
        ofDrawLine(15, rowY + 38, 24, rowY + 34);
        ofFill();

        // eye icon
        ofSetColor(120, 120, 120);
        ofNoFill();
        ofSetLineWidth(1.5);
        ofDrawEllipse(1185, rowY + 27, 36, 20);
        ofDrawCircle(1185, rowY + 27, 6);
        ofFill();
    }

    ofPopMatrix();

    float contentH = max((float)filteredEntries.size() * rowHeight, 1.0f);
    scrollBar.draw(contentH, 565, scrollOffset);



    // add popup
    if (popupOpen == true) {
        ofSetColor(0, 0, 0, 120);
        ofDrawRectangle(0, 0, 1280, 720);

        ofSetColor(235, 235, 235);
        ofDrawRectRounded(popupBG, 12);

        ofSetColor(51, 51, 51);
        labelFont.drawString("Add New Entry", 520, 258);

        // name field
        ofSetColor(popupNameInput ? 50 : 160, popupNameInput ? 50 : 160, popupNameInput ? 50 : 160);
        smallFont.drawString(popupName, 440, 305);
        ofSetColor(255, 64, 160);
        ofSetLineWidth(2);
        ofDrawLine(430, 315, 850, 315);

        // user field
        ofSetColor(popupUserInput ? 50 : 160, popupUserInput ? 50 : 160, popupUserInput ? 50 : 160);
        smallFont.drawString(popupUser, 440, 375);
        ofSetColor(255, 64, 160);
        ofDrawLine(430, 385, 850, 385);

        // pass field
        ofSetColor(popupPassInput ? 50 : 160, popupPassInput ? 50 : 160, popupPassInput ? 50 : 160);
        smallFont.drawString(popupPass, 440, 445);
        ofSetColor(255, 64, 160);
        ofDrawLine(430, 455, 850, 455);
    }

    // edit popup
    if (editPopupOpen == true) {
        ofSetColor(0, 0, 0, 120);
        ofDrawRectangle(0, 0, 1280, 720);

        ofSetColor(235, 235, 235);
        ofDrawRectRounded(editPopupBG, 12);

        ofSetColor(51, 51, 51);
        labelFont.drawString("Edit Entry", 555, 258);

        ofSetColor(editNameInput ? 50 : 160, editNameInput ? 50 : 160, editNameInput ? 50 : 160);
        smallFont.drawString(editName, 440, 305);
        ofSetColor(255, 64, 160);
        ofSetLineWidth(2);
        ofDrawLine(430, 315, 850, 315);

        ofSetColor(editUserInput ? 50 : 160, editUserInput ? 50 : 160, editUserInput ? 50 : 160);
        smallFont.drawString(editUser, 440, 375);
        ofSetColor(255, 64, 160);
        ofDrawLine(430, 385, 850, 385);

        ofSetColor(editPassInput ? 50 : 160, editPassInput ? 50 : 160, editPassInput ? 50 : 160);
        smallFont.drawString(editPass, 440, 445);
        ofSetColor(255, 64, 160);
        ofDrawLine(430, 455, 850, 455);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (mainScreen == false) {
        if (key == OF_KEY_BACKSPACE) {
            if (emailInput && Email.size() > 0) Email.pop_back();
            else if (passwordInput && Password.size() > 0) Password.pop_back();
            else if (rePasswordInput && RePassword.size() > 0) RePassword.pop_back();
        }
        else if (key >= 32 && key < 128) {
            if (emailInput) Email += (char)key;
            if (passwordInput) Password += (char)key;
            if (rePasswordInput) RePassword += (char)key;
        }
    }
    else {
        if (key == OF_KEY_BACKSPACE) {
            if (searchInput && searchString.size() > 0) { searchString.pop_back(); updateFilter(); }
            else if (popupNameInput && popupName.size() > 0) popupName.pop_back();
            else if (popupUserInput && popupUser.size() > 0) popupUser.pop_back();
            else if (popupPassInput && popupPass.size() > 0) popupPass.pop_back();
            else if (editNameInput && editName.size() > 0) editName.pop_back();
            else if (editUserInput && editUser.size() > 0) editUser.pop_back();
            else if (editPassInput && editPass.size() > 0) editPass.pop_back();
        }
        else if (key >= 32 && key < 128) {
            if (searchInput) { searchString += (char)key; updateFilter(); }
            if (popupNameInput) popupName += (char)key;
            if (popupUserInput) popupUser += (char)key;
            if (popupPassInput) popupPass += (char)key;
            if (editNameInput) editName += (char)key;
            if (editUserInput) editUser += (char)key;
            if (editPassInput) editPass += (char)key;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (mainScreen == false) {
        if (emailBox.inside(x, y) && emailInput == false) {
            emailInput = true;
            passwordInput = false;
            rePasswordInput = false;
        }
        else if (passwordBox.inside(x, y) && passwordInput == false) {
            passwordInput = true;
            emailInput = false;
            rePasswordInput = false;
        }
        else if (rePasswordBox.inside(x, y) && rePasswordInput == false && createAccountScreen == true) {
            rePasswordInput = true;
            emailInput = false;
            passwordInput = false;
        }
        else {
            emailInput = false;
            passwordInput = false;
            rePasswordInput = false;
        }
        return;
    }

    // edit popup clicks
    if (editPopupOpen == true) {
        if (editNameBox.inside(x, y) && editNameInput == false) {
            editNameInput = true; editUserInput = false; editPassInput = false;
        }
        else if (editUserBox.inside(x, y) && editUserInput == false) {
            editUserInput = true; editNameInput = false; editPassInput = false;
        }
        else if (editPassBox.inside(x, y) && editPassInput == false) {
            editPassInput = true; editNameInput = false; editUserInput = false;
        }
        else if (!editNameBox.inside(x, y) && !editUserBox.inside(x, y) && !editPassBox.inside(x, y)) {
            editNameInput = false; editUserInput = false; editPassInput = false;
        }
        return;
    }

    // add popup clicks
    if (popupOpen == true) {
        if (popupNameBox.inside(x, y) && popupNameInput == false) {
            popupNameInput = true; popupUserInput = false; popupPassInput = false;
            if (popupName == "App/Website Name") popupName = "";
        }
        else if (popupUserBox.inside(x, y) && popupUserInput == false) {
            popupUserInput = true; popupNameInput = false; popupPassInput = false;
            if (popupUser == "Username") popupUser = "";
        }
        else if (popupPassBox.inside(x, y) && popupPassInput == false) {
            popupPassInput = true; popupNameInput = false; popupUserInput = false;
            if (popupPass == "Password") popupPass = "";
        }
        else if (!popupNameBox.inside(x, y) && !popupUserBox.inside(x, y) && !popupPassBox.inside(x, y)) {
            popupNameInput = false; popupUserInput = false; popupPassInput = false;
        }
        return;
    }

    // search box
    if (searchBox.inside(x, y) && searchInput == false) {
        searchInput = true;
        searchString = "";
    }
    else if (!searchBox.inside(x, y)) {
        searchInput = false;
    }

    // add new box
    if (addNewBox.inside(x, y)) {
        popupOpen = true;
        popupNameInput = false; popupUserInput = false; popupPassInput = false;
        popupConfirmBtn.toggle(true);
        popupCancelBtn.toggle(true);
        return;
    }

    // scrollbar
    float contentH = filteredEntries.size() * rowHeight;
    scrollBar.mousePressed(x, y, contentH, 565, scrollOffset);

    // row interactions
    float adjustedY = y + scrollOffset - 155;
    int rowIndex = (int)(adjustedY / rowHeight);

    if (rowIndex >= 0 && rowIndex < filteredEntries.size() && x < 1245 && y > 155) {
        ofRectangle pencilRect(5, 155 + rowIndex * rowHeight - scrollOffset + 10, 45, 45);
        ofRectangle eyeRect(1160, 155 + rowIndex * rowHeight - scrollOffset + 10, 55, 40);

        if (pencilRect.inside(x, y)) {
            editingRow = rowIndex;
            editName = filteredEntries[rowIndex].appName;
            editUser = filteredEntries[rowIndex].username;
            editPass = filteredEntries[rowIndex].password;
            editNameInput = false; editUserInput = false; editPassInput = false;
            editPopupOpen = true;
            editConfirmBtn.toggle(true);
            editCancelBtn.toggle(true);
        }
        else if (eyeRect.inside(x, y)) {
            int entriesIndex = -1;
            for (int i = 0; i < entries.size(); i++) {
                if (entries[i].appName == filteredEntries[rowIndex].appName) {
                    entriesIndex = i;
                    break;
                }
            }
            if (entriesIndex >= 0 && entriesIndex < passwordVisible.size()) {
                passwordVisible[entriesIndex] = !passwordVisible[entriesIndex];
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    if (mainScreen == false) return;
    float contentH = filteredEntries.size() * rowHeight;
    scrollOffset -= scrollY * 20;
    scrollOffset = max(0.0f, min(scrollOffset, max(0.0f, contentH - 565)));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (mainScreen == false) return;
    float contentH = filteredEntries.size() * rowHeight;
    float newOffset = scrollBar.mouseDragged(x, y, contentH, 565);
    if (newOffset >= 0) scrollOffset = newOffset;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    scrollBar.mouseReleased();
}

//--------------------------------------------------------------
void ofApp::buttonEvent(string& label) {
    if (label == "Sign Up") {
        createAccountScreen = true;
        emailInput = false; passwordInput = false; rePasswordInput = false;
        Email = ""; Password = ""; RePassword = "";
        signInBtn.toggle(false); signUpBtn.toggle(false);
        registerBtn.toggle(true); loginAccountBtn.toggle(true);
    }
    else if (label == "Sign In") {
        if (createAccountScreen == true) {
            // go back to login screen
            createAccountScreen = false;
            emailInput = false; passwordInput = false; rePasswordInput = false;
            Email = ""; Password = ""; RePassword = "";
            signInBtn.toggle(true); signUpBtn.toggle(true);
            registerBtn.toggle(false); loginAccountBtn.toggle(false);
        }
        else {
            // go to main screen
            mainScreen = true;
            signInBtn.toggle(false); signUpBtn.toggle(false);
            logoutBtn.toggle(true);
            updateFilter();
        }
    }
    else if (label == "Register") {
        mainScreen = true;
        registerBtn.toggle(false); loginAccountBtn.toggle(false);
        logoutBtn.toggle(true);
        updateFilter();
    }
    else if (label == "Logout") {
        mainScreen = false;
        createAccountScreen = false;
        emailInput = false; passwordInput = false;
        Email = ""; Password = "";
        signInBtn.toggle(true); signUpBtn.toggle(true);
        logoutBtn.toggle(false);
    }
    else if (label == "Add") {
        if (popupName != "App/Website Name" && popupName.size() > 0) {
            PasswordEntry newEntry;
            newEntry.appName = popupName;
            newEntry.username = popupUser == "Username" ? "" : popupUser;
            newEntry.password = popupPass == "Password" ? "" : popupPass;
            entries.push_back(newEntry);
            passwordVisible.push_back(false);
            updateFilter();
            popupName = "App/Website Name"; popupUser = "Username"; popupPass = "Password";
        }
        popupOpen = false;
        popupNameInput = false; popupUserInput = false; popupPassInput = false;
        popupConfirmBtn.toggle(false);
        popupCancelBtn.toggle(false);
    }
    else if (label == "Cancel") {
        popupOpen = false;
        popupNameInput = false; popupUserInput = false; popupPassInput = false;
        popupName = "App/Website Name"; popupUser = "Username"; popupPass = "Password";
        popupConfirmBtn.toggle(false);
        popupCancelBtn.toggle(false);
    }
    else if (label == "Save") {
        if (editingRow >= 0 && editingRow < filteredEntries.size()) {
            filteredEntries[editingRow].appName = editName;
            filteredEntries[editingRow].username = editUser;
            filteredEntries[editingRow].password = editPass;
            for (int i = 0; i < entries.size(); i++) {
                if (entries[i].appName == filteredEntries[editingRow].appName) {
                    entries[i] = filteredEntries[editingRow];
                }
            }
        }
        editPopupOpen = false;
        editingRow = -1;
        editNameInput = false; editUserInput = false; editPassInput = false;
        editConfirmBtn.toggle(false);
        editCancelBtn.toggle(false);
    }
    else if (label == "Discard") {
        editPopupOpen = false;
        editingRow = -1;
        editNameInput = false; editUserInput = false; editPassInput = false;
        editConfirmBtn.toggle(false);
        editCancelBtn.toggle(false);
    }
}

//--------------------------------------------------------------
void ofApp::updateFilter() {
    filteredEntries.clear();
    for (int i = 0; i < entries.size(); i++) {
        if (searchString == "Search" || searchString.size() == 0) {
            filteredEntries.push_back(entries[i]);
        }
        else {
            string entryLower = entries[i].appName;
            string searchLower = searchString;
            for (int j = 0; j < entryLower.size(); j++) entryLower[j] = tolower(entryLower[j]);
            for (int j = 0; j < searchLower.size(); j++) searchLower[j] = tolower(searchLower[j]);
            if (entryLower.find(searchLower) != string::npos) {
                filteredEntries.push_back(entries[i]);
            }
        }
    }
    while (passwordVisible.size() < entries.size()) passwordVisible.push_back(false);
    scrollOffset = 0;
    editingRow = -1;
}