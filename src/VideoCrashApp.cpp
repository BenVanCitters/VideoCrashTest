#include "VideoCrashApp.h"


//------------------------------------------------------------------------------
void VideoCrashApp::setup()
{
	ofSetFrameRate(60);
    ofSeedRandom();
    ofHideCursor();
//    cout << "dataPathRoot(): " <<  dataPathRoot().toString()  << endl;  //#include "ofUtils.cpp"
    ofSetWorkingDirectoryToDefault();
    mTileLayer.setup();
//    mAssetDownloader.mTileLayer = &mTileLayer;
}

void VideoCrashApp::update()
{

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
//	mTileLayer.updateImages(2,true);
    cout << "mousePressed: " << x << ", " << y << " button: " << button << endl;
}

void VideoCrashApp::mouseMoved(int x, int y)
{
}

void VideoCrashApp::exit()
{
    // stop the thread
//    thread.stopThread();
}