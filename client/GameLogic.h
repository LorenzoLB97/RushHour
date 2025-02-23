// GameLogic.h
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <string>
#include <array>
#include <optional>
#include <vector>
#include <utility> // std::pair

/**
 * OptionalVectorPair è un alias per std::optional<std::vector<std::pair<int, int>>>
 */
using OptionalVectorPair = std::optional<std::vector<std::pair<int, int>>>;

/**
 * @brief Enumerazione per i tipi di direzione.
 *
 * DirectionType è un'enumerazione che rappresenta i possibili tipi di direzione dell'auto,
 * come sinistra/destra (LEFT_RIGHT), su/giù (UP_DOWN), o non trovata (NOT_FOUND).
 */
enum DirectionType { LEFT_RIGHT, UP_DOWN, NOT_FOUND };

/**
 * @brief La classe GameLogic gestisce la logica del gioco.
 *
 * La classe GameLogic è responsabile della gestione della logica del gioco, inclusi i movimenti delle automobili
 * sulla griglia, il controllo delle collisioni, la verifica della vittoria e altro.
 */
class GameLogic {
public:
    static constexpr inline int TOTAL_ROWS = 6;
    static constexpr inline int TOTAL_COLUMNS = 6;

private:
    int m_level{};
    std::array<std::array<std::string, GameLogic::TOTAL_ROWS>, GameLogic::TOTAL_COLUMNS> m_levelArray{};


public:
    GameLogic() = default;

    /**
     * @brief Costruttore della classe GameLogic.
     * @param level Il livello del gioco.
     */
    GameLogic(int level);

    /**
     * @brief Esegue un movimento automatico per l'auto specificata nella rappresentazione interna della board.
     * @param name Il nome dell'auto da muovere.
     * @param pressedArrowKey La direzione in cui spostare l'auto.
     * @return True se il movimento è avvenuto con successo, False altrimenti.
     */
    bool moveAuto(const std::string& name, int pressedArrowKey);

    /**
     * @brief Verifica se è stata raggiunta la vittoria.
     * @return True se la vittoria è stata raggiunta, False altrimenti.
     */
    bool checkVictory();

private:
    /**
     * @brief Controlla se l'auto è "orizzontale", ovvero che la sua lunghezza si espande in orizzontale.
     * @param row La riga della griglia.
     * @param column La colonna della griglia.
     * @param autoName Il nome dell'auto da controllare.
     * @return True se l'auto è di tipo orizzontale, false altrimenti.
     */    
    bool isAutoRowType(int row, int column, const std::string& autoName) const;

    /**
     * @brief Controlla se l'auto è "verticale", ovvero che la sua lunghezza si espande in verticale.
     * @param row La riga della griglia.
     * @param column La colonna della griglia.
     * @param autoName Il nome dell'auto da controllare.
     * @return True se l'auto è di tipo verticale, false altrimenti.
     */
    bool isAutoColumnType(int row, int column, const std::string& autoName) const;

    /**
     * @brief Controlla se c'è una collisione in una posizione specifica, nella rappresentazione interna della board.
     * @param newRow La nuova riga.
     * @param newColumn La nuova colonna.
     * @param autoName Il nome dell'auto da controllare.
     * @return True se c'è una collisione, False altrimenti.
     */
    bool isCollision(int newRow, int newColumn, const std::string& autoName) const;

    /**
     * @brief Ottiene le nuove coordinate per uno spostamento sinistra/destra.
     * @param deltaColumn La direzione dello spostamento.
     * @param autoName Il nome dell'auto da muovere.
     * @return Un oggetto OptionalVectorPair contenente le nuove coordinate, o std::nullopt se non possibile.
     */
    OptionalVectorPair getNewCoordinatesLeftRight(int deltaColumn, const std::string& autoName) const;

    /**
     * @brief Ottiene le nuove coordinate per uno spostamento su/giù.
     * @param deltaRow La direzione dello spostamento.
     * @param autoName Il nome dell'auto da muovere.
     * @return Un oggetto OptionalVectorPair contenente le nuove coordinate, o std::nullopt se non possibile.
     */
    OptionalVectorPair getNewCoordinatesUpDown(int deltaRow, const std::string& autoName) const;

    /**
    * @brief Ottiene la direzione in base al tasto freccia premuto.
    * @param pressedArrowKey Il tasto freccia premuto.
    * @return Una coppia contenente il tipo di direzione e il delta associato.
    */
    std::pair<int, int> getDirection(int pressedArrowKey) const;
};


using BoardType = std::array<std::array<std::string, GameLogic::TOTAL_ROWS>, GameLogic::TOTAL_COLUMNS>;

// The initial board positions (per level) are hardcoded with the names of all autos
// We can then find the corresponding mesh object through this name.
const inline BoardType BOARD_LEVEL1{ {
    {{"AutoL005", "AutoL005", "AutoL004", "AutoL004", "", ""}},
    {{"AutoL008G", "AutoL008G", "AutoL008G", "", "", ""}},
    {{"AutoV003", "", "", "", "", ""}},
    {{"AutoV003", "AutoL006", "AutoL006", "AutoL007G", "AutoL007G", "AutoL007G"}},
    {{"AutoV002", "", "AutoV001", "", "", ""}},
    {{"AutoV002", "", "AutoV001", "", "", ""}
}} };

const inline BoardType BOARD_LEVEL2{ {
    {{""       , ""       , "AutoL008G", "AutoL008G", "AutoL008G", "AutoV007G"}},
    {{""       , "AutoV004", ""       , ""       , ""       , "AutoV007G"}},
    {{"AutoV002", "AutoV004", ""       , ""       , ""       , "AutoV007G"}},
    {{"AutoV002", "AutoV003", "AutoL006", "AutoL006", "AutoL005", "AutoL005"}},
    {{""       , "AutoV003", "AutoV001", ""       , ""       , ""       }},
    {{""       , ""       , "AutoV001", ""       , ""       , ""       }
}} };

const inline BoardType BOARD_LEVEL3{ {
    {{"AutoV004", ""       , ""       , ""       , ""       , ""       }},
    {{"AutoV004", "AutoL005", "AutoL005", "AutoL008G", "AutoL008G", "AutoL008G"}},
    {{"AutoV002", ""       , "AutoL007G", "AutoL007G", "AutoL007G", "AutoV003"}},
    {{"AutoV002", ""       , "AutoV001", ""       , ""       , "AutoV003"}},
    {{"AutoL006", "AutoL006", "AutoV001", ""       , ""       , ""       }},
    {{""       , ""       , ""       , ""       , ""       , ""       }
}} };
#endif  // GAMELOGIC_H