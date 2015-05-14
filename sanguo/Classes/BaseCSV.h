/****************************************************************
	cocos2d x zephyr
*****************************************************************/

#ifndef __BASECSV_H__
#define __BASECSV_H__

#include "cocos2d.h"

class BaseCSV
{
	typedef std::pair<std::string, int>	_PairHead;
	typedef std::map<std::string, int>	_MapHead;
public:
	BaseCSV();
	virtual ~BaseCSV();
public:
	virtual bool init(){ return true ; }
	void load(const char* name);
	
	//! 不主动添加路径的载入
	void _load(const char* name);

	static void setCsvRoot(const char* csvroot);

	void reloadFromMem(const unsigned char* date, long long size);

	virtual void release();

	const char* get(int x, int y) const;

	const char* get(const char* headname, int y) const;
	int get_int(const char* headname, int y) const;
	double get_double(const char* headname, int y) const;
	bool has(const char* headname) const;

	int getWidth() const { return m_iWidth; }

	int getHeight() const { return m_iHeight; }

public:
	char*			m_pBuff;
	char***			m_pArray;
	int				m_iWidth, m_iHeight;	

	_MapHead		m_mapHead;
	std::string		m_filename;
};

#endif  // __BASECSV_H__