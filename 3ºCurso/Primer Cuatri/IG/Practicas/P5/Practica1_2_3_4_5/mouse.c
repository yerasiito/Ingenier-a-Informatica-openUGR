/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Yeray Lopez Ramirez

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informaticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
	modulo mouse.c
	Gestion de eventos de raton

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"

/**	 void clickRaton( int boton, int estado, int x, int y )

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/
bool moviendoCamara;
int xant, yant;
void clickRaton (int boton, int estado, int x, int y)
{
	 if(boton == GLUT_LEFT_BUTTON){ //GLUT_MIDDLE_BUTTON para el raton
		if(estado == GLUT_DOWN){
	 		moviendoCamara = true;
			xant = x;
			yant = y;
		}
	 	else{
	 		moviendoCamara = false;
	 	}
	 }

	 if(boton == GLUT_LEFT_BUTTON){
		if(estado == GLUT_DOWN){
			int i,j;
			i = pick(x,y,&i, &j);
			setSeleccion(i,j);
		}
	 }
}


/**	void RatonMovido( int x, int y )

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/
void RatonMovido (int x, int y)
{
	if(moviendoCamara){
		giroCamara(y-yant, x-xant);
	 	xant = x;
	 	yant = y;
	}
	glutPostRedisplay();
}
