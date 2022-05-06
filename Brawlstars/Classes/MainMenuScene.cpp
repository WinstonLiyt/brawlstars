/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainMenuScene.h"
#include "SettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto VisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 Origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto CloseItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    if (CloseItem == nullptr ||
        CloseItem->getContentSize().width <= 0 ||
        CloseItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = Origin.x + VisibleSize.width - CloseItem->getContentSize().width/2;
        float y = Origin.y + CloseItem->getContentSize().height/2;
        CloseItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto CloseMenu = Menu::create(CloseItem, NULL);
    CloseMenu->setPosition(Vec2::ZERO);
    this->addChild(CloseMenu, 1);

    /////////////////////////////
    
    //创建游戏名标题
    auto GameNameLabel = Label::createWithTTF("Brawlstars", "fonts/Marker Felt.ttf", 40);
    if (GameNameLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        GameNameLabel->setPosition(Vec2(Origin.x + VisibleSize.width/2,
                                Origin.y + VisibleSize.height - GameNameLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(GameNameLabel, 1);
    }
    ////

    /*
    * 以下无法显示 原因未知
    */

    // add "test" splash screen"
    auto BackgroundPictrue = Sprite::create("PicTest.png");
    if (BackgroundPictrue == nullptr)
    {
        problemLoading("'PicTest.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        BackgroundPictrue->setPosition(Vec2(VisibleSize.width / 2 + Origin.x, VisibleSize.height / 2 + Origin.y));

        // add the sprite as a child to this layer
        this->addChild(BackgroundPictrue, 0);
    }

    //创建主菜单选项
    MenuItemFont::setFontName("Times New Romam");
    MenuItemFont::setFontSize(40);

    MenuItemFont* itemStart = MenuItemFont::create("Start",
        CC_CALLBACK_1(MainMenu::menuStartCallback, this));
    MenuItemFont* itemSettings = MenuItemFont::create("Settings",
        CC_CALLBACK_1(MainMenu::menuSettingsCallback, this));

    Menu* MainMenu = Menu::create(itemStart, itemSettings, NULL);
    MainMenu->setPosition(VisibleSize.width / 2 + Origin.x,
        Origin.y + MainMenu->getContentSize().height / 2);
    MainMenu->alignItemsVertically();

    this->addChild(MainMenu);
    ////

    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MainMenu::menuStartCallback(Ref* pSender)
{
    //待完成
    Director::getInstance()->end();

}

void MainMenu::menuSettingsCallback(Ref* pSender)
{
    //创建设置场景
    auto SettingsScene = Settings::createScene();

    //切换设置场景
    Director::getInstance()->pushScene(SettingsScene);
}
