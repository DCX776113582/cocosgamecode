//
//  AStar.cpp
//  ArmatureDemo
//
//  Created by QCJ-Mac on 16/1/12.
//
//
#include "AStar.h"

AStar::AStar():
	m_numSurround(8),
	m_row(0),
	m_col(0)
{
	m_surround[0] = ASCOORD( 0,-1);
	m_surround[1] = ASCOORD( 0, 1);
	m_surround[2] = ASCOORD(-1, 0);
	m_surround[3] = ASCOORD( 1, 0);

	m_surround[4] = ASCOORD(-1,-1);
	m_surround[5] = ASCOORD( 1,-1);
	m_surround[6] = ASCOORD(-1, 1);
	m_surround[7] = ASCOORD( 1, 1);

	for(int i = 0 ; i<4 ; ++i)
		m_gAdd[i] = 10;

	for(int i = 4 ; i<8 ; ++i)
		m_gAdd[i] = 14;

	ClearObstacles();
}

void AStar::ClearObstacles()
{
    obstacle_lists.clear();
	m_closeList.clear();
	m_openList.clear();
}

bool AStar::ComputeRoute()
{
	m_openList.clear();
	m_closeList.clear();

	if(m_row<=0 || m_col<=0 )
		return false;
    //这个遍历是从target向start遍历，
	StepData sd(m_target);
	sd._g = 0;
	sd._h = computeH(m_target);

	m_openList.push_back(sd);
//open表是否为空
	while (!m_openList.empty())
	{
        //从开放列表中找一个最小的,将其添加到封闭列表
		popBestStep(&sd);
		m_closeList.push_back(sd);

		ASCOORD coord;
		//遍历当前节点的周围节点，并且进行G值的判断
		for(int i = 0 ; i<m_numSurround ; ++i)
		{
			coord  = sd._coord;
			coord += m_surround[i];
			
			if(judgeSurround(coord,sd._coord,sd._g+m_gAdd[i]))
				return true;
		}
	}
	return false;
}

bool AStar::judgeSurround(const ASCOORD& coord,const ASCOORD& parentCoord,int G)
{
    //该节点 在地图内 && 该节点 不在 封闭列表中 && 该节点不是 障碍物
	if(coord._x>=0 && coord._x<m_col && coord._y>=0 && coord._y<m_row && !isInList(m_closeList,coord) && !IsObstacle(coord))
	{
		StepData* pSD = findFromList(m_openList,coord); //查找 该节点是否在开放列表中
        //开放列表存在并且值比大，不存在则加入开放列表同时设置父节点,比他大，说明经过此节点到达更优
		if (pSD && pSD->_g > G) //如果在 && 原来的G  >  新的G
		{
			pSD->_g = G;
			pSD->_parentCoord = parentCoord;
		}
		else if(!pSD) //如果 该节点不在 开放列表中
		{
			StepData newSD(coord);
			newSD._g = G;
			newSD._h = computeH(coord);
			newSD._parentCoord = parentCoord;

			m_openList.push_back(newSD);

			if(newSD._coord == m_start)
				return true;
		}
	}

	return false;
}

bool AStar::popBestStep(StepData* pSD)
{
	std::list<StepData>::iterator       i   = m_openList.begin();
	std::list<StepData>::const_iterator end = m_openList.end();

	if(i!=end)
	{
		pSD->_g       = i->_g;
		pSD->_h       = i->_h;
		pSD->_coord   = i->_coord;
		pSD->_parentCoord = i->_parentCoord;

		i++;
//从开放列表，找一个最小的
		while(i!=end)
		{
			if(pSD->_g+pSD->_h > i->_g+i->_h)
			{
				pSD->_g       = i->_g;
				pSD->_h       = i->_h;
				pSD->_coord   = i->_coord;
				pSD->_parentCoord = i->_parentCoord;
			}

			i++;
		}

        //从开放列表中删除刚才找到的
		i = m_openList.begin();
		while(i->_coord != pSD->_coord)
		{
			i++;
		}
        //执行完while之后 i++ 指向 pSD

		m_openList.erase(i); //从开放列表中删除 F值最小的
		return true;
	}
	return false;
}

bool AStar::isInList(std::list<StepData>& list,const ASCOORD& coord)
{
	std::list<StepData>::iterator       i   = list.begin();
	std::list<StepData>::const_iterator end = list.end();

	while(i!=end)
	{
		if(coord == i->_coord)
			return true;

		i++;
	}
	return false;
}

StepData* AStar::findFromList(std::list<StepData>& list, const ASCOORD& coord)
{
	std::list<StepData>::iterator       i   = list.begin();
	std::list<StepData>::const_iterator end = list.end();

	while(i!=end)
	{
		if(coord == i->_coord)
			return &(*i);

		i++;
	}

	return 0;
}

bool AStar::GetRoute(std::vector<ASCOORD>* list)
{
	list->clear();
    //寻找起点
	StepData* sd = findFromList(m_openList,m_start);
	//int size = m_openList.size();
	if(sd!=NULL)
	{
		list->push_back(sd->_coord);

		sd = findFromList(m_closeList,sd->_parentCoord);
		while(sd->_coord!=m_target)
		{
			list->push_back(sd->_coord);
			sd = findFromList(m_closeList,sd->_parentCoord);
		}
		list->push_back(sd->_coord);
		return true;
	}

	return false;
}

bool AStar::SetMapSize(int row,int col)
{
	if(row<= 0 || col<=0)
		return false;

	m_row = row;
	m_col = col;
    
    return true;
}

void AStar::SetObstacle( ASCOORD& coord)
{
	if(coord._x>=0 && coord._x<m_col && coord._y>=0 && coord._y<m_row)
	{
        obstacle_lists.push_back(coord);
	}
}

void AStar::CancleObstacle( ASCOORD& coord)
{
	if(coord._x>=0 && coord._x<m_col && coord._y>=0 && coord._y<m_row)
	{
        auto itor = std::find(obstacle_lists.begin(), obstacle_lists.end(), coord);
        if (itor != obstacle_lists.end()) {
            obstacle_lists.erase(itor);
        }
	}
}

bool AStar::IsObstacle(const ASCOORD& coord)
{
	if(coord._x>=0 && coord._x<m_col && coord._y>=0 && coord._y<m_row)
	{
        auto itor = std::find(obstacle_lists.begin(), obstacle_lists.end(), coord);
        if (itor != obstacle_lists.end()) {
            return true;
        }
	}
	return false;
}