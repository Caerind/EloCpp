#ifndef ELOCPP_HPP_INCLUDED
#define ELOCPP_HPP_INCLUDED

#include <math.h>

namespace elo
{

int scoreToOverpass = 2400;
int basicRank = 1200;

enum Result
{
    Win,
    Draw,
    Lose,

}; // ENUM RESULT

class Player
{
    public:
        Player() { mRank = basicRank; mGamePlayed = 0; mOverpassed = false; }
		Player(float rank, float gamePlayed, bool overpassed) : mRank(rank), mGamePlayed(gamePlayed),mOverpassed(overpassed) {}

        float versus(float const& oRank, Result const& result)
        {
            float e = getE(oRank);
            float s = getS(result);
            float k = getK();
            mRank = mRank + k * (s - e);
            update();
            return mRank;
        }

        float getRank() const { return mRank; }

    private:
        float   getE(float const& oRank) { return getQ(mRank) / (getQ(mRank) + getQ(oRank)); }
        float   getS(Result const& result)
        {
            switch (result)
            {
                case Win: return 1;
                case Draw: return 0.5;
                default: return 0;
            }
        }
        float   getK()
        {
            if (mGamePlayed < 30)
                return 30;
            else if (!mOverpassed)
                return 15;
            return 10;
        }
        float   getQ(float rank) { return pow(10,rank/400); }

        void update()
        {
            mGamePlayed++;
            if (mRank >= scoreToOverpass)
            {
                mOverpassed = true;
            }
            int a = (int)(mRank+0.5);
            mRank = a;
        }

    private:
        float mRank;
        float mGamePlayed;
        bool  mOverpassed;

}; // CLASS PLAYER

void Manager(Player& a, Player& b, Result const& result = Win)
{
    if (result == Win)
    {
        float rankA = a.getRank();
        a.versus(b.getRank(), Win);
        b.versus(rankA, Lose);
    }
    else if (result == Draw)
    {
        float rankA = a.getRank();
        a.versus(b.getRank(), Draw);
        b.versus(rankA, Draw);
    }
    else
    {
        Manager(b,a,Win);
    }

} // VOID MANAGER

} // NAMESPACE ELO

#endif // ELOCPP_HPP_INCLUDED
