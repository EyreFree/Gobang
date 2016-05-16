#include "GameControl.h"

GameControl::GameControl()
{
	InitGame();
}

GameControl::~GameControl()
{
}

void GameControl::InitGame()								//初始化
{
	for(int i = 0;i < CHESSBOARD_SIZE;++ i)
	{
		for(int j = 0;j < CHESSBOARD_SIZE;++ j)
		{
			m_ChessBoard[i][j] = PLAYER_EMPTY;				//初始化棋盘为空
		}
	}

	m_IsEnable = true;

	m_Turn = 0;												//当前已存在棋子数
	m_Player = PLAYER_BLACK;								//当前落子玩家
	m_Result = PLAYER_NONE;									//获胜结果
}

bool GameControl::SetChessPoint(POINT theSite)				//设置棋盘相应点值
{
	bool bRet = false;
	(m_Turn % 2) ? m_Player = PLAYER_WHITE : m_Player = PLAYER_BLACK;
	if(IsChessPointEnable(theSite))
	{
		switch(m_Player)
		{
		case PLAYER_BLACK:
			SetChessPointBlack(theSite);
			++ m_Turn;
			bRet = true;
			break;
		case PLAYER_WHITE:
			SetChessPointWhite(theSite);
			++ m_Turn;
			bRet = true;
			break;
		default:
			break;
		}
	}
	return bRet;
}

void GameControl::MakeGameDisable()							//使游戏停止响应
{
	m_IsEnable = false;
}

void GameControl::MakeGameEnable()							//使游戏正常响应
{
	m_IsEnable = true;
}

bool GameControl::IsGameEnable()							//检测游戏是否进行正常响应
{
	return m_IsEnable;
}

bool GameControl::SetChessPointBlack(POINT theSite)			//设置棋盘相应点值为PLAYER_BLACK
{
	m_ChessBoard[theSite.y][theSite.x] = PLAYER_BLACK;
	return true;
}

bool GameControl::SetChessPointWhite(POINT theSite)			//设置棋盘相应点值为PLAYER_WHITE
{
	m_ChessBoard[theSite.y][theSite.x] = PLAYER_WHITE;
	return true;
}

PlayerType GameControl::GetChessPointValue(POINT theSite)	//获取棋盘相应点值
{
	return (PlayerType)m_ChessBoard[theSite.y][theSite.x];
}

bool GameControl::IsChessPointEnable(POINT theSite)			//检测相应点是否能够落子
{
	if(theSite.x >= 0 && theSite.x < CHESSBOARD_SIZE && theSite.y >= 0 && theSite.y < CHESSBOARD_SIZE )
	{
		return (PLAYER_EMPTY == (PlayerType)m_ChessBoard[theSite.y][theSite.x]);
	}
	return false;
}

bool GameControl::IsGameOver()								//检测游戏是否结束
{
	return (GetGameResult() != PLAYER_NONE || IsChessBoardFull());
}

