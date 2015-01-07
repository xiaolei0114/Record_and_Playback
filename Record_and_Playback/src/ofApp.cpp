#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    //サンプリングレイトの設定
    sampleRate = 44100;
    
    //サウンド録音再生の初期化
    //nOutputChannels
    //nInputChannels,
    //ofBaseApp * appPtr,
    //int sampleRate,
    //int bufferSize,
    //int nBuffers
    ofSoundStreamSetup(1, 1, this, sampleRate, LENGTH, 4);
    
    //Playback Mode
    mode = 2;
    
    //録音、再生の位置を先頭に
    recPos = 0;
    playPos = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /*
    ofSetColor(255);
    if (mode == 1) {
        //録音モードの場合、recordingの表示をして、背景を青に
        ofBackground(255, 0, 0);
        ofDrawBitmapString("recording", 10, 20);
    } else if (mode == 2) {
        //再生モードの場合、playingの表示をして、背景を赤に
        ofBackground(0, 0, 255);
        ofDrawBitmapString("playing", 10, 20);
    } else if (mode == 3 ) {
        ofBackground(0, 0, 0);
        ofDrawBitmapString("stopping", 10, 20);
    }
    */
    
    drawRecordingProgressWithBackground();
    drawPlaybackProgressWithBackground();
    
    /*
    //draw the result of 
    ofSetColor(255);
    for (int i = 0; i < LENGTH; i+=ratio){
        //i/ratio is to make "ratios" of sample share a single line so that in total "LENGTH" samples can be drawn in the display.
        ofLine(i/ratio,ofGetHeight()/2,i/ratio,ofGetHeight()/2+buffer[i]*100.0f);
        //ofLine(i/ratio, 200, i/ratio, 600);//How to let this line run only 1 time per frame
    }
    */
}

//オーディオ入力の処理
void ofApp::audioReceived(float * input, int bufferSize, int nChannels){
    //もし録音モードだったら
    if (mode == 1) {
        //バッファされたサンプルの数だけ処理
        for (int i = 0; i < bufferSize*nChannels; i++) {
            //録音位置が設定した最大の長さに逹っしていなければ
            if(recPos<LENGTH){
                //Bufferにサウンド入力を設定
                recordingBuffer[recPos] = input[i];
                //録音位置を進める
                recPos++;
            } else {
                //もし最大位置を越えていたら、最初に戻る(ループ録音)
                recPos = 0;
            }
            //save the current recording position
            recordingProgressIndex = recPos;
        }
    }
}

//--------------------------------------------------------------
//オーディオ再生の処理
void ofApp::audioRequested(float * output, int bufferSize, int nChannels){
    //もし再生モードだったら
    if (mode == 2) {
        //バッファされたサンプル数だけ処理
        for (int i = 0; i < bufferSize*nChannels; i++) {
            //再生位置が設定した最大の長さに逹っしていなければ
            if(playPos<LENGTH){
                //bufferに格納したサウンドを再生
                //                output[i] = buffer[playPos];
                output[i] = 6 * buffer[playPos];
                //再生位置を進める
                playPos++;
            } else {
                //もし最大位置を越えていたら、最初に戻る(ループ再生)
                playPos = 0;
            }
            //save the current playback position
            playbackProgressIndex = playPos;
        }
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r'://record
            mode = 1;
            break;
        case 'p'://play
            mode = 2;
            break;
        case 's'://stop
            mode = 3;
        default:
            break;
    }
}

void ofApp::drawRecordingProgressWithBackground() {
    //set Background color: Red
    ofSetColor(255,0,0);
    
    //draw space for recording background in the upper half of the background
    ofRect(0, 0, ofGetWidth(), ofGetHeight()/2);
    
    //draw label for "Recording"
    ofSetColor(255);
    ofDrawBitmapString("Recording", 10, 20);
    
    
    //Draw lines for current recording position
    ofSetColor(200 , 200, 200);
    int pos = recordingProgressIndex/ratio;
    //progressIndex+= ratio;
    ofSetLineWidth(1);
    
    //Line for current buffer position
    ofLine(pos, 0, pos, ofGetHeight()/2);
    
    //draw Waves with lines based on the recording sample data
    ofSetColor(255);
    for (int i = 0; i < LENGTH; i+=ratio){
        //i/ratio is to make "ratios" of sample share a single line so that in total "LENGTH" samples can be drawn in the display.
        ofLine(i/ratio,ofGetHeight()/2,i/ratio,ofGetHeight()/2+recordingBuffer[i]*100.0f);
        //ofLine(i/ratio, 200, i/ratio, 600);//How to let this line run only 1 time per frame
    }
    
}

void ofApp::drawPlaybackProgressWithBackground() {
    //set Background color
    ofSetColor(0,0,255);
    
    //draw space for recording background in lower half of the background
    ofRect(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
    
    //draw label for "recording"
    ofSetColor(255);
    ofDrawBitmapString("Playback", 10, 20+ofGetHeight()/2);
    
    //Draw lines for current recording position
    ofSetColor(200 , 200, 200);
    int pos = playbackProgressIndex/ratio;
    //progressIndex+= ratio;
    ofSetLineWidth(1);
    
    //Line for current buffer position
    ofLine(pos, ofGetHeight()/2, pos, ofGetHeight());
    
    //draw Waves with lines based on the recording sample data
    ofSetColor(255);
    for (int i = 0; i < LENGTH; i+=ratio){
        //i/ratio is to make "ratios" of sample share a single line so that in total "LENGTH" samples can be drawn in the display.
        ofLine(i/ratio,ofGetHeight()/2,i/ratio,ofGetHeight()/2+playbackBuffer[i]*100.0f);
        //ofLine(i/ratio, 200, i/ratio, 600);//How to let this line run only 1 time per frame
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
