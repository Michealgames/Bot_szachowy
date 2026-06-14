#include <bits/stdc++.h>
#include <chrono>
using namespace std;
#define pin pair<int, int>
int counter = 0;
char ranks[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
class Move
{
public:
	int startX=-1;
	int startY=-1;
	int endX=-1;
	int endY=-1;
	int piece = -1;
void Show()
{
    char pieces[7] = {' ', ' ', 'N', 'B', 'R', 'Q', 'K'};
    if(startX==-1||endX==-1)
    cout<<"null move"<<endl;
    else
    {
    cout<<pieces[abs(piece)]<<ranks[endY]<<endX+1<<endl;
    }
}
};
Move bestMove;
vector<Move> movesToGen, cleanToGen;
class Pion
{
public:
	int val = 0;
};
bool bnd(int x)
{
	return x>=0&&x<8;
}
void StartPos(vector<vector<Pion>> &tab)
{
	int startL[8] = {4, 2, 3, 5, 6, 3, 2, 4};
	for(int i = 0; i<8; i++) {
		tab[0][i].val = startL[i];
		tab[1][i].val = 1;
		tab[6][i].val = -1;
		tab[7][i].val = -startL[i];
	}
}
void ShowBoard(vector<vector<Pion>> tab)
{
    char lookup[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char pieces[7] = {' ', 'P', 'N', 'B', 'R', 'Q', 'K'};
	for(int i = 7; i>=0; i--)
	{
		for(int j = 0; j<8; j++)
		{
		    if(tab[i][j].val<0)
		    cout<<"\033[31m";
		    else
		    cout<<"\033[93m";
			cout<<" "<<pieces[abs(tab[i][j].val)]<<" ";
		}
		cout<<"\033[90m";
		cout<<i+1<<endl;
	}
	for(int i = 0; i<8; i++)
	cout<<" "<<lookup[i]<<" ";
	cout<<endl;
}
void Make(vector<vector<Pion>> &tab, Move m)
{
    tab[m.endX][m.endY].val = tab[m.startX][m.startY].val;
    tab[m.startX][m.startY].val = 0;
}
void PseudoMoveGen(vector<vector<Pion>> tab, int x, int y)
{
	int piece = tab[x][y].val;
    Move m;
    m.startX = x;
    m.startY = y;
    m.piece = piece;
	switch(abs(piece))
	{
	case 1: //pion basic
	{
		if(piece==-1)
		{
			for(int i = 1; i<=2; i++)
			{
				int xN = x-i;
				if(bnd(xN)&&tab[xN][y].val==0)
				{
				    m.endX = xN;
				    m.endY = y;
					movesToGen.push_back(m);
				}
				else
					break;
				if(x!=6)
				break;
			}
			if(bnd(y-1)&&bnd(x-1)&&tab[x-1][y-1].val*piece<0)
			{
				m.endX = x-1;
				m.endY = y-1;
				movesToGen.push_back(m);
			}
			if(bnd(y+1)&&bnd(x-1)&&tab[x-1][y+1].val*piece<0)
				{
				m.endX = x-1;
				m.endY = y+1;
				movesToGen.push_back(m);
			}
		}
		else
		{
			for(int i = 1; i<=2; i++)
			{
				int xN = x+i;
				if(bnd(xN)&&tab[xN][y].val==0)
				{
					m.endX = xN;
				    m.endY = y;
					movesToGen.push_back(m);
				}
				else
					break;
				if(x!=1)
				break;
			}
			if(bnd(y-1)&&bnd(x+1)&&tab[x+1][y-1].val*piece<0)
				{
				    m.endX = x+1;
				    m.endY = y-1;
					movesToGen.push_back(m);
				}
			if(bnd(y+1)&&bnd(x+1)&&tab[x+1][y+1].val*piece<0)
				{
				    m.endX = x+1;
				    m.endY = y+1;
					movesToGen.push_back(m);
				}
		}
	}
	break;
	case 2: //skoczek
	{
		int offX[] = {-2, -2, -1, -1, 1, 1, 2, 2};
		int offY[] = {-1, 1, -2, 2, -2, 2, -1, 1};
		for(int i = 0; i<8; i++)
		{
			int xN = x+offX[i], yN = y+offY[i];
			if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
			{
			        m.endX = xN;
				    m.endY = yN;
					movesToGen.push_back(m);
			}
		}
	}
	break;
	case 3: //goniec
	{
		int offX[] = {-1, -1, 1, 1};
		int offY[] = {-1, 1, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX[i], yN = y+n*offY[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
					m.endX = xN;
				    m.endY = yN;
					movesToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
	}
	break;
	case 4: //wie¿a
	{
		int offX[] = {-1, 1, 0, 0};
		int offY[] = {0, 0, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX[i], yN = y+n*offY[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
				    m.endX = xN;
				    m.endY = yN;
					movesToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
	}
	break;
	case 5: //hetman
	{
		int offX1[] = {-1, -1, 1, 1};
		int offY1[] = {-1, 1, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX1[i], yN = y+n*offY1[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
					m.endX = xN;
				    m.endY = yN;
					movesToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
		int offX2[] = {-1, 1, 0, 0};
		int offY2[] = {0, 0, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX2[i], yN = y+n*offY2[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
					m.endX = xN;
				    m.endY = yN;
					movesToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
	}
	break;
	case 6: //król
	{
		int offX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
		int offY[] = {-1, 1, 0, -1, 1, 0, -1, 1};
		for(int i = 0; i<8; i++)
		{
			int xN = x+offX[i], yN = y+offY[i];
			if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
			{
				m.endX = xN;
				m.endY = yN;
				movesToGen.push_back(m);
			}
		}
	}
	break;
	default:
		cout<<"coœ Ÿle"<<endl;
	}
}
bool PseudoMovesInPos(vector<vector<Pion>> tab, int turn, int kingX, int kingY)
{
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            if(turn*tab[i][j].val>0)
            {
                movesToGen.clear();
                PseudoMoveGen(tab, i, j);
                for(int i = 0; i<movesToGen.size(); i++)
                {
                if(movesToGen[i].endX==kingX&&movesToGen[i].endY==kingY)
                    return false;
                }
            }
        }
    }
    return true;
}
bool IsLegal(vector<vector<Pion>> tab, Move m)
{
    Make(tab, m);
    int turn = sgn(m.piece)*-1;
    int kingX=-1, kingY=-1;
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            if(tab[i][j].val*turn==-6)
            {
                kingX = i;
                kingY = j;
            }
        }
    }
    return PseudoMovesInPos(tab, turn, kingX, kingY);
}
vector<Move> MoveGen(vector<vector<Pion>> tab, int x, int y)
{
	int piece = tab[x][y].val;
    Move m;
    m.startX = x;
    m.startY = y;
    m.piece = piece;
	switch(abs(piece))
	{
	case 1: //pion basic
	{
		if(piece==-1)
		{
			for(int i = 1; i<=2; i++)
			{
				int xN = x-i;
				if(bnd(xN)&&tab[xN][y].val==0)
				{
				    m.endX = xN;
				    m.endY = y;
					cleanToGen.push_back(m);
				}
				else
					break;
				if(x!=6)
				break;
			}
			if(bnd(y-1)&&bnd(x-1)&&tab[x-1][y-1].val*piece<0)
			{
				m.endX = x-1;
				m.endY = y-1;
				cleanToGen.push_back(m);
			}
			if(bnd(y+1)&&bnd(x-1)&&tab[x-1][y+1].val*piece<0)
				{
				m.endX = x-1;
				m.endY = y+1;
				cleanToGen.push_back(m);
			}
		}
		else
		{
			for(int i = 1; i<=2; i++)
			{
				int xN = x+i;
				if(bnd(xN)&&tab[xN][y].val==0)
				{
					m.endX = xN;
				    m.endY = y;
					cleanToGen.push_back(m);
				}
				else
					break;
				if(x!=1)
				break;
			}
			if(bnd(y-1)&&bnd(x+1)&&tab[x+1][y-1].val*piece<0)
				{
				    m.endX = x+1;
				    m.endY = y-1;
					cleanToGen.push_back(m);
				}
			if(bnd(y+1)&&bnd(x+1)&&tab[x+1][y+1].val*piece<0)
				{
				    m.endX = x+1;
				    m.endY = y+1;
					cleanToGen.push_back(m);
				}
		}
	}
	break;
	case 2: //skoczek
	{
		int offX[] = {-2, -2, -1, -1, 1, 1, 2, 2};
		int offY[] = {-1, 1, -2, 2, -2, 2, -1, 1};
		for(int i = 0; i<8; i++)
		{
			int xN = x+offX[i], yN = y+offY[i];
			if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
			{
			        m.endX = xN;
				    m.endY = yN;
					cleanToGen.push_back(m);
			}
		}
	}
	break;
	case 3: //goniec
	{
		int offX[] = {-1, -1, 1, 1};
		int offY[] = {-1, 1, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX[i], yN = y+n*offY[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
					m.endX = xN;
				    m.endY = yN;
					cleanToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
	}
	break;
	case 4: //wie¿a
	{
		int offX[] = {-1, 1, 0, 0};
		int offY[] = {0, 0, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX[i], yN = y+n*offY[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
				    m.endX = xN;
				    m.endY = yN;
					cleanToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
	}
	break;
	case 5: //hetman
	{
		int offX1[] = {-1, -1, 1, 1};
		int offY1[] = {-1, 1, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX1[i], yN = y+n*offY1[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
					m.endX = xN;
				    m.endY = yN;
					cleanToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
		int offX2[] = {-1, 1, 0, 0};
		int offY2[] = {0, 0, -1, 1};
		for(int i = 0; i<4; i++)
		{
			for(int n = 1; n<8; n++)
			{
				int xN = x+n*offX2[i], yN = y+n*offY2[i];
				if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
				{
					m.endX = xN;
				    m.endY = yN;
					cleanToGen.push_back(m);
					if(tab[xN][yN].val!=0)
						break;
				}
				else
					break;
			}
		}
	}
	break;
	case 6: //król
	{
		int offX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
		int offY[] = {-1, 1, 0, -1, 1, 0, -1, 1};
		for(int i = 0; i<8; i++)
		{
			int xN = x+offX[i], yN = y+offY[i];
			if(bnd(xN)&&bnd(yN)&&tab[xN][yN].val*piece<=0)
			{
				m.endX = xN;
				m.endY = yN;
				cleanToGen.push_back(m);
			}
		}
	}
	break;
	default:
		cout<<"coœ Ÿle"<<endl;
	}
	for(int i = 0; i<cleanToGen.size(); i++)
	{
	    if(!IsLegal(tab, cleanToGen[i]))
	    {
	        cleanToGen.erase(cleanToGen.begin()+i);
	        i--;
	    }
	}
}
vector<Move> MovesInPos(vector<vector<Pion>> tab, int turn)
{
    cleanToGen.clear();
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            if(turn*tab[i][j].val>0)
            {
                MoveGen(tab, i, j);
            }
        }
    }
    return cleanToGen;
}
vector<Move> PseudoMovesInPos(vector<vector<Pion>> tab, int turn)
{
    movesToGen.clear();
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            if(turn*tab[i][j].val>0)
            {
                PseudoMoveGen(tab, i, j);
            }
        }
    }
    return movesToGen;
}
int Eval(vector<vector<Pion>> tab)
{
    const int PST[7][8][8] = {

    // 0 - Pawn
    {
    {  0,  0,  0,  0,  0,  0,  0,  0 },
    { 50, 50, 50, 50, 50, 50, 50, 50 },
    { 10, 10, 20, 30, 30, 20, 10, 10 },
    {  5,  5, 10, 25, 25, 10,  5,  5 },
    {  0,  0,  0, 20, 20,  0,  0,  0 },
    {  5, -5,-10,  0,  0,-10, -5,  5 },
    {  5, 10, 10,-20,-20, 10, 10,  5 },
    {  0,  0,  0,  0,  0,  0,  0,  0 }
    },

    // 1 - Knight
    {
        {-50,-40,-30,-30,-30,-30,-40,-50},
        {-40,-20,  0,  0,  0,  0,-20,-40},
        {-30,  0, 10, 15, 15, 10,  0,-30},
        {-30,  5, 15, 20, 20, 15,  5,-30},
        {-30,  0, 15, 20, 20, 15,  0,-30},
        {-30,  5, 10, 15, 15, 10,  5,-30},
        {-40,-20,  0,  5,  5,  0,-20,-40},
        {-50,-40,-30,-30,-30,-30,-40,-50}
    },

    // 2 - Bishop
    {
        {-20,-10,-10,-10,-10,-10,-10,-20},
        {-10,  5,  0,  0,  0,  0,  5,-10},
        {-10, 10, 10, 10, 10, 10, 10,-10},
        {-10,  0, 10, 10, 10, 10,  0,-10},
        {-10,  5,  5, 10, 10,  5,  5,-10},
        {-10,  0,  5, 10, 10,  5,  0,-10},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-20,-10,-10,-10,-10,-10,-10,-20}
    },

    // 3 - Rook
    {
        {  0,  0,  0,  5,  5,  0,  0,  0},
        { -5,  0,  0,  0,  0,  0,  0, -5},
        { -5,  0,  0,  0,  0,  0,  0, -5},
        { -5,  0,  0,  0,  0,  0,  0, -5},
        { -5,  0,  0,  0,  0,  0,  0, -5},
        { -5,  0,  0,  0,  0,  0,  0, -5},
        {  5, 10, 10, 10, 10, 10, 10,  5},
        {  0,  0,  0,  0,  0,  0,  0,  0}
    },

    // 4 - Queen
    {
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5,  5,  5,  5,  0,-10},
        { -5,  0,  5,  5,  5,  5,  0, -5},
        {  0,  0,  5,  5,  5,  5,  0, -5},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}
    },

    // 5 - King (midgame)
    {
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-20,-30,-30,-40,-40,-30,-30,-20},
        {-10,-20,-20,-20,-20,-20,-20,-10},
        { 20, 20,  0,  0,  0,  0, 20, 20},
        { 20, 30, 10,  0,  0, 10, 30, 20}
    }
};
    int res = 0;
    int vals[] = {-10000000, -900, -500, -300, -300, -100, 0, 100, 300, 300, 500, 900, 10000000};
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
          int p = tab[i][j].val;
          res+=vals[p+6];
          if(p>0)
          {
          res+=PST[p-1][7-i][j];
          //cout<<ranks[j]<<i+1<<" piece "<<p<<"add "<<PST[p-1][7-i][j]<<endl;
          }
          else if(p<0)
          {
          res-=PST[-p-1][i][j];
          //cout<<ranks[j]<<i+1<<" piece "<<-p<<"sub "<<PST[-p-1][i][j]<<endl;
          }
        }
    }
    //cout<<"out "<<res<<endl;
    return res;
}
void ShowMoves(vector<Move> moves)
{
    for(int i = 0; i<moves.size(); i++)
    {
        moves[i].Show();
    }
}
int MinMax(vector<vector<Pion>> tab, int depth, int sD, Move m, int turn, int captureDepth=0)
{
    int ocena = Eval(tab);
    int best;
    if(abs(ocena)>100000||depth==0||captureDepth==3)
    {
    if(counter%100000==0)
    {
    //cout<<counter<<endl;
    //ShowBoard(tab);
    }
    counter++;
    return ocena;
    }
    if(turn==1)
    best = -10000000;
    else
    best = 10000000;
    int res = 0;
    if(m.startX!=-1)
    Make(tab, m);
    vector<Move> moves = PseudoMovesInPos(tab, turn);
    for(int i = 0; i<moves.size(); i++)
    {
        //cout<<moves[i].endX<<" "<<moves[i].endY<<" "<<MinMax(tab, depth-1, moves[i], turn*-1)<<endl;
        int toComp;
        if(tab[moves[i].endX][moves[i].endY].val!=0)
        toComp = MinMax(tab, depth, sD+1, moves[i], turn*-1, captureDepth+1);
        else
        toComp = MinMax(tab, depth-1, sD, moves[i], turn*-1, captureDepth);
            //dziwna ale inspiruj¹ca optymalizacja
            if(turn*toComp>turn*best)
            {
                best = toComp;
                if(depth==sD)
                bestMove = moves[i];
            }
    }
    return best;
}
int main()
{
    vector<vector<Pion>> tab(8);
    Pion p;
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        tab[i].push_back(p);
    }
	StartPos(tab);
	cout<<"Wybierz kolor (b/c)"<<endl;
	char col;
	cin>>col;
	int color = 1;
	if(col!='b')
        color = -1;

	int state = 1;
	Move m;
	//vector<Move> moves = MovesInPos(tab, state);
	//cout<<moves.size()<<endl;
	//ShowMoves(moves);
    //cout<<Eval(tab)<<endl;
	while(true)
	{
	    ShowBoard(tab);
	    if(state==color)
	    {
	        string start, end;
	        int sX, sY, eX, eY;
	        cin>>start>>end;
	        sX = start[1]-'1';
	        eX = end[1]-'1';
	        sY = start[0]-'a';
	        eY = end[0]-'a';
	        cout<<sX<<" "<<sY<<" "<<eX<<" "<<eY<<endl;
	        Move m;
	        m.startX = sX;
	        m.startY = sY;
	        m.endX = eX;
	        m.endY = eY;
	        Make(tab, m);
	    }
	    else
	    {
	       counter = 0;
	       //cout<<"przed"<<endl;
	       std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	       int eval = MinMax(tab, 3, 3, m, state);
	       std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	       //cout<<"po"<<endl;
	       std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	       cout<<"eval "<<eval<<" pos "<<counter<<endl;
	       Make(tab, bestMove);
	    }
	    state*=-1;
	}
	return 0;
}
