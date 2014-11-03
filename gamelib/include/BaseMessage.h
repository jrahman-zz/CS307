#ifndef MESSAGE_H
#define MESSAGE_H

enum class MessageType { MOVE };

class BaseMessage {

public:
    // Force as polymorphic to allow dynamic_cast<>
    virtual ~BaseMessage() {}

    MessageType getType() {
        return m_type;
    }

    unsigned int getTarget() {
        return m_targetID;
    }

protected:  
    BaseMessage(MessageType type, unsigned int targetID)
        : m_type(type)
        , m_targetID(targetID)
    {}

    MessageType m_type;
    unsigned int m_targetID;
};

#endif
