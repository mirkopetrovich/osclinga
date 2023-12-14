#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    


}

//--------------------------------------------------------------
void ofApp::update(){
    //STOP(frame,1);
    //CRC(frame);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofDrawBitmapString("0x"+ofToString(ofToHex(frame[0]))+" 0x"+ofToString(ofToHex(frame[1]))+" 0x"+ofToString(ofToHex(frame[2]))+" 0x"+ofToString(ofToHex(frame[3]))+" 0x"+ofToString(ofToHex(frame[4]))+" 0x"+ofToString(ofToHex(frame[5]))+" 0x"+ofToString(ofToHex(frame[6]))+" 0x"+ofToString(ofToHex(frame[7])), 100, 100);
    

    
    
}

void ofApp::RUN(unsigned char *frame, int address) {
    
    frame[0] = address;    // Address
    frame[1] = 0x06;       // Function Code
    frame[2] = 0x00;       // Register Number
    frame[3] = 0x00;
    frame[4] = 0x00;       // Run
    frame[5] = 0x01;
    CRC(frame);
    }

void ofApp::STOP(unsigned char *frame, int address) {
    
    frame[0] = address;    // Address
    frame[1] = 0x06;       // Function Code
    frame[2] = 0x00;       // Register Number
    frame[3] = 0x00;
    frame[4] = 0x00;       // Stop
    frame[5] = 0x00;
    CRC(frame);
    }

void ofApp::FREC(unsigned char *frame, float frecuencia) {
    
    int frec_int = frecuencia * 10.;
    if (frec_int < 0) frec_int += 0xFFFF + 1;
    frame[3] = 0x01;
    frame[4] = (frec_int >> 8) & 0xFF;
    frame[5] = frec_int & 0xFF;
    CRC(frame);
}

void ofApp::CRC(unsigned char *frame) {
    
    {
      unsigned int temp, temp2, flag;
      temp = 0xFFFF;
      for (unsigned char i = 0; i < 6; i++)
      {
        temp = temp ^ frame[i];
        for (unsigned char j = 1; j <= 8 ; j++)
        {
          flag = temp & 0x0001;
          temp >>= 1;
          if (flag)
            temp ^= 0xA001;
        }
      }

      frame[6] = temp & 0xFF;
      frame[7] = (temp >> 8) & 0xFF;
    }
    
}


//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'r') RUN(frame,1);
    if (key == 't') RUN(frame,2);
    if (key == 's') STOP(frame,1);
    if (key == 'd') STOP(frame,2);
    if (key == '1') FREC(frame, 35);
    if (key == '2') FREC(frame, 5);
    

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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
