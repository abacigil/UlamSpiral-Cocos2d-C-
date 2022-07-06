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

#include "UlamSpiral.h"
#include "cocos2d.h"

USING_NS_CC;

const short circleSize = 1;

// https://stackoverflow.com/a/14418599
bool isPrime(int number) {
    if (number < 2) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; (i * i) <= number; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}


Scene* UlamSpiral::createScene()
{
    return UlamSpiral::create();
}

void drawCircle(UlamSpiral*t, Vec2 pos) {
   
    auto drawNode = DrawNode::create();
    drawNode->drawDot(pos, circleSize, cocos2d::Color4F::WHITE);
    t->addChild(drawNode);
    
}

void addText(UlamSpiral* t, Vec2 pos, std::string number) {
    auto label = Label::createWithTTF(number, "fonts/Marker Felt.ttf", 48);
    label->setPosition(pos);
    label->setTextColor(cocos2d::Color4B::WHITE);
    t->addChild(label);
}


bool UlamSpiral::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    // Prime numbers up to:
    const int limit = 250000;

    // Rotation
    int step = 1;
    int numSteps = 1;
    short state = 0;
    int turnCounter = 1;
    float x = visibleSize.width / 2 + origin.x;
    float y = visibleSize.height / 2 + origin.y;
    int stepSize = 2;
    for (size_t i = 1; i < limit; i++)
    {
        bool isNumberPrime = isPrime(i);
        if (i > 1) {
            switch (state)
            {
            case 0:
                x += stepSize;
                break;
            case 1:
                y += stepSize;
                break;
            case 2:
                x -= stepSize;
                break;
            case 3:
                y -= stepSize;
                break;
            default:
                break;
            }
            // Change state
            if (step % numSteps == 0) {
                state = (state + 1) % 4;
                turnCounter++;
                if (turnCounter % 2 == 0) {
                    numSteps++;
                }
            }
            step++;
        }
      

        auto pos = Vec2(x, y);
        if (isNumberPrime) {
            drawCircle(this, pos);
            
        }
      //  addText(this, pos, std::to_string(i));
    }

    return true;
}

