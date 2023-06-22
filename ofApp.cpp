#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	vector<glm::vec2> hole_location_list;

	ofSetLineWidth(3);
	ofNoFill();
	ofColor color;
	for (int i = 0; i < 2; i++) {

		auto hue = ofMap(i, 0, 2, 0, 255);
		color.setHsb(hue, 200, 255);
		ofSetColor(color);

		vector<glm::vec3> vertices;
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(360));
		for (int k = 0; k < 210; k++) {

			auto x = ofMap(ofNoise(noise_seed.x, k * 0.01 + ofGetFrameNum() * 0.01), 0, 1, -300, 300);
			auto y = ofMap(ofNoise(noise_seed.y, k * 0.01 + ofGetFrameNum() * 0.01), 0, 1, -300, 300);
			auto z = ofMap(sin(((int)noise_seed.z + k + ofGetFrameNum()) * 4 * DEG_TO_RAD), -1, 1, -150, 150);

			vertices.push_back(glm::vec3(x, y, z));

			if (z < 3 && z > -3) {

				hole_location_list.push_back(glm::vec2(x, y));
			}
		}

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(false);
	}

	ofSetLineWidth(1);
	ofSetColor(0);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(-300, -300));
	ofVertex(glm::vec2(-300, 300));
	ofVertex(glm::vec2(300, 300));
	ofVertex(glm::vec2(300, -300));
	for (int i = 0; i < hole_location_list.size(); i++) {

		ofNextContour(true);
		for (int deg = 0; deg <= 360; deg++) {

			ofVertex(hole_location_list[i] + glm::vec2(20 * cos(deg * DEG_TO_RAD), 20 * sin(deg * DEG_TO_RAD)));
		}
	}
	ofEndShape();

	ofNoFill();
	ofSetColor(255);
	ofDrawRectangle(-300, -300, 600, 600);
	for (int i = 0; i < hole_location_list.size(); i++) {

		ofDrawCircle(hole_location_list[i], 20);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}