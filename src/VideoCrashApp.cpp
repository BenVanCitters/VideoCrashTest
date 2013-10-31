#include "VideoCrashApp.h"


//------------------------------------------------------------------------------
void VideoCrashApp::setup()
{
	ofSetFrameRate(60);
    ofSeedRandom();
    ofHideCursor();
    
    ofSetWorkingDirectoryToDefault();
    mTileLayer.setup();
    
}

void VideoCrashApp::update()
{
    float tm = ofGetElapsedTimef();
    
    if(tm > mNextPrintTm)
    {
        cout << ofGetTimestampString() << ": lifeline check" << endl;
        mNextPrintTm += mPrintTimeDelay;
    }
    mPrintTimeDelay = 60;
}

//------------------------------------------------------------------------------
void VideoCrashApp::draw()
{
    ofBackground(255,255,0);
    mTileLayer.draw();
}


//--------------------------------------------------------------
void VideoCrashApp::keyPressed(int key)
{
	if(key == ' ')
    {
		ofToggleFullscreen();
	}
    if(key == 'f')
    {//        toggle FPS display
        mTileLayer.mShowFPS= !mTileLayer.mShowFPS;
        
	}
}

void VideoCrashApp::mousePressed(int x, int y, int button)
{
    cout << "mousePressed: " << x << ", " << y << " button: " << button << endl;
}

void VideoCrashApp::mouseMoved(int x, int y)
{
}

void VideoCrashApp::exit()
{
    
}