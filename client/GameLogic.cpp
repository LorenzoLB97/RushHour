#include "GameLogic.h"

GameLogic::GameLogic(int level)
	: m_level{ level }
{
	if (level == 1) m_levelArray = BOARD_LEVEL1;
	else if (level == 2) m_levelArray = BOARD_LEVEL2;
	else m_levelArray = BOARD_LEVEL3;
}

bool GameLogic::moveAuto(const std::string& name, int pressedArrowKey) {
	// Only for debug (in case we typed the names wrongly). Otherwise this is safe to remove!
	int startRow = 0, startCol = 0;
	bool found = false;
	for (int i = 0; i < TOTAL_ROWS && !found; ++i) {
		for (int j = 0; j < TOTAL_COLUMNS; ++j) {
			if (m_levelArray[i][j] == name) {
				startRow = i;
				startCol = j;
				found = true;
				break;
			}
		}
	}
	if (!found) {
		return false;
	}

	std::pair movementDirection = getDirection(pressedArrowKey);
	// movementDirection.first = DirectionType
	// movementSection = delta (either -1, 0, or 1)

	// Controlla che l'auto non esca dalla board
	auto coordsToMove = movementDirection.first == DirectionType::LEFT_RIGHT
		? getNewCoordinatesLeftRight(movementDirection.second, name)
		: getNewCoordinatesUpDown(movementDirection.second, name);

	if (coordsToMove == std::nullopt) return false;

	// Ora puoi muovere l'auto nella nuova posizione
	for (int i = 0; i < TOTAL_ROWS; ++i) {
		for (int j = 0; j < TOTAL_COLUMNS; ++j) {
			if (m_levelArray[i][j] == name) {
				m_levelArray[i][j] = "";
			}
		}
	}
	
	for (auto coord : coordsToMove.value()) {
		m_levelArray[coord.first][coord.second] = name;
	}
	

	return true;
}


bool GameLogic::isAutoRowType(int row, int column, const std::string& autoName) const {
	if (row < GameLogic::TOTAL_COLUMNS - 1 && m_levelArray[row + 1][column] == autoName) {
		return true;
	}
	if (row > 0 && m_levelArray[row - 1][column] == autoName) { 
		return true;
	}
	return false;
}

bool GameLogic::isAutoColumnType(int row, int column, const std::string& autoName) const {
	if (column < GameLogic::TOTAL_ROWS-1 && m_levelArray[row][column + 1] == autoName) {
		return true;
	}
	if (column > 0 && m_levelArray[row][column - 1] == autoName) {
		return true;
	}
	return false;
}

bool GameLogic::isCollision(int newRow, int newColumn, const std::string& autoName) const {
	if (newRow < 0 || newRow >= GameLogic::TOTAL_ROWS || newColumn < 0 || newColumn >= GameLogic::TOTAL_COLUMNS) {
		return true;
	}
	if (m_levelArray[newRow][newColumn] != "" && m_levelArray[newRow][newColumn] != autoName) {
		return true;
	}
	return false;
}

OptionalVectorPair GameLogic::getNewCoordinatesLeftRight(int deltaColumn, const std::string& autoName) const {
	std::vector<std::pair<int, int>> newCoordinates;
	for (int i = 0; i < GameLogic::TOTAL_ROWS; ++i) {
		for (int j = 0; j < GameLogic::TOTAL_COLUMNS; ++j) {
			if (m_levelArray[i][j] == autoName) {
				if (!isAutoColumnType(i, j, autoName)) {
					// Auto cannot go this direction
					return std::nullopt;
				}
				int newCol = j + deltaColumn;

				if (isCollision(i, newCol, autoName)) return std::nullopt;
				newCoordinates.push_back(std::pair{ i, newCol });
			}
		}
	}
	return std::optional{ newCoordinates };
}

OptionalVectorPair GameLogic::getNewCoordinatesUpDown(int deltaRow, const std::string& autoName) const {
	std::vector<std::pair<int, int>> newCoordinates;
	for (int i = 0; i < GameLogic::TOTAL_ROWS; ++i) {
		for (int j = 0; j < GameLogic::TOTAL_COLUMNS; ++j) {
			if (m_levelArray[i][j] == autoName) {
				if (!isAutoRowType(i, j, autoName)) {
					// Auto cannot go this direction
					return std::nullopt;
				}
				int newRow = i + deltaRow;
				if (isCollision(newRow, j, autoName)) return std::nullopt;
				newCoordinates.push_back(std::pair{ newRow, j });
			}
		}
	}
	return std::optional{ newCoordinates };
}

std::pair<int, int> GameLogic::getDirection(int pressedArrowKey) const {
	int deltaRow = 0, deltaCol = 0;
	switch (pressedArrowKey) {
	case 101: return std::pair{ DirectionType::UP_DOWN, -1 };
	case 103: return std::pair{ DirectionType::UP_DOWN, 1 };
	case 100: return std::pair{ DirectionType::LEFT_RIGHT, -1 };
	case 102: return std::pair{ DirectionType::LEFT_RIGHT, 1 };
	default:  return std::pair{ DirectionType::NOT_FOUND, 0 }; // Impossible case, silence warnings
	}
}

bool GameLogic::checkVictory() {
	if (m_levelArray[0][2] == "AutoV001") return true;
	return false;
}


