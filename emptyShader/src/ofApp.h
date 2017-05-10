#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    //shaders
    ofShader shader;
    string shadersFolder = "shaders_gl3";

    //3d scene
    ofSpherePrimitive sphere;
    ofVec3f lightPos = ofVec3f(130,130,130);
    ofLight light;
    ofEasyCam cam;

    //GUI
    void addGui();
    void maybeDrawGui();
    bool hideGui = false;

    ofxColorSlider materialColor;
    ofxFloatSlider displaceAmount;
    ofxPanel gui;
};
