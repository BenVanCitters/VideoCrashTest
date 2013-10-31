//
//  DiamondVideoTile.cpp
//
//
//  Created by Ben Van Citters on 10/21/13.
//
//

#include "VideoTile.h"

ofVec3f const VideoTile::verts[4] = {ofVec3f(0.f,0.f,0.f),
    ofVec3f(1,0,0.f),
    ofVec3f(0,1,0.f),
    ofVec3f(1,1.f,0.f)};
ofVec3f VideoTile::leg1Dir = (verts[1] - verts[0]).normalize();
ofVec3f VideoTile::leg2Dir = (verts[2] - verts[0]).normalize();

VideoTile::VideoTile()
{
    VideoTile::VideoTile("",ofVec3f(200,200),ofVec3f(200,200));
}

void VideoTile::buildDiamondMesh(ofVec2f currentDim)
{
    if(!mVertsLoaded)
    {
        mVboMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        mVboMesh.addVertex(ofVec3f(0,0));
        mVboMesh.addVertex(leg1Dir*currentDim.x);
        mVboMesh.addVertex(leg2Dir*currentDim.y);
        mVboMesh.addVertex((leg1Dir*currentDim.x+leg2Dir*currentDim.y));
        
        ofVec2f normdTexCoords[4] = {ofVec3f(0,0),
            leg2Dir*currentDim.y,
            leg1Dir*currentDim.x,
            (leg1Dir*currentDim.x+leg2Dir*currentDim.y),
        };
        
        ofVec2f maxDim(0,0);
        float minX = 99999;
        for(int i=0; i < 4; i++)
        {
            minX = MIN(minX,normdTexCoords[i].x);
            maxDim.x = MAX(maxDim.x,normdTexCoords[i].x);
            maxDim.y = MAX(maxDim.y,normdTexCoords[i].y);
        }
        //        minX *= (sin(mAnimOffset+ofGetElapsedTimef()) + 1)/2;
        for(int i=0; i < 4; i++)
        {
            normdTexCoords[i] -= ofVec2f(minX,0);
            normdTexCoords[i].x /= (maxDim.x);
            normdTexCoords[i].y /= maxDim.y;
        }
        mVboMesh.addTexCoord(ofVec2f(0,0));
        mVboMesh.addTexCoord(ofVec2f(1,0));
        mVboMesh.addTexCoord(ofVec2f(0,1));
        mVboMesh.addTexCoord(ofVec2f(1,1));
        mVertsLoaded = true;
    }
}
VideoTile::VideoTile(string url, ofVec3f pos, ofVec2f startDim )
{
    mPos = pos;
    mStartDim = startDim;
    
    mVertsLoaded = false;
    
    buildDiamondMesh(mStartDim);
    
    mImgURL = url;
    mPlayer.play();
    mImageLoaded = false;
}

void VideoTile::loadAsset()
{
    mPlayer.setPixelFormat(OF_PIXELS_RGB);
    mImageLoaded = mPlayer.loadMovie(mImgURL,OF_QTKIT_DECODE_TEXTURE_ONLY);
    mPlayer.play();
    mPlayer.setVolume(0.f);
}


bool VideoTile::isAssetLoaded()
{
    return mImageLoaded;
}

void VideoTile::draw(ofVec2f offset,  ofVec2f rectMin, ofVec2f rectMax)
{
    ofPushMatrix();
    ofVec2f displacement = mPos+offset;
    displacement.x = fmod(displacement.x, rectMax.x)-rectMin.x;
    displacement.y = fmod(displacement.y, rectMax.y)-rectMin.y;
    
    if(isAssetLoaded())
    {
        ofTexture* videoTex = mPlayer.getTexture();
        if(videoTex  != NULL)
        {
            videoTex->bind();
            mVboMesh.draw();
            videoTex->unbind();
        }
        else
        {
            cout << ofGetTimestampString() << " - mPlayer(" << &mPlayer << ").getTexture() returned null"  << endl;
        }
    }
    
    ofPopMatrix();
}