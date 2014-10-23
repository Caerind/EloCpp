#ifndef ELOCPP_HPP_INCLUDED
#define ELOCPP_HPP_INCLUDED

namespace elo
{

class Player
{
    public:
        Player() { mRank = Manager::getBasicRank(); mGamePlayed = 0; mOverpassed = false; }
	Player(float rank, int gamePlayed, bool overpassed) : mRank(rank), mGamePlayed(gamePlayed),mOverpassed(overpassed) {}

        float versus(float const& oRank, Result const& result)
        {
            float e = getE(oRank);
            float s = getS(result);
            float k = getK();
            mRank = mRank + k * (s - e);
            update();
            return mRank;
        }

        int getRank() const { return static_cast<int>(mRank); }
        float getRankF() const { return mRank; }
        int getGamePlayed() const { return mGamePlayed; }
        bool hasOverpassed() const { return mOverpassed; }

    private:
        float getE(float const& oRank) { return getQ(mRank) / (getQ(mRank) + getQ(oRank)); }
        float getS(Result const& result)
        {
            switch (result)
            {
                case Win: return 1;
                case Draw: return 0.5;
                default: return 0;
            }
        }
        float getK()
        {
            if (mGamePlayed < 30)
                return 30;
            else if (!mOverpassed)
                return 15;
            return 10;
        }
        float getQ(float rank) { return pow(10,rank/400); }

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
        int mGamePlayed;
        bool  mOverpassed;

};

class Manager
{
    public:
	static void game(Player& a, Player&b, Result const& result = Win)
	{
	    if (result == Win)
	    {
		float rankA = a.getRankF();
		a.versus(b.getRankF(), Win);
		b.versus(rankA, Lose);
	    }
	    else if (result == Draw)
	    {
		float rankA = a.getRankF();
		a.versus(b.getRankF(), Draw);
		b.versus(rankA, Draw);
	    }
	    else
	    {
		game(b,a,Win);
	    }
	}
	static void setScoreToOverpass(int score) { ScoreToOverpass = static_cast<float>(score); }
	static void setScoreToOverpass(float score) { ScoreToOverpass = score; }
	static void setBasicRank(int rank) { BasicRank = static_cast<float>(rank); }
	static void setBasicRank(float rank) { BasicRank = rank; }
	static float getScoreToOverpass() { return ScoreToOverpass; }
	static float getBasicRank() { return BasiRank; }
		
	enum Result
	{
	    Win,
            Draw,
	    Lose,
	};	
		
    private:
	static float ScoreToOverPass;
	static float BasicRank;

};

}

#endif // ELOCPP_HPP_INCLUDED
