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
    
    //再生モード
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
    
    //画面の幅と録音サンプル数の比率を計算
    //ratio is the average width(pixels) of each sample
    int ratio = LENGTH / ofGetWidth();
    
    //ofLine(ofGetFrameNum() % ofGetWidth(), 200, ofGetFrameNum() % ofGetWidth(), 600);
    //printf("Current frame: %d\n",ofGetFrameNum());
    //画面の横幅にあわせて、波形を描画
    ofSetColor(200 , 200, 200);
    int pos = progressIndex/ratio;
    //progressIndex+= ratio;
    ofSetLineWidth(1);
    ofLine(pos, 200, pos, 600);
    
    ofSetColor(255);
    for (int i = 0; i < LENGTH; i+=ratio){
        ofLine(i/ratio,ofGetHeight()/2,i/ratio,ofGetHeight()/2+buffer[i]*100.0f);
        //ofLine(i/ratio, 200, i/ratio, 600);//How to let this line run only 1 time per frame
    }
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
                buffer[recPos] = input[i];
                //録音位置を進める
                recPos++;
            } else {
                //もし最大位置を越えていたら、最初に戻る(ループ録音)
                recPos = 0;
            }
            progressIndex = recPos;
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
            progressIndex = playPos;
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
