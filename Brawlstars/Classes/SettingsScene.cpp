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

#include "SettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Settings::createScene()
{
    return Settings::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SettingsScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Settings::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
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
        CC_CALLBACK_1(Settings::menuCloseCallback, this));

    if (CloseItem == nullptr ||
        CloseItem->getContentSize().width <= 0 ||
        CloseItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = Origin.x + VisibleSize.width - CloseItem->getContentSize().width / 2;
        float y = Origin.y + CloseItem->getContentSize().height / 2;
        CloseItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto CloseMenu = Menu::create(CloseItem, NULL);
    CloseMenu->setPosition(Vec2::ZERO);
    this->addChild(CloseMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Settings"
    // create and initialize a label

    auto SettingsLabel = Label::createWithTTF("Settings", "fonts/Marker Felt.ttf", 40);
    if (SettingsLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        SettingsLabel->setPosition(Vec2(Origin.x + VisibleSize.width / 2,
            Origin.y + VisibleSize.height - SettingsLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(SettingsLabel, 1);
    }

    //创建返回按钮
    MenuItemFont::setFontName("Times New Romam");
    MenuItemFont::setFontSize(24);
    MenuItemFont* itemBack = MenuItemFont::create("Back",
        CC_CALLBACK_1(Settings::menuBackCallback, this));

    Menu* SettingsBackMenu = Menu::create(itemBack, NULL);
    SettingsBackMenu->setPosition(Origin.x + SettingsLabel->getContentSize().width/2,
        Origin.y + VisibleSize.height - SettingsLabel->getContentSize().height);
    SettingsBackMenu->alignItemsVertically();

    this->addChild(SettingsBackMenu);
    ////

    /**
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(VisibleSize.width/2 + Origin.x, VisibleSize.height/2 + Origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    /**/

    return true;
}


void Settings::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void Settings::menuBackCallback(Ref* pSender)
{
    //返回主菜单
    Director::getInstance()->popScene();
}