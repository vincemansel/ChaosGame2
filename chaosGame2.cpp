//
//  chaosGame.cpp
//  chaosGame
//
//  Created by Vince Mansel on 9/26/11.
//  Copyright 2011 Wave Ocean Networks. Some rights reserved.
//  Feel free to copy while keeping the original copyright intact.
//

/*
 * Chaos game draws a coherent fractal image for certain combinations of vertices and dividers
 * based on a random rendering technique. 3 vertices and a 2 divider create a compelling result.
 *
 * This program is an experimental simulation to discovery if # of vertices > 3 and dividers > 2
 * yields useful, coherent results.
 *
 */

#include <iostream>
#include "graphics.h"
#include "extgraph.h"
#include "random.h"
#include "vector.h"
#include "simpio.h"

const double SmallRadius = 0.01; // inches
const double LargeRadius = 0.2;
const double FrameRate = 0.000001;   // seconds
const double Divider = 2;

const string FigureColor = "Green";
const string DotColor = "Blue";
const string LetterColor = "Red";

struct pointT {
    double x;
    double y;
};

enum colorT {Black, DarkGray, Gray, LightGray, Red, Yellow, Green, Cyan, Blue, Magenta, White};

pointT waitAndGetPoint();
void getAllPoints(int numPoints, Vector<pointT> &vertex);
void drawFigure(Vector<pointT> vertex);
pointT selectRandomVertex(int numPoints, Vector<pointT> vertex);
void drawSmallFilledCircle();
void movePenHalfDistance(pointT currentPoint, pointT selectedPoint, int runDivider);
pointT getCurrentPoint();
void setRandomColor();


int main() {
    
    SetWindowSize(GetFullScreenWidth(), GetFullScreenHeight());
    SetWindowTitle("Chaos Game");
    InitGraphics();
    
    Randomize();
    
    //pointT aPoint;
    //pointT bPoint;
    //pointT cPoint;
    //pointT dPoint;
    
    Vector<pointT> vertex;
    
    pointT selectedPoint;
    pointT currentPoint;
    
    int numPoints;
    int runDivider;
    
    while (true) {
        cout << "How many points for this simulation (>3): ";
        numPoints = GetInteger();
        if (numPoints >= 3) {
            break;
        }
    }
    while (true) {
        cout << "What is the divisor for this run (>2): ";
        runDivider = GetInteger();
        if (runDivider >=2 ) {
            break;
        }
    }
    
    cout << "Click " << numPoints << " points (A, B, C, D, ... , n) in the graphics window" << endl;
    
    //double GetMouseX() 
    //double GetMouseY()
    //void MovePen(double x,double y)
    //DrawArc(r, 0, 360) 	Draws a circle to the left of the current point.
    
    getAllPoints(numPoints,vertex);
    SetPenColor(FigureColor);
    drawFigure(vertex);
    selectRandomVertex(numPoints, vertex);
    SetPenColor(DotColor);
    drawSmallFilledCircle();
    Pause(1.0);
    UpdateDisplay();
    while (!MouseButtonIsDown()) {
        currentPoint = getCurrentPoint();
        selectedPoint = selectRandomVertex(numPoints, vertex);
        movePenHalfDistance(currentPoint,selectedPoint,runDivider);
        //setRandomColor();
        drawSmallFilledCircle();
        //Pause(FrameRate);
        UpdateDisplay();
    }
    
    SetPointSize(48);
    SetPenColor(LetterColor);
    DrawTextString("Bye");
    UpdateDisplay();
    Pause(1.0);
    
    WaitForMouseUp();
    
    ExitGraphics();
    return 0;
}

void getAllPoints(int numPoints, Vector<pointT> &vertex) {

    for (int i = 0; i < numPoints; i++) {
        vertex.add(waitAndGetPoint());
    }
}

pointT waitAndGetPoint() {
    
    pointT clickPoint;
    
    WaitForMouseDown();
    
    clickPoint.x = GetMouseX();
    clickPoint.y = GetMouseY();
    
    return clickPoint;
}

void drawFigure(Vector<pointT> vertex) {
    MovePen(vertex[0].x, vertex[0].y);
    int size = vertex.size();
    
    for (int i = 0; i < size - 1; i++) {
        DrawLine(vertex[i+1].x - vertex[i].x, vertex[i+1]. y - vertex[i].y);
    }
    DrawLine(vertex[0].x - vertex[size - 1].x, vertex[0]. y - vertex[size - 1].y);
}

pointT selectRandomVertex(int numPoints, Vector<pointT> vertex) {
    int startPoint = RandomInteger(0,numPoints-1);
    MovePen(vertex[startPoint].x, vertex[startPoint].y);
    return vertex[startPoint];
}

void drawSmallFilledCircle() {
    StartFilledRegion(1);
    DrawArc(SmallRadius, 0, 360);
    EndFilledRegion();
}

pointT getCurrentPoint() {
    pointT current;
    current.x = GetCurrentX();
    current.y = GetCurrentY();
    //cout << "getCurrentPoint() >> X = " << current.x << " : Y = " << current.y << endl;
    return current;
}

void movePenHalfDistance(pointT currentPoint, pointT selectedPoint, int runDivider) {
    MovePen((currentPoint.x + selectedPoint.x)/runDivider, (currentPoint.y + selectedPoint.y)/runDivider);
}

void setRandomColor() {
    //enum colorT {Black, DarkGray, Gray, LightGray, Red, Yellow, Green, Cyan, Blue, Magenta, White};
    
    colorT color = (colorT) RandomInteger(Black,Magenta);
    switch (color) {
        case Black:
            SetPenColor("Black");
            break;
        case DarkGray:
            SetPenColor("Dark Gray");
            break;
        case Gray:
            SetPenColor("Gray");
            break;
        case LightGray:
            SetPenColor("Light Gray");
            break;
        case Red:
            SetPenColor("Red");
            break;
        case Yellow:
            SetPenColor("Yellow");
            break;
        case Green:
            SetPenColor("Green");
            break;
        case Cyan:
            SetPenColor("Cyan");
            break;
        case Blue:
            SetPenColor("Blue");
            break;
        case Magenta:
            SetPenColor("Magenta");
            break;
            
        default:
            Error("Bad Color choice");
            break;
    }
}
