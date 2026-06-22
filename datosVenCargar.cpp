#include "datosVenCargar.h"

const char* TIT_VENTANA_CARGAR  = "Bienvenidos a Eryndor!";
const char* RUTA_FONDO_CARGAR   = "recursos/imag/Cueva/cueva.png";
const char* ERROR_FONDO_CARGAR  = "No se pudo cargar el fondo";

const int xVent_CARGAR = 1280;
const int yVent_CARGAR = 720;

// ── Paneles ───────────────────────────────────────────────────────────────────
//   Panel izquierdo: lista de partidas
const float PANEL_IZQ_X = 40.f;
const float PANEL_IZQ_Y = 100.f;
const float PANEL_IZQ_W = 380.f;
const float PANEL_IZQ_H = 520.f;

//   Panel central: detalle de la partida seleccionada
const float PANEL_CTR_X = 460.f;
const float PANEL_CTR_Y = 100.f;
const float PANEL_CTR_W = 460.f;
const float PANEL_CTR_H = 520.f;

// ── Archivo de partidas ───────────────────────────────────────────────────────
const char* RUTA_PARTIDAS       = "recursos/archivos/partidas.dat";
const int   MAX_PARTIDAS_MOSTRAR = 10;
