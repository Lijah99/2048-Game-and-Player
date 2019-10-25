/**
 * @file mediocrePlayer.cpp
 * @author Elijah Flinders and Trevor Bormann
 * @brief This file contains the algorithm used by the mediocrePlayer
 * @date 2019-10-22
 * 
 * @copyright Copyright (c) 2019
 */
#include <iostream>
#include <cmath>
#include "board.h"

using namespace std;

#include "player.h"

//constant values for algorithm
const int WEIGHTED[4][4] = {{0,0,0,0}, {1, 3, 7, 20}, 
{1097, 403, 148, 55}, {2981, 8103, 22067, 59874}}; /*!< The weighted board to ensure snake pattern */

const int NUMFUTURELOOKS = 8; /*!< The number of steps of approximation into the future */
const int POWERCHOICE = 111;  /*!< The exponential power used to weigh the future looks */
const int NUM_TRIALS = 5;     /*!< The number of algorithm trials */

//functions
long long int futureLook(Board &b); //Applys the algorithm a step into the future
Player::Player() { }                //Base player constructor

/**
 * @brief This is the player's make move function, it will take in a current status
 * of a board, and semi-recursively walk through possible future outcomes, 
 * accumulate score after checking with a constant weighted board for structure,
 * and then analyze each 4 steps to see which would 
 * most likely give a better score in the future.
 * 
 * This is essentially a smarter greedy algorithm with a weighted preference.
 * 
 * @param[in] b - The changing board being passed it
 * @return ValidMove A decided move based off what the player determines is best
 */
ValidMove Player::makeMove(const Board b)
{
  // Create all 4 boards and check for invalid moves
  long long int bestScore = 0;
  long long int scoreAvg;
  long long int scoreArray[4] = {0,0,0,0};
  ValidMove bestMove = NONE;

  //Go through every possible move on the board
  int i = 0;
  int boardNum = 0;
  for(ValidMove move : {LEFT, RIGHT, UP, DOWN})
  {
    //Check by comparison to weighted
    //Go through the number of trials completed
    scoreAvg = 0;
    for(int k = 0; k< NUM_TRIALS; k++)
      {
        //If good move, compare add weight to score
        Board currBoard(b);
        if(currBoard.checkMove(move))
          {
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    scoreAvg += currBoard.board[i][j] * WEIGHTED[i][j];
            //Add each future move and weigh them based off number of looks
            for(int i = 0; i < NUMFUTURELOOKS; i++)
              scoreAvg  += futureLook(currBoard) * pow(float(NUMFUTURELOOKS - i) / NUMFUTURELOOKS,POWERCHOICE);
          }
        //Invalid move
        else
          scoreAvg += -10000000000;
      }
    //apply averaged score over trials to move's accumulation in array
    scoreArray[boardNum]=scoreAvg/NUM_TRIALS;
    boardNum++;
  }
  //choose the move with the highest score
  i = 0;
  for(i=0; i<4; i++)
  {
    if(scoreArray[i]>bestScore)
      {
	      bestScore = scoreArray[i];
	      bestMove = ValidMove(i+1);
      }
  }
  return bestMove;
}

/**
 * @brief Will take a board, and look one more step into the future, accumulating 
 * score much like the primary player make move function, but it returns a long 
 * integer representing a future score to be associated with a particular move
 * in the main move function. This gives us a semi-recursive property with our 
 * algorithm
 * 
 * @param[in] b - a board being passed by reference to be worked upon
 * @return long long int of highest score one step into the future
 */
long long int futureLook(Board &b)
{
  int boardNum = 0;
  long long int scoreArray[4] = {0};
  //Go through every possible move
  for (ValidMove move : {DOWN, RIGHT, LEFT, UP})
    {
      Board currBoard(b);
      if(currBoard.checkMove(move))
      {
        for(int i = 0; i < 4; i++)
          for(int j = 0; j < 4; j++)
            scoreArray[boardNum] += currBoard.board[i][j] * WEIGHTED[i][j];
      }
      else
        scoreArray[boardNum] += -10000000000;
      boardNum++;
    }
  //Set base move to down and check for best scoring move
  long long int bestScore = 0;
  ValidMove bestMove = DOWN;
  for(int i=0; i<4; i++)
  {
    if(scoreArray[i]>bestScore)
      {
	      bestScore = scoreArray[i];
	      bestMove = ValidMove(i+1);
      }
  }
  b.checkMove(bestMove);
  return bestScore;
}
