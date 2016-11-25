#include "Solution.h"

#include "defs.h"
#include "main.h"

#include <iostream>
#include <iomanip>
#include "field.h"
#include "FieldList.h"

#include "Direction.h"
#include "Step.h"

#include <ctime>
#include <algorithm>

#include "Object.h"

Solution::Solution(int maxSteps)
{
    steps[0] = 0;
    steps[1] = 0;
    way   = new char[maxSteps];
    stone = new char[maxSteps];
    cPosX = new char[maxSteps];
    cPosY = new char[maxSteps];
}

Solution::~Solution(void)
{
    delete[] way;
    delete[] stone;
    delete[] cPosX;
    delete[] cPosY;
}


void Solution::increaseSteps(void)
{
    steps[0]++;
	if (steps[0] >= 100000000)	// 100 million geschafft
	{
		steps[1]++; // einen neue 100million
		steps[0] -=100000000;
	}
}

unsigned long Solution::getSteps(int index) const
{
    return steps[index];
}

void Solution::show(void) const
{
    //char cDir[MAXDIR+1];

/*	cDir[LEFT]	= 'l';
	cDir[UP]	= 'o';
	cDir[DOWN]	= 'u';
	cDir[RIGHT]	= 'r';
  */  
    using namespace std;
    
    cout << endl;
	for (int i = 1; way[i]; i++)
		cout << way[i] << ' ';
    
    
    cout << endl << "Steps: ";

    cout.fill('0');
    cout.width(8);
    cout << getSteps(1);

    cout.fill('0');
    cout.width(8);
    cout << getSteps(0) << endl;
}


StepList Solution::find(int remainingSteps, Field field, FieldList &fieldHistory)
{
    // std::cout << "Depth: " << remainingSteps << std::endl;
    if (field.countUnfinishedBoxes() == 0)
    {
        return StepList();
    }

    if (remainingSteps == 0)
    {
        showState(tooMuchSteps);
        field.print();
        //getch();
        throw false;
    }

    #if defined(TEST_FIELD_AT_START) && TEST_FIELD_AT_START
    if (fieldHistory.containsSimilarField(field))
    {
        showState(similar);
        throw false;
    }

    fieldHistory.push_back(field);
    #endif

    increaseSteps();
    //printStats(remainingSteps);

    //algortihmus V2:
    // alle Steine und Richtungen ausprobieren
    // Weg zum Stein suchen

    try
    {
        return tryStones(remainingSteps, field, field.getBallList(false, true), fieldHistory);
    }
    catch (bool)
    {
        return tryStones(remainingSteps, field, field.getBallList(true, false), fieldHistory);
    }
}

StepList Solution::tryStones(int remainingSteps, const Field &field,const PositionList &stoneList, FieldList &fieldHistory)
{
    for (PositionList::const_iterator stone = stoneList.begin();
         stone != stoneList.end();
         stone++)
    {
        DirectionList dirList = Direction::getAllDirections();
        for (DirectionList::const_iterator dir = dirList.begin();
             dir != dirList.end();
             dir++)
        {
            if (field.isInField((*dir)->back().move(*stone)) &&
                field.getObject((*dir)->back().move(*stone)).playerCanStand() &&
                field.getObject((*dir)->move(*stone)).canAddBall())
            {

                Field nextField = field.createNextField(*stone, **dir);
				// nextField.print();
                #if defined(TEST_FIELD_AFTER_CREATION) && TEST_FIELD_AFTER_CREATION
                if (fieldHistory.containsSimilarField(nextField))
                {
                    showState(similar);
                    throw false;
                }

                fieldHistory.push_back(nextField);
                #endif

                
                try
                {
                    if (!nextField.isPossible((*dir)->move(*stone)))
                    {
                        showState(impossible);
                        #if defined(PRINT_NOT_POSSIBLE) && PRINT_NOT_POSSIBLE
                        nextField.print();
                        #endif
                        continue;
                    }

                   /* if (nextField.isWallFull((*dir)->move(*stone)))
                    {
                        std::cout << "Wall is Full!!!!" << std::endl;
                        nextField.print();
                        continue;
                    }*/


                    //Weg zum Stein
                    //StepList way = field.getWayTo((*dir)->back().move(*stone));
                    StepList way = field.getShortestWayTo((*dir)->back().move(*stone));
                    //Weg mit dem Stein
                    way.push_back(Step(*dir, true));

                    showState(Solution::nextStep);
                    #if defined(PRINT_STEP) && PRINT_STEP
                    nextField.print();
                    #endif

                    if (nextField.countUnfinishedBoxes() == 0)
                    {
                        return way;
                    }

                    // Wag nach dem Stein
                    way += find(remainingSteps - 1, nextField, fieldHistory);

                    return way;
                }
                catch(bool)
                {
					// TODO: only try moves that can be reached
					showState(Solution::cannotReach);
                    continue;
                }
            }
        }
    }
    throw false;
}