bool GameControl::IsAnyWinner()								//检测是否存在获胜者
{
	//'-'方向
	int winCount = 0;
	for(int x = 0;x < CHESSBOARD_SIZE;++ x)
	{
		winCount = 0;
		for(int y = 0;y < CHESSBOARD_SIZE - 1;++ y)
		{
			if(PLAYER_EMPTY != m_ChessBoard[x][y] && m_ChessBoard[x][y] == m_ChessBoard[x][y + 1])
			{
				++ winCount;
				if(winCount >= WIN_SIZE - 1)
				{
					return true;
				}
				continue;
			}
			winCount = 0;
		}
	}
	//'|'方向
	for(int y = 0;y < CHESSBOARD_SIZE;++ y)
	{
		winCount = 0;
		for(int x = 0;x < CHESSBOARD_SIZE - 1;++ x)
		{
			if(PLAYER_EMPTY != m_ChessBoard[x][y] && m_ChessBoard[x][y] == m_ChessBoard[x + 1][y])
			{
				++ winCount;
				if(winCount >=  WIN_SIZE - 1)
				{
					return true;
				}
				continue;
			}
			winCount = 0;
		}
	}
	//'/'方向
	int movex = 0,movey = 0;
	for(int x = WIN_SIZE - 1,y = 0;x <= CHESSBOARD_SIZE - 1;++ x)
	{
		winCount = 0;
		for(movex = x,movey = y;(movex >= 1) && (movey <= CHESSBOARD_SIZE - 2);-- movex,++ movey)
		{
			if(PLAYER_EMPTY != m_ChessBoard[movex][movey] && m_ChessBoard[movex][movey] == m_ChessBoard[movex - 1][movey + 1])
			{
				++ winCount;
				if(winCount >=  WIN_SIZE - 1)
				{
					return true;
				}
				continue;
			}
			winCount = 0;
		}
	}
	for(int x = CHESSBOARD_SIZE - 1,y = 0;y <= CHESSBOARD_SIZE - WIN_SIZE;++ y)
	{
		winCount = 0;
		for(movex = x,movey = y;(movex >= 1) && (movey <= CHESSBOARD_SIZE - 2);-- movex,++ movey)
		{
			if(PLAYER_EMPTY != m_ChessBoard[movex][movey] && m_ChessBoard[movex][movey] == m_ChessBoard[movex - 1][movey + 1])
			{
				++ winCount;
				if(winCount >= WIN_SIZE - 1)
				{
					return true;
				}
				continue;
			}
			winCount = 0;
		}
	}
	//'\'方向
	for(int x = 0,y = 0;y <= CHESSBOARD_SIZE - WIN_SIZE;++ y)
	{
		winCount = 0;
		for(movex = x,movey = y;(movex <= CHESSBOARD_SIZE - 2) && (movey <= CHESSBOARD_SIZE - 2);++ movex,++ movey)
		{
			if(PLAYER_EMPTY != m_ChessBoard[movex][movey] && m_ChessBoard[movex][movey] == m_ChessBoard[movex + 1][movey + 1])
			{
				++ winCount;
				if(winCount >=  WIN_SIZE - 1)
				{
					return true;
				}
				continue;
			}
			winCount = 0;
		}
	}
	for(int x = CHESSBOARD_SIZE - WIN_SIZE,y = 0;x >= 0;-- x)
	{
		winCount = 0;
		for(movex = x,movey = y;(movex <= CHESSBOARD_SIZE - 2) && (movey <= CHESSBOARD_SIZE - 2);++ movex,++ movey)
		{
			if(PLAYER_EMPTY != m_ChessBoard[movex][movey] && m_ChessBoard[movex][movey] == m_ChessBoard[movex + 1][movey + 1])
			{
				++ winCount;
				if(winCount >=  WIN_SIZE - 1)
				{
					return true;
				}
				continue;
			}
			winCount = 0;
		}
	}
	return false;
}

bool GameControl::IsChessBoardFull()						//检测棋盘是否已满
{
	return (CHESSBOARD_SIZE * CHESSBOARD_SIZE < m_Turn);
}

int GameControl::GetChessTurnValue()						//获取棋盘已存在棋子数
{
	return m_Turn;
}

PlayerType GameControl::GetChessPlayer()					//获取当前落子玩家
{
	return m_Player;
}

GameResult GameControl::GetGameResult()						//获取获胜结果
{
	return m_Result;
}

void GameControl::SetGameResult()							//设置获胜结果
{
	if(IsAnyWinner())
	{
		GetChessPlayer() == PLAYER_BLACK ? m_Result = PLAYER_WIN : m_Result = PLAYER_LOSE;
	}
}

bool GameControl::CheckGameState()							//检测游戏状态
{
	return IsGameOver();
}

bool GameControl::AI_Sample(POINT* AIpoint)						//AI
{
	//测试用：随机生成---------------------------------------------------------
	bool posExist = false;
	for(int i = 0;i < CHESSBOARD_SIZE;++ i)
	{
		for(int j = 0;j < CHESSBOARD_SIZE;++ j)
		{
			AIpoint->x = i;
			AIpoint->y = j;
			if(IsChessPointEnable(*AIpoint))
			{
				posExist = true;
				break;
			}
		}
		if(posExist)
		{
			break;
		}
	}
	if(posExist)
	{
		POINT tempPoint = {0,0};
		srand((unsigned int)time(0));
		for(int i = 0;i < 256;++ i)
		{
			tempPoint.x = rand() % CHESSBOARD_SIZE;
			tempPoint.y = rand() % CHESSBOARD_SIZE;
			if(IsChessPointEnable(tempPoint))
			{
				*AIpoint = tempPoint;
				return true;
			}
		}
	}
	return false;
	//-------------------------------------------------------------------------
}

