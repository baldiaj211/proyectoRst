
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "ObjetoMapa.h"


class Unidad
{

public:

    //CARACTERISTICAS DE LAS UNIDADES
     sf::RectangleShape cuerpo;
     sf::RectangleShape seleccion;
     int vida;
     int equipo;
     bool seleccionado;
     sf::Vector2f destino;
     float velocidad;
     float radio;

    Unidad(float x, float y, int equipoUnidad)
    {

             //CONSTRUCTOR
        cuerpo.setSize(sf::Vector2f(50,50));
        seleccion.setSize(sf::Vector2f(60,60));
        cuerpo.setPosition(x,y);
        seleccion.setPosition(x-5,y-5);
        seleccion.setFillColor(sf::Color::Transparent);
        seleccion.setOutlineColor(sf::Color::Yellow);
        seleccion.setOutlineThickness(3);
        vida = 100;
        equipo = equipoUnidad;
        seleccionado = false;
        destino = sf::Vector2f(x,y);
        velocidad = 0.5f;
        radio = 50.0f;


        if(equipo == 1)
        {
            cuerpo.setFillColor(sf::Color::Blue);
        }
        else
        {
            cuerpo.setFillColor(sf::Color::Red);
        }


    }
            //----------Dice donde ocupa espacio

         sf::FloatRect getBounds()
           {
             return cuerpo.getGlobalBounds();
           }

            //----------Dice donde ocupa espacio


};



