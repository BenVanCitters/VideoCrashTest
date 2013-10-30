//
//  TileLayer.h
//  
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#ifndef __videoCrash__TileLayer__
#define __VideoCrashApp__TileLayer__

#include "ofMain.h"
#include "VideoTile.h"
#include <iostream>

class TileLayer
{
    std::vector<VideoTile*> mTiles;

public:
    bool mShowFPS;
    bool mIsUsingLights;
    
    TileLayer();
    void setup();
    void draw();
private:
    void loadVideos();
    ofVec2f mTileDimesions;
    ofVec2f mTileSpacing;
};

#endif /* defined(__VideoCrashApp__TileLayer__) */
