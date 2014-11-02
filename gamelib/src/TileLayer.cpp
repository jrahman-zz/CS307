#include "TileLayer.h"

TileLayer::TileLayer(unsigned int g_width, unsigned int g_height)
	: m_gridWidth(g_width)
	, m_gridHeight(g_height)
{
	m_tiles = new Tile*[m_gridHeight];
	for (unsigned int i = 0; i < m_gridWidth; i++) {
 		m_tiles[i] = new Tile[m_gridWidth];
	}
}

TileLayer::TileLayer(TileLayer& rhs) 
	: m_gridWidth(rhs.m_gridWidth)
	, m_gridHeight(rhs.m_gridHeight)
	, m_tiles(nullptr)
{
	m_tiles = new Tile*[m_gridHeight];
	for (unsigned int i = 0; i < m_gridHeight; i++) {
		m_tiles[i] = new Tile[m_gridWidth];
	}
	
	for (unsigned int i = 0; i < m_gridHeight; i++) {
		for (unsigned int j = 0; j < m_gridWidth; i++) {
			m_tiles[i][j] = rhs.m_tiles[i][j];
		}
	}
}

TileLayer::TileLayer(TileLayer&& rhs)
	: m_gridWidth(rhs.m_gridWidth)
	, m_gridHeight(rhs.m_gridHeight)
	, m_tiles(rhs.m_tiles)
{
	rhs.m_tiles = nullptr;
	rhs.m_gridWidth = 0;
	rhs.m_gridHeight = 0;	
}

TileLayer::~TileLayer() {
  for (unsigned int i = 0; i < m_gridHeight; i++) {
    delete[] m_tiles[i];
  }
  delete[] m_tiles;
}

shared_ptr<TileLayer> TileLayer::merge(TileLayer& rhs) {
	if (rhs.m_gridWidth != m_gridWidth || rhs.m_gridHeight != m_gridHeight) {
  		throw runtime_error("Dimension mismatch");
	}
	shared_ptr<TileLayer> ptr(new TileLayer(m_gridWidth, m_gridHeight));
	for (unsigned int i = 0; i < m_gridHeight; i++) {
		for (unsigned int j = 0; j < m_gridWidth; j++) {
			switch(m_tiles[i][j].getType()) {
				case TileType::None:
				case TileType::Blank:
					(*ptr)[i][j] = rhs.m_tiles[i][j];
					break;
				default:
					(*ptr)[i][j] = m_tiles[i][j];
			}
		}
	}
	return ptr;
}

unsigned int TileLayer::getHeight() {
	return m_gridHeight;
}

unsigned int TileLayer::getWidth() {
	return m_gridWidth;
}
