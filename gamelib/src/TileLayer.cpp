#include "TileLayer.h" 

TileLayer::TileLayer(Json::Value value)
    : m_tiles(nullptr)
    , m_gridWidth(value["width"].asInt())
    , m_gridHeight(value["height"].asInt())
    , m_name(value["name"].asString())
{
    m_tiles = new Tile[m_gridWidth * m_gridHeight];
    if (m_tiles == nullptr) {
        throw runtime_error("Allocation failure");
    }

    // Check data
    auto data = value["data"];
    if (data.size() != m_gridHeight * m_gridWidth) {
        throw invalid_argument("Invalid data array, wrong size");
    }

    for (unsigned int i = 0; i < m_gridHeight; i++) {
        for (unsigned int j = 0; j < m_gridWidth; j++) {
            auto index = i * m_gridWidth + j;
            m_tiles[index] = Tile(data[index].asInt());
        }
    }
}

TileLayer::TileLayer(TileLayer& rhs)  
    : m_tiles(nullptr)
    , m_gridWidth(rhs.m_gridWidth)
    , m_gridHeight(rhs.m_gridHeight)
    , m_name(rhs.m_name)
{
    m_tiles = new Tile[m_gridWidth * m_gridHeight];
    if (m_tiles == nullptr) {
        throw runtime_error("Allocation failure");
    }

    for (unsigned int i = 0; i < m_gridHeight; i++) {
        for (unsigned int j = 0; j < m_gridWidth; j++) {
            auto index = i * m_gridWidth + j;
            m_tiles[index] = rhs.m_tiles[index];
        }
    }
}

TileLayer::TileLayer(TileLayer&& rhs)
    : m_tiles(rhs.m_tiles)
    , m_gridWidth(rhs.m_gridWidth)
    , m_gridHeight(rhs.m_gridHeight)
{
    rhs.m_tiles = nullptr;
    rhs.m_gridWidth = 0;
    rhs.m_gridHeight = 0;
}

TileLayer::~TileLayer() {
    if (m_tiles != nullptr) {
        delete[] m_tiles;
    }
}

shared_ptr<TileLayer> TileLayer::merge(shared_ptr<TileLayer> rhs) {

    // Merge other layer with this one
    // Other layer takes preceedence

    if (rhs->m_gridWidth != m_gridWidth
        || rhs->m_gridHeight != m_gridHeight) {
        throw invalid_argument("Dimension mismatch");
    }
    shared_ptr<TileLayer> ptr(new TileLayer(*this));
    for (unsigned int i = 0; i < m_gridHeight; i++) {
        for (unsigned int j = 0; j < m_gridWidth; j++) {

            auto index = i * m_gridWidth + j;
            switch(rhs->m_tiles[index].getType()) {
                case TileType::None:
                case TileType::Blank:
                    (*ptr)[i][j] = m_tiles[index];
                    break;
                default:
                    (*ptr)[i][j] = rhs->m_tiles[index];
            }
        }
    }
    return ptr;
}

unsigned int TileLayer::getHeight() const {
    return m_gridHeight;
}

unsigned int TileLayer::getWidth() const {
    return m_gridWidth;
}

string TileLayer::getName() const {
    return m_name;
}
