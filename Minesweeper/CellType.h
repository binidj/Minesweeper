#pragma once

/// <summary>
///		Represents a minesweeper cell category. 
/// </summary>
enum CellType
{
	empty = 0,
	one,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	unrevealed,
	banner,
	bomb,
	bombCross
};