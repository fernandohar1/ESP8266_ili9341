#ifndef _SCENE_GAMESTART_H
#define _SCENE_GAMESTART_H
#include "GameScene.h"
#include "Avatar.h"
class Scene_GameStart : public GameScene{
  public: 
  Scene_GameStart(TFT_eSPI *tft){
    GameScene::_tft = tft;
   };
   
  void update(boolean isTouching, uint16_t touchX, uint16_t touchY, boolean* needChangeScene, int* nextSceneIndex) {
    if (isTouching){
      if(!wasTouching){
         //tap down
      }
      wasTouching = true;
    }else{
      if(wasTouching){ 
         //tap up
         *needChangeScene = true;
         *nextSceneIndex = 1;
         return;
      }
      wasTouching = false;
    }
    unsigned long current = millis();
     for (int i = 0; i < numAvatar; ++i) {
        Avatar* avatar = avatars[i];
        if (avatar != NULL) {   
          avatar->updatePos(current);
        }
      }
    
  }
  
  void render(){
    renderScene();
//      for (int i = 0; i < numAvatar; ++i) {
//        Avatar* avatar = avatars[i];
//        if (avatar != NULL) {
//          renderCharacter(avatar->previousRenderedX, avatar->previousRenderedY, avatar->x, avatar->y, avatar->width, avatar->height, avatar->bitmap, avatar->mask, SCREENWIDTH); //temp
//          avatar->savePreviousRenderPos();
//        }
//      }
    
  }

  void initScene(){
    setBackgroundColor(GameScene::rgb565(230, 157, 132));
    wasTouching = false;
    Avatar* avatar = NULL;
    
    //Lowest layer ... top layer
    avatar = new Avatar(100, 0, CAT_WIDTH, CAT_HEIGHT, CatBitmap, CatMask); //100X67
    appendAvatar(avatar);
    //avatar->enableBreathing = true;
    avatar->enableBreathing();
    //avatar->breathInterval = 50;
    avatar->setBreathInterval(500);
    //avatar->breathPosition = 40;
    avatar->setBreathPosition(40);
    avatar->breathAmount = 2;
    uint16_t color = rgb565(230, 157, 132);
    _tft->fillScreen(color);
    //drawBackground(whiteBearHome);
  }

  void destroyScene(){
    wasTouching = false;
    GameScene::destroyScene();
  }
  private :
    boolean wasTouching = false;    
};
#endif
