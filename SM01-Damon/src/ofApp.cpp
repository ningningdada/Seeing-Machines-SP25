#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Set the size of each cell (when drawing, each cell will be 20x20 pixels).
    cellSize = 20;

    // Determine the number of cells horizontally and vertically based on the window size.
    gridWidth = ofGetWidth() / cellSize;
    gridHeight = ofGetHeight() / cellSize;

    // Allocate an ofImage in grayscale to serve as our grid.
    lifeImg.allocate(gridWidth, gridHeight, OF_IMAGE_GRAYSCALE);

    // Fill the image with an initial random state:
    // 0 (black) represents a dead cell, and 255 (white) represents a live cell.
    ofPixels lifePix = lifeImg.getPixels();
    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            if (ofRandomuf() < 0.5)
                lifePix.setColor(x, y, ofColor(0));    // Dead cell
            else
                lifePix.setColor(x, y, ofColor(255));  // Live cell
        }
    }
    // Since getPixels() returns a reference, update the image with our new pixel data.
    lifeImg.setFromPixels(lifePix);

}

//--------------------------------------------------------------
void ofApp::update(){
    // Get a copy of the current pixel data.
    ofPixels currentPixels = lifeImg.getPixels();

    // Allocate a new ofPixels object for the next generation.
    ofPixels newPixels;
    newPixels.allocate(gridWidth, gridHeight, OF_IMAGE_GRAYSCALE);

    // Process each cell in the grid.
    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            int liveNeighbors = 0;

            // Check all 8 neighbors (with wrapping around the edges)
            for (int offsetY = -1; offsetY <= 1; offsetY++) {
                for (int offsetX = -1; offsetX <= 1; offsetX++) {
                    // Skip the cell itself.
                    if (offsetX == 0 && offsetY == 0) continue;

                    // Compute neighbor coordinates with wrapping:
                    int neighborX = (x + offsetX + gridWidth) % gridWidth;
                    int neighborY = (y + offsetY + gridHeight) % gridHeight;

                    // If the neighbor cell is alive (white, brightness 255), count it.
                    if (currentPixels.getColor(neighborX, neighborY).getBrightness() == 255)
                        liveNeighbors++;
                }
            }

            // Apply the Game of Life rules:
            // 1. A live cell with fewer than 2 live neighbors dies (underpopulation).
            // 2. A live cell with more than 3 live neighbors dies (overcrowding).
            // 3. A dead cell with exactly 3 live neighbors becomes alive (reproduction).
            bool isAlive = (currentPixels.getColor(x, y).getBrightness() == 255);
            if (isAlive) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newPixels.setColor(x, y, ofColor(0));    // Cell dies.
                }
                else {
                    newPixels.setColor(x, y, ofColor(255));  // Cell survives.
                }
            }
            else {
                if (liveNeighbors == 3) {
                    newPixels.setColor(x, y, ofColor(255));  // Cell becomes alive.
                }
                else {
                    newPixels.setColor(x, y, ofColor(0));    // Cell remains dead.
                }
            }
        }
    }

    // Update the image with the new generation.
    lifeImg.setFromPixels(newPixels);
    
    // Set texture filtering to nearest neighbor for crisp edges.
    lifeImg.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw the ofImage scaled up so that each cell appears as a 20x20 block.
    lifeImg.draw(0, 0, gridWidth * cellSize, gridHeight * cellSize);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // When the 'r' key is pressed, reset the grid to a new random pattern.
    if (key == 'r' || key == 'R') {
        ofPixels& lifePix = lifeImg.getPixels();
        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {
                if (ofRandomuf() < 0.5)
                    lifePix.setColor(x, y, ofColor(0));    // Dead cell.
                else
                    lifePix.setColor(x, y, ofColor(255));  // Live cell.
            }
        }
        lifeImg.setFromPixels(lifePix);

        // Reapply texture filtering for crisp cell edges.
        lifeImg.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
