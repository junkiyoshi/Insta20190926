#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 300, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotate(180);
	ofRotateX(180);

	string word = "KIYOSHI";
	auto path_list = font.getStringAsPoints(word, true, false);
	for (auto path : path_list) {

		auto outline = path.getOutline();

		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(300);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, vertices[vertices_index].y + this->font.stringHeight(word) * 0.5, 350);
				location = glm::normalize(location) * -350;

				auto angle_x = ofMap(ofNoise(location.x * 0.001, ofGetFrameNum() * 0.005), 0, 1, -PI * 0.25, PI * 0.25);
				auto angle_y = ofMap(ofNoise(location.y * 0.001, ofGetFrameNum() * 0.005), 0, 1, -PI * 0.25, PI * 0.25);
				auto angle_z = ofMap(ofNoise(location.z * 0.001, ofGetFrameNum() * 0.005), 0, 1, -PI * 0.25, PI * 0.25);

				auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
				location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;

				ofVertex(location);
			}
		}
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}