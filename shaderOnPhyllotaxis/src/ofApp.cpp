#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();

    if (!ofIsGLProgrammableRenderer()) {
        ofLogError("this app supports only open the programmable render pipeline");
        return 1;
    } else {
        shader.load(shadersFolder+"/simple.vert", shadersFolder+"/simple.frag");
    };
    
    addGui();
    light.setPointLight();
    // see light docs http://openframeworks.cc/documentation/gl/ofLight/
    // https://forum.openframeworks.cc/t/understanding-oflight/26230/3
    light.setup();
    light.enable();
    light.setPosition(lightPos);


    for (int i = 0; i < n_cubes; i++) {
        children.push_back(ofBoxPrimitive(5,5,5));
    }

    // iterate and position items
    float rad = ofDegToRad(137.5);
    float spread = 0.3;
    for (int i = 0;  i < n_cubes; i++) {
        ofVec3f pos;
        pos = ofxPhyllotaxis::simple(i, rad, spread);
        children[i].setPosition(pos);
    }

    //AUDIO SETUP
    sample.load(ofToDataPath("sound.wav"));
    sampleRate 	= 44100;
    bufferSize	= 512;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    //END AUDIO SETUP


}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetBackgroundColor(bgColor);
    float rad = ofDegToRad(degree);
    for (int i = 0;  i < n_cubes;i++) {
        ofVec3f pos;
        if (selectedType == "simple") {
            pos = ofxPhyllotaxis::simple(i, rad, spread);
        }

        if (selectedType == "conical") {
            pos = ofxPhyllotaxis::conical(i, rad, spread, extrude);
        }

        if (selectedType == "apple") {
            pos = ofxPhyllotaxis::apple(i, rad, spread, n_cubes);
        }
        children[i].setPosition(pos);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    shader.begin();

    shader.setUniform3f("lightPos", light.getPosition());
    shader.setUniform4f("materialColor", ofColor(materialColor));
    shader.setUniform1f("displaceAmount", smoothedVolume * displaceAmount);

    for (int i = 0;  i < n_cubes;i++) {
        children[i].draw();
    }
    
    shader.end();
    //light.draw();
    cam.end();

    maybeDrawGui();
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    float rms = 0.0;
    int numCounted = 0;
    for (int i = 0; i < bufferSize; i++){
        wave = sample.play();
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];

        //rms calculation as explained here http://openframeworks.cc/ofBook/chapters/sound.html
        float left = outputs [0];
        float right = outputs[1];
        rms += left * left;
        rms += right * right;
        numCounted += 2;
    }

    rms /= (float)numCounted;
    rms = sqrt(rms);

    if (enableSmooth) {
        smoothedVolume *= smoothedVal;
        smoothedVolume += 0.07 * rms;
    } else {
        smoothedVolume = rms;
    }
}

// GUI
void ofApp::addGui(){
    gui.setup();
    gui.setPosition(ofPoint(0, 30));
    gui.add(materialColor.setup("object color",
                                ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(bgColor.setup("bg color",
                                ofColor(37, 203, 206), ofColor(0, 0), ofColor(255, 255)));
    gui.add(degree.setup("degree", 137.5, 130.00, 140.00));
    gui.add(displaceAmount.setup("displacement", 10.0, 0.0, 50.0));
    gui.add(spread.setup("spread", 11, 2, 40));
    gui.add(extrude.setup("extrude", 0.3, 0.01, 0.90));
}

void ofApp::maybeDrawGui(){
    if(!hideGui){
        ofDisableDepthTest();
        gui.draw();
        ofPushStyle();
        string displayGui = "press 'g' to toggle the gui, up and down to change presets";
        ofDrawBitmapString(displayGui, 0, 10);
        string types = "press 1, 2, 3 to try different implementation";
        ofDrawBitmapString(types, 5, 20);
        string currentType = "current: "+ selectedType;
        ofDrawBitmapString(currentType, 5, 30);
        //fps
        string msg = "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
        ofEnableDepthTest();
        ofPopStyle();
    }
}

void ofApp::keyPressed(int key){

    switch(key){
        case 'g':
            hideGui = !hideGui;
            break;
        case 49:
            selectedType = "conical";
            break;
        case 50:
            selectedType = "apple";
            break;
        case 51:
            selectedType = "simple";
            break;
        default:
            break;
    }
}

