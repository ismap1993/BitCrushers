/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMenu.h
 * Author: chiri
 *
 * Created on 5 de abril de 2016, 19:41
 */

#ifndef EMENU_H
#define EMENU_H

#include "Escena.h"
#include "Juego.h"

class EMenu: public Escena {
public:
    
    void Handle();
    Juego* getContext();
    static EMenu* Instance(Juego* context);
    
protected:
    EMenu(Juego* context);
    EMenu(const EMenu &);
    EMenu &operator = (const EMenu &);

private:
    
    static EMenu* pinstance;
    Juego* _context;
    
};

#endif /* EMENU_H */