int main()
{
       //-----VENTANA-----//
        sf::RenderWindow window(
        sf::VideoMode(800,600),
        "RTS Batalla");

      //------CAMARA------//
         sf::View camara(
         sf::FloatRect(0, 0, 800, 600)
          );

         window.setView(camara);





            std::vector<Unidad> soldados;
            std::vector<Unidad> enemigos;
            std::vector<ObjetoMapa> objetosMapa;

            sf::RectangleShape mapa;

            float anchoMapa = 3000;
            float altoMapa = 3000;

            mapa.setSize(sf::Vector2f(3000,3000));
            mapa.setFillColor(sf::Color(80,180,80));
            mapa.setPosition(0,0);

            bool tieneDestino = false;
            bool seleccionando = false;
            sf::Vector2f inicioSeleccion;
            sf::RectangleShape cajaSeleccion;
            sf::Vector2f finSeleccion;
            cajaSeleccion.setFillColor(sf::Color(0,255,0,50));
            cajaSeleccion.setOutlineColor(sf::Color::Green);
            cajaSeleccion.setOutlineThickness(1);

            soldados.push_back(Unidad(100,100,1));
            soldados.push_back(Unidad(160,100,1));
            soldados.push_back(Unidad(220,100,1));
            soldados.push_back(Unidad(280,100,1));
            soldados.push_back(Unidad(340,100,1));
            enemigos.push_back(Unidad(500,100,2));
            enemigos.push_back(Unidad(560,100,2));
            enemigos.push_back(Unidad(620,100,2));
            enemigos.push_back(Unidad(680,100,2));
            enemigos.push_back(Unidad(740,100,2));
            objetosMapa.push_back(ObjetoMapa(500,400,0));
            objetosMapa.push_back(ObjetoMapa(800,600,1));
            objetosMapa.push_back(ObjetoMapa(1200,900,2));


            sf::Clock reloj;//relog

    while(window.isOpen())
    {
           float deltaTime = reloj.restart().asSeconds();//relog
           sf::Event event;

           while(window.pollEvent(event))

            //---------------------------

            // MOVIMIENTOS DE LA CAMARA WASD
           sf::Vector2f posicionCamara = camara.getCenter();
           float velocidadCamara = 150.0f;


if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
{
    camara.move(-velocidadCamara * deltaTime,0);
}


if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
{
    camara.move(velocidadCamara * deltaTime,0);
}


if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
{
    camara.move(0,-velocidadCamara * deltaTime);
}


if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
{
    camara.move(0,velocidadCamara * deltaTime);
}

              // Movimiento de cámara con mouse

sf::Vector2i posicionMouse =
sf::Mouse::getPosition(window);


int borde = 20;


if(posicionMouse.x < borde)
{
    // borde izquierdo
    camara.move(-velocidadCamara * deltaTime,0);
}


if(posicionMouse.x > 800 - borde)
{
    // borde derecho
    camara.move(velocidadCamara * deltaTime,0);
}


if(posicionMouse.y < borde)
{
    // borde superior
    camara.move(0,-velocidadCamara * deltaTime);
}


if(posicionMouse.y > 600 - borde)
{
    // borde inferior
    camara.move(0,velocidadCamara * deltaTime);
}


              // FIN  MOVIMIENTOS DE LA CAMARA WASD

              //--------LIMITANTE DE LA CAMARA-----//


              sf::Vector2f posicionCamara = camara.getCenter();


                 float mitadAncho = 400;
                 float mitadAlto = 300;


           if(posicionCamara.x < mitadAncho)
              {
                posicionCamara.x = mitadAncho;
              }


           if(posicionCamara.y < mitadAlto)
              {
                posicionCamara.y = mitadAlto;
              }


           if(posicionCamara.x > anchoMapa - mitadAncho)
              {
                posicionCamara.x = anchoMapa - mitadAncho;
              }


           if(posicionCamara.y > altoMapa - mitadAlto)
              {
                posicionCamara.y = altoMapa - mitadAlto;
              }


               camara.setCenter(posicionCamara);




              //--------FIN LIMITANTE DE LA CAMARA-----//

               window.setView(camara);

              //----------------------------
             {

             if(event.type == sf::Event::Closed)
                 {
                   window.close();
                 }
             if(event.type == sf::Event::MouseButtonPressed)
                 {

                   if(event.mouseButton.button == sf::Mouse::Left)
                    {

                      sf::Vector2f mousePos =
                      window.mapPixelToCoords(
                      sf::Mouse::getPosition(window)
                        );

                     for(int i = 0; i < soldados.size(); i++)
                           {
                            soldados[i].seleccionado = false;
                           }
                           inicioSeleccion = mousePos;
                           seleccionando = true;


                     for(int i = 0; i < soldados.size(); i++)
                         {

                          if(soldados[i].cuerpo.getGlobalBounds().contains(mousePos))
                             {

                             if(soldados[i].seleccionado == true)
                               {
                                soldados[i].seleccionado = false;
                               }
                             else
                               {
                                soldados[i].seleccionado = true;
                               }

                             }

                         }

                      }

                 }

            //Movimiento y evita el amontonamiento
          if(event.type == sf::Event::MouseButtonPressed)
             {

               if(event.mouseButton.button == sf::Mouse::Right)
                {

                   sf::Vector2f nuevaPosicion =
                   window.mapPixelToCoords(
                   sf::Mouse::getPosition(window)
                      );
                      int posicionFormacion = 0;
                      int cantidadSeleccionados = 0;

                for(int i = 0; i < soldados.size(); i++)
                 {

                   if(soldados[i].seleccionado)
                     {
                       cantidadSeleccionados++;
                     }

                 }

                 int columnas = sqrt(cantidadSeleccionados);

                   if(columnas < 1)
                     {
                       columnas = 1;
                     }


                for(int i = 0; i < soldados.size(); i++)
                  {

                   if(soldados[i].seleccionado)
                     {

                       int columna = posicionFormacion % columnas;
                       int fila = posicionFormacion / columnas;

                       soldados[i].destino.x =
                       nuevaPosicion.x + (columna - columnas / 2) * 40;


                       soldados[i].destino.y =
                       nuevaPosicion.y + (fila - columnas / 2) * 40;

                       posicionFormacion++;


                    }

                  }

                   tieneDestino = true;

               }

           }



                if(event.type == sf::Event::MouseMoved)
                  {

                     if(seleccionando)
                       {

                         sf::Vector2f mouseActual =
                         window.mapPixelToCoords(
                         sf::Mouse::getPosition(window)
                           );


                         float ancho =
                         mouseActual.x - inicioSeleccion.x;


                         float alto =
                         mouseActual.y - inicioSeleccion.y;


                         cajaSeleccion.setPosition(inicioSeleccion);

                         cajaSeleccion.setSize(
                         sf::Vector2f(ancho, alto)
                           );

                      }

                 }

if(event.type == sf::Event::MouseButtonReleased)
{

    if(event.mouseButton.button == sf::Mouse::Left)
    {

        finSeleccion =
        window.mapPixelToCoords(
            sf::Mouse::getPosition(window)
        );
           for(int i = 0; i < soldados.size(); i++)
                {

                 if(cajaSeleccion.getGlobalBounds()
                  .intersects(soldados[i].cuerpo.getGlobalBounds()))
                    {

                     soldados[i].seleccionado = true;

                    }

                 }


        seleccionando = false;
        cajaSeleccion.setSize(sf::Vector2f(0,0));

    }

}



}
                window.clear();
                window.draw(mapa);
                for(int i = 0; i < objetosMapa.size(); i++)
{
    objetosMapa[i].dibujar(window);
}

                 //DIBUJO DRAW
            for(int i = 0; i < soldados.size(); i++)
              {
            if(soldados[i].seleccionado)
             {
             window.draw(soldados[i].seleccion);
             }
             window.draw(soldados[i].cuerpo);
             }

            for(int i = 0; i < enemigos.size(); i++)
             {
              window.draw(enemigos[i].cuerpo);
             }
            for(int i = 0; i < soldados.size(); i++)
             {

            if(soldados[i].seleccionado && tieneDestino)
               {

                  sf::Vector2f posicion =
                  soldados[i].cuerpo.getPosition();
                  sf::Vector2f direccion =
                  soldados[i].destino - posicion;

                  float distancia =
                  sqrt(
                  direccion.x * direccion.x +
                  direccion.y * direccion.y
                  );

//-------------------------  RADIO     -------------------------------

                 for(int j = 0; j < soldados.size(); j++)
                  {

                    if(i != j)
                      {

                        sf::Vector2f otraPosicion =
                        soldados[j].cuerpo.getPosition();
                        float distanciaEntreUnidades =
                        sqrt(
                        pow(posicion.x - otraPosicion.x, 2) +
                        pow(posicion.y - otraPosicion.y, 2)
                         );


                    if(distanciaEntreUnidades < soldados[i].radio)
                      {

                        sf::Vector2f separacion =
                        posicion - otraPosicion;


                        separacion.x *= 0.02f;
                        separacion.y *= 0.02f;


                        soldados[i].cuerpo.move(separacion);


                        soldados[i].seleccion.setPosition(
                        soldados[i].cuerpo.getPosition().x - 5,
                        soldados[i].cuerpo.getPosition().y - 5
                          );

                     }

                    }

                 }

//-------------------------  FIN RADIO     -------------------------------



//-------------------------  MOVIMIENTO DEL SOLDADO    -------------------------------


                if(distancia > 2)
                    {
                         direccion /= distancia;

                        // Guardamos posición actual
                        sf::Vector2f posicionAnterior =
                        soldados[i].cuerpo.getPosition();

                       // Intentamos mover
                        soldados[i].cuerpo.move(
                        direccion * soldados[i].velocidad
                             );

                    bool chocando = false;

                       // Revisar objetos del mapa
                   for(int j = 0; j < objetosMapa.size(); j++)
                         {
                          if(objetosMapa[j].bloquea)
                             {
                               if(soldados[i].getBounds().intersects(
                               objetosMapa[j].getBounds()))
                                   {
                                     chocando = true;
                                   }
                             }
                         }


                    // Si chocó vuelve atrás
                         if(chocando)
                            {
                             soldados[i].cuerpo.setPosition(
                             posicionAnterior
                                 );
                            }


                            soldados[i].seleccion.setPosition(
                            soldados[i].cuerpo.getPosition().x - 5,
                            soldados[i].cuerpo.getPosition().y - 5
                             );
                    }
                  else
                    {
                      soldados[i].cuerpo.setPosition(
                      soldados[i].destino
                       );

                      soldados[i].seleccion.setPosition(
                      soldados[i].cuerpo.getPosition().x - 5,
                      soldados[i].cuerpo.getPosition().y - 5
                       );
                    }


         //ENTRADA DE MOVIMIENTO DE SOLDADO (MAUSES)

            if(posicion.x < soldados[i].destino.x)
             {
               soldados[i].cuerpo.move(1,0);
               soldados[i].seleccion.move(1,0);
             }

            if(posicion.x > soldados[i].destino.x)
             {
               soldados[i].cuerpo.move(-1,0);
               soldados[i].seleccion.move(-1,0);
             }

           if(posicion.y < soldados[i].destino.y)
             {
               soldados[i].cuerpo.move(0,1);
               soldados[i].seleccion.move(0,1);
             }

           if(posicion.y > soldados[i].destino.y)
             {
               soldados[i].cuerpo.move(0,-1);
               soldados[i].seleccion.move(0,-1);
             }
        //FIN DE MOVIMIENTO DE SOLDADO (MAUSES)
           if(
              abs(posicion.x - soldados[i].destino.x) < 2 &&
              abs(posicion.y - soldados[i].destino.y) < 2
             )
                     {
                       tieneDestino = false;
                     }

               }

          }
                if(seleccionando)
                 {
                   window.draw(cajaSeleccion);
                 }



        window.display();

    }



    return 0;
}
