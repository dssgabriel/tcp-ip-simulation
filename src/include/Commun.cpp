#include "Commun.hpp"

/**
 * @brief Permet d'afficher le contenu d'une pile contenant des bitset de 16 bits. 
 * 
 * @param pile La pile que l'on veut afficher.
 * @return void.
 **/
void afficher(std::stack<std::bitset<16>> pile) {
    std::cout << "> debut stack <\n\n";

    if (pile.size() > 2) {
        std::bitset<8> a, b, c, d, e ,f;
        diviser(pile.top(), e, f);
        pile.pop();
        diviser(pile.top(), c, d);
        pile.pop();
        diviser(pile.top(), a, b);
        pile.pop();
        std::cout << "m_DestMac : " << a.to_ulong() << ":" << b.to_ulong() << ":";
        std::cout << c.to_ulong() << ":" << d.to_ulong() << ":" << e.to_ulong();
        std::cout << ":" << f.to_ulong() << std::endl;

        diviser(pile.top(), e, f);
        pile.pop();
        diviser(pile.top(), c, d);
        pile.pop();
        diviser(pile.top(), a, b);
        pile.pop();
        std::cout << "m_SrcMac : " << a.to_ulong() << ":" << b.to_ulong() << ":";
        std::cout << c.to_ulong() << ":" << d.to_ulong() << ":" << e.to_ulong();
        std::cout << ":" << f.to_ulong() << std::endl;

        std::cout << "m_Checksum : ";
        std::cout << pile.top().to_ulong() << std::endl;
        pile.pop();

        diviser(pile.top(), a, b);
        pile.pop(); 
        std::cout << "m_ProtocoleId : " << b.to_ulong() << "\nm_TTL : " << a.to_ulong() << std::endl;

        diviser(pile.top(), c, d);
        pile.pop();
        diviser(pile.top(), a, b);
        pile.pop();
        std::cout << "m_IpDest : " << a.to_ulong() << "." << b.to_ulong() << ".";
        std::cout << c.to_ulong() << "." << d.to_ulong() << std::endl;

        diviser(pile.top(), c, d);
        pile.pop();
        diviser(pile.top(), a, b);
        pile.pop();
        std::cout << "m_IpSrc : " << a.to_ulong() << "." << b.to_ulong() << ".";
        std::cout << c.to_ulong() << "." << d.to_ulong() << std::endl;

        std::bitset<16> a2, b2;
        a2 = pile.top();
        pile.pop();
        b2 = pile.top();
        pile.pop();
        std::cout << "m_Ack2 : " << concat(b2, a2).to_ulong() << std::endl;

        a2 = pile.top();
        pile.pop();
        b2 = pile.top();
        pile.pop();
        std::cout << "m_Seq : " << concat(b2, a2).to_ulong() << std::endl;

        std::cout << "m_Ack1 : ";
        std::cout << pile.top().to_ulong() << std::endl;
        pile.pop();

        std::cout << "m_Syn : ";
        std::cout << pile.top().to_ulong() << std::endl;
        pile.pop();

        std::cout << "m_Checksum : ";
        std::cout << pile.top().to_ulong() << std::endl;
        pile.pop();

        std::cout << "m_Cwnd : ";
        std::cout << pile.top().to_ulong() << std::endl;
        pile.pop();

        std::cout << "m_PortDest : ";
        std::cout << pile.top().to_ulong() << std::endl;
        pile.pop();

        std::cout << "m_PortSrc : ";
        std::cout << pile.top().to_ulong() << std::endl;
        pile.pop();

        std::cout << "Il reste encore " << pile.size() << " element(s)\n"; 
    }
    else {
        std::cout << "ack";
    }

    std::cout << "\n< fin stack >\n";
}

/**
 * @brief Permet d'afficher le contenu d'une file contenant des bitset de 16 bits. 
 * 
 * @param pile La file que l'on veut afficher.
 * @return void.
 **/
void afficher(std::queue<std::stack<std::bitset<16>>> file) {
    std::cout << "debut queue\n";
    while (!file.empty()) {
        afficher(file.front());
        file.pop();
    }
    std::cout << "fin queue\n";
}

/**
 * @brief Permet d'afficher le contenu d'une double file (deque) contenant des bitset de 16 bits. 
 * 
 * @param pile La double file que l'on veut afficher.
 * @return void.
 **/
void afficher(std::deque<std::stack<std::bitset<16>>> doubleFile) {
    std::cout << "debut deque\n";
    while (!doubleFile.empty()) {
        afficher(doubleFile.front());
        doubleFile.pop_front();
    }
    std::cout << "fin deque\n";
}