/****************************************************************
	cocos2d x zephyr
*****************************************************************/

#include "BaseCSV.h"
//#include "cocos2d.h"
USING_NS_CC;

#define _MY_ASSERT_(cond) if((cond) == false){MessageBox((m_filename + "(第" + tostr(y+1) + "行)").c_str(),"csv错了哦，亲。请检查是否有逗号---my");CC_ASSERT(cond);}

std::string tostr(int n)
{
	char szbuf[128];
	sprintf(szbuf,"%d",n);
	return std::string(szbuf);
}

static std::string		g_strCsvRoot;

BaseCSV::BaseCSV() 
	: m_pBuff(NULL)
	, m_pArray(NULL)
	, m_iWidth(0)
	, m_iHeight(0)
{
}

BaseCSV::~BaseCSV() 
{
	release();
}

void BaseCSV::load(const char* name)
{
	m_filename = name;
	//std::string fullPath = g_strCsvRoot + name;
	std::string fullPath = "res/csv/";
	fullPath += name;
	_load(fullPath.c_str());
}

//! 不主动添加路径的载入
void BaseCSV::_load(const char* name)
{
	Data filedata = FileUtils::getInstance()->getDataFromFile(name);
	if(filedata.getSize() > 0 )
	{
		reloadFromMem(filedata.getBytes(), filedata.getSize());
	}else
	{
#if CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM
		MessageBox("不能载入对应csv,请检查文件是否被占用或者不存在",name);
#endif
	}
}

void BaseCSV::setCsvRoot(const char* csvroot)
{
	g_strCsvRoot = csvroot;
}

void BaseCSV::release()
{
	if(m_pBuff != NULL)
	{
		free(m_pBuff);

		m_pBuff = NULL;
	}

	if(m_pArray != NULL)
	{
		free(m_pArray);

		m_pArray = NULL;
	}

	m_mapHead.clear();
}

const char* BaseCSV::get(int x, int y) const
{
	if(x >= 0 && x < m_iWidth && y >= 0 && y < m_iHeight)
	{
		if(m_pArray != NULL)
			return m_pArray[y][x];
	}

	return "";
}

const char* BaseCSV::get(const char* headname, int y) const
{
	_MapHead::const_iterator it = m_mapHead.find(headname);
	if(it != m_mapHead.end())
		return get(it->second, y);

	return "";
}

int BaseCSV::get_int(const char* headname, int y) const
{
	_MapHead::const_iterator it = m_mapHead.find(headname);
	if(it != m_mapHead.end())
		return atoi(get(it->second, y));

	return 0;
}

double BaseCSV::get_double(const char* headname, int y) const
{
	_MapHead::const_iterator it = m_mapHead.find(headname);
	if(it != m_mapHead.end())
		return atof(get(it->second, y));

	return 0.0f;
}

bool BaseCSV::has(const char* headname) const
{
	_MapHead::const_iterator it = m_mapHead.find(headname);

	return it != m_mapHead.end();
}

void BaseCSV::reloadFromMem(const unsigned char* pBuff, long long size)
{
	release();

	{
		m_pBuff = (char*)malloc(size + 1);

		memcpy(m_pBuff, pBuff, size);

		m_pBuff[size] = '\0';

		m_iWidth = 0;
		m_iHeight = 0;

		for(unsigned long i = 0; i < size; ++i)
		{
			if(m_iHeight == 0 && m_pBuff[i] == ',')
				++m_iWidth;
			else if(m_pBuff[i] == '\r' && m_pBuff[i + 1] == '\n')
			{
				++i;
				++m_iHeight;
			}
			else if(m_pBuff[i] == '\n')
				++m_iHeight;

		}

		++m_iWidth;

		m_pArray = (char***)malloc(sizeof(char*) * m_iWidth * m_iHeight + sizeof(char**) * m_iHeight);

		for(int i = 0; i < m_iHeight; ++i)
		{
			m_pArray[i] = (char**)((char*)m_pArray + m_iHeight * sizeof(char**) + m_iWidth * i * sizeof(char*));
		}

		int x = 0;
		int y = 0;
		char* last = m_pBuff;

		bool bTestComma = false;
		int iQuoNum = 0;

		int beg = 0;
		if(0xef == (unsigned char)m_pBuff[0] 
		&& 0xbb == (unsigned char)m_pBuff[1]
		&&0xbf == (unsigned char)m_pBuff[2])
		{
			beg = 3;
		}

		last += beg;

		for(unsigned long i = beg; i < size; ++i)
		{			
			if(m_pBuff[i] == '"')
			{
				iQuoNum++;
				if(2 == iQuoNum)
				{
					bTestComma = false;
					iQuoNum = 0;
					m_pBuff[i] = '\0';
				}
				else
				{
					bTestComma = true;
					last++;
				}
			}
			
			if(m_pBuff[i] == ',' && !bTestComma)
			{
				m_pBuff[i] = '\0';

				_MY_ASSERT_(y < m_iHeight);
				_MY_ASSERT_(x < m_iWidth);
				m_pArray[y][x] = last;

				++x;
				last = m_pBuff + i + 1;
			}	
			else if(m_pBuff[i] == '\r' && m_pBuff[i + 1] == '\n')
			{
				m_pBuff[i] = '\0';
				m_pBuff[i + 1] = '\0';

				_MY_ASSERT_(y < m_iHeight);
				_MY_ASSERT_(x < m_iWidth);
				m_pArray[y][x] = last;

				++i;
				++y;
				x = 0;

				last = m_pBuff + i + 1;
			}
			else if(m_pBuff[i] == '\n')
			{
				m_pBuff[i] = '\0';

				_MY_ASSERT_(y < m_iHeight);
				_MY_ASSERT_(x < m_iWidth);
				m_pArray[y][x] = last;

				++y;
				x = 0;

				last = m_pBuff + i + 1;
			}
		}

		for(int i = 0; i < m_iWidth; ++i)
		{
			_PairHead p(m_pArray[0][i], i);

			m_mapHead.insert(p);
		}			
	}
}