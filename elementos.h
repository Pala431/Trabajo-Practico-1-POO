#ifndef ELEMENTOS_H
#define ELEMENTOS_H


enum class TipoElem { //elementos para la matriz de daño
    Agua,
    Tierra,
    Fuego
};

class Elemento {
protected:
    int energia;

public:
    Elemento();
    virtual ~Elemento();
    virtual TipoElem Ataque() const = 0;
    virtual TipoElem Defensa() const = 0;
    int getEnergia() const; //para la super ia

    void RecDanio(int cantidad);
    bool AreUAlive() const;
};

//clases hijas (elementos)

class Agua : public Elemento {
public:
    TipoElem Ataque() const override;
    TipoElem Defensa() const override;
};

class Tierra : public Elemento {
public:
    TipoElem Ataque() const override;
    TipoElem Defensa() const override;
};

class Fuego : public Elemento {
public:
    TipoElem Ataque() const override;
    TipoElem Defensa() const override;
};

#endif