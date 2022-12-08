#ifndef PARAMCMDL_H
#define PARAMCMDL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

/**
 * \enum TParamType
 * \brief Constantes pour le type des parametres de la ligne de commande
 */
typedef enum
{
  PTentier, /**< un nombre entier */
  PTreel,   /**< un nombre reel */
  PTchaine  /**< une chaine de caracteres */
} TParamType;

/** constante chaine de caracteres pour l'affichage des types */
extern char *ParamTypeChaine[];

/**
 * \union TParamValue
 * \brief union permettant de  manipuler un entier/reel/chaine
 */
typedef union
{
  int entier;
  float reel;
  const char *chaine;
} TParamValue;

/**
 * \struct TParamDef
 * \brief represente un parametre de la ligne de commande (nom,type,valeur...)
 */
typedef struct
{
  char *nom;          /**< nom du parametre */
  TParamType type;    /**< type (entier,reel,chaine) */
  char lettre;        /**< lettre a utiliser sur la ligne de commande */
  TParamValue valeur; /**< valeur a affecter au parametre */
} TParamDef;


//Prototypes de fonctions
char* ValeurParamToString(TParamDef *_tabParam, const int _index);
void  PrintParam(TParamDef *_tabParam, const int _nbParam);
int  ReadParamFromCommandLine(TParamDef *_tabParam, const int _nbParam, const int _argc, const char *_argv[]);

#endif