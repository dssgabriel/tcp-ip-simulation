#include <cstdint>

enum TypePaquet: uint8_t {
    Hello = 1, DBD, LSR, LSU, LSAck
};

class PaquetOSPF {
protected:
    TypePaquet m_Type;
    uint8_t m_IdRouteur;

public:
    virtual void setEntete(
        const TypePaquet& type,
        const uint8_t& idRouteur
    ) = 0;
    virtual const TypePaquet& getType() const = 0;
    virtual const uint8_t& getIdRouteur() const = 0;
};
