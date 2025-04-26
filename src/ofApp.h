#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxNetwork.h"
#include <array>

class ofApp : public ofBaseApp {

public:
  struct Pixel {
    float x;
    float y;
  };

  class Driver {
  public:
    Driver(std::string address, std::vector<Pixel> pixels);
    void draw() const;

  private:
    ofxUDPManager mSocket;
    std::vector<Pixel> mPixels;
  };

  void setup();
  // void update();
  void draw();

  // void keyPressed(int key);
  // void keyReleased(int key);
  // void mouseMoved(int x, int y);
  // void mouseDragged(int x, int y, int button);
  // void mousePressed(int x, int y, int button);
  // void mouseReleased(int x, int y, int button);
  // void mouseEntered(int x, int y);
  // void mouseExited(int x, int y);
  // void windowResized(int w, int h);
  // void dragEvent(ofDragInfo dragInfo);
  // void gotMessage(ofMessage msg);

  std::vector<Driver> mDrivers;
};
