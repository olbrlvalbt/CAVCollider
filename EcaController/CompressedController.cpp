#include "pch.h"
#include "CompressedController.h"

CompressedController::CompressedController(int _N, int _rule)
	: CompressedController(_N, _rule, CreateRandomBinaryString(_N)) {
}

CompressedController::CompressedController(int _N, int _rule, string _initialCondition)
	: EcaController(_N, _rule, _initialCondition){
	compressedState = new CompressedState(N, initialCondition);
	lutAgent = new ChunkLUTAgent(rule, N);
}

CompressedController::~CompressedController() {
	delete compressedState;
	delete lutAgent;
}


void CompressedController::reset() {
	compressedState->reset();
}

void CompressedController::reset(string _newInitialCondition) {
	compressedState->reset(_newInitialCondition);
}

void CompressedController::restart() {
	compressedState->restart();
}

void CompressedController::saveState() {
	compressedState->saveState();
}

void CompressedController::applySavedState(bool applySavedCount) {
	compressedState->applySavedState(applySavedCount);
}

void CompressedController::resetWithSavedState() {
	compressedState->resetWithSavedState();
}

void CompressedController::applyRule() {
	compressedState->applyRule(*lutAgent);
}

size_t CompressedController::getChunkArrayLength() {
	return compressedState->getChunkArrayLength();
}

long CompressedController::getCurrentIteration() {
	return compressedState->getCurrentIteration();
}

const vector<string>& CompressedController::getCurrentState() {
	return compressedState->getRawState();
}

char CompressedController::setAtPosition(int position, char newValue) {
	return compressedState->setAtPosition(position, newValue);
}

char CompressedController::getAtPosition(int position) {
	return compressedState->getAtPosition(position);
}
