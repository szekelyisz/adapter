#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofxJSONElement config;
  if (!config.open("config.json")) {
    ofLogError("ofApp::setup") << "Failed to parse JSON" << endl;
    ofExit(1);
  }

  if (!config.isObject()) {
    ofLogError("ofApp::setup") << "config root is not an object";
    ofExit(1);
  }

  if (!config["drivers"].isArray()) {
    ofLogError("ofApp::setup") << "drivers is not an array";
    ofExit(1);
  }

  for (const auto &driverConfig : config["drivers"]) {
    if (!driverConfig.isObject()) {
      ofLogError("ofApp::setup") << "driver is not an object";
      ofExit(1);
    }

    if (!driverConfig["pixels"].isArray()) {
      ofLogError("ofApp::setup") << "pixels is not an array";
      ofExit(1);
    }

    std::vector<Pixel> pixels;
    for (const auto &pixel : driverConfig["pixels"]) {
      if (!pixel.isArray()) {
        ofLogError("ofApp::setup") << "pixel is not an array";
        ofExit(1);
      }

      if (pixel.size() != 2) {
        ofLogError("ofApp::setup") << "pixel format invalid";
        ofExit(1);
      }

      if (!pixel[0].isNumeric() || !pixel[1].isNumeric()) {
        ofLogError("ofApp::setup") << "invalid pixel coordinates";
        ofExit(1);
      }

      pixels.emplace_back(
          Pixel{x : pixel[0].asFloat(), y : pixel[1].asFloat()});
    }

    mDrivers.push_back(Driver(driverConfig["address"].asString(), pixels));
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofClear(0, 0, 0);
  ofSetColor(255, 255, 255);

  for (const auto &driver : mDrivers) {
    driver.draw();
  }
}

ofApp::Driver::Driver(std::string address, std::vector<Pixel> pixels)
    : mSocket(ofxUDPManager()), mPixels(pixels) {
  mSocket.Connect(address.c_str(), 5000);
}

void ofApp::Driver::draw() const {
  for (const auto &pixel : mPixels) {
    ofDrawCircle(pixel.x * ofGetWidth(), pixel.y * ofGetHeight(), 4);
  }
}

// //--------------------------------------------------------------
// void ofApp::update() {}

// //--------------------------------------------------------------
// void ofApp::keyPressed(int key) {}

// //--------------------------------------------------------------
// void ofApp::keyReleased(int key) {}

// //--------------------------------------------------------------
// void ofApp::mouseMoved(int x, int y) {}

// //--------------------------------------------------------------
// void ofApp::mouseDragged(int x, int y, int button) {}

// //--------------------------------------------------------------
// void ofApp::mousePressed(int x, int y, int button) {}

// //--------------------------------------------------------------
// void ofApp::mouseReleased(int x, int y, int button) {}

// //--------------------------------------------------------------
// void ofApp::mouseEntered(int x, int y) {}

// //--------------------------------------------------------------
// void ofApp::mouseExited(int x, int y) {}

// //--------------------------------------------------------------
// void ofApp::windowResized(int w, int h) {}

// //--------------------------------------------------------------
// void ofApp::gotMessage(ofMessage msg) {}

// //--------------------------------------------------------------
// void ofApp::dragEvent(ofDragInfo dragInfo) {}
