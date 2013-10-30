//
//  VideoTile.h
//  
//
//  Created by Ben Van CItters on 10/21/13.
//
//

#ifndef __videoCrash__DiamondVideoTile__
#define __videoCrash__DiamondVideoTile__

#include <iostream>

#include "ofQTKitPlayer.h"

class VideoTile
{
public:
    ofVboMesh mVboMesh;
    
    ofVec3f mPos;
    ofVec2f mStartDim;

    bool mVertsLoaded;
    
    static const ofVec3f verts[4];
    static ofVec3f leg1Dir;
    static ofVec3f leg2Dir;
    
    string mImgURL;

    ofVec2f mStartTexPos[4];
    ofVec2f mEndTexPos[4];

    bool mImageLoaded;
    
    ofQTKitPlayer mPlayer;
    void buildDiamondMesh(ofVec2f currentDim);
    VideoTile();
    VideoTile(string url, ofVec3f pos, ofVec2f startDim);

    bool isAssetLoaded();
    void draw(ofVec2f offset,  ofVec2f rectMin, ofVec2f rectMax);
    void loadAsset();
};
#endif /* defined(__videoCrash__DiamondVideoTile__) */
