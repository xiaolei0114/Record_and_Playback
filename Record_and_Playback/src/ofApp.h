#pragma once

#include "ofMain.h"
#define LENGTH 44100 * 6 //6 secs

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    void audioReceived( float * input, int bufferSize, int nChannels );
    void audioRequested( float * output, int bufferSize, int nChannels );
    
    float buffer[LENGTH]; //オーディオバッファ
    int sampleRate; //サンプリングレイト
    int recPos; //Record位置
    int playPos; //Playback位置
    int mode; //現在のモード、0:off, 1:recording, 2:play
    
    int progressIndex;
    
};
