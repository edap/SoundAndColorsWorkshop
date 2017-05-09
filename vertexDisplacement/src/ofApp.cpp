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


    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);

    sample.load(ofToDataPath("sound.wav"));
    sampleRate 	= 44100;
    bufferSize	= 512;

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    ofSetBackgroundColor(255, 200, 0);

    volHistory.assign(ofGetWidth(), 0.0);

}

//--------------------------------------------------------------
void ofApp::update(){
    //copied from audioInExample
    volHistory.push_back( smoothedVolume );

    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= ofGetWidth() ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    int x = 0;
    for(auto vol:volHistory){
        auto ver = ofVec2f(x, ofGetHeight()-vol * lineScale);
        line.addVertex(ver.x, ver.y);
        if (line.size() > ofGetWidth()){
            line.getVertices().erase(
                                     line.getVertices().begin()
                                     );
        }
        x++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //new
    ofSetColor(255, 0, 0);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, smoothedVolume * radius);
    line.draw();

    //old
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
    gui.add(materialColor.setup("material",
                                ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(enableSmooth.set("enable smothed volume", false));
    gui.add(smoothedVal.set("smoothed value", 0.97, 0.70, 0.99));
    gui.add(radius.set("radius", 200, 100, 800));
    gui.add(lineScale.set("line scale", 500, 200, 1200));
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

