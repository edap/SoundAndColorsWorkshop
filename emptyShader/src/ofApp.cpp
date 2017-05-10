#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    sphere.set(100, 100);

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
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    shader.begin();

    shader.setUniform3f("lightPos", light.getPosition());
    shader.setUniform4f("materialColor", ofColor(materialColor));
    shader.setUniform1f("displaceAmount", displaceAmount);
    sphere.draw();
    
    shader.end();
    light.draw();
    cam.end();

    maybeDrawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'g':
            hideGui = !hideGui;
            break;
        default:
            break;
    }
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

// GUI
void ofApp::addGui(){
    gui.setup();
    gui.setPosition(ofPoint(0, 30));
    gui.add(materialColor.setup("material",
                                ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
}

void ofApp::maybeDrawGui(){
    if(!hideGui){
        ofDisableDepthTest();
        gui.draw();
        ofPushStyle();
        string displayGui = "press 'g' to toggle the gui, up and down to change presets";
        ofDrawBitmapString(displayGui, 0, 10);
        //fps
        string msg = "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
        ofEnableDepthTest();
        ofPopStyle();
    }
}

