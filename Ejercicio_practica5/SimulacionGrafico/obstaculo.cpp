#include "obstaculo.h"
#include "particula.h"
#include <cmath>
#include <algorithm>

Obstaculo::Obstaculo(double x, double y, double ancho, double alto, double resistencia_inicial)
    : x(x), y(y), ancho(ancho), alto(alto),
    resistencia(resistencia_inicial), resistenciaInicial(resistencia_inicial)
{

}

double Obstaculo::getX() const { return x; }
double Obstaculo::getY() const { return y; }
double Obstaculo::getAncho() const { return ancho; }
double Obstaculo::getAlto() const { return alto; }
double Obstaculo::getResistencia() const { return resistencia; }
double Obstaculo::getResistenciaInicial() const { return resistenciaInicial; }

void Obstaculo::recibirDano(double dano)
{
    this->resistencia -= dano;
    if (this->resistencia < 0) {
        this->resistencia = 0;
    }
}

bool Obstaculo::estaDestruido() const
{
    return resistencia <= 0;
}

bool Obstaculo::verificaColision(const Particula& p) const
{
    double centroX = p.getX();
    double centroY = p.getY();

    double cercanoX = std::max(this->x, std::min(centroX, this->x + this->ancho));
    double cercanoY = std::max(this->y, std::min(centroY, this->y + this->alto));

    double distanciaX = centroX - cercanoX;
    double distanciaY = centroY - cercanoY;

    double distanciaCuadrada = (distanciaX * distanciaX) + (distanciaY * distanciaY);

    return distanciaCuadrada < (p.getRadio() * p.getRadio());
}

int Obstaculo::tipoDeRebote(const Particula& p) const
{
    if (!verificaColision(p)) return 0; // No hay colisión

    double centroObsX = this->x + this->ancho / 2.0;
    double centroObsY = this->y + this->alto / 2.0;

    double dx = p.getX() - centroObsX;
    double dy = p.getY() - centroObsY;

    double anchoCombinado = (this->ancho / 2.0) + p.getRadio();
    double altoCombinado = (this->alto / 2.0) + p.getRadio();

    double overlapX = anchoCombinado - std::abs(dx);
    double overlapY = altoCombinado - std::abs(dy);

    if (overlapX < overlapY) {
        return 1;
    } else {
        return 2;
    }
}
