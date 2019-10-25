Algorithm:          Mediocre Player
Authors:            Trevor Bormann, Elijah Flinders
Date:               10/18/2019

We have designed an algorithm that will solve the 2048 game and achieve the best score it possibly can.
Two iterations of this algorithm have been completed and verified so far, with a third one in progress.

The first algorithm did not perform very well at all with an average of 2,200, it was beaten by greedy. It had no flexibility through analysis of clear heuristics. In essence, it was a series of conditional if statements which looked for specific characteristics on the board. If the board had less than a 16 tile, it'd continously work to accumulate tiles in the bottom right. After a tile surpassed the 16, it would iterate through a series of moves to keep pulling greater values towards the bottom right corner by comparing maximum value locations between the bottom and second to bottom rows. It's time complexity was not much of an issue as recursion was not used, only move iteration added significant time. The lack of malleability and recursion was it's downfall.

The second algorithm was a vast improvement to the first. The average for it ranges from 19,000 to 22,000 with maximum scores in the 60,000s. It relies more on recursively looking for future moves and applying a greedy-ish algorithm which accumulated successive score during recursion, and would pick the move that would lead to those higher scores. The time complexity of this algorithm is linearly connected to the number of moves into the future we decide to look, though after a certain point, we cease to see improvements in our score as we increased our future moves.

Our third algorithm was a failed attempt at a true recursive function. It would be an increase to quadratic time complexity, we believe that approaching a more thorough recursive method would increase our scores and may have even been scalable if we wanted to run more tests. If the number of future steps is limited, turn time would still remain low.

In the end, we decided to stick to our 2nd algorithm, it still far outperformed our first algorithm by 10 fold and still has quick run time.