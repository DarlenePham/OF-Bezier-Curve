#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	controlPoints.push_back(ofVec2f(100, 100));
	controlPoints.push_back(ofVec2f(200, 100));
	controlPoints.push_back(ofVec2f(300, 100));
	controlPoints.push_back(ofVec2f(400, 100));
	selectedPointIndex = -1;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::red);
	for (auto x : controlPoints) {
		ofDrawCircle(x, 10);
	}

	ofSetColor(ofColor::blue);
	ofSetLineWidth(1);
	ofDrawLine(controlPoints[0], controlPoints[1]);
	ofDrawLine(controlPoints[1], controlPoints[2]);
	ofDrawLine(controlPoints[2], controlPoints[3]);

	drawCurve(100);
}

glm::vec3 ofApp::curvePt(float t) {
	glm::vec3 p;
	float b0 = pow(1 - t, 3);
	float b1 = 3 * t * pow(1 - t, 2);
	float b2 = 3 * pow(t, 2) * (1 - t);
	float b3 = pow(t, 3);
	glm::vec3 cp1(controlPoints[0].x, controlPoints[0].y, 0);
	glm::vec3 cp2(controlPoints[1].x, controlPoints[1].y, 0);
	glm::vec3 cp3(controlPoints[2].x, controlPoints[2].y, 0);
	glm::vec3 cp4(controlPoints[3].x, controlPoints[3].y, 0);
	p = b0 * cp1 + b1 * cp2 + b2 * cp3 + b3 * cp4;
	return p;
}

glm::vec3 ofApp::curvePt2(float t) {
	// Construct the Bernstein matrix
	glm::vec4 row0(-1.0f, 3.0f, -3.0f, 1.0f);
	glm::vec4 row1(3.0f, -6.0f, 3.0f, 0.0f);
	glm::vec4 row2(-3.0f, 3.0f, 0.0f, 0.0f);
	glm::vec4 row3(1.0f, 0.0f, 0.0f, 0.0f);
	glm::mat4 B(row0, row1, row2, row3);

	// Compute the curve point by multiplying the Bernstein matrix with the control points matrix
	glm::vec4 T(pow(t, 3), pow(t, 2), t, 1.0f);
	glm::mat4 CP = glm::mat4(
		glm::vec4(controlPoints[0].x, controlPoints[0].y, 0, 0),
		glm::vec4(controlPoints[1].x, controlPoints[1].y, 0, 0),
		glm::vec4(controlPoints[2].x, controlPoints[2].y, 0, 0),
		glm::vec4(controlPoints[3].x, controlPoints[3].y, 0, 0)
	);
	glm::vec3 p = glm::vec3(CP * (B * T));
	return p;
}

void ofApp::drawCurve(int nsegments) {
	// Set the color of the curve
	ofSetColor(ofColor::white);

	// Set the thickness of the curve
	ofSetLineWidth(2);

	// Draw the curve segment by segment
	for (int i = 0; i < nsegments; i++) {
		// Compute the start and end points of the current segment
		float t1 = (float)i / (float)nsegments;
		float t2 = (float)(i + 1) / (float)nsegments;
		glm::vec3 p1 = curvePt(t1);
		glm::vec3 p2 = curvePt(t2);

		// Draw a line segment between the start and end points
		ofDrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (selectedPointIndex >= 0) {
		// If a control point is selected, update its position
		controlPoints[selectedPointIndex].x = x;
		controlPoints[selectedPointIndex].y = y;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < controlPoints.size(); i++) {
		float dist = ofDist(x, y, controlPoints[i].x, controlPoints[i].y);
		if (dist < 10) {
			// If the mouse is inside a circle, select it
			selectedPointIndex = i;
			break;
		}

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// Deselect the control point
	selectedPointIndex = -1;
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
