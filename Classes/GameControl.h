#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

#include "EyreFree.h"

#define CHESSBOARD_SIZE	15
#define WIN_SIZE		5

enum PlayerType
{
	PLAYER_EMPTY = 0,
	PLAYER_BLACK = 1,
	PLAYER_WHITE = 2
};

enum GameResult
{
	PLAYER_WIN	= 0,
	PLAYER_LOSE	= 1,
	PLAYER_NONE	= 2,
};

class GameControl
{

private:

	bool m_IsEnable;								//游戏进行中
	int	m_ChessBoard[CHESSBOARD_SIZE][CHESSBOARD_SIZE];	//棋盘
	int	m_Turn;										//当前已存在棋子数
	PlayerType m_Player;							//当前落子玩家
	GameResult m_Result;							//获胜结果

private:

	bool SetChessPointBlack(POINT theSite);			//设置棋盘相应点值为PLAYER_BLACK
	bool SetChessPointWhite(POINT theSite);			//设置棋盘相应点值为PLAYER_WHITE

	bool IsChessPointEnable(POINT theSite);			//检测相应点是否能够落子

	bool IsGameOver();								//检测游戏是否结束
	bool IsAnyWinner();								//检测是否存在获胜者
	bool IsChessBoardFull();						//检测棋盘是否已满

public:
	GameControl();
	~GameControl();

	void InitGame();								//初始化参数

	bool SetChessPoint(POINT theSite);				//设置棋盘相应点值
	
	PlayerType GetChessPointValue(POINT theSite);	//获取棋盘相应点值
	PlayerType GetChessPlayer();					//获取当前落子玩家

	GameResult GetGameResult();						//获取获胜结果
	void SetGameResult();							//设置获胜结果

	int GetChessTurnValue();						//获取棋盘已存在棋子数
	bool CheckGameState();							//检测游戏状态

	void MakeGameDisable();							//使游戏停止响应
	void MakeGameEnable();							//使游戏正常响应
	bool IsGameEnable();							//检测游戏是否进行正常响应

	bool AI_Sample(POINT* AIpoint);					//AI示例：测试用,随机落子
	bool AI_Level_1(POINT* AIpoint);				//AI_Level_1：初级人工智能，可较完美地战胜小学生
};

#endif  // __GAMECONTROL_H__