int Solution::move(int iStep, const Direction &dir, Field &field)
{
    //int destX = dir.moveX(field.getX());
    //int destY = dir.moveY(field.getY());
    
    Position dest = dir.move(field.getPosition());

    if (field.getObject(dest) == Object::wall)
    	return 0;	// nicht nöglich


	if (field.getObject(dest).hasBall())
    {
        //int twoStepX = dir.moveX(destX);
        //int twoStepY = dir.moveY(destY);
        Position twoStep = dir.move(dest);

        if (field.getObject(twoStep).canAddBall())
		{
            // bewegen mit kugel
            stone[iStep] = 1;
            field.getObject(twoStep).addBall();	
            field.getObject(dest).removeBall();
		}
		else
        {
            return 0;	// nicht möglich
        }
    }
	else
    {
        //bewegen ohne Kugel
		stone[iStep] = 0;
    }
	
    field.removePlayer();
	
	way[iStep] = dir.toChar();	// step festlegen
	way[iStep+1] = 0;			// weg ende festlegen

    field.addPlayer(dest); 

    field.print();

    return 1;	// zug gemacht
}

void Solution::undoStep(int iStep)
{
//    int iDir;

/*	iDir = Back(Way[iStep]);

	if (Stone[iStep])	// stein verschoben
	{
        field.removeBall(field.getY() + MoveY[Way[iStep]],
                         field.getX() + MoveX[Way[iStep]]);
        field.addBall(field.getY(), field.getX());

	}
	else// ohne stein
        field.removePlayer(field.getY(), field.getX());
*/	
	
	//PosX += MoveX[iDir];	// typ bewegeb
	//PosY += MoveY[iDir];
	way[iStep] = 0;			// weg ende festlegen
  //  field.addPlayer(field.getY() + MoveY[iDir], field.getX() + MoveX[iDir]);

return;
}




void Solution::printStats(int step) const
{
    using namespace std;

    #define COUNTER 10

    static clock_t last=0;
    static clock_t last10[10]={0};
    static clock_t now=0;
	
	if ((getSteps(0)%COUNTER)== 0)    // alle 100
	{
        int i = (getSteps(0)/COUNTER) % 10;
		now = clock();
        cout << "Tiefe: " << setw(5) << setfill('0') << step;

        cout << ", Steps: " << setw(8) << setfill('0') << getSteps(1)
                            << setw(8) << setfill('0') << getSteps(0);

        cout << ", t: " << setw(8) << setfill('0') << (now - last);
        cout << ", t10: " << setw(8) << setfill('0') << (now - last10[i]) << endl;;

		last = last10[i] = now;
	}
}


void Solution::showState(State state) const
{
    using namespace std;
    static State oldState = undefined;

    if (state == oldState) 
    {
        switch(state)
        {
        case impossible:
		case cannotReach:
            cout << '!';
            break;
        case nextStep:
        case tooMuchSteps:        
        case similar:
            cout << '.';
            break;
        }
    }
    else
    {
        cout << endl;
        switch(state)
        {
		case impossible:
			cout << "NotPossible!";
			break;
		case cannotReach:
			cout << "cannotReach!";
			break;
		case nextStep:
            cout << "NextStep.";
            break;
        case tooMuchSteps:        
            cout << "TooMuch.";
            break;
        case similar:
            cout << "SimilarFields.";
            break;
        }
    }

    oldState = state;
}