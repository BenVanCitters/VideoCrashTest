//
//  TileLayer.cpp
//  
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#include "TileLayer.h"


TileLayer::TileLayer()
{
    ofSeedRandom();
    ofDisableArbTex();
    ofEnableNormalizedTexCoords();
}

//functions to call from inside ofAppBase::setup()
void TileLayer::setup()
{
    //init spacing
    float debugScaling = .75;
    float hSpacing =ofGetWindowWidth()*debugScaling/(7-1);
    mTileSpacing = ofVec2f(ofVec2f(hSpacing,hSpacing*sqrt(3)/2));
    mTileDimesions = ofVec2f(7*mTileSpacing.x,
                             4*mTileSpacing.y);
    loadVideos();

    mShowFPS = false;
}


void TileLayer::draw()
{
    ofEnableDepthTest();
    ofPushMatrix();
    ofTranslate(500,200);
    float tm = ofGetElapsedTimef();
    ofVec2f offset = ofVec2f(.2,.2) * tm * 200;
    
    offset.x = fmod(offset.x, mTileDimesions.x);
    offset.y = fmod(offset.y, mTileDimesions.y);
    ofSetColor(255,255,255);
    
    for(int i=0; i<mTiles.size(); i++)
    {
        ofVec2f rectMin =mTileDimesions/4;
        ofVec2f rectMax =mTileDimesions;
        
        ofVec2f displacement = mTiles[i]->mPos+offset;

        displacement.x = fmod(displacement.x, rectMax.x)-rectMin.x;
        displacement.y = fmod(displacement.y, rectMax.y)-rectMin.y;
        ofPushMatrix();
        ofTranslate(displacement); // position the current mesh
        
        mTiles[i]->draw(offset, mTileDimesions/4, mTileDimesions);
        ofPopMatrix();
    }
    ofPopMatrix();
    ofDisableDepthTest();
    
    // draw the framerate in the top left corner
    if(mShowFPS)
        ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}


void TileLayer::loadVideos()
{
    string videoURLs[] = {"https://v.cdn.vine.co/r/videos/75718FD4-223F-47BE-9719-5540C196F23C-2233-000000B1AEC0F330_1b3bdb9086b.1.2.mp4",
                          "https://v.cdn.vine.co/v/videos/17CA24CE-0455-421B-9E6F-5EE25F47B490-77284-0000144C972CE63F_1dbb33a24c5.1.2.mp4",
                          "https://mtc.cdn.vine.co/r/videos/7E617D98861001326564430028800_1cada92245b.3.4_YXAz6Z2YqkfQ0gyT0AxUFAG.hSDhMQNEf1jSR4b0AwZa.0JEIU_0ArVKbK0lwWGa.mp4?versionId=3.Pu.OUmDTQng2mSv.kaP.VAeeRtuOk7",
                          "http://mtc.cdn.vine.co/r/videos/B91DD7F7-3089-42E1-996E-943BA815F3D4-1830-000001D61083A5F7_1eee9790afd.1.3.mp4?versionId=En2KECj9ARV8Uo7t.X5Wqz_GLIcJ37rB",
                          "https://keek-a.akamaihd.net/keek/video/LDtqdab/mp4",
                          "http://mtc.cdn.vine.co/r/videos/01261F49D4984116279600439296_133c952ffc6.3.1_ZsC.nqYpf9zOW_G9abz1B8SPXIQkchKiP6puIQLQzvSbsHkwRDXg4nPfSEshoIwY.mp4?versionId=BbmmbSyTS79TqRQPO5MzP.b3rDB70vHr",
                          "http://mtc.cdn.vine.co/r/videos/6BEF26EBB31003765863972753408_14b3ff32638.3.4_AehNHT39R80ofrYZ2wca93VFeOpQLk6b0jWwubvaXz_mtiGqHt_rr03J.grzZgbs.mp4",
                          "https://v.cdn.vine.co/v/videos/C5B8ADEB-DADF-48C5-A6F4-4C1FBD82EA9E-27504-0000073253DA7A93_1.1.2.mp4",
                          "https://v.cdn.vine.co/r/videos/322EAD5010964958264859205632_1a2e761b627.3_lQeLDs5tQgwwxknTdW8yi5Dc7CQwCXjOwLrgOonnpBcsAYvD_qT6QyZL0gqrtr4Y.mp4",
                          "https://v.cdn.vine.co/v/videos/E4A9EC7D-0BC4-4B65-8420-03184DABBE9B-1518-0000009CD00FBF18_1.1.2.mp4",
                          "https://mtc.cdn.vine.co/v/videos/CF0EB648-F756-4B4E-A7B6-1F1815A61E8D-227-0000004442CF3564_1.0.5.mp4",
                          "https://v.cdn.vine.co/v/videos/0B0FD0D4-DED1-4F5C-BF9F-6E76488BCCDD-696-0000001B9FB6D9FD_1f58eaaf58e.1.2.mp4",
                          "https://v.cdn.vine.co/v/videos/3BC5BD25-9876-4647-B4A7-20BA5F83EA11-5822-00000708F1147E43_1d76d9e1a8c.1.2.mp4",
                          "https://mtc.cdn.vine.co/v/videos/8B474922-0D0E-49AD-B237-6ED46CE85E8A-118-000000FFCD48A9C5_1.0.6.mp4",
                          "https://v.cdn.vine.co/v/videos/AC5539AF-9251-4363-A641-E7F01C4E6239-141-0000012CB4E3656E_1.0.mp4?versionId=GzoAU2AQAlSzFs_9XM5u.FF90IScP45j",
                          "https://mtc.cdn.vine.co/v/videos/E017FAAE-70D6-4C32-9E2E-1F7BD75364D0-30013-00000C1610BD348F_1.0.1.mp4?versionId=YMcsxJHzLww3Ehi1lgOScCdiev3bxgcS",
                          "https://v.cdn.vine.co/videos/0EC293CD-1B38-42EC-91CB-6755BB5161E0-696-0000003CFE484AF8_1.0_Beta_2.mp4",
                          "http://www.funnyvinevideos.com/content/vines/files/If-Youre-Happy-and-You-Know-It-Clap-Your-Hair.mp4"};
    
    for(int i = 0; i < 14; i++)
    {
        VideoTile* tile = new VideoTile(videoURLs[i],
                                                      ofVec2f(ofRandom(ofGetWindowWidth()),
                                                              ofRandom(ofGetWindowHeight())),
                                                      ofVec2f(mTileSpacing.x*1,
                                                              mTileSpacing.y*1));
        tile->loadAsset();
        mTiles.push_back(tile);
    }
}