bool GameControl::AI_Level_1(POINT* AIpoint)						//AI_Level_1:EyreFree ,2011
{
	//初级AI

	bool posExist = false;
	for(int i = 0;i < CHESSBOARD_SIZE;++ i)
	{
		for(int j = 0;j < CHESSBOARD_SIZE;++ j)
		{
			AIpoint->x = i;
			AIpoint->y = j;
			if(IsChessPointEnable(*AIpoint))
			{
				posExist = true;
				break;
			}
		}
		if(posExist)
		{
			break;
		}
	}
	if(posExist)
	{
		POINT tempPoint = {0,0};

		//各种乱七八糟的变量
		int Disabled1 = 1,Disabled2 = 1,Disabled3 = 1,Disabled4 = 1,Liver1 = 1,Liver2 = 1,Defender = 0;
		int screen[CHESSBOARD_SIZE][CHESSBOARD_SIZE],SCREEN[CHESSBOARD_SIZE][CHESSBOARD_SIZE],Points[CHESSBOARD_SIZE][CHESSBOARD_SIZE],screentemp[CHESSBOARD_SIZE][CHESSBOARD_SIZE],Pointstemp[CHESSBOARD_SIZE][CHESSBOARD_SIZE],Pointstemp2[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
		for(int i = 0;i < CHESSBOARD_SIZE;++ i)
		{
			for(int j = 0;j < CHESSBOARD_SIZE;++ j)
			{
				screen[i][j] = m_ChessBoard[j][i];
				Points[i][j] = 0;
			}
		}
		int FirstX = 0,FirstY = 0,PointAX = 0,PointAY = FirstY,PointBX = FirstX,PointBY = FirstY,TEST = PLAYER_WHITE,Player = 1,ResultX[2],ResultY[2],Result[2],StepA=0,StepB=0;
		int i = 0,j = 0;

		int mark = 0,Finder = 0;
Again:	
		for(i = 0;i < 15;++ i)
		{
			for(j = 0;j < 15;++ j)
			{
				//进攻程序开始
				//竖方向结分过程开始
				Disabled1 = 1,Disabled2 = 1,Disabled3 = 1,Disabled4 = 1,Liver1 = 1,Liver2 = 1;
				if(screen[i][j]==0)
				{
					FirstX=i;
					FirstY=j;
					PointAX=FirstX;
					PointAY=FirstY;
					screen[i][j]=TEST;
					Player = 1;
					while(screen[PointAX][PointAY+1]==TEST&&PointAY<14)
						PointAY++;
					while(screen[PointAX][PointAY-1]==TEST&&PointAY>0)
					{
						PointAY--;
						Player++;
					}
					if(Player>=5)
					{
						if(Defender==0)
						{
							ResultX[mark]=i;
							ResultY[mark]=j;
							if(Finder!=0)
							{
								ResultX[mark]=j;
								ResultY[mark]=i;
							}
						}
						else
						{
							ResultX[mark]=i;
							ResultY[mark]=j;
							if(Finder!=0)
							{
								ResultX[mark]=j;
								ResultY[mark]=i;
							}
							for(i=0;i<15;i++)
							{
								for(j=0;j<15;j++)
								{
									screen[i][j]=SCREEN[i][j];
								}
							}
						}
						goto STO;
					}
					//当该位置为独子时，判断可能存在的连子
					if(Player==1)
					{
						if(screen[i][j+2]==TEST&&screen[i][j+1]==0&&j<13)
						{
							PointAX=FirstX;
							PointAY=FirstY+2;
							Disabled1=1;
							while(screen[PointAX][PointAY+1]==TEST&&PointAY<14)
							{
								Disabled1++;
								PointAY++;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX][PointAY+mark]==0||screen[PointAX][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15)
							{
								StepA++;
								mark++;
							}
							PointAX=FirstX,PointAY=FirstY,mark=1;
							while((screen[PointAX][PointAY-mark]==0||screen[PointAX][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0)
							{
								StepB++;
								mark++;
							}
							if((StepA+StepB)<(3-Disabled1))
								Disabled1=1;
						}
						else if(screen[i][j-2]==TEST&&screen[i][j-1]==0&&j>1)
						{
							PointAX=FirstX;
							PointAY=FirstY-2;
							Disabled1=1;
							while(screen[PointAX][PointAY-1]==TEST&&PointAY>0)
							{
								Disabled1++;
								PointAY--;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX][PointAY-mark]==0||screen[PointAX][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0)
							{
								StepA++;
								mark++;
							}
							PointAX=FirstX,PointAY=FirstY,mark=1;
							while((screen[PointAX][PointAY+mark]==0||screen[PointAX][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15)
							{
								StepB++;
								mark++;
							}
							if((StepA+StepB)<(3-Disabled1))
								Disabled1=1;
						}
					}
					//当该位置不为独子时，讨论当为连子中某一子时
					if(Player>1)
					{
						if(screen[FirstX][FirstY+1]==screen[FirstX][FirstY-1]&&screen[FirstX][FirstY-1]==TEST&&FirstY>0&&FirstY<14)
						{
							PointAX=FirstX,PointAY=FirstY;
							PointBX=FirstX,PointBY=FirstY;
							while(screen[PointAX][PointAY+1]==TEST&&PointAY<14)
							{
								PointAY++;
							}
							while(screen[PointBX][PointBY-1]==TEST&&PointBY>0)
							{
								PointBY--;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX][PointAY+mark]==0||screen[PointAX][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15)
							{
								StepA++;
								mark++;
							}
							mark=1;
							while((screen[PointBX][PointBY-mark]==0||screen[PointBX][PointBY-mark]==TEST)&&mark<=2&&(PointBY-mark)>=0)
							{
								StepB++;
								mark++;
							}
							Liver1=Player;
							Disabled2=1;
							if((StepA+StepB)<(5-Player))
								Liver1=1;
							if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
							{
								if((StepA+StepB)>=(5-Player))
									Disabled2=Liver1;
								Liver1=1;
							}
						}
						//当该位置不为独子时，讨论当为连子两端时
						else
						{
							if(screen[FirstX][FirstY+1]==0&&FirstY<14)
							{
								StepA=0,StepB=0,mark=1;
								PointAX=FirstX,PointBX=FirstX;
								PointAY=FirstY,PointBY=FirstY;
								while(screen[PointBX][PointBY-1]==TEST&&PointBY>0)
									PointBY--;
								StepA=0,StepB=0,mark=1;
								while((screen[PointAX][PointAY+mark]==0||screen[PointAX][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15)
								{
									StepA++;
									mark++;
								}
								mark=1;
								while((screen[PointBX][PointBY-mark]==0||screen[PointBX][PointBY-mark]==TEST)&&mark<=2&&(PointBY-mark)>=0)
								{
									StepB++;
									mark++;
								}
								Liver2=Player,mark=2,Disabled3=1;
								if((StepA+StepB)<(5-Player))
								{
									Liver2=1;
									mark=0;
								}
								if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
								{
									if(mark!=0)
										Disabled3=Player;
									Liver2=1;
									mark=0;
								}
								Disabled4=1;
								if((screen[FirstX][FirstY+2]==TEST)&&(mark!=0)&&(FirstY<13))
								{
									if((screen[FirstX][FirstY+3]==TEST)&&(FirstY<12))
										Disabled4=3;
									else
										Disabled4=2;
								}
							}
							else
							{
								if(screen[FirstX][FirstY-1]==0&&FirstY>0)
								{
									StepA=0,StepB=0,mark=1;
									PointAX=FirstX,PointBX=FirstX;
									PointAY=FirstY,PointBY=FirstY;
									while(screen[PointBX][PointBY+1]==TEST&&PointBY<14)
										PointBY++;
									StepA=0,StepB=0,mark=1;
									while((screen[PointAX][PointAY-mark]==0||screen[PointAX][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0)
									{
										StepA++;
										mark++;
									}
									mark=1;
									while((screen[PointBX][PointBY+mark]==0||screen[PointBX][PointBY+mark]==TEST)&&mark<=2&&(PointBY+mark)<15)
									{
										StepB++;
										mark++;
									}
									Liver2=Player,mark=2;
									if((StepA+StepB)<(5-Player))
									{
										Liver2=1;
										mark=0;
									}
									Disabled3=1;
									if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
									{
										if(mark!=0)
											Disabled3=Player;
										Liver2=1;
										mark=0;
									}
									Disabled4=1;
									if(screen[FirstX][FirstY-2]==TEST&&mark!=0&&FirstY>=2)
									{
										if(screen[FirstX][FirstY-3]==TEST&&FirstY>=3)
											Disabled4=3;
										else
											Disabled4=2;
									}
								}
							}
						}
					}
					if(Defender!=1)
					{
						switch(Liver1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+400;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+4000;break;
						default:Points[i][j]=Points[i][j]+20000;break;
						}
						switch(Liver2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+400;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+4000;break;
						default:Points[i][j]=Points[i][j]+20000;break;
						}
						switch(Disabled1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled3)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled4)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
					}
					else
					{
						switch(Liver1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+200;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+2500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Liver2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+200;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+2500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled3)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled4)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
					}
					screen[i][j]=0;
				}
				//竖方向结分过程结束
			}
		}
		//横方向结分过程开始
		if(Finder==0)
		{
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					screentemp[i][j]=screen[i][j];
					Pointstemp[i][j]=Points[i][j];
					Points[i][j]=0;
				}
			}
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					screen[i][j]=screentemp[j][i];
				}
			}
			Finder=2;
			goto Again;
		}
		else
		{
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					screen[i][j]=screentemp[i][j];
					Pointstemp2[i][j]=Points[i][j];
				}
			}
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					Points[i][j]=Pointstemp2[j][i];
				}
			}
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					Points[i][j]=Points[i][j]+Pointstemp[i][j];
				}
			}
		}
		//横方向结分过程结束
		//"丶"方向结分过程开始
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				Disabled1=1,Disabled2=1,Disabled3=1,Disabled4=1,Liver1=1,Liver2=1;
				if(screen[i][j]==0)
				{
					FirstX=i;
					FirstY=j;
					PointAX=FirstX;
					PointAY=FirstY;
					screen[i][j]=TEST;
					Player=1;
					while(screen[PointAX+1][PointAY+1]==TEST&&PointAY<14&&PointAX<14)
					{
						PointAY++;
						PointAX++;
					}
					while(screen[PointAX-1][PointAY-1]==TEST&&PointAY>0&&PointAX>0)
					{
						PointAY--;
						PointAX--;
						Player++;
					}
					if(Player>=5)
					{
						if(Defender==0)
						{
							ResultX[mark]=i;
							ResultY[mark]=j;
						}
						else
						{
							ResultX[mark]=i;
							ResultY[mark]=j;
							for(i=0;i<15;i++)
							{
								for(j=0;j<15;j++)
								{
									screen[i][j]=SCREEN[i][j];
								}
							}
						}
						goto STO;
					}
					//当该位置为独子时，判断可能存在的连子
					if(Player==1)
					{
						if(screen[i+2][j+2]==TEST&&screen[i+1][j+1]==0&&i<13&&j<13)
						{
							PointAX=FirstX+2;
							PointAY=FirstY+2;
							Disabled1=1;
							while(screen[PointAX+1][PointAY+1]==TEST&&PointAX<14&&PointAY<14)
							{
								Disabled1++;
								PointAY++;
								PointAX++;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX+mark][PointAY+mark]==0||screen[PointAX+mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX+mark)<15)
							{
								StepA++;
								mark++;
							}
							PointAX=FirstX,PointAY=FirstY,mark=1;
							while((screen[PointAX-mark][PointAY-mark]==0||screen[PointAX-mark][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX-mark)>=0)
							{
								StepB++;
								mark++;
							}
							if((StepA+StepB)<(3-Disabled1))
								Disabled1=1;
						}
						else if(screen[i-2][j-2]==TEST&&screen[i-1][j-1]==0&&j>1&&i>1)
						{
							PointAX=FirstX-2;
							PointAY=FirstY-2;
							Disabled1=1;
							while(screen[PointAX-1][PointAY-1]==TEST&&PointAY>0&&PointAX>0)
							{
								Disabled1++;
								PointAY--;
								PointAX--;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX-mark][PointAY-mark]==0||screen[PointAX-mark][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX-mark)>=0)
							{
								StepA++;
								mark++;
							}
							PointAX=FirstX,PointAY=FirstY,mark=1;
							while((screen[PointAX+mark][PointAY+mark]==0||screen[PointAX+mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX+mark)<15)
							{
								StepB++;
								mark++;
							}
							if((StepA+StepB)<(3-Disabled1))
								Disabled1=1;
						}
					}
					//当该位置不为独子时，讨论当为连子中间某一子时
					if(Player>1)
					{
						if(screen[FirstX+1][FirstY+1]==screen[FirstX-1][FirstY-1]&&screen[FirstX-1][FirstY-1]==TEST&&FirstY>0&&FirstY<14&&FirstX>0&&FirstX<14)
						{
							PointAX=FirstX,PointAY=FirstY;
							PointBX=FirstX,PointBY=FirstY;
							while(screen[PointAX+1][PointAY+1]==TEST&&PointAY<14&&PointAX<14)
							{
								PointAY++;
								PointAX++;
							}
							while(screen[PointBX-1][PointBY-1]==TEST&&PointBY>0&&PointBX>0)
							{
								PointBY--;
								PointBX--;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX+mark][PointAY+mark]==0||screen[PointAX+mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX+mark)<15)
							{
								StepA++;
								mark++;
							}
							mark=1;
							while((screen[PointBX-mark][PointBY-mark]==0||screen[PointBX-mark][PointBY-mark]==TEST)&&mark<=2&&(PointBY-mark)>=0&&(PointBX-mark)>=0)
							{
								StepB++;
								mark++;
							}
							Liver1=Player;
							Disabled2=1;
							if((StepA+StepB)<(5-Player))
								Liver1=1;
							if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
							{
								if((StepA+StepB)>=(5-Player))
									Disabled2=Liver1;
								Liver1=1;
							}
						}
						//当该位置不为独子时，讨论当为连子两端时
						else
						{
							if(screen[FirstX+1][FirstY+1]==0&&FirstY<14&&FirstX<14)
							{
								StepA=0,StepB=0,mark=1;
								PointAX=FirstX,PointBX=FirstX;
								PointAY=FirstY,PointBY=FirstY;
								while(screen[PointBX-1][PointBY-1]==TEST&&PointBY>0&&PointBX>0)
								{
									PointBY--;
									PointBX--;
								}
								StepA=0,StepB=0,mark=1;
								while((screen[PointAX+mark][PointAY+mark]==0||screen[PointAX+mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX+mark)<15)
								{
									StepA++;
									mark++;
								}
								mark=1;
								while((screen[PointBX-mark][PointBY-mark]==0||screen[PointBX-mark][PointBY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX-mark)>=0)
								{
									StepB++;
									mark++;
								}
								Liver2=Player,mark=2,Disabled3=1;
								if((StepA+StepB)<(5-Player))
								{
									Liver2=1;
									mark=0;
								}
								if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
								{
									if(mark!=0)
										Disabled3=Player;
									Liver2=1;
									mark=0;
								}
								Disabled4=1;
								if((screen[FirstX+2][FirstY+2]==TEST)&&(mark!=0)&&(FirstY<13)&&(FirstX<13))
								{
									if((screen[FirstX+3][FirstY+3]==TEST)&&(FirstY<12)&&(FirstX<12))
										Disabled4=3;
									else
										Disabled4=2;
								}
							}
							else
							{
								if(screen[FirstX-1][FirstY-1]==0&&FirstY>0&&FirstX>0)
								{
									StepA=0,StepB=0,mark=1;
									PointAX=FirstX,PointBX=FirstX;
									PointAY=FirstY,PointBY=FirstY;
									while(screen[PointBX+1][PointBY+1]==TEST&&PointBY<14&&PointBX<14)
									{
										PointBY++;
										PointBX++;
									}
									StepA=0,StepB=0,mark=1;
									while((screen[PointAX-mark][PointAY-mark]==0||screen[PointAX-mark][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX-mark)>=0)
									{
										StepA++;
										mark++;
									}
									mark=1;
									while((screen[PointBX+mark][PointBY+mark]==0||screen[PointBX+mark][PointBY+mark]==TEST)&&mark<=2&&(PointBY+mark)<15&&(PointBX+mark)<15)
									{
										StepB++;
										mark++;
									}
									Liver2=Player,mark=2;
									if((StepA+StepB)<(5-Player))
									{
										Liver2=1;
										mark=0;
									}
									Disabled3=1;
									if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
									{
										if(mark!=0)
											Disabled3=Player;
										Liver2=1;
										mark=0;
									}
									Disabled4=1;
									if(screen[FirstX-2][FirstY-2]==TEST&&mark!=0&&FirstY>=2&&FirstX>=2)
									{
										if(screen[FirstX-3][FirstY-3]==TEST&&FirstY>=3&&FirstX>=3)
											Disabled4=3;
										else
											Disabled4=2;
									}
								}
							}
						}
					}
					if(Defender!=1)
					{
						switch(Liver1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+400;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+4000;break;
						default:Points[i][j]=Points[i][j]+20000;break;
						}
						switch(Liver2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+400;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+4000;break;
						default:Points[i][j]=Points[i][j]+20000;break;
						}
						switch(Disabled1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled3)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled4)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
					}
					else
					{
						switch(Liver1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+200;break;
						case 3:Points[i][j]=Points[i][j]+1100;break;
						case 4:Points[i][j]=Points[i][j]+2500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Liver2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+200;break;
						case 3:Points[i][j]=Points[i][j]+1100;break;
						case 4:Points[i][j]=Points[i][j]+2500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled3)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled4)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
					}
					screen[i][j]=0;
				}
			}
		}
		//"丶"方向结分过程结束
		//"/"方向结分过程开始
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				Disabled1=1,Disabled2=1,Disabled3=1,Disabled4=1,Liver1=1,Liver2=1;
				if(screen[i][j]==0)
				{
					FirstX=i;
					FirstY=j;
					PointAX=FirstX;
					PointAY=FirstY;
					screen[i][j]=TEST;
					Player=1;
					while(screen[PointAX-1][PointAY+1]==TEST&&PointAY<14&&PointAX>0)
					{
						PointAY++;
						PointAX--;
					}
					while(screen[PointAX+1][PointAY-1]==TEST&&PointAY>0&&PointAX<14)
					{
						PointAY--;
						PointAX++;
						Player++;
					}
					if(Player>=5)
					{
						if(Defender==0)
						{
							ResultX[mark]=i;
							ResultY[mark]=j;
						}
						else
						{
							ResultX[mark]=i;
							ResultY[mark]=j;
							for(i=0;i<15;i++)
							{
								for(j=0;j<15;j++)
								{
									screen[i][j]=SCREEN[i][j];
								}
							}
						}
						goto STO;
					}
					//当该位置为独子时，判断可能存在的连子
					if(Player==1)
					{
						if(screen[i-2][j+2]==TEST&&screen[i-1][j+1]==0&&i>1&&j<13)
						{
							PointAX=FirstX-2;
							PointAY=FirstY+2;
							Disabled1=1;
							while(screen[PointAX-1][PointAY+1]==TEST&&PointAX>0&&PointAY<14)
							{
								Disabled1++;
								PointAY++;
								PointAX--;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX-mark][PointAY+mark]==0||screen[PointAX-mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX-mark)>=0)
							{
								StepA++;
								mark++;
							}
							PointAX=FirstX,PointAY=FirstY,mark=1;
							while((screen[PointAX+mark][PointAY-mark]==0||screen[PointAX+mark][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX+mark)<15)
							{
								StepB++;
								mark++;
							}
							if((StepA+StepB)<(3-Disabled1))
								Disabled1=1;
						}
						else if(screen[i+2][j-2]==TEST&&screen[i+1][j-1]==0&&j>1&&i<13)
						{
							PointAX=FirstX+2;
							PointAY=FirstY-2;
							Disabled1=1;
							while(screen[PointAX+1][PointAY-1]==TEST&&PointAY>0&&PointAX<14)
							{
								Disabled1++;
								PointAY--;
								PointAX++;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX+mark][PointAY-mark]==0||screen[PointAX+mark][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX+mark)<15)
							{
								StepA++;
								mark++;
							}
							PointAX=FirstX,PointAY=FirstY,mark=1;
							while((screen[PointAX-mark][PointAY+mark]==0||screen[PointAX-mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX-mark)>=0)
							{
								StepB++;
								mark++;
							}
							if((StepA+StepB)<(3-Disabled1))
								Disabled1=1;
						}
					}
					//当该位置不为独子时，讨论当为连子中间某一子时
					if(Player>1)
					{
						if(screen[FirstX-1][FirstY+1]==screen[FirstX+1][FirstY-1]&&screen[FirstX+1][FirstY-1]==TEST&&FirstY>0&&FirstY<14&&FirstX>0&&FirstX<14)
						{
							PointAX=FirstX,PointAY=FirstY;
							PointBX=FirstX,PointBY=FirstY;
							while(screen[PointAX-1][PointAY+1]==TEST&&PointAY<14&&PointAX>0)
							{
								PointAY++;
								PointAX--;
							}
							while(screen[PointBX+1][PointBY-1]==TEST&&PointBY>0&&PointBX<14)
							{
								PointBY--;
								PointBX++;
							}
							StepA=0,StepB=0,mark=1;
							while((screen[PointAX-mark][PointAY+mark]==0||screen[PointAX-mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX-mark)>=0)
							{
								StepA++;
								mark++;
							}
							mark=1;
							while((screen[PointBX+mark][PointBY-mark]==0||screen[PointBX+mark][PointBY-mark]==TEST)&&mark<=2&&(PointBY-mark)>=0&&(PointBX+mark)<15)
							{
								StepB++;
								mark++;
							}
							Liver1=Player;
							Disabled2=1;
							if((StepA+StepB)<(5-Player))
								Liver1=1;
							if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
							{
								if((StepA+StepB)>=(5-Player))
									Disabled2=Liver1;
								Liver1=1;
							}
						}
						//当该位置不为独子时，讨论当为连子两端时
						else
						{
							if(screen[FirstX-1][FirstY+1]==0&&FirstY<14&&FirstX>0)
							{
								StepA=0,StepB=0,mark=1;
								PointAX=FirstX,PointBX=FirstX;
								PointAY=FirstY,PointBY=FirstY;
								while(screen[PointBX+1][PointBY-1]==TEST&&PointBY>0&&PointBX<14)
								{
									PointBY--;
									PointBX++;
								}
								StepA=0,StepB=0,mark=1;
								while((screen[PointAX-mark][PointAY+mark]==0||screen[PointAX-mark][PointAY+mark]==TEST)&&mark<=2&&(PointAY+mark)<15&&(PointAX-mark)>=0)
								{
									StepA++;
									mark++;
								}
								mark=1;
								while((screen[PointBX+mark][PointBY-mark]==0||screen[PointBX+mark][PointBY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX+mark)<15)
								{
									StepB++;
									mark++;
								}
								Liver2=Player,mark=2,Disabled3=1;
								if((StepA+StepB)<(5-Player))
								{
									Liver2=1;
									mark=0;
								}
								if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
								{
									if(mark!=0)
										Disabled3=Player;
									Liver2=1;
									mark=0;
								}
								Disabled4=1;
								if((screen[FirstX-2][FirstY+2]==TEST)&&(mark!=0)&&(FirstY<13)&&(FirstX>1))
								{
									if((screen[FirstX-3][FirstY+3]==TEST)&&(FirstY<12)&&(FirstX>2))
										Disabled4=3;
									else
										Disabled4=2;
								}
							}
							else
							{
								if(screen[FirstX+1][FirstY-1]==0&&FirstY>0&&FirstX<14)
								{
									StepA=0,StepB=0,mark=1;
									PointAX=FirstX,PointBX=FirstX;
									PointAY=FirstY,PointBY=FirstY;
									while(screen[PointBX-1][PointBY+1]==TEST&&PointBY<14&&PointBX>0)
									{
										PointBY++;
										PointBX--;
									}
									StepA=0,StepB=0,mark=1;
									while((screen[PointAX+mark][PointAY-mark]==0||screen[PointAX+mark][PointAY-mark]==TEST)&&mark<=2&&(PointAY-mark)>=0&&(PointAX+mark)<15)
									{
										StepA++;
										mark++;
									}
									mark=1;
									while((screen[PointBX-mark][PointBY+mark]==0||screen[PointBX-mark][PointBY+mark]==TEST)&&mark<=2&&(PointBY+mark)<15&&(PointBX-mark)>=0)
									{
										StepB++;
										mark++;
									}
									Liver2=Player,mark=2;
									if((StepA+StepB)<(5-Player))
									{
										Liver2=1;
										mark=0;
									}
									Disabled3=1;
									if(StepA==0||StepB==0||((StepA+StepB)==(5-Player)))
									{
										if(mark!=0)
											Disabled3=Player;
										Liver2=1;
										mark=0;
									}
									Disabled4=1;
									if(screen[FirstX+2][FirstY-2]==TEST&&mark!=0&&FirstY>=2&&FirstX<13)
									{
										if(screen[FirstX+3][FirstY-3]==TEST&&FirstY>=3&&FirstX<12)
											Disabled4=3;
										else
											Disabled4=2;
									}
								}
							}
						}
					}
					if(Defender!=1)
					{
						switch(Liver1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+400;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+4000;break;
						default:Points[i][j]=Points[i][j]+20000;break;
						}
						switch(Liver2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+400;break;
						case 3:Points[i][j]=Points[i][j]+1000;break;
						case 4:Points[i][j]=Points[i][j]+4000;break;
						default:Points[i][j]=Points[i][j]+20000;break;
						}
						switch(Disabled1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled3)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
						switch(Disabled4)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+400;break;
						default:Points[i][j]=Points[i][j]+900;break;
						}
					}
					else
					{
						switch(Liver1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+200;break;
						case 3:Points[i][j]=Points[i][j]+1100;break;
						case 4:Points[i][j]=Points[i][j]+2500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Liver2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+200;break;
						case 3:Points[i][j]=Points[i][j]+1100;break;
						case 4:Points[i][j]=Points[i][j]+2500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled1)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled2)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled3)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
						switch(Disabled4)
						{
						case 0:
						case 1:break;
						case 2:Points[i][j]=Points[i][j]+50;break;
						case 3:Points[i][j]=Points[i][j]+300;break;
						case 4:Points[i][j]=Points[i][j]+500;break;
						default:Points[i][j]=Points[i][j]+10000;break;
						}
					}
					screen[i][j]=0;
				}
			}
		}
		//"/"方向结分过程结束
		//进攻程序结束
		//守护程序开始
		if(Defender==0)
		{	
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					SCREEN[i][j]=screen[i][j];
				}
			}
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					if(screen[i][j]==1)
						screen[i][j]=2;
					else
					{
						if(screen[i][j]==2)
							screen[i][j]=1;
					}
				}
			}
			Defender=1;
			Finder=0;
			goto Again;
		}
		else
		{
			for(i=0;i<15;i++)
			{
				for(j=0;j<15;j++)
				{
					screen[i][j]=SCREEN[i][j];
				}
			}
		}
		//守护程序结束
		//判定过程开始
		i=rand()%9+3;
		j=rand()%9+3;
		int tempA = 0;
		while(screen[i][j]!=0&&tempA<=25)
		{
			tempA++;
			i=rand()%9+3;
			j=rand()%9+3;
		}
		if(tempA>25)
		{
			for(i=3;i<=11;i++)
			{
				for(j=3;j<=11;j++)
				{
					if(screen[i][j]==0)
					{
						tempA=1;
						goto loop;
					}
				}
			}
		}
		if(tempA>25)
		{
			i=rand()%11+2;
			j=rand()%11+2;
			tempA=0;
			while(screen[i][j]!=0&&tempA<=25)
			{
				tempA++;
				i=rand()%9+3;
				j=rand()%9+3;
			}
		}
		if(tempA>25)
		{
			for(i=0;i<=14;i++)
			{
				for(j=0;j<=14;j++)
				{
					if(screen[i][j]==0)
					{
						tempA=1;
						goto loop;
					}
				}
			}
		}

loop:	ResultX[0]=i,ResultY[0]=j;
		ResultX[1]=i,ResultY[1]=j;
		Result[0]=0,Result[1]=0;
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(Points[i][j]>Result[0])
				{
					Result[0]=Points[i][j];
					ResultX[0]=i;
					ResultY[0]=j;
				}
				else if(Points[i][j]>Result[1])
				{
					Result[1]=Points[i][j];
					ResultX[1]=i;
					ResultY[1]=j;
				}
			}
		}
		if((Result[0]-Result[1])<100)
			mark=(rand()%15%10%2);
		else
			mark=0;
STO:	screen[ResultX[mark]][ResultY[mark]]=2;
		//判定过程结束

		tempPoint.x = ResultX[mark];
		tempPoint.y = ResultY[mark];
		if(IsChessPointEnable(tempPoint))
		{
			*AIpoint = tempPoint;
			return true;
		}
	}

	return false;
}